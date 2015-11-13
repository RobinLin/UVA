#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>

#define true 1
#define false 0

bool fg1 = false;
bool fg2 = false;
bool fg3 = false;

int m = 0;
int n = 0;
int status = 0;
int status2 = 0;
int status3 = 0;
double r[100];
int temp_1[15];


int section1(double data)
{
    if( (data < (0.4*512*512)) && fg1 == false && fg2 == false && fg3 == false) {
        printf("----------rule 1 start----------\r\n");
        fg1 = true;
        status = n;
        return 1;
    } else {
        printf("----------No----------\r\n");
        return 0;
    }
}

int main()
{
    int real_acc[3];
    double a = 0;
    int i = 0;
    int j = 0;
    int temp = 0;
    int counter = 0;

    while(1) {
        scanf("%d%d%d", &real_acc[0],&real_acc[1],&real_acc[2]);
        a = ((real_acc[0]*real_acc[0])+(real_acc[1]*real_acc[1])+(real_acc[2]*real_acc[2]));

        r[n%100] = a;
        n++;

        printf("X:%d, Y:%d, Z:%d, id:%d, status:%d, status2:%d, status3:%d, fg1:%d, fg2:%d, fg3:%d\r\n",real_acc[0], real_acc[1], real_acc[2], n, status, status2, status3, fg1, fg2, fg3);

        section1(a); // 條件一 a < 0.4g

        if(fg3) {    // 條件三:數300次，a = 1g
            temp_1[i] = a;
            i++;
            if(i == 15) {
                m++;
                i = 0;
            }
            if(temp_1[14] == 512*512 && m == 19) {
                printf("..........Alarm..........\r\n");
                fg1 = false;
                fg2 = false;
                fg3 = false;
                i = 0;
                m = 0;
            }
            if((n-(status3+15)) == 0) {
                printf("----------END----------\r\n");
                fg1 = false;
                fg2 = false;
                fg3 = false;
                i = 0;
                m = 0;
            }
        }

        if(fg2) {    // 條件三:數15次，a = 1g
            temp_1[i] = a;
            i++;
            if(temp_1[14] == 512*512) {
                printf("..........success -> go to rule4..........\r\n");
                //fg1 = false;
                fg2 = false;
                fg3 = true;
                status3 = n;
                i = 0;
            }
            if((n-(status2+15)) == 0) {
                printf("----------fail -> go to rule4----------\r\n");
                //fg1 = false;
                fg2 = false;
                fg3 = true;
                status3 = n;
                i = 0;
            }
        }

        if(fg1) {   // 條件二:15次內任一 a > 3g
            temp_1[i] = a;
            i++;
            for(j = 0; j < 15; j++) {
                if(temp_1[j] > (3*512*512)) {
                    fg2 = true;
                    status2 = n;
                    printf(".........rule3 start..........\r\n");
                    i = 0;
                    fg1 = false;
                }
            }
            if((n-(status+15))==0) {
                printf("----------rule2 END----------\r\n");
                fg1 = false;
                fg2 = false;
                i = 0;
            }
        }
    }
    return 0;
}
