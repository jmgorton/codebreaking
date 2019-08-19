#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_KEY_LENGTH 32

#define INPUT_FILE "message1"
#define OUTPUT_FILE "cipher"

//#if 0
int calculate_lcm(int *key_lengths, int num_keys) {
  // could do the prime factorization, smoosh factors together
  // that is too complex of a solution for this time
  int i = 1, lcm = key_lengths[0];

  while (i < num_keys) {
    int temp1 = lcm, temp2 = key_lengths[i];
    while (temp1 != temp2) {
      while (temp1 < temp2) {
	temp1 += lcm;
      }
      if (temp1 != temp2) temp2 += key_lengths[i];
    }
    lcm = temp1;
    i++;
  }

  return lcm;
}
//#endif

int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <number of keywords.\n", argv[0]);
    return -1;
  }

  int num_keys = atoi(argv[1]);

  // i is a generic counter, k is a counter of keys
  int i, k;
  // j is a collection of counters for the index of each key
  // try calloc instead
  int *j = (int *) calloc(sizeof (int), num_keys);
  //  int *j = (int *) malloc(sizeof (int) * num_keys);
  //  i = 0;
  //  while (i < num_keys) {
  //    j[i++] = 0;
  //  }

  char **keyword = (char **) malloc(sizeof (char *) * num_keys);
  int *key_lengths = (int *) calloc(sizeof (int), num_keys);
  i = 0;
  while (i < num_keys) {
    keyword[i] = (char *) malloc(MAX_KEY_LENGTH);
    i++;
  }

  i = 0;
  while (i < num_keys) {
    printf("Please enter key %d: ", i + 1);
    // this actually always assigns key_lengths[i] a value of 1 because a string is only a single character pointer
    scanf("%s", keyword[i]);
    // convert input to lowercase, check values
    if ((key_lengths[i] = strlen(keyword[i])) > MAX_KEY_LENGTH) {
      fprintf(stderr, "Key exceeds max key length.\n");
      return -2;
    }
    i++;
  }

  int effective_key_length = calculate_lcm(key_lengths, num_keys);
  printf("\nEffective key length: %d\n", effective_key_length);

  char buffer[64];
  //  fread(&keyword, sizeof (keyword), 1, stdin);
  //  printf("%s\n", keyword);

  FILE *f, *in;
  int char_encrypted = 0, char_notencrypted = 0;
  f = fopen(OUTPUT_FILE, "w");
  in = fopen(INPUT_FILE, "r");

  while (fgets(buffer, 64, in)) {
    // if i redeclare i here as a char there is no warning about redeclaration
    char_encrypted += strlen(buffer);
    char ch, shift, upper;
    for (i = 0; i < 64 && buffer[i]; i++) {
      upper = 0;
      ch = buffer[i] - 65;
      if (ch >= 0 && ch <= 25) upper = 1;
      else ch -= 32;

      if (ch < 0 || ch > 25) {
	// handle numbers and punctuation
	// could leave those unencrypted, or implement a switch

	fputc(buffer[i], f);
	char_encrypted--;
	char_notencrypted++;

      } else {
	k = 0;
	shift = 0;
	while (k < num_keys) {
	  shift += keyword[k][j[k]++] - 97;
	  // just use key_lengths for this part
	  if (keyword[k][j[k]] == '\n' || keyword[k][j[k]] == '\0') j[k] = 0;
	  k++;
	}
	if (upper) fputc(((ch + shift) % 26) + 65, f);
	else fputc(((ch + shift) % 26) + 97, f);
      }

    }
  }

  printf("Total characters encrypted: %d\n", char_encrypted);
  printf("Total characters not encrypted: %d\n\n", char_notencrypted);

  free(key_lengths);
  free(j);
  i = 0;
  while (i < num_keys) {
    free(keyword[i]);
    i++;
  }
  free(keyword);

  fclose(in);
  fclose(f);

  return 0;
}
