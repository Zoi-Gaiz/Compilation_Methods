// scan.cpp : Defines the entry point for the console application.
#include "string.h"
#include "math.h"

#include <iostream>

char keywords[30][12] = {"program", "begin", "end", "var", "while", "do", "repeat",
                         "until", "for", "to", "if", "then", "else", ";", ":", "(", ")", ",",
                         ":=", "+", "-", "*", "/", ">", ">=", "==", "<", "<="};
int num_key = 28;
int aut[11][8] = {0, 0, 0, 0, 0, 0, 0, 0,
                  0, 2, 0, 0, 0, 8, 9, 15,
                  0, 2, 3, 5, 11, 0, 0, 11,
                  0, 4, 0, 0, 0, 0, 0, 0,
                  0, 4, 0, 5, 11, 0, 0, 11,
                  0, 7, 0, 0, 6, 0, 0, 0,
                  0, 7, 0, 0, 0, 0, 0, 0,
                  0, 7, 0, 0, 11, 0, 0, 11,
                  0, 8, 0, 0, 0, 8, 0, 12,
                  0, 0, 0, 0, 0, 0, 10, 14,
                  0, 0, 0, 0, 0, 0, 0, 13};
char ID[50][12];
int C[20];
int num_ID = 0, num_C = 0;

struct token {
    int code;
    int value;
};                                    //Token�ṹ
struct token tok[100];                    //Token����
int i_token = 0, num_token = 0;              //Token��������Token����
char strTOKEN[15];                    //��ǰ����
int i_str;                              //��ǰ����ָ��
int n, p, m, e, t;                           //β��ֵ��ָ��ֵ��С��λ����ָ�����ţ�����
double num;                           //����ֵ
char w[50];                            //Դ���򻺳���
int i;                                  //Դ���򻺳���ָ��,��ǰ�ַ�Ϊw[i]

struct map                             //��ǰ�ַ���״̬ת�������б�ǵ�ӳ��
{
    char str[50];
    int col;
};
struct map col1[4] = {{"0123456789", 1},
                      {".",          2},
                      {"Ee",         3},
                      {"+-",         4}};    //����
struct map col2[2] = {{"abcdefghijklmnopqrstuvwxyz", 5},
                      {"0123456789",                 1}}; //�ؼ��ֻ��ʶ��
struct map col3[1] = {{";:(),+-*/=><", 6}};                    //���
struct map *ptr;
int num_map;

void act(int s);

int find(int s, char ch);

int InsertConst(double num);

int Reserve(char *str);

int InsertID(char *str);

int main(int argc, char *argv[]) {
    FILE *fp;
    int s;                                //��ǰ״̬
    fp = fopen("exa.txt", "r");
    while (!feof(fp)) {
        fgets(w, 50, fp);
        i = 0;
        do {
            while (w[i] == ' ')                       //�˿ո�
                i++;

            if (w[i] >= 'a' && w[i] <= 'z')                     //�ж��������
            {
                ptr = col2;
                num_map = 2;
            } else if (w[i] >= '0' && w[i] <= '9') {
                ptr = col1;
                num_map = 4;
            } else if (strchr(col3[0].str, w[i]) == NULL) {
                printf("�Ƿ��ַ�%c\n", w[i]);
                i++;
                continue;
            } else {
                ptr = col3;
                num_map = 1;
            }

            i--;
            s = 1;                                   //��ʼ����һ������
            while (s != 0) {
                act(s);
                if (s >= 11 && s <= 14)
                    break;
                i++;                                  //getchar()
                s = find(s, w[i]);
            }
            if (s == 0) {
                strTOKEN[i_str] = '\0';
                printf("�ʷ�����%s\n", strTOKEN);
                break;
            }

        } while (w[i] != 10);
    }

    printf("�ؼ��ֱ�");                        //������
    for (i = 0; i < 30; i++)
        printf("%s ", keywords[i]);
    printf("\n");
    printf("Token���У�");
    for (i = 0; i < num_token; i++)
        printf("(%d,%d)", tok[i].code, tok[i].value);
    printf("\n");
    printf("���ű�");
    for (i = 0; i < num_ID; i++)
        printf("%s ", ID[i]);
    printf("\n");
    printf("������");
    for (i = 0; i < num_C; i++)
        printf("%d ", C[i]);
    printf("\n");

    fclose(fp);
    printf("Hello World!\n");
    return 0;
}

