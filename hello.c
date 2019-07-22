#include <cs50.h>
#include <stdio.h>



int main(void)
{
  //prompts user for their name
    string name = get_string("What is your name?\n");
    //return hell "users name"
    printf("hello, %s\n", name);
}