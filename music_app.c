#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ONE 1
#define ZERO 0

// A playlist
typedef struct Playlist {
    char *songTitle;
    char *songArtist;
    struct Playlist* next;
    struct Playlist* previous;
} Playlist;


// Helper function for addSong() method, which connects the second last node to the new song.
void setPrevAndNextSongs(struct Playlist* last, struct Playlist* newSong) {
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = newSong;
    newSong->previous = last;
}

/*
 * Adds a song to the end of the playlist.
 * Allocates memory for the new song.
 */
void addSong(struct Playlist** head, char *songTitle, char *songArtist) {
    struct Playlist* newSong = (struct Playlist*) malloc(sizeof(struct Playlist));
    if (newSong == NULL) {
        printf("No memory was allocated.");
        exit(ZERO);
    }
    struct Playlist* last = *head;

    newSong->songTitle = songTitle;
    newSong->songArtist = songArtist;
    newSong->next = NULL;

    if (*head == NULL) {       // If the playlist is empty (this is the first song)
        newSong->previous = NULL;
        *head = newSong;
        return;
    }

    setPrevAndNextSongs(last, newSong);
}


// Displays the current song in the playlist.
void currentSong(struct Playlist* currentSong) {
    printf("\nCurrent Song: \n%s, %s\n", currentSong->songTitle, currentSong->songArtist);
}


/*
 * Searches for a song in the playlist based on the song title.
 * If the song is not found, a message is printed saying the song does not exist.
 */
void searchSong(struct Playlist** song, char *songTitle) {
    struct Playlist* currentSong = *song;

    while (currentSong != NULL) {
        if (strcmp(currentSong->songTitle, songTitle) == ZERO) {
            printf("\nSearched Song: \n%s, %s\n", currentSong->songTitle, currentSong->songArtist);
            return;
        }
        currentSong = currentSong->next;
    }

    printf("\nSearched Song: \n%s, Does not exist\n", songTitle);
}


// Displays all songs in the playlist in the opposite order.
void displayReversePlaylist(struct Playlist* head) {
    // Struct stores the last song in the playlist
    struct Playlist* lastSong = NULL;

    // Go to the last song
    while (head != NULL) {
        lastSong = head;
        head = head->next;
    }

    printf("\nPlaylist in Reverse:\n");
    while (lastSong != NULL) {
        printf("%s, %s\n", lastSong->songTitle, lastSong->songArtist);
        lastSong = lastSong->previous;
    }
}


// Displays all songs in the playlist.
void displayPlaylist(struct Playlist* head) {
    printf("\nPlaylist:\n");
    while (head != NULL) {
        printf("%s, %s\n", head->songTitle, head->songArtist);
        head = head->next;
    }
}


// Displays the next song in the playlist.
void nextSong(struct Playlist* currentSong) {
    if (currentSong->next != NULL) {
        struct Playlist* nextSong = currentSong->next;
        printf("\nNext Song: \n%s, %s\n", nextSong->songTitle, nextSong->songArtist);
    } else {
        printf("\nNext Song: \nEnd of Playlist\n");
    }
}


// Displays the previous song in the playlist.
void previousSong(struct Playlist* currentSong) {
    if (currentSong->previous != NULL) {
        struct Playlist* previousSong = currentSong->previous;
        printf("\nPrevious Song: \n%s, %s\n", previousSong->songTitle, previousSong->songArtist);
    } else {
        printf("\nPrevious Song: \nEnd of Playlist\n");
    }
}


/*
 * Helper method to remove a song from the playlist.
 * Sets the new values of the previous and next songs.
 */
void removeSongFromList(struct Playlist** currentSong) {
    struct Playlist *previousSong = (*currentSong)->previous;
    struct Playlist *nextSong = (*currentSong)->next;

    if (previousSong != NULL) {
        previousSong->next = nextSong;
    }

    if (nextSong != NULL) {
        nextSong->previous = previousSong;
    }

    printf("\nSong Deleted: \n%s, %s\n", (*currentSong)->songTitle, (*currentSong)->songArtist);
}

/*
 * Helper method to remove a song from the playlist.
 * Sets the new value of the next song is the song being deleted is the first song in the playlist.
 */
void removeFirstSongFromList(struct Playlist** currentSong) {
    struct Playlist *nextSong = (*currentSong)->next;
    nextSong->previous = NULL;

    printf("\nSong Deleted: \n%s, %s\n", (*currentSong)->songTitle, (*currentSong)->songArtist);
}

/*
 * Checks if the song title parameter matches a song in the playlist and calls the method to delete it.
 * Returns 1 of the song was found, or 0 if it wasn't found.
 */
int checkSongToDelete(struct Playlist** head, struct Playlist* currentSong, char *songTitle) {
    if (strcmp(currentSong->songTitle, songTitle) == ZERO) {   // If playlist has 1 song
        removeFirstSongFromList(&currentSong);
        free(currentSong);
        *head = (*head)->next;
        return ONE;
    }

    while (currentSong != NULL) {   // Check each song in the playlist
        if (strcmp(currentSong->songTitle, songTitle) == ZERO) {
            removeSongFromList(&currentSong);
            free(currentSong);
            return ONE;
        }
        currentSong = currentSong->next;
    }
    return ZERO;
}

/*
 * Deletes a song from the playlist.
 * The parameter currentSong refers to the head (first element of the playlist).
 * If the song isn't found or the playlist is empty, nothing is deleted.
 */
void deleteSong(struct Playlist** head, char *songTitle) {
    struct Playlist* currentSong = *head;
    if (currentSong == NULL) {     // If playlist is empty
        printf("\nThe song: '%s' cannot be deleted because the playlist is empty.\n", songTitle);
        return;
    }

    // Calls the method the search for the song in the playlist and delete it if it's found
    int checkSong = checkSongToDelete(head, currentSong, songTitle);
    if (checkSong == ONE) {
        return;
    }

    printf("\nThe song: '%s' cannot be deleted because it does not exist.\n", songTitle);
}



int main() {
    Playlist * album = NULL;
    addSong (&album, "Memories","Maroon 5");
    addSong (&album, "With or Without You", "U2");
    addSong (&album, "Nothing Else Matters", "Metallica");
    addSong (&album, "Maki Madni","The Derek Trucks Band");
    addSong (&album, "Summer of 69", "Bryan Adams");
    addSong (&album, "Another Brick in the Wall", "Pink Floyd");
    displayReversePlaylist(album);
    displayPlaylist(album);

    currentSong(album);
    nextSong(album);
    previousSong(album);
    searchSong(&album, "Ideal 30 days");
    searchSong(&album, "Maki Madni");
    deleteSong(&album, "Memories");

    free(album);

    return 0;
}
