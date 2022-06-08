
#include "scan.hpp"

Scanner::Scanner(int speed) : m_speed(speed)
{
    for (int i = 0; i < 4; i++)
    {
        m_byteEnd[i] = 0;
        m_byteStart[i] = 0;
    }
}
std::vector<std::string> Scanner::scan_all(std::string start, std::string end)
{
    std::vector<std::string> result;
    std::pair<int, int> iprange;
    iprange = validateIp(start, end);
    for (int i = iprange.first; i < iprange.second; i++)
    {
        std::stringstream cmd;

        cmd << "ping " << m_byteStart[0] << "." << m_byteStart[1] << "." << m_byteStart[2]
            << "." << i << " -c 1 -i 0.2   -w " << m_speed << "| head -n 2 | tail -n 1";
        // std::cout << cmd.str() << std::endl;
        std::string out = exec(cmd.str().c_str());
        if (out.find("Unreachable") == std::string::npos && out.size() != 1)
        {
            std::stringstream active;
            active << m_byteStart[0] << "." << m_byteStart[1] << "." << m_byteStart[2]
                   << "." << i;
            result.push_back(active.str());
            std::cout << active.str() << " is active" << std::endl;
        }
        else
        {
            // std::cout << "Not Active" << std::endl;
        }
    }
    return result;
}
std::vector<std::string> Scanner::scan_once(std::string ip)
{
    return std::vector<std::string>{"Test"};
}
std::pair<int, int> Scanner::validateIp(std::string ipS, std::string ipE)
{
    std::pair<int, int> ret;

    convertIptoBytes(ipS, m_byteStart);
    convertIptoBytes(ipE, m_byteEnd);
    if (std::all_of(std::begin(m_byteStart), std::end(m_byteStart), [&](uint val)
                    { return val <= 255; }) == false)
    {
        std::cout << "[X] Start ip is invaild" << std::endl;
        ret = std::make_pair(-1, -1);
    }
    else if (std::all_of(std::begin(m_byteEnd), std::end(m_byteEnd), [&](uint val)
                         { return val <= 255; }) == false)
    {
        std::cout << "[X] End ip is invaild" << std::endl;
        ret = std::make_pair(-1, -1);
    }
    /*ip subnets  are okay */
    else if (std::equal(std::begin(m_byteStart), std::begin(m_byteStart) + 3, std::begin(m_byteEnd), std::begin(m_byteEnd) + 3))
    {
        std::cout << "[+] Start Ip is valid " << std::endl;
        std::cout << "[+] End Ip is valid " << std::endl;
        ret = std::make_pair(m_byteStart[3], m_byteEnd[3]);
    }
    else
    {
        std::cout << "[X] this program for just class C subnet " << std::endl;

        ret = std::make_pair(-1, -1);
    }
    return ret;
}
void Scanner::convertIptoBytes(std::string ip, uint *out)
{
    std::stringstream ipstream(ip);
    char dot;

    ipstream >> out[0] >> dot >> out[1] >> dot >> out[2] >> dot >> out[3] >> dot;
}
std::string Scanner::exec(const char *cmd)
{
    char buffer[128];
    std::string result = "";
    FILE *pipe = popen(cmd, "r");
    if (!pipe)
        throw std::runtime_error("popen() failed!");
    try
    {
        while (fgets(buffer, sizeof buffer, pipe) != NULL)
        {
            result += buffer;
        }
    }
    catch (...)
    {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}