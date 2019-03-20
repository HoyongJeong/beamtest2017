/*
 * DeuteronCarbonElasticScatteringModel.cc
 *
 *  Created on: 13.01.2017
 *      Author: pmaanen
 */

#include <G4Deuteron.hh>
#include "G4ParticleDefinition.hh"
#include <G4Event.hh>
#include "G4IonTable.hh"
#include "G4ios.hh"
#include "TVector3.h"
#include <math.h>
#include <TMath.h>
#include "JediScatteringHelperFunctions.hh"
#include <G4NucleiProperties.hh>
//#include <JediConfigurationManager.hh>
#include <JediDeuteronElastic.hh>
#include <TROOT.h>
#include <TMath.h>
#include <TRandom3.h>
JediDeuteronElastic::JediDeuteronElastic():G4HadronicInteraction("dcelastic"),fBeamPolarization(0),fNucleus(nullptr),fNucleusMass(0) {
	ROOT::EnableThreadSafety();
	theMinEnergy=30*CLHEP::MeV;
	SetRecoilEnergyThreshold(10*CLHEP::keV);
	fIncidentParticle=G4Deuteron::DeuteronDefinition();

	fQmin=0.04*CLHEP::GeV;
	fQmax=.4*CLHEP::GeV;

//	if(JediConfigurationManager::Instance()->GetMap().count("generator.theta_min"))
//		fThetaMin=JediConfigurationManager::Instance()->GetMap()["generator.theta_min"].as<double>()*CLHEP::deg;
//	else
		fThetaMin=3*CLHEP::deg;
//	if(JediConfigurationManager::Instance()->GetMap().count("generator.theta_max"))
//		fThetaMax=JediConfigurationManager::Instance()->GetMap()["generator.theta_max"].as<double>()*CLHEP::deg;
//	else
		fThetaMax=20*CLHEP::deg;

	auto diff=fThetaMax-fThetaMin;
	if(diff<0){
		G4ExceptionDescription ed;
					ed<<"theta_max<theta_min!"<<G4endl
							<<" theta_max (deg) "<<fThetaMax/CLHEP::deg
							<<" theta_min (deg) "<<fThetaMin/CLHEP::deg;
					G4Exception("JediDeuteronElastic::ApplyYourself","",FatalException,ed);
	}
	if(diff<1*CLHEP::deg){
		G4ExceptionDescription ed;
					ed<<"Angle range is very small. Expect slow generation and consider upping nTryMax in case of crashes."<<G4endl
							<<" theta_max (deg) "<<fThetaMax/CLHEP::deg
							<<" theta_min (deg) "<<fThetaMin/CLHEP::deg;
					G4Exception("JediDeuteronElastic::ApplyYourself","",JustWarning,ed);
	}


	if(!fIncidentParticle)
		G4Exception("JediElasticModel::JediElasticModel","",FatalException,"no deuteron definition found");
	fIncidentParticleMass=fIncidentParticle->GetPDGMass();
	fOutParticles.push_back(fIncidentParticle);
//	verboseLevel=JediConfigurationManager::Instance()->GetVerbose();
	verboseLevel=0;
	DefineCommands();
}

