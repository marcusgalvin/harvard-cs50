#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{

  //Make sure ther is only one command line argument
  if (argc != 2)
  {
    printf("Try Again\n");
    return 1;
  }

  //Convert user input string to int
  int k = atoi(argv[1]);

  //Make sure command line argument is non negative
  if (k < 0)
  {
    printf("Try Again\n");
    return 1;
  }
  else
  {

    //Get user input string
    string plainText = get_string("plaintext: ");

    //Place to print cipher text
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plainText); i < n; i++)
    {

      //Encrypt lower case
      if
        islower(plainText[i])
        {
          printf("%c", (((plainText[i] + k) - 97) % 26) + 97);
        }
      //encrypt upper case
      else if
        isupper(plainText[i])
        {
          printf("%c", (((plainText[i] + k) - 65) % 26) + 65);
        }
      //print anything else
      else
      {
        printf("%c", plainText[i]);
      }
    }

    printf("\n");

    return 0;
  }
}