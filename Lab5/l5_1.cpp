#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

char *readline_(const char *prompt)
{
    printf("%s", prompt);

    char buf[BUFSIZ] = {0};  // временный буфер для строки
    char *res = NULL;        // строка, в которой будет по итогу лежать вся введенная строка
    int len = 0;             // длина этой строки
    int n = 0;               // специальный флаг

    do {
        n = scanf("%8192[^\n]", buf);  // 8192[^\n] - обознает, что считываем 8192 символов не включая \n
        if (n < 0) {                   // scanf дал -1 <=> мы дошли до конца файла
            if (!res) {
                return NULL;
            }
        }
        else if (n > 0) {
            int chunk_len = strlen(buf);  // узнать размер части строки, записанной в буфер
            int str_len = len + chunk_len;
            res = (char *)realloc(res, str_len + 1);  // удлиняем строку: делаем +1 под нуль символ '\0'
            memcpy(res + len, buf, chunk_len);  // копируем char из буфера в итоговую строку
            len = str_len;  // обновляем длину строки
        }
        else {  // поподаем в else только в случае, если n == 0 ТОЛЬКО ЕСЛИ В Потоке остался символ переноса строки '\n'
            scanf("%*c");  // считывает 1 символ char в никуда == просто его выкидывает
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    }
    else {
        res = (char *)calloc(1, sizeof(char));  // возврает 1 нуль символ == пустая строка [s = '\0']
    }

    return res;
}

int *func(char *str)
{
    int *ans = (int *)calloc(4, sizeof(int));

    // длину, количество слов, цифр, пробелы
    // "word1a   word2      word"

    int not_space = 0;
    for (int idx = 0; str[idx] != '\0'; ++idx) {
        ans[0] += 1;

        if (48 <= str[idx] && str[idx] <= 57) {  // нашли цифру
            ans[2] += 1;
            not_space = 1;
        }
        else if (str[idx] == 32) {
            ans[3] += 1;

            if (not_space == 1) {
                ans[1] += 1;
            }
            not_space = 0;
        }
        else {
            not_space = 1;
        }
    }
    if (not_space == 1) {
        ans[1] += 1;
    }

    return ans;
}

int *func2(char *str)
{
    int *ans = (int *)calloc(4, sizeof(int));

    ans[0] = strlen(str);
    for (int idx = 0; str[idx] != '\0'; ++idx) {
        if (isdigit(str[idx])) {
            ans[2] += 1;
        }
        else if (isspace(str[idx])) {
            ans[3] += 1;
        }
    }

    char *cur_str = strtok(str, " \t-");
    while (cur_str != NULL) {
        printf("%s\n", cur_str);
        ans[1] += 1;
        cur_str = strtok(NULL, " \t-");
    }

    return ans;
}

char *intToString(int x)
{
    int integer_len = 0;
    int tmp_x = x;
    while (tmp_x > 0) {
        ++integer_len;
        tmp_x /= 10;
    }

    char *res = (char *)calloc(integer_len + 2, sizeof(char));

    tmp_x = x;
    int idx = integer_len;
    while (idx >= 1) {
        char digit = tmp_x % 10 + '0';
        res[idx] = digit;
        --idx;
    }
    res[0] = ' ';

    return res;
}

char *addString(char *dest, char *src, int *len)
{
    int tmp_len = strlen(src);

    dest = (char *)realloc(dest, *len + tmp_len + 1);
    strcat(dest, src);

    *len = *len + tmp_len;
    dest[*len] = '\0';

    return dest;
}

char *addInfo(char *str, int *m)
{
    int len = strlen(str);
    for (int i = 0; i < 4; ++i) {
        char *tmp_str = intToString(m[i]);

        str = addString(str, tmp_str, &len);

        free(tmp_str);
    }
    return str;
}

char *solve()
{
    char *res = (char *)calloc(1, sizeof(char));
    int res_len = 0;

    char *str_with = (char *)calloc(1, sizeof(char));
    int str_with_len = 0;

    char *str_without = (char *)calloc(1, sizeof(char));
    int str_without_len = 0;

    char *str = readline_("Введите строку: ");
    while (strcmp(str, "and") != 0) {
        int *m = func(str);

        str = addInfo(str, m);
        int len = strlen(str);

        // printf("%s\n", str);

        if (m[2] != 0) {
            str_with = addString(str_with, str, &str_with_len);
        }
        else {
            str_without = addString(str_without, str, &str_without_len);
        }

        free(m);
        free(str);

        str = readline_("Введите строку: ");
    }

    res = (char *)realloc(res, res_len + str_with_len + 2);
    strcat(res, str_with);

    res_len += str_with_len;

    res[res_len] = ' ';
    res[res_len + 1] = '\0';
    res_len++;

    res = addString(res, str_without, &res_len);

    return res;
}

void format_print(char *str, int row, int column)
{
    int idx = 0;
    for (int i = 0; i < row && str[idx]; ++i) {
        for (int j = 0; j < column && str[idx]; ++j) {
            printf("%c", str[idx++]);
        }
        printf("\n");
    }
}

int main()
{
    char *res = solve();

    int column, row;

    printf("Введите длину строки: ");
    scanf("%d", &column);
    printf("Введите количество строк: ");
    scanf("%d", &row);

    format_print(res, row, column);

    return 0;
}