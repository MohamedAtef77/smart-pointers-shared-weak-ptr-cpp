/**
 * @file    main.cpp
 * @brief   Demonstrates std::unique_ptr::reset() and std::unique_ptr::release()
 *          using a minimal object example in modern C++.
 * @author  Mohamed Atef
 * @date    2026-05-23
 */

/*===========================================================================*
 *                          F I L E  I N C L U S I O N S                     *
 *===========================================================================*/
#include <iostream>
#include <memory>
#include "Document.h"
using namespace std;
namespace SimpleUsage
{
    namespace Raw
    {
        void Main(void)
        {
            Document *p = new Document{};
            p->SetTitle("Note");
            p->AddContent("Using Raw Pointers ");
            cout << *p << endl; 


            delete p; /* If not added, there will be a memory leakage */
        }
    }

    namespace Smart
    {
        void Main(void)
        {
            unique_ptr<Document>p {new Document{}};
            p->SetTitle("Note");
            p->AddContent("Using unique Pointers ");
            cout << *p << endl; 
        }
    }
}

int main(int argc, char const *argv[])
{
    SimpleUsage::Raw::Main();
    SimpleUsage::Smart::Main();
}
