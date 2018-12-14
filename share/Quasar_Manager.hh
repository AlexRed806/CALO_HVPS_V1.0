#ifndef Quasar_Manager_H_
#define Quasar_Manager_H_

#include <vector>
#include <map>
#include <cstring>
#include <string>
#include "lappThread.h"

class DataAccessClientOPCUA;
class MOS_CallbackInterface;
class ConfigQuasar;
class ListElementQuasar;

using namespace std;
typedef std::vector<std::string> list_t;

class Quasar_Manager : public LAPPThread {
        static Quasar_Manager *singleton;  // pointeur vers le singleton
public:
 	static Quasar_Manager *getInstance();

	Quasar_Manager(std::string url,int *status);
	~Quasar_Manager();
    	int subscribe(std::vector<ListElementQuasar*>* listSubscribe,MOS_CallbackInterface* MOS_callback);
    	int close();
    	void* run(void *params);

	int getIntVariable(std::string node);
	short int getInt16Variable(std::string node);
        bool getBoolVariable(std::string node);
	float getFloatVariable(std::string node);
	string getStringVariable(std::string node);

        int setVariable(std::string node,int value);
	int setVariable(std::string node,std::string value);
        int setVariable(std::string node,float value);
        int setVariable(std::string node,short value);
private:
	vector<string> t_url;
	vector<DataAccessClientOPCUA*> m_plugins;
        int  startRun();
        int m_stop;
        int m_pause;
	int m_forceStop;
        ConfigQuasar *m_config;
	map<string, list_t> m_listGetStatus;

        int m_nameSpace;
        string m_rootName;
	string m_url;
};

#endif //  Quasar_Manager_H_
