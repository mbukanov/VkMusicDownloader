#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <fstream>
#include <string>

class FileOperations
{
public:
    FileOperations(){};
    ~FileOperations(){};

    static std::string readFromFile(std::string &filename)
    {
        std::string result = "";
        std::ifstream myFile(filename.c_str());
        if(myFile.is_open())
        {
            std::string tempstr;
            while(std::getline(myFile, tempstr))
            {
                result += tempstr;
            }
        }else
        {
            // Create File
            std::ofstream createFile(filename.c_str());
            createFile.close();
        }
        myFile.close();

        return result;
    }

    static void writeToFile(std::string &filename, std::string& text)
    {
        std::ofstream myFile(filename.c_str());
        myFile << text;
        myFile.close();
    }

};

#endif // FILEOPERATIONS_H
