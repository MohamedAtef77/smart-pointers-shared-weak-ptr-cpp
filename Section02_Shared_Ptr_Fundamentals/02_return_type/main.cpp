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
    namespace Smart
    {
        /** @brief Factory function that creates and returns a shared_ptr<Document>. */
        shared_ptr<Document> NewDocument(const string &title)
        {
            if (title.empty())
            {
                return nullptr;
            }
            return shared_ptr<Document>{new Document{title}};
        }

        class View
        {
        private:
            shared_ptr<Document> m_pDocument;

        public:
            /** @brief Sets the Document pointer for this View. */
            void SetDocument(shared_ptr<Document> pDoc)
            {
                m_pDocument = pDoc;
            }

            /** @brief Returns a const reference to the Document shared_ptr. */
            const shared_ptr<Document> & GetDocument() const
            {
                return m_pDocument;
            }

            /** @brief Displays the Document's title and content. */
            void Display() const
            {
                cout << "{}" << " -> {}" << endl;
            }
        };

        /** @brief Demonstrates smart pointer return types and null checking. */
        void Main(void)
        {
            auto p = NewDocument("Note");
            cout << "After NewDocument: use_count = " << p.use_count() << endl;

            if (!p)
            {
                cout << "The document could not be created" << endl;
                return;
            }

            p->AddContent("This is some content");
            cout << *p << '\n';

            View view{};
            cout << "After View creation: use_count = " << p.use_count() << endl;

            view.SetDocument(p);
            cout << "After SetDocument: use_count = " << p.use_count() << endl;

            view.Display();
            auto &p2 = view.GetDocument();
            cout << "After GetDocument: use_count = " << p.use_count() << endl;
        }
    }
}


/** @brief Entry point — demonstrates double delete dilemma. */
int main(int argc, char const *argv[])
{
    Sharing::Smart::Main();
}
