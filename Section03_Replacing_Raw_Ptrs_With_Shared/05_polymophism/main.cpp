/**
 * @file    main.cpp
 * @brief   Demonstrates polymorphism with raw pointers and shared_ptr,
 *          including virtual dispatch and dynamic_cast downcasting.
 * @author  Mohamed Atef
 * @date    2026-05-29
 */

/*===========================================================================*
 *                          F I L E  I N C L U S I O N S                     *
 *===========================================================================*/
#include <vector>
#include <iostream>
#include <memory>
#include <cassert>
#include "Document.h"
#include "Note.h"
#include "Report.h"
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
 *                       S T A T I C  F U N C T I O N S                      *
 *===========================================================================*/
/* None */

/*===========================================================================*
 *                       G L O B A L  F U N C T I O N S                      *
 *===========================================================================*/

namespace Raw {
	class Application {
		vector<Document*> m_Documents{};
	public:
		void List() {
			for (auto doc : m_Documents) {
				doc->Display();
				cout << '\n';
			}
		}
		void Add(Document* p) {
			m_Documents.emplace_back(p);
		}
		void Remove(size_t index) {
			auto to_delete = m_Documents[index];
			m_Documents.erase(m_Documents.begin() + index);
			delete to_delete;
		}
		Document* GetAt(size_t index) {
			assert(index < m_Documents.size());
			return m_Documents[index];
		}
		size_t Count() const {
			return m_Documents.size();
		}
		~Application() {
			for (auto doc : m_Documents)
				delete doc;
		}
	};

	void ShowProperties(const Document* p) {
		cout << "==== PROPERTIES ====\n";
		auto pDoc = const_cast<Document*>(p);

		if (auto report = dynamic_cast<Report*>(pDoc); report) {
			cout << "[Report :" << pDoc->GetTitle() << '\n';
			cout << "[Author :" << report->GetAuthor() << '\n';
		} else if (auto note = dynamic_cast<Note*>(pDoc); note) {
			cout << "[Note: " << note->GetTitle() << " ]\n";
			cout << "Tags:";
			for (const auto& tag : note->GetTags())
				cout << tag << ' ';
			cout << '\n';
		} else {
			cout << "[Document : " << pDoc->GetTitle() << '\n';
		}
	}

	void Init(Application& app) {
		Document* p1 = new Document{ "C++ Best Practices" };
		p1->AddContent("Prefer smart pointers over raw pointers");
		Report* rp1 = new Report{ "Umar", "Expenses" };
		rp1->AddContent("Fuel - 1200\n");
		rp1->AddContent("Food -  800");
		Note* n1 = new Note{ "Groceries" };
		n1->AddContent("Milk");
		n1->AddContent("Eggs");
		n1->AddContent("Bread");
		n1->AddContent("Apple");
		n1->AddTag("personal");
		n1->AddTag("todo");
		app.Add(p1);
		app.Add(rp1);
		app.Add(n1);
	}

	void Main() {
		Application app{};
		Init(app);
		app.Remove(1);
		app.List();
		ShowProperties(app.GetAt(1));
	}
}

namespace Smart {
	class Application {
		vector<shared_ptr<Document>> m_Documents{};
	public:
		void List() {
			for (auto doc : m_Documents) {
				doc->Display();
				cout << '\n';
			}
		}
		void Add(shared_ptr<Document> p) {
			m_Documents.emplace_back(move(p));
		}
		void Remove(size_t index) {
			m_Documents.erase(m_Documents.begin() + index);
		}
		shared_ptr<Document> GetAt(size_t index) {
			assert(index < m_Documents.size());
			return m_Documents[index];
		}
		size_t Count() const {
			return m_Documents.size();
		}
	};

	void ShowProperties(const shared_ptr<Document> p) {
		cout << "==== PROPERTIES ====\n";
		auto pDoc = const_pointer_cast<Document>(p);

		if (auto report = dynamic_pointer_cast<Report>(pDoc); report) {
			cout << "[Report :" << pDoc->GetTitle() << '\n';
			cout << "[Author :" << report->GetAuthor() << '\n';
		} else if (auto note = dynamic_pointer_cast<Note>(pDoc); note) {
			cout << "[Note: " << note->GetTitle() << " ]\n";
			cout << "Tags:";
			for (const auto& tag : note->GetTags())
				cout << tag << ' ';
			cout << '\n';
		} else {
			cout << "[Document : " << pDoc->GetTitle() << '\n';
		}
	}

	void Init(Application& app) {
		shared_ptr<Document> p1{ new Document{ "C++ Best Practices" } };
		p1->AddContent("Prefer smart pointers over raw pointers");
		shared_ptr<Report> rp1{ new Report{ "Umar", "Expenses" } };
		rp1->AddContent("Fuel - 1200\n");
		rp1->AddContent("Food -  800");
		shared_ptr<Note> n1{ new Note{ "Groceries" } };
		n1->AddContent("Milk");
		n1->AddContent("Eggs");
		n1->AddContent("Bread");
		n1->AddContent("Apple");
		n1->AddTag("personal");
		n1->AddTag("todo");
		app.Add(p1);
		app.Add(rp1);
		app.Add(n1);
	}

	void Main() {
		Application app{};
		Init(app);
		app.Remove(1);
		app.List();
		ShowProperties(app.GetAt(1));
	}
}

/** @brief Entry point — runs the Smart pointer polymorphism demo. */
int main() {
	Smart::Main();
}
