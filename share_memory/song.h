typedef struct song_str { 
  char title[50];
  char author[50];
  char genre[40];
  int duration;
} song_t;

typedef struct songs_str {
  long mesg_type;
  song_t data[4];
} songs_t;