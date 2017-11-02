#include <stdio.h>
#include <string.h>

// skip to KEYSTRING
#define KEYSTRING "<h2 class=midashigo"

int main(int argc, char *argv[])
{
  FILE *fp_i, *fp_o;      
  char fname[128] = {0}; 
  char str[10000];
  char c;
  int newline_cnt;
  int len;

  if (argc != 2) {
    fprintf(stderr, "%s\n", "usage: tb en_word");
  }

  strncpy(fname, argv[1], strlen(argv[1]));
  len = strlen(argv[1]);
  fname[len] = '1';
  fname[len+1] = '\0';
  
  if ((fp_i = fopen(argv[1], "r")) == NULL) {
    perror("fopen");
    return 1;
  }

  if ((fp_o = fopen(fname, "w")) == NULL) {
    perror("fopen");
    return 1;
  }


  // until body tag is read
  while (strncmp(fgets(str, sizeof(str), fp_i), KEYSTRING, strlen(KEYSTRING)) != 0) {
  }

  // when body tag was not found
  if (strncmp(str, KEYSTRING, strlen(KEYSTRING)) != 0) {
    fprintf(stderr, "%s\n", "body tag was not found");
    return 1;
  }

  // output the extracted data
  newline_cnt = 0;
  while (((c = fgetc(fp_i)) != EOF) && (newline_cnt < 3)) {
    if (c == '<') {
      while (c != '>') {
        c = fgetc(fp_i);
      }
      continue;
    }

    fputc(c, fp_o);
    if (c == '\n') {
      newline_cnt++;
    }
      
    if (c == '.') {
      fputc('\n', fp_o);
      fputc('\n', fp_o);
    }
  }

  return 0;
}
