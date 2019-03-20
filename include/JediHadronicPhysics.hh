/*
 * JediHadronicPhysics.hh
 *
 *  Created on: 13.01.2017
 *      Author: pmaanen
 */

#ifndef INCLUDE_JEDIHADRONICPHYSICS_HH_
#define INCLUDE_JEDIHADRONICPHYSICS_HH_

#include <G4VPhysicsConstructor.hh>
//#include <JediBreakupModel.hh>
#include <G4GenericMessenger.hh>
#include <JediDeuteronElastic.hh>


#include <memory>

class G4VProcess;
class JediHadronicPhysics: public G4VPhysicsConstructor {
public:
	JediHadronicPhysics(G4int ver=0);
	virtual ~JediHadronicPhysics()=default;

public:

	void ConstructParticle();
	void ConstructProcess();

protected:

	//virtual void ApplyInteractionModel(G4VProcess* process);

protected:

	std::unique_ptr<JediDeuteronElastic> fElastic;
//	std::unique_ptr<JediBreakupModel> fBreakup;

private:
	G4bool fUseFastSim;
	std::unique_ptr<G4GenericMessenger> fMessenger;
};

#endif /* INCLUDE_JEDIHADRONICPHYSICS_HH_ */
