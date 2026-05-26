#include "Note.h"

#include <print>

void Note::AddContent(const std::string& content) {
	Document::AddContent(std::format("* {}\n",content));
}

void Note::AddTag(const std::string& tag) {
	m_Tags.emplace_back("#" + tag) ;
}

const std::vector<std::string>& Note::GetTags() const {
	return m_Tags;
}

void Note::Display() const {
	Document::Display() ;
	for (const auto &tag : m_Tags) {
		std::print("{} ", tag) ;
	}
	std::println() ;
}
