#include "Document.h"

#include <print>

Document::Document(const std::string& title) :m_Title{ title } {
}

void Document::SetTitle(const std::string& title) {
	m_Title = title;
}

const std::string& Document::GetTitle() const {
	return m_Title;
}

void Document::AddContent(const std::string& content) {
	m_Content += content;
}

void Document::DeleteContent() {
	m_Content.clear();
}

const std::string& Document::GetContent() const {
	return m_Content;
}

bool Document::IsEmpty() const {
	return m_Content.empty();
}

void Document::Display() const {
	std::println("#### [{}] ####", m_Title);
	std::println("{}", m_Content);
}


