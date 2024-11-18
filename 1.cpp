#include <iostream>

using namespace std;
int main(){
    cout<<"horsh";
    return 0;

}



// int hash(int key)
// {
// return( key % MAX);
// }
// //function for inserting a record using linear probe
// int linear_prob(int Hashtable[], int key)
// {
// int pos, i;
// pos = Hash(Key);
// if(Hashtable[pos] == 0) // empty slot
// {
// Hashtable[pos] = key;
// return pos;
// }
// else // slot is not empty
// {
// for(i = pos + 1; i % MAX != pos; i++)
// {
// if(Hashtable[i] == 0)
// {
// Hashtable[i] = key;
// return i;
// }
// }
// }
// // Table overflow
// return -1;
// }