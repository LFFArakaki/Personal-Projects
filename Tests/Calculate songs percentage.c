#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHARACTERS 100

struct artists {
		char name[CHARACTERS];
		float totalSongs;
		float likedSongs;
		float percentageLiked;
	};

void order(int numberOfArtists, struct artists* artist, int type);
void displayArtists(int numberOfArtists, struct artists* artist);
void changeOrder(struct artists* artist, int i);
void sortingOptions(int numberOfArtists, struct artists* artist);

int main()
{
	int numberOfArtists, ch, loop;

	printf("Number of Artists: ");
	scanf("%i",&numberOfArtists);
	while((ch = getchar()) != '\n' && ch != EOF);

	struct artists artist[numberOfArtists];

	for(int i=0; i<numberOfArtists; i++)
	{
		printf("\nName of Artist %i: ",i+1);
		fgets(artist[i].name, 100, stdin);
		artist[i].name[strcspn(artist[i].name, "\n")] = '\0';
		printf("\nHow many songs %s has: ",artist[i].name);
		scanf("%f",&artist[i].totalSongs);
		printf("\nHow many %s songs you like: ",artist[i].name);
		scanf("%f",&artist[i].likedSongs);
		while((ch = getchar()) != '\n' && ch != EOF);
        
		artist[i].percentageLiked = artist[i].likedSongs/artist[i].totalSongs;
	}
	
	while(loop==0)
	{
        displayArtists (numberOfArtists, artist);
        sortingOptions(numberOfArtists, artist); 
	}
    
	
	return 0;
}

void order(int numberOfArtists, struct artists* artist, int type)
{
	int changes;
	changes = 1;

	while(changes == 1)
	{
		changes = 0;
		
		for(int i = 0; i<numberOfArtists; i++)
		{
            switch(type)
            {
                case 1:
                if(artist[i].likedSongs < artist[i+1].likedSongs)
                {
                    changeOrder(artist, i);
                    changes = 1;
                }
                break;
                case 2:
                if(artist[i].likedSongs > artist[i+1].likedSongs)
                {
                    changeOrder(artist, i);
                    changes = 1;
                }
                break;
                case 3:
                if(artist[i].totalSongs < artist[i+1].totalSongs)
                {
                    changeOrder(artist, i);
                    changes = 1;
                }
                break;
                case 4:
                if(artist[i].totalSongs > artist[i+1].totalSongs)
                {
                    changeOrder(artist, i);
                    changes = 1;
                }
                break;
                case 5:
                if(artist[i].percentageLiked < artist[i+1].percentageLiked)
                {
                    changeOrder(artist, i);
                    changes = 1;
                }
                break;
                case 6:
                if(artist[i].percentageLiked > artist[i+1].percentageLiked)
                {
                    changeOrder(artist, i);
                    changes = 1;
                }
                break;
            }
		}
	}
	return;
}

void changeOrder(struct artists* artist, int i)
{
	float tempFloat;
	char tempString[CHARACTERS];

	strcpy(tempString, artist[i].name);
	strcpy(artist[i].name, artist[i+1].name);
	strcpy(artist[i+1].name, tempString);

	tempFloat = artist[i].percentageLiked;
	artist[i].percentageLiked = artist[i+1].percentageLiked;
	artist[i+1].percentageLiked = tempFloat;

	tempFloat = artist[i].totalSongs;
	artist[i].totalSongs = artist[i+1].totalSongs;
	artist[i+1].totalSongs = tempFloat;

	tempFloat = artist[i].likedSongs;
	artist[i].likedSongs = artist[i+1].likedSongs;
	artist[i+1].likedSongs = tempFloat;

	return;
}

void displayArtists(int numberOfArtists, struct artists* artist)
{
    printf("\n---------------------------------------------------------------\n");
    printf("|                       RANKING ARTISTS                       |\n");
    printf("---------------------------------------------------------------\n");
    printf("|       ARTIST       |TOTAL SONGS|LIKED SONGS|%% OF SONGS LIKED|\n");
    for(int i=0;i<numberOfArtists;i++)
    {
        printf("---------------------------------------------------------------\n");   
        printf("|%-20s|%-11.0f|%-11.0f|%16.2f%%|\n",artist[i].name, artist[i].totalSongs, artist[i].likedSongs, artist[i].percentageLiked*100);
    }
    printf("---------------------------------------------------------------\n"); 
}

void sortingOptions(int numberOfArtists, struct artists* artist)
{
    int type;
    
    printf("\nWhat would you like to do?\n");
    printf("1 - Sort by most songs liked\n");
    printf("2 - Sort by least songs liked\n");
    printf("3 - Sort by most songs\n");
    printf("4 - Sort by least songs\n");
    printf("5 - Sort by highest liked percentage\n");
    printf("6 - Sort by lowest liked percentage\n");
    printf("7 - End Program\n");
    scanf("%i",&type);
    if(type<1 || type>7)
    {
        printf("Invalid answer!\n");
        sortingOptions(numberOfArtists, artist);
    }
    
    if(type==7)
    {
        printf("Thanks for using the program!");
        fflush(stdin);
        exit(0);
    }
    else
    {
        order(numberOfArtists, artist, type);
    }
}