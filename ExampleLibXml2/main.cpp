/**
 *******************************************************************************
 *
 * @file    servermain.c
 * @authors panazol@lapp.in2p3.fr
 * @date    25/04/2014
 * @Modif   12/05/2016
 * @version v2.0.0
 * @brief description :
 *     main file for the M.O.S. (Multipurpose Opcua Server) application.
 * 
 *
 * @details
 *  <full description...>
 * 12/05/2016 --> disable muti namespace in this server in order to allow some API clients (ex labview)  who 
 *                to access at this server (can't use diferents namespace). 
 *------------------------------------------------------------------------------
 *
 * @copyright Copyright � 2014, LAPP/CNRS
 *
 *
 *******************************************************************************
 */


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "string"
#include <iostream>

#include "ExampleLibXml2.h"

void usage() {
	printf("\nUsage : ExampleLibXml2 -f <Description XmlFile>\n");
}

int main(int argc, char **argv) {
    	std::cout << "RUNNING DEBUG PROGRAM : for testing exampleLibXml2" << std::endl;
	int ret = 0;
	int c;
	std::string descriptionFile="test.xml";

	opterr = 0;
	while ((c = getopt(argc, argv, "f:?h")) != -1)
		switch (c) {
		case 'f':
			descriptionFile = optarg;
			break;
		case '?':
		case 'h':
			usage();
			return 1;
		default:
			usage();
			return 1;
	}
    	std::cout << "Open " << descriptionFile << std::endl;
	ExampleLibXml2 * testLibXml2 = new ExampleLibXml2(descriptionFile);

	std::cout << "RootName = " << testLibXml2->getRootName() << std::endl;
	std::cout << "getOpcUaRef = " << testLibXml2->getOpcUaRef() << std::endl;
	std::vector<ListElement*>* m_list = testLibXml2->getListElements();

        int count= m_list->size();
        for (int i=0; i<count; i++ ) {
		std::cout << " ********************************************* " << std::endl;
		std::cout << "Name        = " << (*m_list)[i]->Name << std::endl;
		std::cout << "Description = " << (*m_list)[i]->Description << std::endl;
		std::cout << "NameSpace   = " << (*m_list)[i]->NameSpace << std::endl;
		std::cout << "NodeId      = " << (*m_list)[i]->NodeId << std::endl;
		std::cout << "Type        = " << (*m_list)[i]->Type << std::endl;
		std::cout << " ********************************************* " << std::endl;
	}
}
