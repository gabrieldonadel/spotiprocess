#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "song.h"

volatile sig_atomic_t stop;

void inthand(int signum){
    stop = 1;
}

void convertSecToMin (int time, char * res){
  int min = time/60;
  int sec = time%60;
  sprintf(res, "%d:%02d",min,sec);
}

int printSong(song_t song, int grep){

  char duration[12];
  convertSecToMin(song.duration, duration);
  if(grep){
    printf("titulo: %s; autor: %s; gerero: %s;duração: %s;\n",song.title, song.author,song.genre,duration);
  }else{

  printf("\n#######################################");
  printf("\n%-12s%-25s%2s","# Titulo: ",song.title," #");
  printf("\n%-12s%-25s%2s","# Autor: ",song.author," #");
  printf("\n%-13s%-25s%2s","# Gênero: ",song.genre," #");
  printf("\n%-14s%-25s%2s","# Duração: ", duration," #");
  printf("\n#######################################\n");

  }

  return 1;

}

int main(int argc, char *argv[])
{
    int grep = 0;
    int repetitions = 0;
    int songs_played = 0;
    key_t key;
    int msgid;
    song_t song;

    signal(SIGINT, inthand);

    if(argc>=2){
        for(int counter=0;counter<argc;counter++){
            if(strcmp(argv[counter],"-g") == 0){
              grep = 1;
            }
            if(strcmp(argv[counter],"-r") == 0 && counter<argc-1 && strspn(argv[counter+1], "0123456789") == strlen(argv[counter+1])){
              repetitions = atoi(argv[counter+1]);
            }
          }
    }

    key = ftok("spotiprocess", 65); 
    msgid = msgget(key, 0666 | IPC_CREAT);


    while ( msgrcv(msgid, &song, (sizeof(song)-sizeof(long)), 1, 0) != -1 && !stop) {

      printSong(song, grep);
      songs_played++;
      if( songs_played == repetitions){
        break;
      }
    }



    printf("\nObrigado por usar spotiprocess!\n");
    // to destroy the message queue
    //msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
