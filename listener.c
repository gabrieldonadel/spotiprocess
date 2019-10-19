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

    printf("#######################################");
    printf("\n%-12s%-25s%2s",  "# Titulo: ",song.title, " #");
    printf("\n%-12s%-25s%2s","# Autor: ",song.author," #");
    printf("\n%-13s%-25s%2s","# Gênero: ",song.genre," #");
    printf("\n%-14s%-25s%2s","# Duração: ", duration," #");
    printf("\n#######################################\n\n");
}
    // to destroy the message queue
    //msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
