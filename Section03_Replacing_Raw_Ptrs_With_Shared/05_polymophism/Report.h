#pragma once
#include <ostream>

#include "Document.h"
class Report :
    public Document
{
    std::string m_Author{} ;

public:
    Report(const std::string& author, const std::string& title="Untitled");
    const std::string & GetAuthor()const ;
    void Display() const override;
    friend std::ostream& operator<<(std::ostream& os, const Report& obj) {
	    return os
		    << obj.m_Author << ":" << static_cast<const Document&>(obj) ;
    }
};

