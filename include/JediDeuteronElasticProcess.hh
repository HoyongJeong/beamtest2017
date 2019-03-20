/*
 * JediElasticScatteringProcess.hh
 *
 *  Created on: 13.01.2017
 *      Author: pmaanen
 */

#ifndef INCLUDE_JEDIDEUTERONELASTICPROCESS_HH_
#define INCLUDE_JEDIDEUTERONELASTICPROCESS_HH_
#include "GenEventProducer.hh"
#include <G4HadronicProcess.hh>
#include <memory>
#include <Rtypes.h>
#include "JediClasses.hh"
#include <vector>
class JediDeuteronElastic;
class JediDeuteronElasticProcess: public G4HadronicProcess, GenEventProducer {
public:
	explicit JediDeuteronElasticProcess();
	virtual ~JediDeuteronElasticProcess();


public:
	G4VParticleChange *  PostStepDoIt( const G4Track &  track,
			const G4Step &  step );

	G4bool  IsApplicable( const G4ParticleDefinition &  particle );

	void    RegisterModel( JediDeuteronElastic *  model );


private:
	void  CalculateTargetNucleus(  const G4Material *  material );
	JediDeuteronElastic *   fModel;

	G4ParticleChange *      theTotalResult;

	G4Nucleus               targetNucleus;
};

#endif /* INCLUDE_JEDIDEUTERONELASTICPROCESS_HH_ */
