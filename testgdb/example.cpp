#include <iostream>
using namespace std;

const int Asize = 10;

int main() {
    char input[Asize];

    cout << "Enter a line of text: ";
    cin.get(input, Asize);
    cout << "You entered: " << input << " AND THE LAST ONE IS "<< input[Asize-2] <<endl;

    return 0;
}
