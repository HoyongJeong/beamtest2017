/*
 * GenEventProducer.cc
 *
 *  Created on: 23.02.2017
 *      Author: pmaanen
 */

#include "GenEventProducer.hh"
//#include "Analysis.hh"
GenEventProducer::GenEventProducer(G4String name):fName(name) {
//	Analysis::Instance()->RegisterMe(this);
	fGenVertices=std::unique_ptr<std::vector<genvertex_t>>(new std::vector<genvertex_t>);
}


GenEventProducer::~GenEventProducer() {
	//Analysis::Instance()->UnRegisterMe(this);
}
