#ifndef ConfigQuasar_h
#define ConfigQuasar_h

#include "ConfigQuasar.h"
#include "string"
#include "vector"
#include "map"
#include <libxml/parser.h>
#include <libxml/xpath.h>

typedef std::vector<std::string> list_t;


class ListElementQuasar {
public :
        std::string Name;
        std::string Description;
        std::string NameSpace;
        std::string NodeId;
        std::string Type;
};

class ConfigQuasar {
 static ConfigQuasar *singleton;
 public:
    static ConfigQuasar *getInstance(const std::string& fileName);
    static ConfigQuasar *getInstance();
    static void kill();
    ConfigQuasar(const std::string& fileName);

    std::string getOpcUaRef();
    std::string getRootName();
    std::vector<ListElementQuasar*>* getListElementQuasars();
    ListElementQuasar *searchElement(const std::string& element);
 private:
	std::string m_fileName;
	std::string m_OpcUaRef;
	std::string m_RootName;
	std::vector<ListElementQuasar *>m_ListElementQuasars; 
	std::map<std::string, ListElementQuasar *>m_MapElements; 
	xmlNodePtr readFile(); 
	int readConfigQuasar();
};

#endif // ConfigQuasar_h

