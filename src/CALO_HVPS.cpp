#include "Quasar_Manager.hh"
#include "CALO_HVPS.h"
#include "quasar_callback.h"
#include "ConfigQuasar.h"

#define NB_MAX_MODULE 13
#define NB_MAX_CHANNEL 32
#define FIRST_INDEX_MODULE 0
#define FIRST_INDEX_CHANNEL 0

using namespace std;

CALO_HVPS::CALO_HVPS() {
//	m_config = ConfigQuasar::getInstance("/var/tmp/SNEMO/CALORIMETER/CALO_HVPS/Quasar.xml");
	m_config = ConfigQuasar::getInstance("/home/user/dev/OPCUA_SL6/OPCUA_LAPP/trunk/example/0_Tutorial/2_UsePlugins/CALO_HVPS_V1.0/Quasar.xml");
	m_quasar_manager=NULL;
}

int CALO_HVPS::get(const std::string& chaine,int commandStringAck, std::vector<boost::any>& tabValue) {
    int ret=0;
    std::string result;
    if(!chaine.empty()) {
        get(chaine,commandStringAck,result);
        tabValue.resize(1);
        
        // debug dans notre cas toujours un floatant renvoye
        float val;
        val = atof(result.c_str());
        (tabValue)[0] = val;
        
        if(string *pstr = boost::any_cast<string>(&(tabValue)[0])){
            printf("sonde jl string \n");
            (tabValue)[0]=(string) result.c_str();
        }
        else if (int *pi = boost::any_cast <int> (&(tabValue)[0]))
        {
            printf("sonde jl int \n");
            (tabValue)[0] = (int) atoi(result.c_str());
        }
        else if (float *pi = boost::any_cast <float> (&(tabValue)[0]))
        {
            printf("sonde jl float \n");
            (tabValue)[0] = (float) atof(result.c_str());
        }
        else if (double *pi = boost::any_cast <double> (&(tabValue)[0]))
        {
            printf("sonde jl double\n");
            (tabValue)[0] = (double) atof(result.c_str());
        }
        else if (short int *pi = boost::any_cast <short int> (&(tabValue)[0]))
        {
            printf("sonde jl short int \n");
            (tabValue)[0] = (short int) atoi(result.c_str());
        }
        else if (long *pi = boost::any_cast <long> (&(tabValue)[0]))
        {
            printf("sonde jl long \n");
            (tabValue)[0] = (long) atol(result.c_str());
        }
        else if (bool *pi = boost::any_cast <bool> (&(tabValue)[0]))
        {
            printf("sonde jl bool \n");
            (tabValue)[0]= (bool) atoi(result.c_str()) ;
        }
        else
        {
        }
    }
    else ret = 1;
    
    return ret;
}

int CALO_HVPS::get(const std::string& chaine, int commandStringAck,std::string& result) {
	int ret=0;
	printf("sonde jl CALO_HVPS::get\n");
	result="test";
    return ret;
}

int CALO_HVPS::set(const std::string& chaine, int commandStringAck) {
    int ret = 0;
	printf("sonde jl CALO_HVPS::set\n");
    std::string result;
    return ret;
}

int CALO_HVPS::set(const std::string& l_chaine,int commandStringAck, std::vector<boost::any>& tabValue){
        int ret=0;
	 std::string chaine=l_chaine;
        if(string *pstr = boost::any_cast<string>(&tabValue[0])){
                        chaine += " ";
                        chaine += *pstr;
                }
                else if (int *pi = boost::any_cast <int> (&tabValue[0]))
                {
                        chaine += " ";
                        chaine += *pi;
                }
                else if (float *pi = boost::any_cast <float> (&tabValue[0]))
                {
                        chaine += " ";
                        chaine += *pi;
                }
                else if (double *pi = boost::any_cast <double> (&tabValue[0]))
                {
                        chaine += " ";
                        chaine += *pi;
                }
                else if (short int *pi = boost::any_cast <short int> (&tabValue[0]))
                {
                        chaine += " ";
                        chaine += *pi;
                }
                else if (long *pi = boost::any_cast <long> (&tabValue[0]))
                {
                        chaine += " ";
                        chaine += *pi;
                }
                else if (bool *pi = boost::any_cast <bool> (&tabValue[0]))
                {
                        chaine += " ";
                        chaine += *pi;
                }
                else
                {
                        printf(" unknown type\n");
                }
	set(chaine,commandStringAck);
    return ret;
}


