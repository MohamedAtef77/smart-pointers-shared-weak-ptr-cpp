/**
 * @file    main.cpp
 * @brief   Demonstrates the double-delete problem when sharing raw pointers
 *          between objects and how smart pointers prevent this issue.
 * @author  Mohamed Atef
 * @date    2026-05-27
 */

/*===========================================================================*
 *                          F I L E  I N C L U S I O N S                     *
 *===========================================================================*/
#include <iostream>
#include <memory>
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
/** @brief Entry point */
int main(int argc, char const *argv[])
{
    shared_ptr<int> p{new int{10}, [](int *ptr) {
        cout << "Custom deleter executed! Cleaning up memory." << endl;
        delete ptr;
    }};

    auto op = p; /* op becomes an co-owner of this resource */

    p.reset();
    if(op)
    {
        cout << *op << endl;
    }
}
