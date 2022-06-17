#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/*
Проект: Склад (поставщики)
Создайте структуру supplier со следующими полями:
Тип данных	Назначение поля
int	номер секции
char*	Название фирмы
double	цена
int	количество
Создать массив из n позиций товаров (ввод с клавиатуры)
Реализовать функции :
	добавить товар (товар – это название + цена).
Если товар  уже есть, то добавляем количество, иначе создаем новую позицию ;
	распечатать информацию о товаре в табличном виде;
	найти все товары заданной секции, результат отсортировать по алфавиту, запомнить в массиве и вывести на экран;
определить товары с количеством меньше заданного, результат вывести на экран;
*/

/*
typedef <что объявить> <с каким именем>;
*/

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

void stdinClear()
{
    scanf("%*[^\n]");
    scanf("%*c");
}

int getInt(int *ans)
{
    int flag = 0;
    while ((flag = scanf("%d", ans)) != 1)
    {
        if (flag == -1) {
            *ans = 0;
            return 0;
        }
        printf("Ошибка при считывании. Повторите ввод\n");
        scanf("%*[^\n]");
    }
    stdinClear();
    return 1;
}

int getDouble(double *ans)
{
    int flag = 0;
    while ((flag = scanf("%lf", ans)) != 1)
    {
        if (flag == -1) {
            *ans = 0;
            return 0;
        }
        printf("Ошибка при считывании. Повторите ввод\n");
        scanf("%*[^\n]");
    }
    stdinClear();
    return 1;
}


typedef struct supplier
{
    int sectionNumber;
    char *firmName;
    double price;
    int amount;
} supplier;


typedef struct sequence
{
    supplier *seq;
    int count;
} sequence;

void print_menu(char *menu[], const int N)
{
    printf("Выберите пункт меню\n");
    for (int i = 0; i < N; ++i) {
        printf("%s\n", menu[i]);
    }
    printf("\n");
}

void clearTable(sequence *mas)
{
    for (int i = 0; i < mas->count; ++i) {
        if (mas->seq[i].firmName) {
            free(mas->seq[i].firmName);
        }
    }
    free(mas->seq);
    mas->seq = NULL;
    mas->count = 0;
}

void read_item(supplier *item)
{
    printf("Введите номер секции: ");
    getInt(&(item->sectionNumber));

    item->firmName = readline_("Введите название фирмы: ");

    printf("Введите стоимость: ");
    getDouble(&(item->price));

    printf("Введите количество: ");
    getInt(&(item->amount));
}

void add_goods(sequence *mas)
{
    // (*mas).count  тоже самое, что и mas->count}
    int n = -1;
    printf("Введите количество элементов для добавления: ");
    while (n <= 0) {
        scanf("%d", &n);
        if (n <= 0) {
            printf("Неверное количество товаров\nПовторите ввод\n");
        }

    }

    int cur_idx = mas->count;
    mas->count = mas->count + n;
    mas->seq = (supplier *)realloc(mas->seq, sizeof(supplier) * (mas->count));
    while (n > 0) {
        read_item(&(mas->seq[cur_idx]));

        cur_idx++;
        n--;
    }
}

void print_table(sequence *mas)
{
    printf("Секция                Стоимость               Количество             Общая сумма                   Название\n");
    printf("                          (руб)                     (шт)                   (руб)                      Фирмы\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < mas->count; ++i) {
        printf("%6d", (mas->seq)[i].sectionNumber);
        printf("%24lf", (mas->seq)[i].price);
        printf("%25d", (mas->seq)[i].amount);
        printf("%24lf", (mas->seq)[i].price * (mas->seq)[i].amount);
        printf(" %s\n", (mas->seq)[i].firmName);
    }
    printf("-----------------------------------------------------------------------------------------------------------\n");

}

void add_element(sequence *mas, supplier *item)
{
    mas->count = mas->count + 1;
    mas->seq = (supplier *)realloc(mas->seq, sizeof(supplier) * mas->count);

    mas->seq[mas->count - 1] = *item;
}

sequence *find_less_than(sequence *mas)
{
    sequence *new_seq = (sequence *)calloc(1, sizeof(sequence));

    int n = -1;
    printf("Введите количество: ");
    getInt(&n);

    for (int i = 0; i < mas->count; ++i){
        if ((mas->seq)[i].amount < n) {
            add_element(new_seq, &(mas->seq)[i]);
        }
    }

    return new_seq;
}

int compareFunc(const void *l, const void *r)  // вернуть 1, если нужно поменять
{
    char *name1 = ((supplier *)l)->firmName;
    char *name2 = ((supplier *)r)->firmName;

    return strcmp(name1, name2) > 0;
}

sequence *find_section(sequence *mas)
{
    sequence *new_seq = (sequence *)calloc(1, sizeof(sequence));

    int n = -1;
    printf("Введите номер секции: ");
    getInt(&n);

    for (int i = 0; i < mas->count; ++i){
        if ((mas->seq)[i].sectionNumber == n) {
            add_element(new_seq, &(mas->seq)[i]);
        }
    }
    //printf("%d\n", new_seq->count);
    //print_table(new_seq);
    qsort(new_seq->seq, new_seq->count, sizeof(supplier), compareFunc);
    return new_seq;
}

int main()
{
    setlocale(0, "Russian");
    sequence mas;
    mas.seq = NULL;
    mas.count = 0;

    char *menu[] = {
        "0. Завершить работу",
        "1. Добавить товар",
        "2. Найти товары по секции",
        "3. Найти товары с меньшим количеством",
        "4. Вывести все товары"
    };

    sequence *tmp;
    int d = -1;
    while (d != 0) {
        print_menu(menu, 5);
        scanf("%d", &d);

        switch (d)
        {
        case 0:
            clearTable(&mas);
            break;
        case 1:
            add_goods(&mas);
            break;
        case 2:
            tmp = find_section(&mas);
            print_table(tmp);
            break;
        case 3:
            tmp = find_less_than(&mas);
            print_table(tmp);
            break;
        case 4:
            print_table(&mas);
            break;
        default:
            printf("Неверный пункт меню. Повторите ввод\n");
            break;
        }
    }

    return 0;
}
