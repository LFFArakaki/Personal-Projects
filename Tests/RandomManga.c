#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printRandoms(int min, int max) {
    
    char manga[100][100] = 
    {
    "Slam Dunk", "Vagabond", "Steel Ball Run", "Berserk", "Climber",
    "Fire Punch", "Goodbye, Eri", "Undead Unluck", "Nana", "Celestia",
    "Gokurakugai", "Summer Hikaru Died", "Touge Oni", "Sengoku Youko",
    "Fable", "Shonen no Abyss", "Gachiakuta", "Kagurabachi", "After God",
    "Call the Name of the Night", "Ichinose Family Secret", "Fool Night",
    "Touge Anki", "Land of the Lustrous", "Just Like Mona Lisa",
    "Usuzumi no Hanate", "Hiraeth: The End of the Journey", "Monster",
    "Saranghaneun Jugeum", "Unknown", "Kindergarten Wars", "Booyakasya"
    };
    unsigned int seed = time(0);
    
    int rd_num = rand_r(&seed) % (max - min + 1) + min;
    printf("%s", manga[rd_num]);
}

int main() {
    int min = 0, max = 31;
    printRandoms(min, max);
    return 0;
}