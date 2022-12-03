#include <stdio.h>
#include <string.h>

char findMatch(char *line) {
    long highs1 = 0L;
    long highs2 = 0L;
    long compsize = strlen(line) / 2;
    for (int i = 0; i < compsize; i++) {
        if (line[i] < 'a') {
            highs1 = highs1 | (1L << (line[i] - 'A'));
        } else {
            highs1 = highs1 | (1L << (line[i] - 'a' + 30));
        }
        if (highs1 & highs2) {
            return line[i];
        }
        if (line[compsize + i] < 'a') {
            highs2 = highs2 | (1L << (line[compsize + i] - 'A'));
        } else {
            highs2 = highs2 | (1L << (line[compsize + i] - 'a' + 30));
        }
        if (highs1 & highs2) {
            return line[compsize + i];
        }
    }
}

int value(char c) {
    if (c < 'a') {
        return c - 'A' + 27;
    } else {
        return c - 'a' + 1;
    }
}

void part1() {
    FILE *input = fopen("/tmp/aoc/input", "r");
    char line[100];
    int sum = 0;
    while (fscanf(input, "%s\n", line) != EOF) {
        char c = findMatch(line);
        sum += value(c);
    }
    printf("Part 1: %d\n", sum);
}

char findBadge(char *line1, char *line2, char *line3) {
    int l1 = strlen(line1);
    int l2 = strlen(line2);
    int l3 = strlen(line3);
    long bits1 = 0L;
    long bits2 = 0L;
    int i;
    for (i = 0; i < l1; i++) {
        int c = line1[i] < 'a' ? line1[i] - 'A' : line1[i] - 'a' + 30;
        bits1 = bits1 | 1L << c;
    }
    for (i = 0; i < l2; i++) {
        int c = line2[i] < 'a' ? line2[i] - 'A' : line2[i] - 'a' + 30;
        bits2 = bits2 | 1L << c;
    }
    bits1 = bits1 & bits2;
    for (i = 0; i < l3; i++) {
        int c = line3[i] < 'a' ? line3[i] - 'A' : line3[i] - 'a' + 30;
        if (bits1 & (1L << c)) return line3[i];
    }
    fprintf(stderr, "Found no matching character for %s %s %s", line1, line2, line3);
    return 0;
}

void part2() {
    FILE *input = fopen("/tmp/aoc/input", "r");
    char line1[100];
    char line2[100];
    char line3[100];
    int sum = 0;
    while (fscanf(input, "%s\n%s\n%s\n", line1, line2, line3) != EOF) {
        sum += value(findBadge(line1, line2, line3));
    }
    printf("Part 2: %d", sum);
}

int main() {
    part1();
    part2();
}
