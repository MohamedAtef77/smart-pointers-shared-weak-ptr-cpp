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

/** @brief Custom deleter functor that frees malloc-allocated memory. */
 struct Functor
 {
    void operator()(int *ptr)
    {

        cout << "You are inside the customer deleter (functor)" << endl;
        free(ptr);
    }
 };

/*===========================================================================*
 *                       S T A T I C  F U N C T I O N S                     *
 *===========================================================================*/
/** @brief Custom deleter function that frees a heap-allocated int array. */
static void arrayDeleter(int *ptr)
{
    cout << "You are inside the custom deleter (function)" << endl;
    delete[] ptr;
}

/*===========================================================================*
 *                       G L O B A L  F U N C T I O N S                     *
 *===========================================================================*/
/** @brief Demonstrates functor, lambda, and function custom deleters with shared_ptr. */
 int main(int argc, char const *argv[])
 {
    shared_ptr<int> p{static_cast<int *> (malloc(sizeof(int))),Functor()};


    cout << "Checking whether the reset member function calls the default deleter (deleter) or the custom one: " << endl;

    p.reset(new int[2]);

    cout << "End of check" << endl; /* It called the default deleter */

    cout << "Checking whether the reset member function calls the default deleter (deleter) or the custom one: " << endl;

    p.reset(new int[4], [](int *ptr) {
        cout << "You are inside the custom deleter (lambda)" << endl;
        delete[] ptr;
    });


    cout << "End of check" << endl;  /* it has called the specified deleter */


    cout << "Checking whether the reset member function calls the default deleter (deleter) or the custom one: " << endl;

    p.reset(new int,arrayDeleter);

    if (auto *d = get_deleter<void(*)(int*)>(p))
        cout << "get_deleter: function deleter is active, address=" << (void*)*d << endl;

    cout << "End of check" << endl;  /* it has called the specified deleter */

 }
