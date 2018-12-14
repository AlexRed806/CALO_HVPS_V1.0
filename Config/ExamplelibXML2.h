#ifndef ExampleLibXML2_h
#define ExampleLibXML2_h

#include "ExampleLibXML2.h"
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

class ExampleLibXML2 {
 public:
    	ExampleLibXML2(const std::string& fileName);

   	std::string getOpcUaRef();
    	std::string getRootName();
    	std::vector<ListElementQuasar*>* getListElement();
 private:
	xmlNodePtr readFile(const std::string& fileName); 
	int readExampleLibXML2(const std::string& fileName);
	
	std::string m_OpcUaRef;
	std::string m_RootName;
	std::vector<ListElement *>m_ListElement; 
};

#endif // ExampleLibXML2_h

