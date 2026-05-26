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
#include <vector>
#include <algorithm>
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

    void DisplayTitle(const vector<Document *> &docs)
    {
        for (const Document *doc : docs)
        {
            if (doc == nullptr)
                continue;

            cout << doc->GetTitle() << "\t" << doc->GetContent() << endl;
        }
    }
    void Main(void)
    {
        vector<Document *> open_docs{};

        open_docs.emplace_back(new Document{"05. May sales"});
        open_docs.emplace_back(new Document{"02. Feb sales"});
        open_docs.emplace_back(new Document{"01. Jan sales"});
        open_docs.emplace_back(new Document{"09. Sep sales"});
        open_docs.emplace_back(new Document{"05. May sales"});
        open_docs.emplace_back(new Document{"10. Oct sales"});
        

        DisplayTitle(open_docs);


        cout << "\nSorted by title: "<< endl << endl;

        std::sort(open_docs.begin(), open_docs.end(), [](const Document *a, const Document *b){
            if (a == nullptr) return false;
            if (b == nullptr) return true;
            return a->GetTitle() < b->GetTitle();
        });

        // Remove consecutive duplicates (by title) after sorting
        auto new_end = std::unique(open_docs.begin(), open_docs.end(),
            [](const Document *a, const Document *b){
                if (a == nullptr || b == nullptr)
                    return a == b;
                return a->GetTitle() == b->GetTitle();
            });

        // Delete the duplicate Document objects moved to the tail by unique
        for (auto it = new_end; it != open_docs.end(); ++it)
            delete *it;

        // Erase the duplicate pointer entries from the vector
        open_docs.erase(new_end, open_docs.end());

        cout << "\nAfter removing duplicates:" << endl << endl;
        DisplayTitle(open_docs);

        // Clean up remaining raw Document objects.
        for (Document *d : open_docs)
            delete d;

        open_docs.clear();
    }
 }

 namespace Smart
 {
    void DisplayTitle(const vector<shared_ptr<Document>> &docs)
    {
        for (const auto &doc : docs)
        {
            if (!doc)
                continue;

            cout << doc->GetTitle() << "\t" << doc->GetContent() << endl;
        }
    }

    void Main(void)
    {
        vector<shared_ptr<Document>> open_docs{};

        open_docs.emplace_back(make_shared<Document>("05. May sales"));
        open_docs.emplace_back(make_shared<Document>("02. Feb sales"));
        open_docs.emplace_back(make_shared<Document>("01. Jan sales"));
        open_docs.emplace_back(make_shared<Document>("09. Sep sales"));
        open_docs.emplace_back(make_shared<Document>("05. May sales"));
        open_docs.emplace_back(make_shared<Document>("10. Oct sales"));

        DisplayTitle(open_docs);

        cout << "\nSorted by title: "<< endl << endl;

        std::sort(open_docs.begin(), open_docs.end(), [](const shared_ptr<Document> &a, const shared_ptr<Document> &b){
            if (!a) return false;
            if (!b) return true;
            return a->GetTitle() < b->GetTitle();
        });

        auto new_end = std::unique(open_docs.begin(), open_docs.end(),
            [](const shared_ptr<Document> &a, const shared_ptr<Document> &b){
                if (!a || !b)
                    return a == b;
                return a->GetTitle() == b->GetTitle();
            });

        open_docs.erase(new_end, open_docs.end());

        cout << "\nAfter removing duplicates:" << endl << endl;
        DisplayTitle(open_docs);

        // No manual delete required: shared_ptr will free documents automatically.
    }
 }


/** @brief Entry point — executes both raw and shared pointer demonstrations. */
int main(int argc, char const *argv[])
{
    Raw::Main();
    Smart::Main();
}
