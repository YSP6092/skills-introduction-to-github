#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct playlist
{
    char songName[50];
    char songArtist[50];
    struct playlist* next;
};

struct playlist* createSong(char songName[], char songArtist[])
{
    struct playlist* newSong = (struct playlist*)malloc(sizeof(struct playlist));
    if (!newSong)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(newSong->songName, songName);
    strcpy(newSong->songArtist, songArtist);
    newSong->next = newSong;
    return newSong;
}

void addSong(struct playlist** head, char songName[], char songArtist[])
{
    struct playlist* newSong = createSong(songName, songArtist);
    if (*head == NULL)
    {
        *head = newSong;
    }
    else
    {
        struct playlist* temp = *head;
        while (temp->next != *head)
        {
            temp = temp->next;
        }
        temp->next = newSong;
        newSong->next = *head;
    }
}

void displaySongs(struct playlist* head)
{
    if (head == NULL)
    {
        printf("The list is empty!\n");
        return;
    }

    struct playlist* temp = head;
    do
    {
        printf("Song: %s, Artist: %s\n", temp->songName, temp->songArtist);
        temp = temp->next;
    } while (temp != head);
}

void deleteSong(struct playlist** head, char songName[])
{
    if (*head == NULL)
    {
        printf("The list is empty!\n");
        return;
    }

    struct playlist *temp = *head, *prev = NULL;
    while (temp->next != *head && strcmp(temp->songName, songName) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if (strcmp(temp->songName, songName) == 0)
    {
        if (prev == NULL)
        {
            struct playlist* last = *head;
            while (last->next != *head)
            {
                last = last->next;
            }
            if (*head == (*head)->next)
            {
                free(*head);
                *head = NULL;
            }
    else
    {
                *head = temp->next;
                last->next = *head;
                free(temp);
    }
        }
        else
        {
        prev->next = temp->next;
            free(temp);
        }
    } else {
        printf("Song not found!\n");
    }
}

int countSongs(struct playlist* head)
{
    if (head == NULL) return 0;

    int count = 0;
    struct playlist* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);

    return count;
}

void searchSong(struct playlist* head, char songName[]) {
    if (head == NULL) {
        printf("The list is empty!\n");
        return;
    }

    struct playlist* temp = head;
    do {
        if (strcmp(temp->songName, songName) == 0)
        {
            printf("\nFound Song: %s, Artist: %s\n", temp->songName, temp->songArtist);
            return;
        }
        temp = temp->next;
    } while (temp != head);

    printf("Song not found!\n");
}

int main() {
    struct playlist* songList = NULL;

    addSong(&songList, "Shape of You", "Ed Sheeran");
    addSong(&songList, "The Nights" ,"One direction");
    addSong(&songList, "Sorry", "Justin Bieber");
    addSong(&songList, "Tum hi ho", "Arjit Singh");
    displaySongs(songList);

    searchSong(songList, "Shape of you");

    printf("\n\nNumber of songs: %d\n", countSongs(songList));

    deleteSong(&songList, "Sorry");
    printf("\nAfter deletion:\n");
    displaySongs(songList);
    printf("\nNumber of songs after deletion: %d\n", countSongs(songList));

    return 0;
}
