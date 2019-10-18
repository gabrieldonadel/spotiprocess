#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "song.h"


int main()
{
    key_t key;
    int msgid;

    song_t song = {1,"Fear of the dark","Iron maiden","Rock",437};

    // ftok to generate unique key
    key = ftok("spotiprocess", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);


    // msgsnd to send message
    msgsnd(msgid, &song, sizeof(song), 0);


    printf("Data send is : %s \n", song.title);
    while(1 < 2){
      msgsnd(msgid, &song, sizeof(song), 0);
      printf("Aguardou 1 segundos\n");
      sleep(1);

    }

    return 0;
}
