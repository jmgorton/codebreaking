#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define INPUT_FILE "message1"

#define TESTING 0
#define METHOD 2

#define NUM_TOP_LETTERS 5
#define NUM_BOT_LETTERS 5
#define NUM_TOP_BIGRAMS 5
#define NUM_BOT_BIGRAMS 5

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

void print_letter_freqz(short letters[26]) {
  int i = 0, total = 0;
  while (i < 26) {
    total += letters[i];
    printf("The letter \'%c\' occurred %d times.\n", i + 97, letters[i]);
    i++;
  }
  printf("Total letters: %d\n", total);
}

void print_bigram_freqz(short bigrams[26][26]) {
  int i = 0, j = 0;
  printf("\t");
  while (i < 26) printf("\'%c\'\t", i++ + 97);
  printf("\n");
  i = 0;
  while (i < 26) {
    printf("\'%c\'\t", i + 97);
    j = 0;
    while (j < 26) {
      printf("%d\t", bigrams[i][j++]);
    }
    i++;
    printf("\n");
  }
}

void fill_topbot_letters(short **top_letters, short **bot_letters, short letters[26]) {

#define swap(a, b) { \
    typeof (a) _tmp = a; \
    a = b; \
    b = _tmp; \
  }

  // handle ties here sometime
  // at the start of the i loop, check if letters[i] matches *top_letters[j] for some j
  // if it does, increment some tie value array counting how many elements tied

  // i think if there is a NULL pointer passed into this function it may cause a seg fault
  // when the test block is uncommented, seg faults seem to happen

  /*
    // test
  top_letters[0] = &letters[0];
  top_letters[1] = &letters[1];
  top_letters[2] = NULL;

  printf("%c\t%c\n", (char) (top_letters[0] - letters) + 97, (char) (top_letters[1] - letters) + 97);
  printf("%d\t%d\n", letters[0], letters[1]);

  swap(top_letters[0], top_letters[1]);

  printf("%c\t%c\n", (char) (top_letters[0] - letters) + 97, (char) (top_letters[1] - letters) + 97);
  printf("%d\t%d\n", letters[0], letters[1]);
  */

  int i = 0;
  int j = NUM_TOP_LETTERS - 1;
  while (i < 26) {

    j = NUM_TOP_LETTERS - 1;
    while (letters[i] > *top_letters[j]) {
      if (j != NUM_TOP_LETTERS - 1) {
	top_letters[j + 1] = top_letters[j];
      }
      top_letters[j] = &letters[i];

      if (j <= 0) {
	break;
      }
      j--;
    }

    j = NUM_BOT_LETTERS - 1;
    while (letters[i] < *bot_letters[j]) {
      if (j != NUM_BOT_LETTERS - 1) {
	bot_letters[j + 1] = bot_letters[j];
      }
      bot_letters[j] = &letters[i];

      if (j <= 0) {
	break;
      }
      j--;
    }

    i++;
  }

#undef swap

}

void fill_topbot_bigrams(short **top_bigrams, short **bot_bigrams, short bigrams[26][26]) {
  
#define swap(a, b) { \
    typeof (a) _tmp = a; \
    a = b; \
    b = _tmp; \
  }

  // copy of fill_topbot_letters

  int i = 0, j = 0;
  int k;
  while (i < 26) {
    j = 0;
    while (j < 26) {

      k = NUM_TOP_BIGRAMS - 1;
      while (bigrams[i][j] > *top_bigrams[k]) {
	if (k != NUM_TOP_BIGRAMS - 1) {
	  top_bigrams[k + 1] = top_bigrams[k];
	}
	top_bigrams[k] = &bigrams[i][j];

	if (k <= 0) {
	  break;
	}
	k--;
      }

      k = NUM_BOT_BIGRAMS - 1;
      while (bigrams[i][j] < *bot_bigrams[k]) {
	if (k != NUM_BOT_BIGRAMS - 1) {
	  bot_bigrams[k + 1] = bot_bigrams[k];
	}
	bot_bigrams[k] = &bigrams[i][j];

	if (k <= 0) {
	  break;
	}
	k--;
      }

      j++;
    }

    i++;
  }

#undef swap

}

