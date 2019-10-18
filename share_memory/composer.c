
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include "song.h"
#include <time.h>

const int CHAR_SIZE = 200;
const char authors[][CHAR_SIZE] = {"Iron maiden","Pink Floyod", "Mamonas Assacinas", "Charlie Brown"};

song_t randomSong(){
	char title[CHAR_SIZE];
	char author[CHAR_SIZE];
	char genre[CHAR_SIZE];
	int duration = 600;

	sprintf(author, "%s",authors[rand()%(sizeof(authors)/CHAR_SIZE)]);

	printf("author random %s\n",author);
	song_t s = {"t",author,"genre", duration};
	return s;
}


int main()
{
	// ftok to generate unique key
	key_t key = ftok("shmfile",65);

	// shmget returns an identifier in shmid
	int shmid = shmget(key,1024,0666|IPC_CREAT);

	// shmat to attach to shared memory
	//char *str = (char*) shmat(shmid,(void*)0,0);

  songs_t *songs  = (songs_t*) shmat(shmid,(void*)0,0);

	//cout<<"Write Data : ";
	//gets(str);

	srand(time(NULL));
  printf("Data written in memory: %d and this other %d\n",rand(),rand());

  song_t a = randomSong();//{"Feara of the dark","Iron maiden","Rock",437};

    printf("Titulo: %d \n",  a.author);
  songs->data[0] = a;

	printf("Data written in memory: %lu\n",(sizeof(authors)/CHAR_SIZE));

	//detach from shared memory
	//shmdt(songs);

	return 0;
}


