#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_LENGTH 10
#define SEARCH_LENGTH 65

char* password;
char characters[65] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','x','y'
        ,'w','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','X','Y','W'
        ,'Z','0','1','2','3','4','5','6','7','8','9','-','_','.'};
char* temp;
char* guess;
int found;
int msec;

char* brute(int current, char* current_guess,int length){
    if(current < length && !found) {
        for (int i = 0; i < 65; i++) {
            strcpy(temp, current_guess);
            temp[current] = characters[i];
            if (strcmp(temp, password) == 0) {
                found = 1;
                strcpy(guess,temp);
            }
            brute(current+1,temp,length);
        }
    }
    return temp;
}

int main() {
    password = calloc(65,sizeof(char));
    guess = calloc(65,sizeof(char));
    temp = calloc(65,sizeof(char));

    found = 0;
    printf("Hello, World!\n");
    printf("Enter the password:");
    scanf("%s",password);
    printf("LET'S BEGIN\n");

    clock_t before = clock();

    for(int i=1;i<=MAX_LENGTH;i++) {
        clock_t before_loop = clock();
        brute(0, guess, i);
        clock_t difference_loop = clock() - before_loop;
        printf("----------------------------------------\n");
        printf("All passwords of length %d tested !\n",1);
        printf("Passwords tested : %d\n", (int)pow(SEARCH_LENGTH,i));
        printf("Execution time : %ld seconds %ld milliseconds %ld microseconds %ld nanoseconds\n"
                ,(difference_loop * 1000 / CLOCKS_PER_SEC)/1000
                ,(difference_loop * 1000 / CLOCKS_PER_SEC)%1000
                ,(difference_loop * 1000000 / CLOCKS_PER_SEC)
                ,(difference_loop * 1000000000 / CLOCKS_PER_SEC));
        printf("----------------------------------------\n\n");
    }

    if(found) printf("Your password is : %s\n",guess);
    else printf("Password not found\n");

    clock_t difference = clock() - before;
    msec = difference * 1000 / CLOCKS_PER_SEC;

    printf("Time taken %d seconds %d milliseconds\n",msec/1000, msec%1000);

    free(password);
    free(guess);

    return 0;
}