void print_top_letters(short **top_letters, short letters[26]) {
  int k = 0;
  while (k < NUM_TOP_LETTERS) {
    //    printf("The #%d most common letter is \'%c\'\n", k + 1, (char) (&top_letters[k] - letters) + 97);
    printf("The #%d most common letter is \'%c\'\n", k + 1, (char) (top_letters[k] - letters) + 97);
    k++;
  }
  
}

void print_bot_letters(short **bot_letters, short letters[26]) {
  int k = 0;
  while (k < NUM_BOT_LETTERS) {
    //    printf("The #%d most common letter is \'%c\'\n", k + 1, (char) (&top_letters[k] - letters) + 97);
    printf("The #%d least common letter is \'%c\'\n", k + 1, (char) (bot_letters[k] - letters) + 97);
    k++;
  }
  
  
}

void print_top_bigrams(short **top_bigrams, short bigrams[26][26]) {
  int k = 0;
  while (k < NUM_TOP_BIGRAMS) {
    printf("The #%d most common bigram is \'%c%c\'\n", k + 1, (char) ((top_bigrams[k] - bigrams[0]) / 26) + 97, (char) ((top_bigrams[k] - bigrams[0]) % 26) + 97);
    k++;
  }
  
}

void print_bot_bigrams(short **bot_bigrams, short bigrams[26][26]) {
  int k = 0;
  while (k < NUM_BOT_BIGRAMS) {
    printf("The #%d least common bigram is \'%c%c\'\n", k + 1, (char) ((bot_bigrams[k] - bigrams[0]) / 26) + 97, (char) ((bot_bigrams[k] - bigrams[0]) % 26) + 97);
    k++;
  }
}