void act(int s) {
    int code;
    switch (s) {
        case 1:
            n = 0;
            m = 0;
            p = 0;
            t = 0;
            e = 1;
            num = 0;
            i_str = 0;
            strTOKEN[i_str] = '\0';                   //����������ʼ��
            break;
        case 2:
            n = 10 * n + w[i] - 48;
            break;
        case 3:
            t = 1;
            break;
        case 4:
            n = 10 * n + w[i] - 48;
            m++;
            break;
        case 5:
            t = 1;
            break;
        case 6:
            if (w[i] == '-') e = -1;
            break;
        case 7:
            p = 10 * p + w[i] - 48;
            break;
        case 8:
            strTOKEN[i_str++] = w[i];  //��ch�еķ���ƴ�ӵ�strTOKEN��β����
            break;
        case 9:
            strTOKEN[i_str++] = w[i];  //��ch�еķ���ƴ�ӵ�strTOKEN��β����
            break;
        case 10:
            strTOKEN[i_str++] = w[i]; //��ch�еķ���ƴ�ӵ�strTOKEN��β����
            break;
        case 11:
            num = n * pow(10, e * p - m);           //���㳣��ֵ
            tok[i_token].code = 2;
            tok[i_token++].value = InsertConst(num);  //���ɳ���Token
            num_token++;
            break;
        case 12:
            strTOKEN[i_str] = '\0';
            code = Reserve(strTOKEN);                   //��ؼ��ֱ�
            if (code) {
                tok[i_token].code = code;
                tok[i_token++].value = 0;
            }   //���ɹؼ���Token
            else {
                tok[i_token].code = 1;
                tok[i_token++].value = InsertID(strTOKEN);
            }    //���ɱ�ʶ��Token
            num_token++;
            break;
        case 13:
            strTOKEN[i_str] = '\0';
            code = Reserve(strTOKEN);                    //������
            if (code) {
                tok[i_token].code = code;
                tok[i_token++].value = 0;
            }   //���ɽ��Token
            else {
                strTOKEN[strlen(strTOKEN) - 1] = '\0';           //�����
                i--;
                code = Reserve(strTOKEN);                 //������
                tok[i_token].code = code;
                tok[i_token++].value = 0;  //���ɽ��Token
            }
            num_token++;
            break;
        case 14:
            strTOKEN[i_str] = '\0';
            code = Reserve(strTOKEN);                   //������
            tok[i_token].code = code;
            tok[i_token++].value = 0;    //���ɽ��Token
            num_token++;
            break;
    }
}

int find(int s, char ch) {
    int i, col = 7;
    struct map *p;
    p = ptr;
    for (i = 0; i < num_map; i++)
        if (strchr((p + i)->str, ch)) {
            col = (p + i)->col;
            break;
        }
    return aut[s][col];
}

int InsertConst(double num) {
    int i;
    for (i = 0; i < num_C; i++)
        if (num == C[i])
            return i;
    C[i] = num;
    num_C++;
    return i;
}

int Reserve(char *str) {
    int i;
    for (i = 0; i < num_key; i++)
        if (!strcmp(keywords[i], str))
            return (i + 3);
    return 0;
}

int InsertID(char *str) {
    int i;
    for (i = 0; i < num_ID; i++)
        if (!strcmp(ID[i], str))
            return i;
    strcpy(ID[i], str);
    num_ID++;
    return i;
}
