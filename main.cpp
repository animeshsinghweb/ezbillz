#include <iostream>

#include "structures.cpp"
#include "getDataFiles.cpp"
#include "saveDataFiles.cpp"
#include "displays.cpp"
#include "billing.cpp"

using namespace std;

void choiceMain()
{
  int ch;
  cout << "\n Enter 1 to Generate the bill or 0 to exit: ";
  cin >> ch;

  cout << "\033[2J\033[1;1H"; // clear screen

  if (ch != 1)
    return;

  generateBill();
}

int main()
{

  cout << "\033[2J\033[1;1H"; // clear screens

  cout << "\n \t\t EZ-Billz Billing Software \n\n";

  choiceMain();

  return 0;
}