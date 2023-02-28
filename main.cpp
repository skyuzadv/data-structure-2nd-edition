#include <cstdio>
#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    /*

    char c;
    fseek(stdin, 0, SEEK_SET);		//1> clear stdin buffer
    fflush(stdin);					//2> clear stdin buffer
    rewind(stdin);					//3> clear stdin buffer
    scanf("%*[^\n]%*c");			//4> jump \n

    //	while ((c =getchar()) != '\n' && c != EOF);
    while (1) {
            c = getchar();
            if (c == '\n' || c == EOF) break;
    }
    printf("c=%d\n", c);
    int ch = getchar();
    printf("%d\n", ch);

    */
    bool flag = 1;
    bool a = !flag;
    bool b = ~flag;
    printf("a = %d, b = %d\n", a, b);
    int bits = 1;
    int m = !bits;
    int n = ~bits;
    printf("m = %d, n = %d\n", m, n);
    exit(0);
}
