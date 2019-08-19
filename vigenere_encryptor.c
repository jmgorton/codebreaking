#include <stdio.h>

#define INPUT_FILE "plaintext"
#define OUTPUT_FILE "cipher"

int main(int argc, char *argv[]) {
  printf("Please enter a keyword to encrypt the plaintext with: \n");
  char keyword[64], buffer[64];
  fread(&keyword, sizeof (keyword), 1, stdin);
  //  printf("%s\n", keyword);

  FILE *f, *in;
  f = fopen(OUTPUT_FILE, "w");
  in = fopen(INPUT_FILE, "r");

  while (fgets(buffer, 64, in)) {
    int i, ch, shift;
    int j = 0;
    for (i = 0; i < 64 && buffer[i]; i++) {
      ch = buffer[i] - 97;
      if (ch < 0 || ch > 25) {
        // handle numbers and uppercase letters and punctuation

        fputc(buffer[i], f);

        //      return -1;
      } else {
	//        fputc(buffer[i], f);
	shift = keyword[j++] - 97;
	if (keyword[j] == '\n' || keyword[j] == '\0') j = 0;
	fputc(((ch + shift) % 26) + 97, f);
      }

    }
  }

  fclose(in);
  fclose(f);

  return 0;
}
