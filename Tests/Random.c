#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printRandoms(int min, int max) {
    
    unsigned int seed = time(0);
    
    int rd_num = rand_r(&seed) % (max - min + 1) + min;
    switch(rd_num)
    {
        case 1:
        printf("Overwatch");
        break;
        case 2:
        printf("LoL");
        break;
        case 3:
        printf("Valorant");
        break;
        case 4:
        printf("Omori");
        break;
        case 5:
        printf("Anime");
        break;
        case 6:
        printf("Movie");
        break;
    }
}

int main() {
    int min = 1, max = 6;
    printRandoms(min, max);
    return 0;
}