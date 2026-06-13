/**
 * @file    main.cpp
 * @brief   Demonstrates a shared resource observed by another class using raw pointers,
 *          setting the stage for std::weak_ptr to prevent dangling pointers.
 * @author  Mohamed Atef
 * @date    2026-05-27
 */

/*===========================================================================*
 *                          F I L E  I N C L U S I O N S                     *
 *===========================================================================*/
#include <iostream>
#include <memory>
#include <string>
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
/**
 * @brief Entry point
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 upon successful execution.
 */
int main(int argc, char const *argv[])
{
    shared_ptr<int> ptr{new int{10}};

    weak_ptr<int> ob = ptr;           // observe the shared object without owning it

    auto res = ob.lock();              // attempt to promote weak_ptr to shared_ptr
    if (res)                           // check whether the object is still alive
    {
        cout << *res << endl;          // print the managed value through shared_ptr
    }

}
