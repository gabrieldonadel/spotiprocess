int MAXSIZE =4;

typedef struct song_str {
  long mesg_type;
  char title[50];
  char author[50];
  char genre[40];
  int duration;
} song_t;

typedef struct songs_str {
  long mesg_type;
  song_t data[MAXSIZE];
} songs_t;
