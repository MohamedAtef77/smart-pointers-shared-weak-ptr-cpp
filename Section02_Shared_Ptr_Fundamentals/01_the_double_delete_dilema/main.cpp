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

/** @brief View class that holds a reference to a Document. */
class View
{
    private:
        Document *m_pDocument;

    public:
        /** @brief Sets the Document pointer for this View. */
        void SetDocument(Document *pDoc)
        {
            m_pDocument = pDoc;
        }

        /** @brief Displays the Document's title and content. */
        void Display() const
        {
            cout << "{}" << " -> {}" << endl;
        }
        ~View()
        {
            delete m_pDocument;
        }
};

/*===========================================================================*
 *                       S T A T I C  F U N C T I O N S                      *
 *===========================================================================*/
/* None */

/*===========================================================================*
 *                       G L O B A L  F U N C T I O N S                      *
 *===========================================================================*/

namespace Sharing
{
    namespace Raw
    {
        /** @brief Demonstrates the double-delete problem with raw pointers. */
        void Main(void)
        {
            View view{};
            Document *p = new Document{};
            p->SetTitle("Note");
            p->AddContent("Using Raw Pointers ");
            view.SetDocument(p);
            view.Display();

            delete p; /* Both view and p point to same memory — double delete risk */
        }
    }

    namespace Smart
    {
        /** @brief Demonstrates basic ownership using shared_ptr. */
        void Main(void)
        {
            shared_ptr<Document>p {new Document{}};
            p->SetTitle("Note");
            p->AddContent("Using shared Pointers ");
            cout << *p << endl; 
        }
    }
}


/** @brief Entry point — demonstrates double delete dilemma. */
int main(int argc, char const *argv[])
{
    Sharing::Raw::Main();
    Sharing::Smart::Main();
}
