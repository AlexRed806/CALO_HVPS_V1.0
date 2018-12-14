#include "Quasar_Manager.hh"
#include "dynamicLoader.h"
#include "ConfigQuasar.h"

#include <iostream>
#include <fstream>

#define API_LIB_PATH "/MOS_X86_4.0.2/lib/libDataAccessClientOPCUA.so";
#define MAX_PATH 1023

Quasar_Manager *Quasar_Manager::singleton = NULL;

Quasar_Manager *Quasar_Manager::getInstance() {
        return singleton;
}

Quasar_Manager::Quasar_Manager(std::string url,int *status) {
	m_url = url;
	singleton= this;
        int ret=0;
        m_config = NULL;
        m_config = ConfigQuasar::getInstance();
        if(m_config) {
                m_rootName = m_config->getRootName() + ".";
        }
        std::string m_pluginFile=API_LIB_PATH;

        char* pPath;
        pPath = getenv ("MOS_PATH");
        if (pPath!=NULL) {
                 m_pluginFile = pPath;
                 m_pluginFile += "/../lib/libDataAccessClientOPCUA.so";
        }

        std::string m_pluginClass="ptr_Plugin";
        DynamicLoader *m_pluginsLoader;
        //PluginInterfaceClientOPCUA *my_plugins;
        DataAccessClientOPCUA *my_plugins;
	m_nameSpace=2; // par defaut sur PLC d'ino

        m_pluginsLoader = new DynamicLoader(m_pluginFile, m_pluginClass);
                //my_plugins = m_pluginsLoader->loadAllSenderReceiverPlugins();
                my_plugins = m_pluginsLoader->load();
                if(my_plugins==NULL) {
                        ret = 1;
                }
                 else {
			int cpt=0;
			int flag=0;
			do {
				ret = my_plugins->connect(url);
				flag= ret;
				if(cpt==3) flag=0;
				cpt++;
			}
			while(flag==-1);
			if(ret!=-1) {
				m_plugins.push_back(my_plugins);
				m_pause = true;
        			m_forceStop=0;
        			m_stop = false;
				startRun();
			}
		}
		*status = ret;
}

Quasar_Manager::~Quasar_Manager() {
 	m_pause = false;
        m_stop = true;
        wait();
	//nnif(opcc) delete opcc;
}



int Quasar_Manager::close()
{
        int ret=0;
 	for (vector<DataAccessClientOPCUA *>::iterator it=m_plugins.begin(); it!=m_plugins.end(); ++it) {
                if(*it) {
                 ret = (*it)->disconnect();
                }
                else ret=-1;
                printf("\tsonde jl ici pluginClient->Close()\n");
        }
        return ret;

 	m_pause = true;
        return ret;
}


int Quasar_Manager::setVariable(std::string node,short value){
        node = m_rootName + node;
        int element=0;
        m_plugins[0]->setDatapoint(node,m_nameSpace,value);
        return element;
}

int Quasar_Manager::setVariable(std::string node,int value){
        node = m_rootName + node;
        int element=0;
        m_plugins[0]->setDatapoint(node,m_nameSpace,value);
        return element;
}

int Quasar_Manager::setVariable(std::string node,std::string value){
        node = m_rootName + node;
        int element=0;
        element = m_plugins[0]->setDatapoint(node,m_nameSpace,value);
        return element;
}

int Quasar_Manager::setVariable(std::string node,float value){
        node = m_rootName + node;
        int element=0;
        element = m_plugins[0]->setDatapoint(node,m_nameSpace,value);
        return element;
}


short int Quasar_Manager::getInt16Variable(std::string node){
	string finalnode = "";
 	short int element;
        ListElementQuasar* tempElement=NULL;
	if(m_config) tempElement = m_config->searchElement(node);
 	finalnode= m_rootName + tempElement->NodeId;
	m_plugins[0]->getDatapoint(finalnode,m_nameSpace,element);
	return element;
}

int Quasar_Manager::getIntVariable(std::string node){
	string finalnode = "";
 	int element;
        ListElementQuasar* tempElement=NULL;
	if(m_config) tempElement = m_config->searchElement(node);
 	finalnode= m_rootName + tempElement->NodeId;
	m_plugins[0]->getDatapoint(finalnode,m_nameSpace,element);
	return element;
}

bool Quasar_Manager::getBoolVariable(std::string node){
	string finalnode="";
 	bool elementBool;
        ListElementQuasar* tempElement=NULL;
	if(m_config) tempElement = m_config->searchElement(node);
 	finalnode= m_rootName + tempElement->NodeId;
	m_plugins[0]->getDatapoint(finalnode,m_nameSpace,elementBool);
	return elementBool;
}

float Quasar_Manager::getFloatVariable(std::string node){
	string finalnode="";
        bool elementFloat;
        ListElementQuasar* tempElement=NULL;
	if(m_config) tempElement = m_config->searchElement(node);
 	finalnode= m_rootName + tempElement->NodeId;
        m_plugins[0]->getDatapoint(finalnode,m_nameSpace,elementFloat);
        return elementFloat;
}
string  Quasar_Manager::getStringVariable(std::string node){
        string finalnode = "";
        ListElementQuasar* tempElement=NULL;
        string elementString;
	if(m_config) tempElement = m_config->searchElement(node);
 	finalnode= m_rootName + tempElement->NodeId;
        m_plugins[0]->getDatapoint(finalnode,m_nameSpace,elementString);
        return elementString;
}

int Quasar_Manager::subscribe(std::vector<ListElementQuasar*>* listSubscribe,MOS_CallbackInterface* MOS_callback) {
        int ret=0;
        std::vector<std::string> m_elements;
        std::vector<int> m_namespace;
        int count= listSubscribe->size();
        m_elements.resize(count);
        m_namespace.resize(count);

        for (int i=0; i<count; i++ ) {
                m_elements[i] = m_rootName + (*listSubscribe)[i]->NodeId;
                m_namespace[i] = atoi((*listSubscribe)[i]->NameSpace.c_str());
        }
	if(MOS_callback==NULL) printf("sonde jl pb NULL\n");
        m_plugins[0]->subscribe(m_elements,m_namespace,MOS_callback);
        return ret;
}

void *Quasar_Manager::run(void *params) {
        while (m_stop == false) {
                if (m_pause == false) {
                        usleep(100000);
		}
		 else {
                	usleep(1000000);
		}
        }
}

int  Quasar_Manager::startRun() {
        int ret=0;
        start(NULL);
        return ret;
}

