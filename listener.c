#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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

    song_t song;


    key = ftok("spotiprocess", 65);


    msgid = msgget(key, 0666 | IPC_CREAT);


  while ( msgrcv(msgid, &song, sizeof(song), 1, 0) != -1) {

    char duration[12];
    convertSecToMin(song.duration, duration);

    printf("Titulo: %s \n",  song.title);
    printf("Autor: %s \n",song.author);
    printf("Gênero: %s \n",song.genre);
    printf("Duração: %s \n", duration);
}
    // to destroy the message queue
    //msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
