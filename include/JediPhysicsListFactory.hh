/*
 * JediPhysicsListFactory.hh
 *
 *  Created on: 13.01.2017
 *      Author: pmaanen
 */

#ifndef INCLUDE_JEDIPHYSICSLISTFACTORY_HH_
#define INCLUDE_JEDIPHYSICSLISTFACTORY_HH_
#include "JediHadronicPhysics.hh"
//Physics Lists
#include <G4VModularPhysicsList.hh>
#include <G4PhysListFactory.hh>
//Additional Physics
#include <G4EmParameters.hh>
#include <G4OpticalPhysics.hh>
#include <G4RadioactiveDecayPhysics.hh>
#include <G4StepLimiterPhysics.hh>
#include <G4HadronicProcessStore.hh>

class  JediPhysicsListFactory
{
public:
	static G4VModularPhysicsList *    Create();


private:
	JediPhysicsListFactory();
};


G4VModularPhysicsList *  JediPhysicsListFactory::Create()
{
	G4PhysListFactory theFactory;
	theFactory.SetVerbose(0);
	G4HadronicProcessStore::Instance()->SetVerbose(0);
//	auto the_physics=theFactory.GetReferencePhysList(JediConfigurationManager::Instance()->GetMap()["general.physics"].as<std::string>());
	auto the_physics=theFactory.GetReferencePhysList("QGSP_BERT");
	if(!the_physics){
//		std::string message=JediConfigurationManager::Instance()->GetMap()["general.physics"].as<std::string>()+" is not a known reference physics list.";
		std::string message="WhatTheHell is not a known reference physics list.";
		G4Exception("JediPhysicsListFactory::Create()","",FatalException,
				message.c_str());
	}
	the_physics->SetVerboseLevel(0);
	the_physics->RegisterPhysics(new JediHadronicPhysics(0));
	//the_physics->RegisterPhysics(new G4StepLimiterPhysics);
	/*
		auto em=G4EmParameters::Instance();
		em->SetMscStepLimitType(fUseDistanceToBoundary);
		em->SetMscRangeFactor(0.02);
		em->SetMinEnergy(1000*CLHEP::eV);
		em->SetMaxEnergy(5*CLHEP::GeV);
		em->SetNumberOfBins(400);
		em->SetSpline(true);
	 */
	return the_physics;
}




#endif /* INCLUDE_JEDIPHYSICSLISTFACTORY_HH_ */
