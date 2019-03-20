/*
 * GenEventProducer.hh
 *
 *  Created on: 23.02.2017
 *      Author: pmaanen
 *
 *
 */

#ifndef GENEVENTPRODUCER_HH_
#define GENEVENTPRODUCER_HH_
#include <G4String.hh>
#include <G4ios.hh>
#include <JediClasses.hh>
#include <memory>
//#include <JediConfigurationManager.hh>
class GenEventProducer {
public:
	GenEventProducer(G4String name);
	virtual ~GenEventProducer();
	const std::vector<genvertex_t>& genGenVertices() const;
	const G4String getName() const;
	void CopyVerticesToRun(genevent_t& anEvent) const;

	virtual void EndOfEvent();
	virtual void BeginOfRun();


protected:
	G4String fName;
	std::unique_ptr<std::vector<genvertex_t>> fGenVertices;
};

inline const std::vector<genvertex_t>& GenEventProducer::genGenVertices() const {
		return *fGenVertices;
	}

inline const G4String GenEventProducer::getName() const {
	return fName;
}

inline void GenEventProducer::CopyVerticesToRun(genevent_t& anEvent) const  {
//	if(JediConfigurationManager::Instance()->GetVerbose()>3)
//			G4cout<<" GenEventProducer::CopyVerticesToRun: "<<fName<<" "<<fGenVertices->size()<<G4endl;
	anEvent.generators[fName]=*fGenVertices.get();
}

inline void GenEventProducer::EndOfEvent() {
	fGenVertices->clear();
}

inline void GenEventProducer::BeginOfRun(){
	fGenVertices->clear();
}

#endif /* GENEVENTPRODUCER_HH_ */
