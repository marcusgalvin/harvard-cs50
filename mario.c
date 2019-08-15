#include <stdio.h>
#include <cs50.h>

int main(void)
{

  int n;

  do
  {
    //promt user for a number (height)
    n = get_int("please enter a number: ");
  }
  //make sure the user can only pick a number from 0-23, if not ask again
  while (n < 0 || n > 23);

  //n = height
  for (int rows = 0; rows < n; rows++)
  {
    for (int j = 0; j < n; j++)
    {
      if (rows + j >= n - 1)
        printf("#");
      else
        printf(" ");
    }
    printf("\n");
  }
}