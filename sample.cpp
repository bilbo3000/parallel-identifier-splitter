#include <time.h> 
#include <iostream> 
#include <stdlib.h>

using namespace std; 

int main(int argc, char* argv[]) {
    time_t t1 = atoi(argv[1]);
    time_t t2 = atoi(argv[2]);

    cout << difftime(t2, t1) << endl; 
    return 0; 
}
