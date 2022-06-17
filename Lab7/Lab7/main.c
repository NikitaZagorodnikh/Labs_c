#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct FIO
{
    char *name;
    char *another_name;
    char *lastname;
} FIO;


typedef struct Date {
    int day;
    // char *month;
    int month;
    int year;
} Date;

typedef struct supplier
{
    int sectionNumber;
    char *firmName;
    double price;
    int amount;
    FIO fio;
    Date date;
} supplier;


typedef struct sequence
{
    supplier *seq;
    int count;
} sequence;

char *readline_(const char *prompt)
{
    printf("%s", prompt);

    char buf[BUFSIZ] = {0};  // ��������� ����� ��� ������
    char *res = NULL;        // ������, � ������� ����� �� ����� ������ ��� ��������� ������
    int len = 0;             // ����� ���� ������
    int n = 0;               // ����������� ����

    do {
        n = scanf("%8192[^\n]", buf);  // 8192[^\n] - ��������, ��� ��������� 8192 �������� �� ������� \n
        if (n < 0) {                   // scanf ��� -1 <=> �� ����� �� ����� �����
            if (!res) {
                return NULL;
            }
        }
        else if (n > 0) {
            int chunk_len = strlen(buf);  // ������ ������ ����� ������, ���������� � �����
            int str_len = len + chunk_len;
            res = (char *)realloc(res, str_len + 1);  // �������� ������: ������ +1 ��� ���� ������ '\0'
            memcpy(res + len, buf, chunk_len);  // �������� char �� ������ � �������� ������
            len = str_len;  // ��������� ����� ������
        }
        else {  // �������� � else ������ � ������, ���� n == 0 ������ ���� � ������ ������� ������ �������� ������ '\n'
            scanf("%*c");  // ��������� 1 ������ char � ������ == ������ ��� ����������
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    }
    else {
        res = (char *)calloc(1, sizeof(char));  // �������� 1 ���� ������ == ������ ������ [s = '\0']
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
        printf("������ ��� ����������. ��������� ����\n");
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
        printf("������ ��� ����������. ��������� ����\n");
        scanf("%*[^\n]");
    }
    stdinClear();
    return 1;
}

void print_menu(const char *menu[], const int N)
{
    printf("�������� ����� ����\n");
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
    printf("������� ����� ������: ");
    getInt(&(item->sectionNumber));

    item->firmName = readline_("������� �������� �����: ");

    printf("������� ���������: ");
    getDouble(&(item->price));

    printf("������� ����������: ");
    getInt(&(item->amount));

    item->fio.name = readline_("��� ����������: ");
    item->fio.another_name = readline_("�������� ����������: ");
    item->fio.lastname = readline_("������� ����������: ");

    item->date.day = -1;
    while (!(1 <= item->date.day && item->date.day <= 31)) {
        printf("������� ���� ��������: ");
        getInt(&item->date.day);
    }

    // item->date.month = readline_("����� ��������: ");
    item->date.month = -1;
    while (!(1 <= item->date.month && item->date.month <= 12)) {
        printf("������� ����� ��������: ");
        getInt(&item->date.month);
    }

    printf("��� ��������: ");
    getInt(&item->date.year);
}

void add_goods(sequence *mas)
{
    // (*mas).count  ���� �����, ��� � mas->count}
    int n = -1;
    printf("������� ���������� ��������� ��� ����������: ");
    while (n <= 0) {
        scanf("%d", &n);
        if (n <= 0) {
            printf("�������� ���������� �������\n��������� ����\n");
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
    printf("������                ���������               ����������             ����� ����� �������� ���� �����   ��� ������� �������� ���\n");
    printf("                          (���)                     (��)                   (���)    �����                                      \n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < mas->count; ++i) {
        printf("%6d", (mas->seq)[i].sectionNumber);
        printf("%24lf", (mas->seq)[i].price);
        printf("%25d", (mas->seq)[i].amount);
        printf("%24lf", (mas->seq)[i].price * (mas->seq)[i].amount);
        printf(" %s ", (mas->seq)[i].firmName);
        printf("| %10d", (mas->seq)[i].date.day);
        printf(" %d ", (mas->seq)[i].date.month);
        printf("%4d |", (mas->seq)[i].date.year);
        printf(" %s ", (mas->seq)[i].fio.name);
        printf(" %s ", (mas->seq)[i].fio.another_name);
        printf(" %s\n", (mas->seq)[i].fio.lastname);
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
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
    printf("������� ����������: ");
    getInt(&n);

    for (int i = 0; i < mas->count; ++i){
        if ((mas->seq)[i].amount < n) {
            add_element(new_seq, &(mas->seq)[i]);
        }
    }

    return new_seq;
}

int compareFunc(const void *l, const void *r)  // ������� 1, ���� ����� ��������
{
    char *name1 = ((supplier *)l)->firmName;
    char *name2 = ((supplier *)r)->firmName;

    return strcmp(name1, name2) > 0;
}

sequence *find_section(sequence *mas)
{
    sequence *new_seq = (sequence *)calloc(1, sizeof(sequence));

    int n = -1;
    printf("������� ����� ������: ");
    getInt(&n);

    for (int i = 0; i < mas->count; ++i){
        if ((mas->seq)[i].sectionNumber == n) {
            add_element(new_seq, &(mas->seq)[i]);
        }
    }

    qsort(new_seq->seq, new_seq->count, sizeof(supplier), compareFunc);
    return new_seq;
}

sequence *find_by_date(sequence *mas, int cur_year)
{
    sequence *new_seq = (sequence *)calloc(1, sizeof(sequence));

    for (int i = 0; i < mas->count; ++i) {
        if (mas->seq[i].date.year != cur_year) {

            add_element(new_seq, &(mas->seq)[i]);
        }
    }

    return new_seq;
}

void loadString(char *str, FILE *f)
{
    int len = strlen(str);
    fwrite(&len, sizeof(int), 1, f);
    fwrite(str, sizeof(char), len, f);
}

void saveTable(sequence *mas)
{
    FILE *f = fopen("save.bin", "w");
    fwrite(&mas->count, sizeof(int), 1, f);
    for (int i = 0; i < mas->count; ++i) {
        supplier *cur = &mas->seq[i];
        fwrite(&cur->sectionNumber, sizeof(int), 1, f);
        loadString(cur->firmName, f);
        fwrite(&cur->price, sizeof(double), 1, f);
        fwrite(&cur->amount, sizeof(int), 1, f);
        loadString(cur->fio.name, f);
        loadString(cur->fio.another_name, f);
        loadString(cur->fio.lastname, f);
        fwrite(&cur->date.day, sizeof(int), 1, f);
        // loadString(cur->date.month, f);
        fwrite(&cur->date.month, sizeof(int), 1, f);
        fwrite(&cur->date.year, sizeof(int), 1, f);
    }
}

char *unloadString(FILE *f)
{
    int tmp = 1;
    fread(&tmp, sizeof(int), 1, f);
    char *str = (char *)calloc(tmp, sizeof(char));
    fread(str, sizeof(char), tmp, f);
    return str;
}

int readTable(sequence *mas)
{
    FILE *f = fopen("save.bin", "r");
    if (!f) {
        return 1;
    }

    fread(&mas->count, sizeof(int), 1, f);
    mas->seq = (supplier *)calloc(mas->count, sizeof(supplier));
    for (int i = 0; i < mas->count; ++i) {
        supplier *cur = &mas->seq[i];
        fread(&cur->sectionNumber, sizeof(int), 1, f);
        cur->firmName = unloadString(f);
        fread(&cur->price, sizeof(double), 1, f);
        fread(&cur->amount, sizeof(int), 1, f);
        cur->fio.name = unloadString(f);
        cur->fio.another_name = unloadString(f);
        cur->fio.lastname = unloadString(f);
        fread(&cur->date.day, sizeof(int), 1, f);
        // cur->date.month = unloadString(f);
        fread(&cur->date.month, sizeof(int), 1, f);
        fread(&cur->date.year, sizeof(int), 1, f);
    }

    return 0;
}

int main()
{
    setlocale(0, "");

    sequence mas;
    mas.seq = NULL;
    mas.count = 0;

    int flag = 0;
    printf("��������� ��������� �������? (1/0) ");
    getInt(&flag);

    if (flag) {
        readTable(&mas);
    }

    const char *menu[] = {
        "0. ��������� ������",
        "1. �������� �����",
        "2. ����� ������ �� ������",
        "3. ����� ������ � ������� �����������",
        "4. ������� ��� ������",
        "5. ������� ������ �� ����������� ����"
    };

    sequence *tmp;
    int d = -1;
    while (d != 0) {
        print_menu(menu, 6);
        scanf("%d", &d);

        switch (d)
        {
        case 0:
            saveTable(&mas);
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
        case 5:
            tmp = find_by_date(&mas, 2022);
            print_table(tmp);
            break;
        default:
            printf("�������� ����� ����. ��������� ����\n");
            break;
        }
    }

    return 0;
}
