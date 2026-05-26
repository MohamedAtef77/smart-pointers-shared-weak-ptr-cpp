/**
 * @file    main.cpp
 * @brief   Demonstrates reference counting behavior of std::shared_ptr in
 *          modern C++, comparing raw pointer ownership with shared pointer
 *          automatic memory management.
 * @author  Mohamed Atef
 * @date    2026-05-27
 */

/*===========================================================================*
 *                          F I L E  I N C L U S I O N S                     *
 *===========================================================================*/
#include <iostream>
#include <memory>
#include "Document.h"
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

namespace SimpleUsage
{
    /** @brief Namespace demonstrating raw pointer ownership issues. */
    namespace Raw
    {
        /** @brief Demonstrates manual memory management with raw pointers. */
        void Main(void)
        {
            Document *p = new Document{};
            p->SetTitle("Note");
            p->AddContent("Using Raw Pointers ");
            cout << *p << endl; 


            delete p; /* If not added, there will be a memory leakage */
        }
    }

    /** @brief Namespace demonstrating automatic memory management with shared_ptr. */
    namespace Smart
    {
        /** @brief Demonstrates reference counting with std::shared_ptr and use_count(). */
        void Main(void)
        {
            shared_ptr<Document>p {new Document{}};
            p->SetTitle("Note");
            p->AddContent("Using unique Pointers ");
            cout << *p << endl; 

            cout << p.use_count() << endl; 

            {
                auto p1 = p;
                cout << p.use_count() << endl;         

            }

            cout << p.use_count() << endl;    
        }
    }
}

/** @brief Entry point — compares raw and shared pointer ownership models. */
int main(int argc, char const *argv[])
{
    SimpleUsage::Raw::Main();
    SimpleUsage::Smart::Main();
}