int CALO_HVPS::init(const std::string& l_chaine) {
    printf("sonde jl TCP_Plugin::init() avec chaine=%s\n",l_chaine.c_str());
    // Mandatory always need
    PluginsBase::init(l_chaine);
    
    
    ///////////   This part is to fill the mapping and reference values of OMs, added by Alessandro (not sure it should go here)   ///////////
    
    ifstream inFile;

    inFile.open("calorimeter.map",ios::in);

    std::string str_file_line;

    while (inFile) {
        
        getline(inFile, str_file_line);
        
        if(str_file_line.compare(0,1,"M") == 0) {
            
            optical_module _optical_module_;
            
            string str_row = str_file_line.substr(5,2);
            _optical_module_._location_channel_.row = atoi((str_row).c_str());
            
            string str_column = str_file_line.substr(8,2);
            _optical_module_._location_channel_.column = atoi((str_column).c_str());
            
            string str_crate = str_file_line.substr(14,1);
            _optical_module_._electronic_channel_.crate = atoi((str_crate).c_str());
            
            string str_board = str_file_line.substr(16,2);
            _optical_module_._electronic_channel_.board = atoi((str_board).c_str());
            
            string str_channel = str_file_line.substr(19,2);
            _optical_module_._electronic_channel_.channel = atoi((str_channel).c_str());
            
            int file_line_length = std::distance(str_file_line.begin(),str_file_line.end());
            
            std::string str_voltage = str_file_line.substr(file_line_length-4,4);
            _optical_module_.nominal_voltage = atoi((str_voltage).c_str());
            
            optical_modules.push_back(_optical_module_);
        }
    }
    inFile.close();
    

    
    /*for(int i_module = FIRST_INDEX_MODULE; i_module < NB_MAX_MODULE; i_module++) {
        
        for(int i_ch = FIRST_INDEX_CHANNEL; i_ch < NB_MAX_CHANNEL; i_ch++) {

            
            ifstream inFile;

            inFile.open("calorimeter.map");
            string strOneLine;
            
            while (inFile) {
                
                getline(inFile, strOneLine);
                
                if(strOneLine.compare(0,1,"#"))
                    std::cout << strOneLine << endl;
                else std::cout <<"Ciao bello"<<std::endl;
            }
            
            inFile.close();
      
        }
    }*/
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    std::string chaine=l_chaine;
    int ret=0;
    chaine = chaine + " ";
    std::string::size_type pos;
    std::string valueString;
    std::string nameString;
    std::string subChaine1 = chaine;
    std::string subChaine2 = chaine;
    int flag=1;
    while (flag) {
        subChaine1 = subChaine2;
        pos = subChaine2.find(' '); // cherche separateur ' '
        if (pos == std::string::npos) // il n'y a plus : alors on sort
        flag = 0;
        else {
            subChaine1.erase(pos); // isole le binome name:value
            subChaine2.erase(0, pos + 1); // reste
            
            valueString = subChaine1;
            nameString = subChaine1;
            pos = valueString.find_first_of(':'); // caratere separateur name:value = ':'
            if (pos != std::string::npos) {
                nameString.erase(pos); // isole dans le biname name
                valueString.erase(0, pos + 1); // isole dans le binome value
                // et maintenant on traite
                if(nameString.compare("Address") ==0) {
                    m_quasar_address= valueString.c_str();
                }
            }
        }
    }
    return ret;
}

int CALO_HVPS::afterStart() {
	int ret=0;
	std::string resultCall;
	std::string currentAz;
	std::string element;
	int status_PLC_Connection;
	my_callBack=NULL;
// Mandatory allways need 
	ret = PluginsBase::afterStart();

 	m_quasar_manager= new Quasar_Manager(m_quasar_address,&status_PLC_Connection);
	std::vector<ListElementQuasar*>* tempListSubscribe = m_config->getListElementQuasars();
                
	my_callBack = new Quasar_Callback(this);
	if(m_quasar_manager){
		m_quasar_manager->subscribe(tempListSubscribe,my_callBack);
	}
	return ret;
}

int CALO_HVPS::cmdAsynch(const std::string& command, int commandStringAck, const std::string& datapointName, int nameSpace, std::string& result) {
	int ret=0;

	return ret;
}


int CALO_HVPS::close() {
        int ret=0;
        std::string retValue;
        return ret;
}

int CALO_HVPS::startChannel(const std::string &element) {
	int ret=0;
	std::string elementFinal = element;
	elementFinal +=".Pw";
	ret = m_quasar_manager->setVariable(elementFinal.c_str(),1);
	return ret;
}


