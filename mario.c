#include <stdio.h>
#include <cs50.h>

int main(void)
{

  int height;

  do
  {
    //promt user for a number (height)
    height = get_int("please enter a number: ");
  }
  //make sure the user can only pick a number from 0-23, if not ask again
  while (height < 0 || height > 23);

  //n = height
  for (int rows = 0; rows < height; rows++)
  {
    for (int j = 0; j < height; j++)
    {
      if (rows + j >= height - 1)
        printf("#");
      else
        printf(" ");
    }
    printf("\n");
  }
}