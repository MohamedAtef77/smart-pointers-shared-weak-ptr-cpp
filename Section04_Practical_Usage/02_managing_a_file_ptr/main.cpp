/**
 * @file    main.cpp
 * @brief   Demonstrates managing a FILE* resource with raw pointers before
 *          transitioning to a smart-pointer approach.
 * @author  Mohamed Atef
 * @date    2026-05-30
 */

/*===========================================================================*
 *                          F I L E  I N C L U S I O N S                     *
 *===========================================================================*/
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;

/*===========================================================================*
 *                     M A C R O S  &  F U N C T I O N - L I K E             *
 *                              M A C R O S                                  *
 *===========================================================================*/
/* None */

/*===========================================================================*
 *                           U S E R  T Y P E S                              *
 *===========================================================================*/
/* None */

/*===========================================================================*
 *                       S T A T I C  F U N C T I O N S                     *
 *===========================================================================*/
/* None */

/*===========================================================================*
 *                       G L O B A L  F U N C T I O N S                     *
 *===========================================================================*/

namespace raw
{
    /** @brief Reads and prints a file using raw FILE* and manual memory management. */
    void Main(const char *fileName)
    {
        FILE *fp = fopen(fileName, "r");
        if (!fp)
            throw logic_error{"Could not open file"};

        fseek(fp, 0, SEEK_END);
        long file_length   = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char *file_content = new char[file_length + 1];

        if (!fread(file_content, 1, file_length, fp))
        {
            delete[] file_content;
            fclose(fp);
            throw logic_error{"Could not read from file"};
        }

        file_content[file_length] = '\0';
        cout << file_content << "\n";

        delete[] file_content;
        fclose(fp);
    }
}

namespace Smart
{
    /** @brief Reads and prints a file using shared_ptr for automatic resource cleanup. */
    void Main(const char *fileName)
    {
        shared_ptr<FILE> fp{fopen(fileName, "r"), fclose};
        if (!fp)
            throw logic_error{"Could not open file"};

        fseek(fp.get(), 0, SEEK_END);
        long file_length = ftell(fp.get());
        fseek(fp.get(), 0, SEEK_SET);
        shared_ptr<char> file_content{new char[file_length + 1], [](char *p){ delete[] p; }};

        if (!fread(file_content.get(), 1, file_length, fp.get())) /* .get() yields the raw pointer */
            throw logic_error{"Could not read from file"};

        file_content.get()[file_length] = '\0';
        cout << file_content.get() << "\n";
    }
}

/** @brief Entry point — calls raw::Main and catches any exceptions. */
int main()
{
    try
    {
        raw::Main("test.txt");
    }
    catch (const exception &e)
    {
        cout << "Exception -> " << e.what() << "\n";
    }
}