int CALO_HVPS::startAndStopChannel(const std::string &element,const int iteration) {
	int ret=0;
	std::string elementFinal = element;
	elementFinal +=".Pw";
    for(int i=0 ; i<iteration ; i++) {
	ret = m_quasar_manager->setVariable(elementFinal.c_str(),1);
	//wait(100);
    ret = m_quasar_manager->setVariable(elementFinal.c_str(),0);
    }
	return ret;
}



int CALO_HVPS::stopChannel(const std::string &element) {
        int ret=0;
        std::string elementFinal = element;
        elementFinal +=".Pw";
        ret = m_quasar_manager->setVariable(elementFinal.c_str(),0);
        return ret;
}

int CALO_HVPS::setChannel(const std::string &element,const std::string &voltage) {
	int ret=0;
	int error=0;
	std::string elementFinal = element;
                                                
	elementFinal +=".V0Set";
	float voltageF= atof(voltage.c_str());
	ret = m_quasar_manager->setVariable(elementFinal,voltageF);
	if(ret) error=1;


        /*elementFinal = element;
        elementFinal +=".RUp";
        float rampF= atof(ramp.c_str());
        ret = m_quasar_manager->setVariable(elementFinal,rampF);
        if(ret) error=1;
	

        elementFinal = element;
        elementFinal +=".PDwn";
        int  pdnI= 10;
        ret = m_quasar_manager->setVariable(elementFinal,pdnI);
        if(ret) error=1;
*/
	return error;
}


int CALO_HVPS::setRamp(const std::string &element,const std::string &rampUp,const std::string &rampDwn) {
        int ret=0;
        int error=0;
        std::string elementFinal = element;

        elementFinal = element;
        elementFinal +=".RUp";
        float rampF= atof(rampUp.c_str());
        ret = m_quasar_manager->setVariable(elementFinal,rampF);
        if(ret) error=1;


        elementFinal = element;
        elementFinal +=".RDWn";
        rampF= atof(rampUp.c_str());
        ret = m_quasar_manager->setVariable(elementFinal,rampF);
        if(ret) error=1;
        return error;
}

int CALO_HVPS::setFan(const std::string &element,const std::string  &fan) {
        int ret=0;
        int error=0;
        std::string elementFinal = element;
printf("sonde jl CALO_HVPS::setFan\n");

        elementFinal = element;
        elementFinal +="HVFanSpeed";
        int value = atoi(fan.c_str());
        ret = m_quasar_manager->setVariable(elementFinal,value);
        if(ret) error=1;
        return error;
}



