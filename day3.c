#include <stdio.h>
#include <string.h>

char findMatch(char* line) {
    long highs1 = 0L;
    long highs2 = 0L;
    long compsize = strlen(line) / 2;
    for (int i = 0; i < compsize; i++) {
        printf("[%c %c]",line[i],line[compsize+i]);
        if (line[i] < 'a') {
            highs1 = highs1 | (1 << (line[i] - 'A'));
        } else {
            highs1 = highs1 | (1 << (line[i] - 'a' + 30));
        }
        if ((highs1 & highs2) != 0) {
            return line[i];
        }
        if (line[compsize+i] < 'a') {
            highs2 = highs2 | (1 << (line[compsize+i] - 'A'));
        } else {
            highs2 = highs2 | (1 << (line[compsize+i] - 'a' + 30));
        }
        if ((highs1 & highs2) != 0) {
            return line[compsize+i];
        }
    }
}

int value (char c) {
    if (c < 'a') {
        return c - 'A' + 27;
    } else {
        return c - 'a' + 1;
    }
}

int main() {
    FILE* input = fopen("/tmp/aoc/input.t","r");
    char line[100];
    int sum = 0;
    while (fscanf(input,"%s\n", line) != EOF) {
        char c = findMatch(line);
        sum += value(c);
        printf(" -> %d %s -> %c\n",strlen(line), line,c);
    }
    printf("sum: %d\n",sum);
}