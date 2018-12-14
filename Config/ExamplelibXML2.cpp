#include "ExampleLibXML2.h"
#include <iostream>


ExampleLibXML2::ExampleLibXML2(const std::string& fileName)
{
	readExampleLibXML2(fileName);
}

std::string  ExampleLibXML2::getOpcUaRef()
{
	return m_OpcUaRef;
}

std::string  ExampleLibXML2::getRootName()
{
	return m_RootName;
}

std::vector<ListElement*>*  ExampleLibXML2::getListElements()
{
	return &m_ListElements;
}

int ExampleLibXML2::readConfigQuasar(const std::string& fileName) {
        int ret=0;
	xmlNodePtr element=NULL;
/****************************************/
        std::string tempName="";
        std::string tempDescription="";
        std::string tempNameSpace="";
        std::string tempNodeId="";
        std::string tempType="";
        xmlNodePtr n2,n3,n4;
        std::string res2="";
	std::string res="";
/****************************************/

        element = readFile(fileName);
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
								ListElement* tempElement=new ListElement();
								tempElement->Name = tempName;
								tempElement->Description = tempDescription;
								tempElement->NameSpace = tempNameSpace;
								tempElement->NodeId = tempNodeId;
								tempElement->Type = tempType;
								m_ListElements.push_back(tempElement);
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

xmlNodePtr ExampleLibXML2::readFile(const std::string& fileName) {
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