int CALO_HVPS::cmd(const std::string& command, int commandStringAck, std::string& result) {
    
    int ret=0;
    std::string result2="";
    result ="";
    std::string chaine = command + " ";
    std::string::size_type pos;
    std::string valueString;
    std::string nameString;
    std::string subChaine1 = chaine;
    std::string subChaine2 = chaine;
    int boardNumber=1;
    std::string fan="0";
    int channelNumber=0;
    int iteration=1;
    std::string voltage;
    std::string rampUp, rampDwn;
    int columnNumber = 0; //Ale
    int rowNumber = 0; //Ale
    int flag=1;
    printf("command=%s\n",command.c_str());
    while (flag) {
        subChaine1 = subChaine2;
        pos = subChaine2.find(' '); // cherche separateur ' '
        if (pos == std::string::npos) // il n'y a plus : alors on sort
            flag = 0;
        
        else {
            subChaine1.erase(pos); // isole le binome name:value
            subChaine2.erase(0, pos + 1); // reste
            
            valueString = subChaine1;
            nameString = subChaine1;
            pos = valueString.find_first_of(':'); // caratere separateur name:value = ':'
            if (pos != std::string::npos) {
                nameString.erase(pos); // isole dans le biname name
                valueString.erase(0, pos + 1); // isole dans le binome value
                // et maintenant on traite
                if(nameString.compare("board") ==0) {
                    boardNumber = atoi(valueString.c_str());
                }
                if(nameString.compare("channel") ==0) {
                    channelNumber = atoi(valueString.c_str());
                }
                if(nameString.compare("iteration") ==0) {
                    iteration = atoi(valueString.c_str());
                }
                if(nameString.compare("voltage") ==0) {
                    voltage = valueString.c_str();
                }
                if(nameString.compare("rampUp") ==0) {
                    rampUp = valueString.c_str();
                }
                if(nameString.compare("rampDwn") ==0) {
                    rampDwn = valueString.c_str();
                }
                if(nameString.compare("valueFan") ==0) {
                    fan = valueString.c_str();
                }
                if(nameString.compare("row") ==0) {
                    rowNumber = atoi(valueString.c_str());
                }
                if(nameString.compare("column") ==0) {
                    columnNumber = atoi(valueString.c_str());
                }
            } else {
                //ret=1;
            }
        }
    }
    char RacineElementCh[200];
    char RacineElementBoard[200];
    std::string element;
    if(chaine.find("SetFan")==0) setFan(RacineElementCh,fan);
    
    if((chaine.find("StartChannel")==0) ||
       (chaine.find("StopChannel")==0) ||
       (chaine.find("SetRamp")==0) ||
       (chaine.find("StartAndStop")==0) ||
       (chaine.find("SetChannel")==0)
       )
    {
        if(boardNumber==-1) {
            for(int i=(FIRST_INDEX_MODULE); i<(NB_MAX_MODULE - FIRST_INDEX_MODULE); i++) {
                sprintf(RacineElementBoard,"board%02d",i);
                if(channelNumber==-1) {
                    for(int j=(FIRST_INDEX_CHANNEL); j<(NB_MAX_CHANNEL - FIRST_INDEX_CHANNEL); j++) {
                        sprintf(RacineElementCh,"%s.channel%02d",RacineElementBoard,j);
                        if(chaine.find("StartChannel")==0) startChannel(RacineElementCh);
                        if(chaine.find("StartAndStopChannel")==0) startAndStopChannel(RacineElementCh,iteration);
                        if(chaine.find("StopChannel")==0) stopChannel(RacineElementCh);
                        if(chaine.find("SetChannel")==0) setChannel(RacineElementCh,voltage);
                        if(chaine.find("SetRamp")==0) setRamp(RacineElementCh,rampUp,rampDwn);
                    }
                }
                else {
                    sprintf(RacineElementCh,"%s.channel%02d",RacineElementBoard,channelNumber);
                    if(chaine.find("StartChannel")==0) startChannel(RacineElementCh);
                    if(chaine.find("StartAndStopChannel")==0) startAndStopChannel(RacineElementCh,iteration);
                    if(chaine.find("StopChannel")==0) stopChannel(RacineElementCh);
                    if(chaine.find("SetChannel")==0) setChannel(RacineElementCh,voltage);
                    if(chaine.find("SetRamp")==0) setRamp(RacineElementCh,rampUp,rampDwn);
                }
            }
        }
        else {
            sprintf(RacineElementBoard,"board%02d",boardNumber);
            if(channelNumber==-1) {
                for(int j=(FIRST_INDEX_CHANNEL); j<(NB_MAX_CHANNEL - FIRST_INDEX_CHANNEL); j++) {
                    sprintf(RacineElementCh,"%s.channel%02d",RacineElementBoard,j);
                    if(chaine.find("StartChannel")==0) startChannel(RacineElementCh);
                    if(chaine.find("StopChannel")==0) stopChannel(RacineElementCh);
                    if(chaine.find("SetChannel")==0) setChannel(RacineElementCh,voltage);
                    if(chaine.find("SetRamp")==0) setRamp(RacineElementCh,rampUp,rampDwn);
                }
            }
            else {
                sprintf(RacineElementCh,"%s.channel%02d",RacineElementBoard,channelNumber);
                if(chaine.find("StartChannel")==0) startChannel(RacineElementCh);
                if(chaine.find("StopChannel")==0) stopChannel(RacineElementCh);
                if(chaine.find("SetChannel")==0) setChannel(RacineElementCh,voltage);
                if(chaine.find("SetRamp")==0) setRamp(RacineElementCh,rampUp,rampDwn);
            }
        }
    }
    
    /////// Ale
    if((chaine.find("SetNominalCol")==0) ||
       (chaine.find("SetNominalRow")==0) ||
       (chaine.find("SetNominalAll")==0) ) {
        
        for(std::vector<optical_module>::iterator it = optical_modules.begin(); it != optical_modules.end(); ++it) {

            sprintf(RacineElementBoard,"board%02d",*it.electronic_channel.board);
            sprintf(RacineElementCh,"%s.channel%02d",RacineElementBoard,*it.electronic_channel.channel);

            if( ( *it.location_channel.column == columnNumber && chaine.find("SetNominalCol")==0 )
               || ( *it.location_channel.row == rowNumber && chaine.find("SetNominalRow")==0 )
               || chaine.find("SetNominalAll")==0 ) {
                
                setChannel(RacineElementCh,*it.nominal_voltage);
                startChannel(RacineElementCh);
            }
        }
    }
    /////// end Ale
    
    return ret;
    
}

// becarefull :  allways need : allow to connect this Plugin with MOS 
extern "C" {
CALO_HVPS *make_protocole1() {
	return new CALO_HVPS();
}
}

