#ifndef CALO_HVPS_H_
#define CALO_HVPS_H_ 

#include "pluginsBase.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

class Quasar_Manager;
class ConfigQuasar;
class Quasar_Callback;

class CALO_HVPS: public PluginsBase {
public:
    
	CALO_HVPS();
	int init(const std::string& chaine);
	int close();
	int cmd(const std::string& chaine, int commandStringAck,
			std::string& result);
	int afterStart();
	int cmdAsynch(const std::string& command, int commandStringAck,
			const std::string& datapointName, int nameSpace,
			std::string& result);
	int get(const std::string& chaine, int commandStringAck,
			std::vector<boost::any>& tabValue);
	int set(const std::string& chaine, int commandStringAck,
			std::vector<boost::any>& tabValue);
private:
	int set(const std::string& chaine, int commandStringAck);
	int get(const std::string& chaine, int commandStringAck,
			std::string& result);

	Quasar_Manager *m_quasar_manager;
	std::string m_quasar_address;
	ConfigQuasar *m_config;
	Quasar_Callback *my_callBack;

	int startChannel(const std::string &element);
	int startAndStopChannel(const std::string &element,int ieration);
	int stopChannel(const std::string &element);
	int setChannel(const std::string &element, const std::string &voltage);
	int setFan(const std::string &element,const std::string  &fan);
	int setRamp(const std::string &element, const std::string &rampUp,
			const std::string &rampDwn);
    
public:
    struct optical_module{

        struct electronic_channel{
            unsigned short int crate;
            unsigned short int board;
            unsigned short int channel;
        };
        struct location_channel{
            unsigned short int row;
            unsigned short int column;
        };
        std::map<electronic_channel,location_channel> channel_mapping;

        int om_id;
        int om_number;
        int nominal_voltage;
    };
    optical_module _optical_module_;
    std::vector<optical_module> optical_modules;
    
};
#endif //  CALO_HVPS_H__
