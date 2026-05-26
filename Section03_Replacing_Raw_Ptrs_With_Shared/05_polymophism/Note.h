#pragma once
#include <vector>
#include "Document.h"
class Note :
    public Document
{
    std::vector<std::string> m_Tags{} ;
    using Document::Document ;
public:
    void AddContent(const std::string& content) override;
    void AddTag(const std::string &tag) ;
    const std::vector<std::string> & GetTags()const ;
    void Display() const override;
};

