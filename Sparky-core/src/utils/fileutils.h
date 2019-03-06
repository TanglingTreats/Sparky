#pragma once

#include <string>


namespace sparky {

    class FileUtils
    {
    public:
        //using a c library, thus it looks different
        static std::string read_file(const char* filepath)
        {
            FILE* file = fopen(filepath, "rt");
            fseek(file, 0, SEEK_END);               //to find out how long the file is. navigate to the end of the file
            unsigned long length = ftell(file);     //retrieve the length of the file. gives number of bytes

            char* data = new char[length + 1];      //use a character array to read into it. +1 for termination character to tell it has terminated
            memset(data, 0, length + 1);            //set all of it to zero. ftell will give us extra bytes.
            fseek(file, 0, SEEK_SET);                //reset seek position
            fread(data, 1, length, file);
            fclose(file);

            std::string result(data);
            delete[] data;

            return result;
        }

    };


}