G4HadFinalState* JediDeuteronElastic::ApplyYourself(const G4HadProjectile& aTrack,
		G4Nucleus& targetNucleus) {
	theParticleChange.Clear();

	const G4HadProjectile* aParticle = &aTrack;
	G4double ekin = aParticle->GetKineticEnergy();
	if(ekin <= theMinEnergy) {
		theParticleChange.SetEnergyChange(ekin);
		theParticleChange.SetMomentumChange(aTrack.Get4Momentum().vect().unit());
		return &theParticleChange;
	}
	G4int A = targetNucleus.GetA_asInt();
	G4int Z = targetNucleus.GetZ_asInt();

	G4double plab = aParticle->GetTotalMomentum();

	// Scattered particle referred to axis of incident particle
	const G4ParticleDefinition* theParticle = aParticle->GetDefinition();
	G4double m1 = theParticle->GetPDGMass();

	if (verboseLevel>1) {
		G4cout << "JediDeuteronElastic: "
				<< aParticle->GetDefinition()->GetParticleName()
				<< " Plab(GeV/c)= " << plab/CLHEP::GeV
				<< " Ekin(MeV) = " << ekin/CLHEP::MeV
				<< " scattered off Z= " << Z
				<< " A= " << A
				<< G4endl;
	}

	G4double mass2 = G4NucleiProperties::GetNuclearMass(A, Z);
	G4LorentzVector lv1 = aParticle->Get4Momentum();
	G4LorentzVector lv(0.0,0.0,0.0,mass2);
	lv += lv1;
	G4ThreeVector bst = lv.boostVector();
	lv1.boost(-bst);

	G4ThreeVector p1 = lv1.vect();
	G4double momentumCMS = p1.mag();


	G4double thetaLab=0;
	G4int nTry=0;
	G4int nTryMax=1000;
	do{
		nTry++;
		if(nTry>nTryMax){
			G4ExceptionDescription ed;
			ed<<"nTry>nTryMax. Can not satisfy cut conditions!"<<G4endl
					<<"nTryMax "<<nTryMax<<G4endl
					<<" theta_max (deg) "<<fThetaMax/CLHEP::deg
					<<" theta_min (deg) "<<fThetaMin/CLHEP::deg<<G4endl
					<<" Projectile: "<<aTrack.GetDefinition()->GetParticleName()
					<<" at "<<aTrack.GetKineticEnergy()/CLHEP::MeV<<" (MeV)"<<G4endl;

			G4Exception("JediDeuteronElastic::ApplyYourself","",FatalException,ed);

		}
		theParticleChange.Clear();
		// Sampling in CM system
		G4double q    = SampleQ(ekin);
		G4double theta = 2*TMath::ASin(q/2/momentumCMS)*CLHEP::rad;
		G4double phi  = 0.;
		// problem in sampling
		if( q<fQmin || q> fQmax ) {
			//if(verboseLevel > 0) {
			G4cout << "JediElasticModel WARNING q= " << q
					<< " after scattering of "
					<< aParticle->GetDefinition()->GetParticleName()
					<< " p(GeV/c)= " << plab/CLHEP::GeV
					<< " on an ion Z= " << Z << " A= " << A
					<< G4endl;
			//}
			theta=0;
			// normal situation
		}
		if (verboseLevel>1) {
			G4cout <<"JediDeuteronElastic::ApplyYourself:"
					<<" q(GeV)= " << q/CLHEP::GeV
					<< " Pcms(GeV)= " << momentumCMS/CLHEP::GeV
					<< " theta=" << theta/CLHEP::deg << G4endl;
		}
		//v1=3-Momentum in CMS, nlv1=4-Mom ins cms
		G4ThreeVector v1(std::sin(theta)*std::cos(phi),std::sin(theta)*std::sin(phi),std::cos(theta));
		v1 *= momentumCMS;
		G4LorentzVector nlv1(v1.x(),v1.y(),v1.z(),
				std::sqrt(momentumCMS*momentumCMS + m1*m1));


		//boost 4-mom to lab system
		nlv1.boost(bst);


		G4double eFinal = nlv1.e() - m1;
		if (verboseLevel > 1) {
			G4cout <<"Proj: m= " << m1 << " Efin(MeV)= " << eFinal
					<< " 4-mom " << lv1 << " Final: " << nlv1
					<< G4endl;
		}

		if(eFinal <= theMinEnergy) {
			if(eFinal < 0.0 && verboseLevel > 0) {
				G4cout << "JediElastic WARNING Efinal= " << eFinal
						<< " after scattering of "
						<< aParticle->GetDefinition()->GetParticleName()
						<< " p(GeV/c)= " << plab/CLHEP::GeV
						<< " on an ion Z= " << Z << " A= " << A
						<< G4endl;
			}
			theParticleChange.SetEnergyChange(0.0);
			nlv1 = G4LorentzVector(0.0,0.0,0.0,m1);

		} else {
			auto outdir=nlv1.vect().unit();
			if(std::fabs(outdir.mag2()-1)>0.01){
				G4ExceptionDescription d;
				d<<"Momentum change is not unit vector! "
						<<outdir;
				G4Exception("JediElasticModel::ApplyYourself","",JustWarning,d.str().c_str());
				outdir*=1/outdir.mag();

			}
			theParticleChange.SetMomentumChange(outdir);
			theParticleChange.SetEnergyChange(eFinal);
		}

		lv -= nlv1;
		G4double erec =  lv.e() - mass2;
		if (verboseLevel > 1) {
			G4cout << "Recoil: " <<" m= " << mass2 << " Erec(MeV)= " << erec/CLHEP::MeV
					<< " 4-mom: " << lv
					<< G4endl;
		}

		if(erec > 100*CLHEP::keV) {
			G4ParticleDefinition * theDef = G4ParticleTable::GetParticleTable()->GetIonTable()->GetIon(Z,A,0.0);
			G4DynamicParticle * aSec = new G4DynamicParticle(theDef, lv);
			theParticleChange.AddSecondary(aSec);
		} else if(erec > 0.0) {
			theParticleChange.SetLocalEnergyDeposit(erec);
		}
		thetaLab=nlv1.vect().getTheta();
	} while(thetaLab<fThetaMin or thetaLab>fThetaMax);
	return &theParticleChange;

}

