#include <cs50.h>
#include <stdio.h>

int main(void)
{

  // Check number of args
  if (argc != 2)
  {
    printf("Wrong number of arguments. Please try again.\n");

    return 1;
  }
  else
  {
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
      if (!isalpha(argv[1][i]))
      {
        printf("Must be alphabetic characters only. Please Try Again");

        return 1;
      }
    }
  }