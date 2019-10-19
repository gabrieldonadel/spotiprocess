#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "song.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

// Compilar com -pthread: ex. gcc compete.c -pthread -o compete

pthread_t tid0, tid1, tid2, tid3;

key_t key;
int msgid;

const int CHAR_SIZE = 200;
char authors[][200] = {"Iron maiden","Pink Floyod", "Mamonas Assassinas", "Charlie Brown","Aerosmith","Guns N' Roses","Metallica","AC/DC","Queen"};
char titles[][200] = {"Fear of the dark","In the end", "Pelados em Santos", "Zoio de lula", "Gimme o anel"};
char genres[][200] = {"Rock","Samba", "Funk", "Pagode", "Foro", "Sertanejo universitario", "Gospel"};



song_t randomSong(){
	int duration = (int) rand()%600;

	song_t s;

  s.mesg_type = 1;
  s.duration= duration;
 	strcpy(s.title,titles[rand()%(sizeof(titles)/CHAR_SIZE)]);
	strcpy(s.genre,genres[rand()%(sizeof(genres)/CHAR_SIZE)]);
	strcpy(s.author,authors[rand()%(sizeof(authors)/CHAR_SIZE)]);
	return s;
}




void * sendRandomSong(void* thread){
	int a = *((int*) thread);
	free(thread);
	for(;;){
	  song_t song = randomSong();
	  float sleep_time = (rand()%500)/100.0;
	  sleep(sleep_time);
	  msgsnd(msgid, &song, sizeof(song), 0);

		printf("Thread %d produziu %s e demorou %f segundos \n", a, song.title,sleep_time);

	}
}

int main()
{



    // ftok to generate unique key
    key = ftok("spotiprocess", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    //song_t song = {1,"Fear of the dark","Iron maiden","Rock",437};
    // msgsnd to send message

	  srand(time(NULL));

    int *thread_0 = malloc(sizeof(*thread_0));
		int *thread_1 = malloc(sizeof(*thread_1));
		int *thread_2 = malloc(sizeof(*thread_2));
		int *thread_3 = malloc(sizeof(*thread_3));
		*thread_0 = 0;
		*thread_1 = 1;
		*thread_2 = 2;
		*thread_3 = 3;

    pthread_create(&tid0, NULL, sendRandomSong, (void*)thread_0) ;
    pthread_create(&tid1, NULL, sendRandomSong, (void*)thread_1) ;
    pthread_create(&tid2, NULL, sendRandomSong, (void*)thread_2) ;
    pthread_create(&tid3, NULL, sendRandomSong, (void*)thread_3) ;

    pthread_join(tid0,NULL);
		pthread_join(tid1,NULL);
		pthread_join(tid2,NULL);
		pthread_join(tid3,NULL);

    return 0;
}
