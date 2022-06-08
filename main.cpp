#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include "scan.hpp"
#include "decorator.hpp"
int main(int argc, char *argv[])
{
    uint8_t select = 0;
    std::string start;
    std::string end;
    decorator doc;
    if (argc != 2)
    {
        doc.DisplaySpliiter("[X] Wrong Usage");
        // std::cout << "[X] Wrong Usage" << std::endl;
        std::cout << "[-] Usage: scanner <speed> [1][2][3] " << std::endl;
        std::cout << "[-] Example: scanner 2 " << std::endl;
        return 0;
    }
    uint8_t value = atoi(argv[1]);
    if (value > 3)
    {
        value = 3;
        std::cout << "[+] Your speed value is the max which is 3 " << std::endl;
    }
    Scanner l_scan(value);
    doc.DisplaySpliiter("Select Type of Scan");
    std::cout
        << "Would you like to scan range of Ips or single ip ?\n1-Range of ips\n2-Single ip " << std::endl;
    std::cin >> select;
    switch (select)
    {
    case '1':;

        std::cout << "please insert the inital ip : ";
        std::cin >> start;
        std::cout << "\nplease insert the last ip : ";
        std::cin >> end;
        std::cout << std::endl;
        doc.DisplaySpliiter("[+]start scanning your network ");
        l_scan.scan_all(start, end);
        break;
    case '2':
        break;
    default:
        std::cout << "[X] Please try again and keep in considration the choice of scan  is 1 or 2 " << std::endl;
        break;
    }
    return 0;
}
