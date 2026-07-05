#include <iostream>
#include <queue>
#include <string>

#include "tail_modern.hpp"

void tail(std::istream& readable_stream, int k)
{
    int threshold = k;
    std::string line;
    std::queue<std::string> q;

    while (std::getline(readable_stream, line))
    {
        if (q.size() == threshold)
        {
            q.pop();
        }

        q.push(line);
        k--;
    }

    while (q.size())
    {
        auto temp = std::move(q.front());
        q.pop();

        std::cout << temp << "\n";
    }
}
