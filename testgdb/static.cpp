#include<iostream>

const int Asize =10;

void strcount(const char* str)
{
  using namespace std;
  static int total = 0; // static local variable
  int cnt =0;
  cout << str <<" string ";
  while(*str++)
  {
    cnt ++;
  }
  total += cnt;
  cout<< "has "<< cnt<< " characters";
  cout << " total is "<< total<< endl;
}

int main()
{
  using namespace std;
  char input[Asize];
  char next;

  cin.get(input, Asize);
  while(cin)
  {
    cin.get(next);
    while (next != '\n')
    {
      cin.get(next);
    }
    strcount(input);
    cin.get(input,Asize);

  }
  return 0;
}

