/**
 * @file    main.cpp
 * @brief   Demonstrates the double-delete problem when sharing raw pointers
 *          between objects and how smart pointers prevent this issue.
 *          Also shows exception-safe ownership with `std::shared_ptr`.
 * @author  Mohamed Atef
 * @date    2026-05-27
 */

/*===========================================================================*
 *                          F I L E  I N C L U S I O N S                     *
 *===========================================================================*/
#include <iostream>
#include <climits>
#include <limits>
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


/*===========================================================================*
 *                       S T A T I C  F U N C T I O N S                      *
 *===========================================================================*/
/* None */

/*===========================================================================*
 *                       G L O B A L  F U N C T I O N S                      *
 *===========================================================================*/

 namespace Raw
 {

     class Application
     {
     public:
         Document *p_doc{};
         char *p_buffer{};


         Application()
         {
            p_doc = new Document{};
            p_buffer = new char [1024 * 1024];  // won't trigger bad alloc because of compiler options preventing me from compilation 
         }

         ~Application()
         {
            delete p_doc;
            delete [] p_buffer;
         }
     };

    void Main(void)
    {
        try
        {
            Application app;
            cout << "The application has started with an empty document..." << endl;
        }
        catch (const std::exception &e)
        {
            cout << "Exception: " << e.what() << endl;


            /* inside the exception in this case I can't delete the allocated memory as there is no external interface inside the class */
        }
    }
 }

 namespace Smart
 {

     class Application
     {
     public:
         shared_ptr<Document> p_doc;
         shared_ptr<char> p_buffer;


         Application()
         {
            p_doc.reset(new Document{});
            p_buffer.reset(new char [1024 * 1024]);  // won't trigger bad alloc because of compiler options preventing me from compilation 
         }

         ~Application()
         {
         }
     };

    void Main(void)
    {
        try
        {
            Application app;
            cout << "The application has started with an empty document..." << endl;
        }
        catch (const std::exception &e)
        {
            cout << "Exception: " << e.what() << endl;


            /* inside the exception in this case I can't delete the allocated memory as there is no external interface inside the class */
            /* but luckily the destructor of the smart (shared) pointers will be called eventually at the end of this process */
        }
    }
 }


/** @brief Entry point — executes both raw and shared pointer demonstrations. */
int main(int argc, char const *argv[])
{
    Raw::Main();
    Smart::Main();
}
