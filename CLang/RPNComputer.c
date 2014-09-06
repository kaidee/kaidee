// Reverse Polish notation，RPN，或逆波兰记法
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100   /* 操作数或运算符的最大长度 */
#define NUMBER '0'  /* 标识找到一个数 */

int getop(char []);
void push(double);
double pop(void);

// 逆波兰计算器
int main(int argc, char const *argv[])
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF){
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero devisor\n");
                break;
            default:
                printf("error: unknown commond %s\n", s);
                break;
        }
    }
    // printf("hello, world\n");
    return 0;
}

#define MAXVAL 100   /* 栈val的最大深度 */

int sp = 0;     // 下一个空闲栈位置
double val[MAXVAL]; // 值栈

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push%g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else{
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
    {
        return c;
    }
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}











