/**
 * @file    main.cpp
 * @brief   Demonstrates how std::weak_ptr breaks a shared_ptr cyclic dependency,
 *          allowing objects to be destroyed instead of leaked.
 * @author  GitHub Copilot
 * @date    2026-06-13
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

class Node
{
public:
    explicit Node(const string &name)
        : m_name{name}
    {
        cout << "Node '" << m_name << "' created\n";
    }

    ~Node()
    {
        cout << "Node '" << m_name << "' destroyed\n";
    }

    void setNext(const shared_ptr<Node> &next)
    {
        m_next = next;                     // weak_ptr does not contribute to reference count
    }

    void printNext() const
    {
        if (auto nextShared = m_next.lock())
        {
            cout << m_name << " -> " << nextShared->m_name << "\n";
        }
        else
        {
            cout << m_name << " has no valid next node\n";
        }
    }

private:
    string m_name;
    weak_ptr<Node> m_next;                // breaks the ownership cycle
};

/**
 * @brief Entry point
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 upon successful execution.
 */
int main(int argc, char const *argv[])
{
    {
        auto first = make_shared<Node>("First");       // owns the node
        auto second = make_shared<Node>("Second");     // owns the node

        first->setNext(second);                          // first observes second
        second->setNext(first);                          // second observes first through weak_ptr

        first->printNext();                              // valid because second is still alive
        second->printNext();                             // valid because first is still alive

        cout << "First use count: " << first.use_count() << "\n";
        cout << "Second use count: " << second.use_count() << "\n";
    }

    cout << "Exited scope, weak_ptr broke the cyclic dependency so both nodes can be destroyed." << endl;

    return 0;
}
