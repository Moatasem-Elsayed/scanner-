#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "sstream"
class Scanner
{
public:
    Scanner() = default;
    Scanner(int speed);
    Scanner(const Scanner &scan) = delete;
    Scanner operator=(const Scanner scan) = delete;
    std::vector<std::string> scan_all(std::string start, std::string end);
    std::vector<std::string> scan_once(std::string ip);

private:
    int m_speed;
    uint m_byteStart[4];
    uint m_byteEnd[4];
    void convertIptoBytes(std::string ip, uint *out);
    std::pair<int, int> validateIp(std::string ipS, std::string ipE);

    // it is preferred to move "exec" into standalone class to apply concept of single responsibility
    std::string exec(const char *cmd);
};