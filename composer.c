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

const int CHAR_SIZE = 200;
char authors[][200] = {"Iron maiden","Pink Floyod", "Mamonas Assassinas", "Charlie Brown","Aerosmith","Guns N' Roses","Metallica","AC/DC","Queen"};
char titles[][200] = {"Fear of the dark","In the end", "Pelados em Santos", "Zóio de lula", "Gimme o anel"};
char genres[][200] = {"Rock","Samba", "Funk", "Pagode", "Foró", "Sertanejo universitário", "Gospel"};



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


    

void * sendRandomSong(void* arg){
  int msgid = *((int*)arg);

  printf("Data send is : %d \n", msgid); 
  song_t song = randomSong();
  msgsnd(msgid, &song, sizeof(song), 0);

  float sleep_time = (rand()%500)/100.0;
 
  sleep(sleep_time);
}

int main()
{
    key_t key;
    int msgid;



    // ftok to generate unique key
    key = ftok("spotiprocess", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    //song_t song = {1,"Fear of the dark","Iron maiden","Rock",437};
    // msgsnd to send message 

	  srand(time(NULL));
    
    int i = 10;
    pthread_create(&tid0, NULL, sendRandomSong, &msgid) ; 
    //pthread_create(&tid1, NULL, t1, NULL) ; 
    pthread_join(tid0,NULL);  
    pthread_join(tid1,NULL);  
    while(1 < 2){


    }

    return 0;
}
