
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include "song.h"
#include <time.h>
#include <string.h>
#include <unistd.h>

const int CHAR_SIZE = 200;
char authors[][200] = {"Iron maiden","Pink Floyod", "Mamonas Assassinas", "Charlie Brown"};
char titles[][200] = {"Fear of the dark","In the end", "Pelados em Santos", "Zóio de lula", "Gimme o anel"};
char genres[][200] = {"Rock","Samba", "Funk", "Pagode", "Foró", "Sertanejo universitário", "Gospel"};

song_t randomSong(){ 
	int duration = (int) rand()%(sizeof(authors)/CHAR_SIZE);

	song_t s;

 	strcpy(s.title,titles[rand()%(sizeof(titles)/CHAR_SIZE)]);
	s.duration= duration;
	strcpy(s.genre,genres[rand()%(sizeof(genres)/CHAR_SIZE)]);
	strcpy(s.author,authors[rand()%(sizeof(authors)/CHAR_SIZE)]); 
	return s;
}


int main()
{
	// ftok to generate unique key
	key_t key = ftok("shmfile",65);

	// shmget returns an identifier in shmid
	int shmid = shmget(key,1024,0666|IPC_CREAT);

	// shmat to attach to shared memory
	 
  	songs_t *songs  = (songs_t*) shmat(shmid,(void*)0,0);

	//cout<<"Write Data : ";
	//gets(str);

	srand(time(NULL));
  	printf("Data written in memory: %d and this other %d\n",rand(),rand());
	for(;;){
	songs->current_song= ((songs->current_song+1)%4);
  	songs->data[0] = (song_t)randomSong();
  	songs->data[1] = (song_t)randomSong();
  	songs->data[2] = (song_t)randomSong();
  	songs->data[3] = (song_t)randomSong();
	  sleep(1);
	}

	printf("Data written in memory: %lu\n",(sizeof(authors)/CHAR_SIZE));

	//detach from shared memory
	shmdt(songs);

	return 0;
}


