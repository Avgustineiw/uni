#include <iostream>
#include <stdlib.h>

void func(std::string str, int len)
{
    if (!len) {
        std::cout << str << std::endl;
        return;
    }
    func(str + '0', len - 1);
    func(str + '1', len - 1);
    
}
 
int main()
{
    int n;
 
    std::cin >> n;
 
    func("", n);
    return 0;
}