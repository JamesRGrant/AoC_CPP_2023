#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <cctype>

#include <chrono>
using namespace std::chrono;
using namespace std;

void file_to_array(string filename, list<string> &lines)
{
    ifstream file(filename);
    string s;
    while (getline(file, s))
        lines.push_back(s);
}

long p1(list<string> &input)
{
    long sum = 0;
    for (auto &line : input)
    {
        // Find the first number
        string s;
        for (auto &c : line)
        {
            if (isdigit(c))
            {
                s.push_back(c);
                break;
            }
        }

        // Find the last number
        for (auto it = s.rbegin(); it != s.rend(); ++it)
        {
            char c = *it;
            if (isdigit(c))
            {
                s.push_back(c);
                break;
            }
        }

        sum += stol(s);
    }
    return sum;
}
long p2(list<string> &input)
{
    long sum = 0;
    string nums[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    for (auto &line : input)
    {
        // Find the first number
        string s;
        for (int i = 0; i < sizeof(line); i++)
        {
            char c = line[i];
            bool breakflag = false;
            if (isdigit(c))
            {
                s.push_back(c);
                break;
            }

            // look for words
            for (int j = 0; j < 10; j++)
            {
                if (line.substr(i, line.length() - i).find(nums[j]) == 0)
                {
                    s.push_back(digit[j]);
                    breakflag = true;
                    break;
                }
            }
            if (breakflag)
                break;
        }

        // Find the last number
        for (int i = line.length(); i >= 0; i--)
        {
            bool breakflag = false;
            char c = line[i];
            if (isdigit(c))
            {
                s.push_back(c);
                break;
            }

            // look for words
            for (int j = 0; j < 10; j++)
            {
                if (line.substr(i, line.length() - i).find(nums[j]) == 0)
                {
                    s.push_back(digit[j]);
                    breakflag = true;
                    break;
                }
            }
            if (breakflag)
                break;
        }

        sum += stol(s);
    }
    return sum;
}

int main(void)
{
    list<string> lines;
    file_to_array("input\\01.txt", lines);

    auto start = high_resolution_clock::now();
    long answer = p1(lines);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "P1: " << answer << " in " << duration.count() << " ms" << endl;

    start = high_resolution_clock::now();
    answer = p2(lines);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "P2: " << answer << " in " << duration.count() << " ms" << endl;
}
