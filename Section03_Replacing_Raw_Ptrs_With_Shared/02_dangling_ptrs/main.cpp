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

 namespace Raw
 {
    void Display(Document *doc)
    {
        if (doc != nullptr)
        {
            cout << doc->GetContent() << "\t" << doc->GetTitle();
        }
    }
    void Serialize(Document *p)
    {
        if((p != nullptr) && !p->IsEmpty())
        {
            cout << "Serializing Document..." << endl; 
            delete p;
        }
    }
    void Main(void)
    {
        Document *p = new Document{"New"};
        p->AddContent("Prefer Smart Pointers Over Raw Pointers ");
        Display(p);
        // delete p;
        // p = nullptr;
        Display(p); /* Crashes if you didn't assign it to null and do a null ptr check  */
        Serialize(p);
        //delete p; /* crahes */
    }
 } // namespace Raw
 
 namespace Smart
 {
    void Display(const shared_ptr<Document> &doc)
    {
        if (doc != nullptr)
        {
            cout << doc->GetContent() << "\t" << doc->GetTitle();
        }
    }

    void Serialize(shared_ptr<Document> &p)
    {
        if (p && !p->IsEmpty())
        {
            cout << "Serializing Document..." << endl;
            p.reset();
        }
    }

    void Main(void)
    {
        auto p = make_shared<Document>("New");
        p->AddContent("Prefer Smart Pointers Over Raw Pointers ");
        Display(p);
        Display(p);
        Serialize(p);
        Display(p); /* safe: prints nothing because p is null */
    }
 } // namespace Smart
 

/** @brief Entry point — demonstrates raw vs shared pointer usage. */
int main(int argc, char const *argv[])
{
    Raw::Main();
    Smart::Main();
}
