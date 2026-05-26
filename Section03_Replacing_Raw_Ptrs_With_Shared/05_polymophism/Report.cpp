#include "Report.h"
#include <print>
Report::Report( const std::string& author,const std::string& title): Document{title},
                                                                     m_Author{author} {
}

const std::string& Report::GetAuthor() const {
	return m_Author;
}

void Report::Display() const {
	Document::Display() ;
	std::println("Author : {}", m_Author) ;
}

