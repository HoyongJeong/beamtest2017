/*
 * JediElasticCrossSectionData.hh
 *
 *  Created on: 18.01.2017
 *      Author: pmaanen
 */

#ifndef INCLUDE_JEDIELASTICCROSSSECTIONDATA_HH_
#define INCLUDE_JEDIELASTICCROSSSECTIONDATA_HH_

#include <G4VCrossSectionDataSet.hh>
#include <G4SystemOfUnits.hh>
class  G4Element;
class  G4ParticleDefinition;
class G4GenericMessenger;
#include <limits>
#include <G4Deuteron.hh>
#include <G4DynamicParticle.hh>
#include <G4Material.hh>
#include <memory>
class JediElasticCrossSectionData: public G4VCrossSectionDataSet {
public:
	JediElasticCrossSectionData(G4double factor=1);
	virtual ~JediElasticCrossSectionData()=default;

	void      BuildPhysicsTable( const G4ParticleDefinition & )
	{}

	void      DumpPhysicsTable( const G4ParticleDefinition & )
	{}

private:
	G4double fFactor;
	std::unique_ptr<G4GenericMessenger> fMessenger;
	G4double fCrossSectionData[31]={000.00,000.00,000.00,000.00,165.99,357.75,514.22,
			578.08,570.71,525.60,464.50,400.12,338.73,287.07,243.99,208.99,179.46,
			155.27,135.08,119.38,106.27,094.92,085.80,077.74,071.32,067.02,062.71,
			058.41,054.10,049.80,045.50};
	virtual G4bool IsElementApplicable( const G4DynamicParticle *, G4int, const G4Material*)
	{
		return true;
	}

	virtual G4double GetElementCrossSection( const G4DynamicParticle * particle, G4int Z, const G4Material*){

		G4double xsec=0;
		G4double deltaE=10; //MeV

		if(particle->GetParticleDefinition()==G4Deuteron::DeuteronDefinition() and Z==6){
			auto e=particle->GetKineticEnergy()/CLHEP::MeV;
			auto bin=int(floor(e/deltaE));
			auto dydx=(fCrossSectionData[bin+1]-fCrossSectionData[bin])/deltaE;
			auto dx=e-bin*deltaE;
			xsec=fCrossSectionData[bin]+dydx*dx;
			xsec*=CLHEP::millibarn*fFactor;
		}
		return xsec;
	}
};
#endif /* INCLUDE_JEDIELASTICCROSSSECTIONDATA_HH_ */
