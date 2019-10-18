#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "song.h"

int main()
{

	int current_song;
	// ftok to generate unique key
	key_t key = ftok("shmfile",65);

	// shmget returns an identifier in shmid
	int shmid = shmget(key,1024,0666|IPC_CREAT);

	// shmat to attach to shared memory
	//char *str = (char*) shmat(shmid,(void*)0,0);
    songs_t *songs  = (songs_t*) shmat(shmid,(void*)0,0);
	current_song = songs->current_song;

	for(;;){
	printf("Track: %d \n",current_song);
	printf("Titulo: %s \n",songs->data[current_song].title);
	printf("Autor: %s \n", songs->data[current_song].author);
	printf("Gênero: %s \n",songs->data[current_song].genre);
	while(current_song == songs->current_song){

		
	
	}
	current_song = songs->current_song;
	}
	//detach from shared memory
	shmdt(songs);

	// destroy the shared memory
//	shmctl(shmid,IPC_RMID,NULL);

	return 0;
}


// void listenToMusic(songs_t *song, int* current_song){ 
// }