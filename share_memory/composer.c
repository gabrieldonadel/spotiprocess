
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "song.h"

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
  song_t a ={"Feara of the dark","Iron maiden","Rock",437};
  songs->data[0] = a;

	printf("Data written in memory: %s\n",a.title);

	//detach from shared memory
	shmdt(songs);

	return 0;
}
