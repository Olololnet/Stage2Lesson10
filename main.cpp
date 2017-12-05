#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>

#define ERASE_NOT_NEEDED 2
#define CHANGE_STRING_NOT_NEEDED 1

void Exercise2()
{
    // Exercise2: вывести последние k строк файла

    const int iShowLastXLines = 5;

    std::ifstream fsFile("/home/pem/development/SomeTextFile.txt");

    if (!fsFile.is_open())
    {
        std::cout << "File not found." << std::endl;
        return;
    }

    std::queue<std::string> quStringQueue;
    std::string strCurrentLine;

    while (std::getline(fsFile, strCurrentLine))
    {
        if (quStringQueue.size() >= iShowLastXLines)
            quStringQueue.pop();

        quStringQueue.push(strCurrentLine);
    }
    for(int i = 0; i < iShowLastXLines; i++)
    {
        std::cout << quStringQueue.front() << std::endl;
        quStringQueue.pop();
    }
}

template <typename T>
std::string NumberToString(T tNumber)
{
    std::ostringstream ossStringStream;
    ossStringStream << tNumber;
    return ossStringStream.str();
}

void ChangeString(std::string& strBaseString, const int& iCharCount,
                  int& iCurrentStringIndex, int& iStringLength)
{
    std::string strSubString = NumberToString(iCharCount);
    const int iSubStringLength = strSubString.length();
    const int iReplaceStartPos = iCurrentStringIndex + 1;
    strBaseString.replace(iReplaceStartPos, iSubStringLength, strSubString);

    if (iCharCount == ERASE_NOT_NEEDED)
        iCurrentStringIndex += iCharCount;
    else
    {
        const int iCharCountWithoutFirst = iCharCount - 1;
        const int iCharToEraseCount = iCharCountWithoutFirst - iSubStringLength;
        strBaseString.erase(iReplaceStartPos + iSubStringLength, iCharToEraseCount);
        iStringLength = (int)strBaseString.length();

        iCurrentStringIndex += iSubStringLength;
    }
}

void CompressString(std::string& strBaseString)
{
    int iStringLength = (int)strBaseString.length();

    for (int i = 0; i < iStringLength;)
    {
        const char chCurrentChar = strBaseString[i];
        int iCharCount = 1;

        for (int j = i + 1; j < iStringLength; ++j)
        {
            if (strBaseString[j] == chCurrentChar)
                ++iCharCount;
            else
                break;
        }

        if (iCharCount == CHANGE_STRING_NOT_NEEDED)
            ++i;
        else if (iCharCount > 1)
            ChangeString(strBaseString, iCharCount, i, iStringLength);
    }
}

void Exercise1()
{
    // Exercise1: сжатие строки
    // AABCCCCDDEEEEE -> A2BC4D2E5, учитывать варианты A10.
    // В один проход, без пересоздания строки

    std::string strBaseString = "AABCCCCDDEEEEE";
    CompressString(strBaseString);

    std::cout << strBaseString << std::endl;
}

int main()
{

//    Exercise2();
//    Exercise1();

    return 0;
}
