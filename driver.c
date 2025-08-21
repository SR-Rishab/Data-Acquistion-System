#include<functions.h>
int main() {
    // Main driver code to be written here
    TransmitMessage(initial_message);
    char choice = ReceiveString();
    if(choice == '0')
        Auto();
    Manual();
}
