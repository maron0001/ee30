#include <iostream>

int main(){
    int i;
    std::cin >> i;

    for ( ; i>0; i--){
        if(i%2==0){
            std::cout << i << std::endl;
        }

    }

}