#include "ConfigQuasar.h"
#include <iostream>

ConfigQuasar *ConfigQuasar::singleton = NULL;

ConfigQuasar *ConfigQuasar::getInstance(const std::string& fileName) {
        if (!singleton) {
                singleton = new ConfigQuasar(fileName);
        }
        return singleton;
}

ConfigQuasar *ConfigQuasar::getInstance() {
        return singleton;
}

void ConfigQuasar::kill() {
        if (NULL != singleton) {
                delete singleton;
                singleton = NULL;
        }
}

ConfigQuasar::ConfigQuasar(const std::string& fileName)
{
	m_fileName = fileName;
	readConfigQuasar();
}

std::string  ConfigQuasar::getOpcUaRef()
{
	return m_OpcUaRef;
}

std::string  ConfigQuasar::getRootName()
{
	return m_RootName;
}

std::vector<ListElementQuasar*>*  ConfigQuasar::getListElementQuasars()
{
	return &m_ListElementQuasars;
}

ListElementQuasar* ConfigQuasar::searchElement(const std::string& element)
{
	return m_MapElements[element];
}

int ConfigQuasar::readConfigQuasar() {
        int ret=0;
        std::string tempName="";
        std::string tempDescription="";
        std::string tempNameSpace="";
        std::string tempNodeId="";
        std::string tempType="";
	xmlNodePtr element=NULL;
        xmlNodePtr n2,n3,n4;
        std::string res2="";
	std::string res="";

        element = readFile();
	if(element!=NULL) {
                for (n2 = element->children; n2 != NULL; n2 = n2->next) {
                                res2 = (char *) n2->name;
                                if (res2.compare("Elements") == 0) {
                                        for (n3 = n2->children; n3 != NULL; n3 = n3->next) {
                                                res = (char *) n3->name;
                                                if (res.compare("Element") == 0) {
							tempName="";
							tempDescription="";
							tempNameSpace="";
							tempNodeId="";
							tempType="";
                                                        for (n4 = n3->children; n4 != NULL; n4 = n4->next) {
                                                                res = (char *) n4->name;
                                                                if (res.compare("Name") == 0) {
                                                                tempName = ((char *) xmlNodeGetContent(n4));
                                                                }
                                                                if (res.compare("Description") == 0) {
                                                                tempDescription = ((char *) xmlNodeGetContent(n4));
                                                                }
                                                                if (res.compare("NameSpace") == 0) {
                                                                tempNameSpace = ((char *) xmlNodeGetContent(n4));
                                                                }
                                                                if (res.compare("NodeId") == 0) {
                                                                tempNodeId = ((char *) xmlNodeGetContent(n4));
                                                                }
                                                                if (res.compare("Type") == 0) {
                                                                tempType = ((char *) xmlNodeGetContent(n4));
                                                                }
                                                        }
							if(tempNodeId.size()>0) {
								ListElementQuasar* tempElement=new ListElementQuasar();
								tempElement->Name = tempName;
								tempElement->Description = tempDescription;
								tempElement->NameSpace = tempNameSpace;
								tempElement->NodeId = tempNodeId;
								tempElement->Type = tempType;
								m_ListElementQuasars.push_back(tempElement);
								m_MapElements[tempName]=tempElement;
							}
                                                }
                                        }
                                }
                               if (res2.compare("GeneralInfo") == 0) {
                                        for (n3 = n2->children; n3 != NULL; n3 = n3->next) {
                                                res = (char *) n3->name;
 						if (res.compare("OPCUA_Address") == 0) {
							m_OpcUaRef = ((char *) xmlNodeGetContent(n3));
						}
 						if (res.compare("RootName") == 0) {
							m_RootName = ((char *) xmlNodeGetContent(n3));
						}
					}
				}
                }
	} else {
		ret=1;
	}
	return ret;
}

xmlNodePtr ConfigQuasar::readFile() {
        xmlDocPtr doc=NULL;
        xmlNodePtr ret_racine;
        xmlNodePtr racine;

        doc = xmlParseFile(m_fileName.c_str());
        racine = xmlDocGetRootElement(doc);
        ret_racine = xmlDocGetRootElement(doc);
        if (racine == NULL) {
		fprintf(stderr, "Document XML vierge\n");
		xmlFreeDoc(doc);
        }
        return ret_racine;
}
