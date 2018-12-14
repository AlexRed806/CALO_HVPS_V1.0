#ifndef ExampleLibXml2_h
#define ExampleLibXml2_h

#include "ExampleLibXml2.h"
#include "string"
#include "vector"
#include "map"
#include <libxml/parser.h>
#include <libxml/xpath.h>

class ListElement {
public :
        std::string Name;
        std::string Description;
        std::string NameSpace;
        std::string NodeId;
        std::string Type;
};

class ExampleLibXml2 {
 public:
    	ExampleLibXml2(const std::string& fileName);

   	std::string getOpcUaRef();
    	std::string getRootName();
    	std::vector<ListElement*>* getListElements();
 private:
	xmlNodePtr readFile(const std::string& fileName); 
	int readExampleLibXml2(const std::string& fileName);
	
	std::string m_OpcUaRef;
	std::string m_RootName;
	std::vector<ListElement *>m_ListElements; 
};

#endif // ExampleLibXml2_h

