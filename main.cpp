////////////////////////////////////////////////////////////////////////////
/// @mainpage Smart bugs
/// 
///
#include <vector>
#include <boost/shared_ptr.hpp>
#include <string>
#include <iostream>
#include <istream>
#include "utils.h"
#include "field.h"
#include "bugsuper.h"
#include "cockroach.h"
#include "bugSVer.h"
#include "exept.h"
bool IsDead(boost::shared_ptr<bug> ptrToBug)
{
    return !ptrToBug->GetTimeOfLiving();
}
int main(int argc, char *argv[])
{
    std::string strMapFile;
    if(argc != 2)
    {
    	std::cout << "Error opening source file";
    	return 1;
    }

    if(argc == 2)
    {
		strMapFile = argv[1];

		if((strMapFile.find("-h") < strMapFile.size()) 
		 ||(strMapFile.find("--help") < strMapFile.size()))
		{
    		std::cout << "Smart Bugs. Version "<< __APP_VERSION__ << std::endl << std::endl;
    		std::cout << "Usage  :  bugs.exe [options]" << std::endl
    			  << "          bugs.exe <Map_file>" << std::endl
    			  << "Enabled options:"<< std::endl<<"----------------"<< std::endl
    			  << "          -h   OR  --help "<< std::endl
    			  << "          Print this help message "<< std::endl<< std::endl
    			  << "          -v   OR   --version "<< std::endl
    			  << "          Print version number "<< std::endl<< std::endl;
    		return 1;
    	}
		if((strMapFile.find("-v") < strMapFile.size()) 
		 ||(strMapFile.find("--version") < strMapFile.size()))
		{
    		std::cout << "Smart Bugs. Version "<< __APP_VERSION__ << std::endl << std::endl;
    		return 1;
    	}
    	if((strMapFile.find("-") == 0) 
		 ||(strMapFile.find("--") == 0))
		{
    		std::cout << "Unknown command line option "<< strMapFile << std::endl << std::endl;
			return 1;
		}
    }

   	
   	// Initializing of the map
   	Field fField;
   	try
   	{ 
		fField.LoadField(strMapFile);    	
    }
    catch(eExeption exept)
    {
		std::cout << "Error: "<< exept.ExeptionStr()<< std::endl << std::endl;
		return 1;
    }

	
    // Vector for storing bugs
    std::vector<boost::shared_ptr<bug> > vecPtrToBugsOntheField;
    // Let's init some Cockroaches
    for(unsigned int iTmp = 0;iTmp < fField.GetNumberOfBugs(); ++iTmp)
    {
        vecPtrToBugsOntheField.push_back(boost::shared_ptr<BugCockroach>(new BugCockroach));
        vecPtrToBugsOntheField[iTmp]->Initialize(fField.GetBugName(iTmp), iTmp + 1,
                BugActions::eStaying, 100);
    }
    // while we have a Cockroaches on the map
    while(!vecPtrToBugsOntheField.empty())
    {
        std::vector<boost::shared_ptr<bug> >::iterator itCurrentBug;
        for(itCurrentBug = vecPtrToBugsOntheField.begin();
                itCurrentBug < vecPtrToBugsOntheField.end(); ++ itCurrentBug)
        {
            // coacroach is testing all around
            (*itCurrentBug)->GetField(fField);
            // after that we are getting the Bug's action
            fField.AskToBug((*itCurrentBug)->WhatDoYouWhantToDo(),
                            (*itCurrentBug)->GetBugNum());
        }
        std::vector<boost::shared_ptr<bug> >::iterator itDeadBug
        = std::find_if(vecPtrToBugsOntheField.begin(),vecPtrToBugsOntheField.end(),IsDead);
        if(itDeadBug != vecPtrToBugsOntheField.end())
        {
            fField.RemoveBug((*itDeadBug)->GetBugNum());
            vecPtrToBugsOntheField.erase(itDeadBug);
        }
        if(fField.IsAnyBugAtTheExit())
        {
            unsigned int nBugAtTheExit = fField.WhatBugIsOntheExit();
            for(std::vector<boost::shared_ptr<bug> >::iterator itBugAtTheExit = vecPtrToBugsOntheField.begin();
                    itBugAtTheExit != vecPtrToBugsOntheField.end(); ++itBugAtTheExit)
            {
                if((*itBugAtTheExit)->GetBugNum() == nBugAtTheExit)
                {
                    vecPtrToBugsOntheField.erase(itBugAtTheExit);
                    fField.RemoveBug(nBugAtTheExit);
                    break;
                }
            }
        }
    }
    return 0;
}