int main(int argc, char *argv[]) {

  // take in a letter as an argument for more specific information regarding that letter
  // common preceding and succeeding letters, percentage distributions, etc.

  int i, k;
  short letters[26], bigrams[26][26];
  short **top_letters, **top_bigrams, **bot_letters, **bot_bigrams;

  // allocate space
  top_letters = (short **) calloc(sizeof (short *), NUM_TOP_LETTERS);
  top_bigrams = (short **) calloc(sizeof (short *), NUM_TOP_LETTERS);
  bot_letters = (short **) calloc(sizeof (short *), NUM_TOP_LETTERS);
  bot_bigrams = (short **) calloc(sizeof (short *), NUM_TOP_LETTERS);
  if (!top_letters || !top_bigrams || !bot_letters || !bot_bigrams) {
    fprintf(stderr, "Failed to allocate space.\n");
    return -1;
  }

  // keep allocating space
  i = 0;
  while (i < NUM_TOP_LETTERS || i < NUM_BOT_LETTERS || i < NUM_TOP_BIGRAMS || i < NUM_BOT_BIGRAMS) {
    if (i < NUM_TOP_LETTERS) {
      top_letters[i] = (short *) calloc(sizeof (short), 1);
      if (!top_letters[i]) { fprintf(stderr, "Failed to allocate memory.\n"); return -1; }
      *top_letters[i] = -1;
    }
    if (i < NUM_BOT_LETTERS) {
      bot_letters[i] = (short *) calloc(sizeof (short), 1);
      if (!bot_letters[i]) { fprintf(stderr, "Failed to allocate memory.\n"); return -1; }
      *bot_letters[i] = SHRT_MAX;
    }
    if (i < NUM_TOP_BIGRAMS) {
      top_bigrams[i] = (short *) calloc(sizeof (short), 1);
      if (!top_bigrams[i]) { fprintf(stderr, "Failed to allocate memory.\n"); return -1; }
      *top_bigrams[i] = -1;
    }
    if (i < NUM_BOT_BIGRAMS) {
      bot_bigrams[i] = (short *) calloc(sizeof (short), 1);
      if (!bot_bigrams[i]) { fprintf(stderr, "Failed to allocate memory.\n"); return -1; }
      *bot_bigrams[i] = SHRT_MAX;
    }
    i++;
  }

  // initialize to 0
  i = k = 0;
  while (i < 26) {
    letters[i] = 0;
    k = 0;
    while (k < 26) {
      bigrams[i][k] = 0;
      k++;
    }
    i++;
  }

  // since we used calloc, i don't think we need to use this part
/*   i = k = 0; */
/*   short zero = 0; */
/*   while (i < NUM_TOP_LETTERS) { */
/*     top_letters[i++] = &k; */
/*   } */
/*   i = 0; */
/*   while (i < NUM_BOT_LETTERS) { */
/*     bot_letters[i++] = letters; */
/*   } */
/*   i = 0; */
/*   while (i < NUM_TOP_BIGRAMS) { */
/*     top_bigrams[i++] = zero; */
/*   } */
/*   i = 0; */
/*   while (i < NUM_BOT_BIGRAMS) { */
/*     bot_bigrams[i++] = bigrams[0]; */
/*   } */


  char buffer[64];

  FILE *in;
  in = fopen(INPUT_FILE, "r");

  int prev = -1;
  while (fgets(buffer, 64, in)) {
    int ch, upper;
    for (i = 0; i < 64 && buffer[i]; i++) {
      // turn ch into value between 0-25, set flag if input character was uppercase
      upper = 0;
      ch = buffer[i] - 65;
      if (ch >= 0 && ch <= 25) upper = 1;
      else ch -= 32;

      // TEST LINE FORMATTING
      //printf("\n");
      //printf("%c: ", ch + 97);

      if (ch < 0 || ch > 25) {
	// handle numbers and punctuation
	// could leave those unencrypted, or implement a switch

	// this keeps separated letters from being considered bigrams
	// e.g. 'nt' in "won't" would not be considered a bigram with this line
	// e.g. 'zb' in the phrase "buzz by" would not be considered a bigram with this line
	// take out these lines to ignore spaces and punctuation entirely
	// using this line makes frequency analysis easier, but also less realistic
	prev = -1;

      } else {
	// in this block we know that ch has a value 0-25 corresponding to the letter of buffer[i]
	// handle ties
	//	char replace = 0;
	letters[ch]++;
	// attempts to fill the top and bot pointer arrays while running instead of at the end

#if TESTING
#if METHOD = 1
	// this if block has bugs
	// this line and the comment under it seem to be identical
	if (letters[ch] > *top_letters[NUM_TOP_LETTERS - 1]) {
	//	if (letters[ch] > **(top_letters + NUM_TOP_LETTERS - 1)) {
	  // TEST LINE
	  //	  printf("%d vs %d\t", letters[ch], *(top_letters + NUM_TOP_LETTERS - 1));
	  printf("%d vs %d\t", letters[ch], *top_letters[NUM_TOP_LETTERS - 1]);
	  k = NUM_TOP_LETTERS - 1;
	  replace = 1;
	  while (k >= 0 && replace) {
	    if (&letters[ch] == top_letters[k]) {
	      // must also check that the value is in the right place in top_letters
	      replace = 0;
	    }
	    k--;
	  }
	  // TEST LINE
	  printf("%d", (int) replace);
	  if (replace) {
	    k = NUM_TOP_LETTERS - 2;
	    while (k >= 0) {
	      // this if-else block is failing big time
	      if (letters[ch] > *(top_letters[k]) && k > 0) {
		//      		top_letters[k + 1] = (top_letters[k]);
		//		if (k == NUM_TOP_LETTERS) to
      		top_letters[k] = top_letters[k - 1];
		//top_letters += k;
		//top_letters = top_letters + 1;
		//top_letters -= k;
	      }
	      else {
		if (k == 0) top_letters[k] = &letters[ch];
	        else (top_letters[k + 1]) = &letters[ch];
		//top_letters += k + 1;
		//top_letters = &letters[ch];
		//top_letters -= k + 1;
	      }
	      k--;
	    }
	  }
	  //	  top_letters = &letters[ch];
	}
	// repeat above but with bot_letters
	// see comment for bot_bigrams
	if (!bot_letters || letters[ch] < *bot_letters[0]) {
	  // change [0]
	  bot_letters[0] = &letters[ch];
	}
#elsif
	// not sure how the preprocessor directives if and elsif are supposed to work
	printf"method 2\n");
#endif
#endif

	if (prev >= 0 && prev <= 25) bigrams[prev][ch]++;

#if TESTING
	// unimplemented
	// do something similar to above above
	if (!top_bigrams || bigrams[prev][ch] > *top_bigrams[0]) {
	  // change [0]
	  top_bigrams[0] = &bigrams[prev][ch];
	}
	// repeat above but with bot_bigrams
	// check if bigrams[prev][ch] is already a member of bot_bigrams or if it has moved off the list
	if (!bot_bigrams || bigrams[prev][ch] < *bot_bigrams[0]) {
	  // change [0]
	  bot_bigrams[0] = &bigrams[prev][ch];
	}
#endif

	prev = ch;
      }

    }
  }

  fill_topbot_letters(top_letters, bot_letters, letters);
  fill_topbot_bigrams(top_bigrams, bot_bigrams, bigrams);

