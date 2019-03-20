/*
 * JediElasticCrossSectionData.cc
 *
 *  Created on: 18.01.2017
 *      Author: pmaanen
 */

#include <JediElasticCrossSectionData.hh>

#include <G4GenericMessenger.hh>
JediElasticCrossSectionData::JediElasticCrossSectionData(G4double factor):G4VCrossSectionDataSet("elastic"),fFactor(factor){
	fMessenger=std::unique_ptr<G4GenericMessenger>(new G4GenericMessenger(this,"/PolarimeterStudies/physics/",""));
	auto elaCmd=fMessenger->DeclareProperty("elastic",JediElasticCrossSectionData::fFactor,"");
	elaCmd.SetStates(G4State_PreInit, G4State_Idle);
}
