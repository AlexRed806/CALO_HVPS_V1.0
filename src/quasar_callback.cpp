#include "quasar_callback.h"
#include "pluginsBase.h"
#include "CALO_HVPS.h"
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include <cmath>


// global pour le test flip/flop sur un datapoint
int t;

Quasar_Callback::Quasar_Callback(){
                t = 0;
}

void Quasar_Callback::infoDebug() {
	printf("info debug\n");
}

Quasar_Callback::Quasar_Callback(CALO_HVPS *hvCalo){
                m_hvCalo = hvCalo;
}

void Quasar_Callback::abort() {
}

void  Quasar_Callback::dataChange(std::vector<std::string> listElements, std::vector<std::string> listValues) {
        int count=(int)listElements.size();
	std::string elementS;
	std::string elementS1;

        for (int i=0; i<count; i++ ) {
		 if((listElements[i].find("V0Set") !=std::string::npos) ||
		   (listElements[i].find("V1Set") !=std::string::npos) ||
		   (listElements[i].find("I1Set") !=std::string::npos) ||
		   (listElements[i].find("I0Set") !=std::string::npos) ||
		   (listElements[i].find("TripExt") !=std::string::npos) ||
		   (listElements[i].find("PDWn") !=std::string::npos) ||
		   (listElements[i].find("RUp") !=std::string::npos) ||
		   (listElements[i].find("Temp") !=std::string::npos) ||
		   (listElements[i].find("HVMax") !=std::string::npos) ||
		   (listElements[i].find("SVMax") !=std::string::npos) 
		)
 		{
			std::size_t pos = listElements[i].find("board");      // position of "live" in str
  			std::string str3 = listElements[i].substr (pos);  
		 	elementS = "CMS.CALO_HVPS.";
		 	elementS += str3;


			pos = listElements[i].find_last_of(".");      // position of "live" in str
  			str3 = listElements[i].substr (pos);  
		 	elementS += str3;

		 	elementS += "_v";
			float valueF=atof(listValues[i].c_str());
			m_hvCalo->getDataAccessClientOPCUARef()->setDatapoint(elementS.c_str(),2,valueF);
		}
		else {
			if((listElements[i].find(".Status") !=std::string::npos) ||
			   (listElements[i].find(".Trip") !=std::string::npos) ||
			   (listElements[i].find(".BdStatus") !=std::string::npos) ||
		       	   (listElements[i].find(".channelCount") !=std::string::npos) ||
			   (listElements[i].find(".TripInt") !=std::string::npos) 
			)
			{
	                        std::size_t pos = listElements[i].find("board");      // position of "live" in str
	                        std::string str3 = listElements[i].substr (pos);
		 		elementS = "CMS.CALO_HVPS.";
	                        elementS += str3;
	                        pos = listElements[i].find_last_of(".");      // position of "live" in str
	                        str3 = listElements[i].substr (pos);
	                        elementS += str3;
	                        elementS += "_v";
	                        int  valueI=atoi(listValues[i].c_str());
	                        m_hvCalo->getDataAccessClientOPCUARef()->setDatapoint(elementS.c_str(),2,valueI);
			}
			else {
		   		if((listElements[i].find(".IMon") !=std::string::npos) ||
		        	   (listElements[i].find(".VMon") !=std::string::npos) 
				){
					std::size_t pos = listElements[i].find("board");      // position of "live" in str
  					std::string str3 = listElements[i].substr (pos);  
		 			elementS = "CMS.CALO_HVPS.";
		 			elementS += str3;
					elementS1 = elementS;
					float valueResolution=0;
				 	float valueNew=atof(listValues[i].c_str());
				 	float valueOld=0;
					float diff=0;

					pos = listElements[i].find_last_of(".");      // position of "live" in str
  					str3 = listElements[i].substr (pos);  
		 			elementS += str3;

		 			elementS += "_v";
		 			elementS1 += "._ResolutionDataChange";
					std::string valueString;
					m_hvCalo->getDataAccessClientOPCUARef()->getDatapoint(elementS1.c_str(),5,valueString);
					if(valueString.find("%") != std::string::npos) {
						pos = listElements[i].find("%");
						valueResolution = atof(valueString.substr(0,pos).c_str());
						m_hvCalo->getDataAccessClientOPCUARef()->getDatapoint(elementS.c_str(),2,valueOld);
						valueResolution= valueOld * valueResolution /100;
					}
					else {
						m_hvCalo->getDataAccessClientOPCUARef()->getDatapoint(elementS.c_str(),2,valueOld);
						valueResolution = atof(valueString.c_str());
					}
					diff=fabs(valueNew-valueOld);
					if(diff>valueResolution) 
						m_hvCalo->getDataAccessClientOPCUARef()->setDatapoint(elementS.c_str(),2,valueNew);
				}
				else   {
 					if((listElements[i].find(".IPAddr") !=std::string::npos) || 
		        	   	   (listElements[i].find(".MemoryStatus") !=std::string::npos)  ||
		        	   	   (listElements[i].find(".HVFanStat") !=std::string::npos) ||
		        	   	   (listElements[i].find(".SwRelease") !=std::string::npos) ||
		        	   	   (listElements[i].find(".SymbolicName") !=std::string::npos) ||
		        	   	   (listElements[i].find(".PWFanStat") !=std::string::npos) ||
		        	   	   (listElements[i].find(".PWVoltage") !=std::string::npos) ||
		        	   	   (listElements[i].find(".PWCurrent") !=std::string::npos) ||
		        	   	   (listElements[i].find(".description") !=std::string::npos) ||
		        	   	   (listElements[i].find(".firmwareRelease") !=std::string::npos) ||
		        	   	   (listElements[i].find(".model") !=std::string::npos) ||
		        	   	   (listElements[i].find(".serialNumber") !=std::string::npos) 
                        		)
                        		{
                        		        std::size_t pos ; // = listElements[i].find("board");      // position of "live" in str
                        		        std::string str3 ;
                        		        pos = listElements[i].find(".");      // position of "live" in str
                        		        str3= listElements[i].substr (pos);
						if((listElements[i].find("board08.firmwareRelease") !=std::string::npos) ||
		        	   	   		(listElements[i].find(".model") !=std::string::npos) ||
		        	   	   		(listElements[i].find(".channelCount") !=std::string::npos) ||
		        	   	   		(listElements[i].find(".description") !=std::string::npos) ||
		        	   	   		(listElements[i].find(".serialNumber") !=std::string::npos) 
						)
						{
                        		        	elementS = "CMS.CALO_HVPS.";
							pos = listElements[i].find("board");      // position of "live" in str
                        		        	str3= listElements[i].substr (pos);
						}
						else {
                        		        	elementS = "CMS.CALO_HVPS";
                        		        	pos = listElements[i].find(".");      // position of "live" in str
                        		        	str3= listElements[i].substr (pos);
						}

                        		        elementS += str3;
                        		        pos = listElements[i].find_last_of(".");      // position of "live" in str
                        		        str3 = listElements[i].substr (pos);
                                		elementS += str3;
                                		elementS += "_v";
                                		//int  valueI=atoi(listValues[i].c_str());
                                		m_hvCalo->getDataAccessClientOPCUARef()->setDatapoint(elementS.c_str(),2,listValues[i]);
                        		}
				}
			}

		}
        }

        t+=1;
        bool element = (t%2);
        m_hvCalo->getDataAccessClientOPCUARef()->setDatapoint("CMS.CALO_HVPS.Test.Test_v",2,element);
}