void JediDeuteronElastic::DefineCommands() {
	fMessenger=std::unique_ptr<G4GenericMessenger>(new G4GenericMessenger(this,"/jedi/elastic/",""));
	fMessenger->DeclarePropertyWithUnit("theta_min","rad",JediDeuteronElastic::fThetaMin,"");
	fMessenger->DeclarePropertyWithUnit("theta_max","rad",JediDeuteronElastic::fThetaMax,"");
}

G4double JediDeuteronElastic::SampleQ(G4double kinEnergy) {

	auto ymax=JediScatteringHelperFunctions::elastic::q(fQmin/CLHEP::GeV,kinEnergy/CLHEP::MeV);
	G4double xrand,yrand;
	while(true){

		xrand=(fQmax/CLHEP::GeV-fQmin/CLHEP::GeV)*G4UniformRand()+fQmin/CLHEP::GeV;
		yrand=G4UniformRand()*ymax;
		if(yrand<JediScatteringHelperFunctions::elastic::q(xrand,kinEnergy/CLHEP::MeV))
			break;
	}

	auto q=xrand*CLHEP::GeV;

	return q;
}

G4double JediDeuteronElastic::SamplePhi(G4double kinEnergy, G4double pol, G4double thetaLab) {
	//pol=0.5;
	//kinEnergy=270*CLHEP::MeV;
	//thetaLab=20*CLHEP::deg;
	//G4cout<<JediScatteringHelperFunctions::elastic::phi(0.,pol,kinEnergy/CLHEP::MeV,thetaLab/CLHEP::deg)<<G4endl;
	//G4cout<<JediScatteringHelperFunctions::elastic::phi(CLHEP::pi,pol,kinEnergy/CLHEP::MeV,thetaLab/CLHEP::deg)<<G4endl;
	auto ymax=1+std::abs(pol)*JediScatteringHelperFunctions::elastic::ay(kinEnergy/CLHEP::MeV,thetaLab/CLHEP::deg);
	G4double xrand,yrand;
	while(true){
		xrand=G4UniformRand()*CLHEP::twopi;
		yrand=G4UniformRand()*ymax;
		if(yrand<JediScatteringHelperFunctions::elastic::phi(xrand,pol,kinEnergy/CLHEP::MeV,thetaLab/CLHEP::deg))
			break;
	}
	G4double phi=xrand*CLHEP::rad;
	return phi;
}