// print letter stats
  printf("\n");
  print_letter_freqz(letters);
  printf("\n");
  print_top_letters(top_letters, letters);
  printf("\n");
  print_bot_letters(bot_letters, letters);
  printf("\n");

// print bigram stats
  printf("\n");
  print_bigram_freqz(bigrams);
  printf("\n");
  print_top_bigrams(top_bigrams, bigrams);
  printf("\n");
  print_bot_bigrams(bot_bigrams, bigrams);
  printf("\n");





#if 0
  printf("\e[1mbold\e[0m\n");
  printf("\e[3mitalic\e[0m\n");
  printf("\e[4munderline\e[0m\n");
  printf("\e[9mstrikethrough\e[0m\n");
  printf("\e[31mHello World\e[0m\n");
  printf("\x1B[31mHello World\e[0m\n");

  printf ("\033[32;1m OK \033[0m\n");
  printf(BLUE "some text\n" RESET);



  printf("\e[1mbold\e[22m\n");
  printf("\e[2mdim\e[22m\n");
  printf("\e[3mitalic\e[23m\n");
  printf("\e[4munderline\e[24m\n");
  printf("\e[4:1mthis is also underline (new in 0.52)\e[4:0m\n");
  printf("\e[21mdouble underline (new in 0.52)\e[24m\n");
  printf("\e[4:2mthis is also double underline (new in 0.52)\e[4:0m\n");
  printf("\e[4:3mcurly underline (new in 0.52)\e[4:0m\n");
  printf("\e[5mblink (new in 0.52)\e[25m\n");
  printf("\e[7mreverse\e[27m\n");
  printf("\e[8minvisible\e[28m <- invisible (but copy-pasteable)\n");
  printf("\e[9mstrikethrough\e[29m\n");
  printf("\e[53moverline (new in 0.52)\e[55m\n");

  printf("\e[31mred\e[39m\n");
  printf("\e[91mbright red\e[39m\n");
  printf("\e[38:5:42m256-color, de jure standard (ITU-T T.416)\e[39m\n");
  printf("\e[38;5;42m256-color, de facto standard (commonly used)\e[39m\n");
  printf("\e[38:2::240:143:104mtruecolor, de jure standard (ITU-T T.416) (new in 0.52)\e[39m\n");
  printf("\e[38:2:240:143:104mtruecolor, rarely used incorrect format (might be removed at some point)\e[39m\n");
  printf("\e[38;2;240;143;104mtruecolor, de facto standard (commonly used)\e[39m\n");

  printf("\e[46mcyan background\e[49m\n");
  printf("\e[106mbright cyan background\e[49m\n");
  printf("\e[48:5:42m256-color background, de jure standard (ITU-T T.416)\e[49m\n");
  printf("\e[48;5;42m256-color background, de facto standard (commonly used)\e[49m\n");
  printf("\e[48:2::240:143:104mtruecolor background, de jure standard (ITU-T T.416) (new in 0.52)\e[49m\n");
  printf("\e[48:2:240:143:104mtruecolor background, rarely used incorrect format (might be removed at some point)\e[49m\n");
  printf("\e[48;2;240;143;104mtruecolor background, de facto standard (commonly used)\e[49m\n");

  printf("\e[21m\e[58:5:42m256-color underline (new in 0.52)\e[59m\e[24m\n");
  printf("\e[21m\e[58;5;42m256-color underline (new in 0.52)\e[59m\e[24m\n");
  printf("\e[4:3m\e[58:2::240:143:104mtruecolor underline (new in 0.52) (*)\e[59m\e[4:0m\n");
  printf("\e[4:3m\e[58:2:240:143:104mtruecolor underline (new in 0.52) (might be removed at some point) (*)\e[59m\e[4:0m\n");
  printf("\e[4:3m\e[58;2;240;143;104mtruecolor underline (new in 0.52) (*)\e[59m\e[4:0m\n");


  // without this line, the terminal output stays dim after calling dim
  printf("\e[1m%s\e[0m\n%s\n", "hello", "hello");
#endif

  //  free(top_letters);
  //  free(top_bigrams);

  fclose(in);

  return 0;
}
