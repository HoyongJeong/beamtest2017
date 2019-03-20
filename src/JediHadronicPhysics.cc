/*
 * JediHadronicPhysics.cc
 *
 *  Created on: 13.01.2017
 *      Author: pmaanen
 */

#include <JediHadronicPhysics.hh>
//#include "JediBreakupProcess.hh"
#include <G4ProcessManager.hh>
//#include <JediFakeCrossSectionData.hh>
#include <JediElasticCrossSectionData.hh>
//#include <JediBreakupCrossSectionData.hh>
#include <G4IonTable.hh>
//#include <JediConfigurationManager.hh>
#include <JediDeuteronElasticProcess.hh>
//#include "JediStudiedProcess.hh"
JediHadronicPhysics::JediHadronicPhysics(G4int ver):G4VPhysicsConstructor("Jedi") {

	fMessenger=std::unique_ptr<G4GenericMessenger>(new G4GenericMessenger(this,"/PolarimeterStudies/hadronic/"));

	verboseLevel=ver;

	fMessenger->DeclareProperty("verboseLevel",JediHadronicPhysics::verboseLevel,"");

//	fUseFastSim=JediConfigurationManager::Instance()->GetMap()["physics.use_fast_sim"].as<bool>();
	fUseFastSim=false;


//	if(JediConfigurationManager::Instance()->GetVerbose()>2)
	if(ver>2)
		G4cout<<"JediHadronicPhysics::JediHadronicPhysics()"
		<<G4endl;
}

void JediHadronicPhysics::ConstructParticle() {
	G4GenericIon::GenericIonDefinition();
	G4Deuteron::DeuteronDefinition();
}

void JediHadronicPhysics::ConstructProcess() {
	auto elasticProcess=new JediDeuteronElasticProcess;
	elasticProcess->RegisterModel(new JediDeuteronElastic);
//	JediStudiedProcess* wrapperProcess=nullptr;
//	if(fUseFastSim){
//		elasticProcess->AddDataSet(new JediFakeCrossSectionData);
//		wrapperProcess=new JediStudiedProcess;
//		wrapperProcess->RegisterProcess(elasticProcess);
//		if(JediConfigurationManager::Instance()->GetVerbose()>2)
//			G4cout<<"JediHadronicPhysics::ConstructProcess()"
//			<<" using wrapper process"
//			<<G4endl;
//	}
//	else{
		elasticProcess->AddDataSet(new JediElasticCrossSectionData(1));
//		if(JediConfigurationManager::Instance()->GetVerbose()>2)
		if(verboseLevel>2)
			G4cout<<"JediHadronicPhysics::ConstructProcess()"
			<<" using elastic process"
			<<G4endl;
//	}

	auto particle=G4Deuteron::DeuteronDefinition();
	if ( particle )
	{
		G4ProcessManager *  processManager( particle->GetProcessManager() );
//		if(fUseFastSim)
//			processManager->AddDiscreteProcess( wrapperProcess );
//		else
			processManager->AddDiscreteProcess(elasticProcess);
	}

}
