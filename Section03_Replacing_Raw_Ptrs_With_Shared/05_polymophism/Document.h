#include <fstream>
#include <string>
#pragma once
class Document {
	std::string m_Title{};
	std::string m_Content{};
public:
	Document(const std::string &title = "Untitled");
	void SetTitle(const std::string &title);
	const std::string &GetTitle()const;
	virtual void AddContent(const std::string &content);
	void DeleteContent();
	const std::string &GetContent()const;
	bool IsEmpty()const;
	virtual void Display()const ;
	friend std::ostream& operator<<(std::ostream& os, const Document& obj) {
		return os << obj.m_Content;
	}
	virtual ~Document()=default ;
};

