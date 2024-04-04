#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "get_line.h"

bool checkline(char* str, bool flag) {
    // printf("\n%s\n", str);
    u32 i; 
    if (flag) {
        if (memcmp(str, "p edge ", 7)) return false;
        i = 7;
    } else {
        if (memcmp(str, "e ", 2)) return false;        
        i = 2;
    }

    u32 length = 0;

    while (str[length] != '\0' && str[length] != '\n') {
        length++;
    }

    int k = 0;
    while (str[i] != '\0' && str[i]!='\n' && str[i] != EOF) {
        if ((str[i] < '0' || '9' < str[i]) && str[i] != ' ') {
            return false;
        }
        if (str[i] == ' ') k++;
        i++;
    } 

    return k==1;

}

char* get_line() {
    char* str = (char*)malloc(sizeof(char));
    char* temp = NULL;
    if (!str) return str;

    int count = 0, size = 1;

    char ch = fgetc(stdin);
    while (ch != EOF && ch != '\n') {
        
        str[count] = ch;
        count++;
        if (count == size) {
            size *= 2;
            temp = realloc(str, sizeof(char) * size);
            if(temp)
               str = temp;
            if (!str) return str;
        }
        ch = fgetc(stdin);
    }
    str[count] = '\0';

    temp = realloc(str, sizeof(char) * (count+1));
    if(temp)
        str = temp; 
    
    int i = 0;
    while (i < count) {
        if(str[i] == ' ' && (i > 0 && (str[i+1]==' ' || str[i-1]==' '))) {
            for(int j=i; j < count; j++) str[j] = str[j+1];
            count--;
        } else {
            i++;
        }
    }
    if (count > 0 && str[count-1] == ' ') count--;
    str[count] = '\0';

    return str;
}


void get_numbers(char* line, u32 start, u32* n, u32* m) {

    u32 i = start, val = 0;
    while (line[i] != ' ') {
        val = val * 10 + (line[i]-'0');
        i++;
    }

    *n = val;
    i++, val = 0;

    while (line[i] != '\0') {
        val = val * 10 + (line[i]-'0');
        i++;
    }
    *m = val;
}
