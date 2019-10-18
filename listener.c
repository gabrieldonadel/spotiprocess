#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#include "song.h"

void convertSecToMin (int time, char * res){

  int min = time/60;
  int sec = time%60;
  sprintf(res, "%d:%d",min,sec);
}

int main()
{
    key_t key;
    int msgid;

    songs_t *songs;


    key = ftok("spotiprocess", 65);


    msgid = msgget(key, 0666 | IPC_CREAT);
printf("size of : %ld \n",  sizeof(songs));

    msgrcv(msgid, &songs, sizeof(songs), 1, 0);

    char duration[12];
    //convertSecToMin(songs[0]->duration, duration);

    printf("Titulo: %s \n",  songs->data[0].title);
    free(songs);
    //printf("Autor: %s \n",songs[0]->author);
    //printf("Gênero: %s \n",songs[0]->genre);
    //printf("Duração: %s \n", duration);

    // to destroy the message queue
    //msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
