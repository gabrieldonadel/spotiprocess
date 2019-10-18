#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "song.h"
#include <stdlib.h>


int main()
{
    key_t key;
    int msgid;


    song_t son = {1,"Fear of the dark","Iron maiden","Rock",437};
    song_t son2 = {1,"Mamonas","Iron maiden","Rock",437};
    song_t *song = &son;
    song_t *song_2 = &son2;
    song_t *song_3 = &son;
    song_t *song_4 = &son;

    songs_t *songs;
     songs_t soangs= {1,{son,son2,son,son}};
     songs = &soangs;

    // ftok to generate unique key
    key = ftok("spotiprocess", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);


    // msgsnd to send message
    msgsnd(msgid, &songs, sizeof(songs), 0);
printf("size of : %ld \n",  sizeof(songs));


    printf("Data send is : %ld \n", songs->mesg_type);
    songs->data[0] = son2;

    free(songs);

      //msgsnd(msgid, &song, sizeof(song), 0);
    //while(1 < 2){
      printf("Aguardou 1 segundos\n");
      sleep(1);

    //}

    return 0;
}
