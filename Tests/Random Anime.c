#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printRandoms(int min, int max) {
    
    char anime[100][100] = 
    {
    "Monogatari", "Violet Evergarden", "Your Lie in April", "Romantic Killer", "Elusive Samurai",
    "Frieren", "Made in Abyss", "Girls Band Cry", "Jellyfish Can't Swim at Night", "Call of the Night",
    "Durarara", "March Comes in Like a Lion", "Tatami Galaxy", "Ningen Fushin", "Dungeon Meshi",
    "Gurren Lagann", "Jigokuraku", "Paripi Koumei", "Heike Monogatari", "Dolls Frontline", "Kaiba",
    "Re:Zero", "Sakurada Reset", "Ryuu no Haisha", "Noein", "The Ideon", "Princess Principal",
    "Bocchi the Rock", "Make Heroine ga Oosugiru", "True Tears", "Clockwork Planet", "91 Days",
    "Kurayukaba", "Magic-Kyun!", "Engaged to the Unidentified", "Noragami", "Golden Kamuy",
    "Yuri Kuma Arashi", "Cider no You ni Kotoba ga Wakiagaru", "Amanchu", "Blue Exorcist",
    "Apothecary Diaries", "Idaten", "Ozmafia", "Afterlost", "Beatless", "ACCA 13-ku", "Hakubo",
    "Executioner and her Way of Life", "Summer Storm", "Black Clover", "Infinite Dendogram",
    "Soul Buster", "Gatchaman Crowds", "Nichijou", "Say 'I Love You'", "Cluster Edge", "Rampo Kitan",
    "Scorching Ping Pong Girls", "Occultic;Nine", "Chaos;Child", "Oooku", "Insomniacs After School",
    "And Yet the Town Moves", "Nazotokine", "To the Abandoned Sacred Beasts", "Wind Breaker",
    "Chou Yuu Sekai", "Roujin Z", "Mushishi", "Samurai Champloo", "Yubisaki to Renren", "Yi Ren Zhi Xia",
    "Ikebukuro West Gate Park", "Nobunaga the Fool", "Tamayomi", "RWBY", "Unnamed Memory", "Baki", "Senjuushi"
    };
    unsigned int seed = time(0);
    
    int rd_num = rand_r(&seed) % (max - min + 1) + min;
    printf("%s", anime[rd_num]);
}

int main() {
    int min = 0, max = 79;
    printRandoms(min, max);
    return 0;
}