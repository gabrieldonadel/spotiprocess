const int MAXSIZE = 4;

typedef struct song_str {
  char title[200];
  char author[200];
  char genre[200];
  int duration;
} song_t;

typedef struct songs_str {
  long mesg_type;
  song_t data[4];
} songs_t;
