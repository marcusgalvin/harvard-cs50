#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
//include these librarys for buttom loops
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Usage: ./caesar k\n");
    return 1;
  }

  int k = atoi(argv[1]);
  if (k < 0)
  {
    printf("key must be pos\n");
    return 1;
  }

  string plaintext = get_string("plaintext: ");
  //loop thru plain text, output encrypted text
  for (int i = 0, len = strlen(plaintext); i < len; i++)
  {
    if (islower(plaintext[i]))
      printf("%c", (plaintext[i] - 'a' + k) % 26 + 'a');
    else if (isupper(plaintext[i]))
      printf("%c", (plaintext[i] - 'A' + k) % 26 + 'A');

    else
      printf("%c", plaintext[i]);
  }
  printf("\n");
}
