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

/** @brief View class that owns a raw Document pointer. */
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

        /** @brief Destroys the owned Document on View cleanup. */
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

 namespace Raw
 {
    void Serialize(Document *p)
    {
        if(p && p->IsEmpty())
        {
            cout << "Serializing Document ..." << endl;
            delete p; // Serialize assumes ownership of the raw pointer when empty.

            return; 
        }

        throw logic_error("No content to serialize... ");
    }

    void Main(void)
    {
        Document *p{new Document{"Note"}};

        p->AddContent("Prefer Smart Pointers over Raw Pointers ;)");
        cout << p->GetTitle() << "\t" << p->GetContent() << endl;

        p->DeleteContent();

        // Raw pointer ownership is ambiguous here: Serialize may delete p,
        // and the caller also deletes p in the normal path.
        try
        {
            Serialize(p);
            delete p; /* There is a chance of multiple deletions */
        }
        catch (const std::exception &e)
        {
            cout << "Exception: " << e.what() << endl;

            delete p; /* Delete if Serialize threw before taking ownership. */
        }
    }
 }

 namespace Smart
 {
    void Serialize(shared_ptr<Document> p)
    {
        if(p && p->IsEmpty())
        {
            cout << "Serializing Document ..." << endl;
            // shared_ptr handles the cleanup automatically when it goes out of scope.
            return; 
        }

        throw logic_error("No content to serialize... ");
    }

    void Main(void)
    {
        shared_ptr<Document> p{};

        // reset acquires a new Document and makes p its sole owner.
        p.reset(new Document{});
        p->AddContent("Prefer Smart Pointers over Raw Pointers ;)");
        cout << p->GetTitle() << "\t" << p->GetContent() << endl;

        p->DeleteContent();

        try
        {
            Serialize(p);
        }
        catch (const std::exception &e)
        {
            cout << "Exception: " << e.what() << endl;
        }
    }
 }


/** @brief Entry point — executes both raw and shared pointer demonstrations. */
int main(int argc, char const *argv[])
{
    Raw::Main();
    Smart::Main();
}
