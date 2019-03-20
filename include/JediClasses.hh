/*
 * hit.hh
 *
 *  Created on: Jul 24, 2013
 *      Author: maanen
 */
#ifndef HIT_HH_
#define HIT_HH_
#include <TObject.h>
#include <vector>
#include <map>
#include <string>
class calorhit_t: public TObject {
public:
	calorhit_t():TObject(),edep(0),detid(0){;};
	Double_t edep;
	Int_t detid;
	ClassDef(calorhit_t,2)  //Event structure
};

class trackerhit_t : public TObject {
public:
	trackerhit_t():TObject(),x(0),y(0),z(0),px(0),py(0),pz(0),edep(0),pid(0),trid(0),tof(0),ekin(0),detid(0){;};
	Double_t x,y,z,px,py,pz,edep,pid,trid,tof,ekin,detid;
	ClassDef(trackerhit_t,5)
};

class simevent_t: public TObject {
public:
	simevent_t():TObject(),eventid(0),time(0){;};
	Int_t eventid;
	Int_t time;
	std::map<std::string,std::vector<calorhit_t> > calorimeter;
	std::map<std::string, std::vector<trackerhit_t> > tracker;
	ClassDef(simevent_t,2)
};

class particle_t : public TObject{
public:
	particle_t():TObject(),id(0),px(0),py(0),pz(0),E(0){;};
	particle_t(Int_t iid,Double_t ppx,Double_t ppy,Double_t ppz,Double_t ee):id(iid),px(ppx),py(ppy),pz(ppz),E(ee){;};
	Int_t id;
	Double_t px,py,pz,E;
	ClassDef(particle_t,5)
};

class genvertex_t : public TObject{
public:
	genvertex_t():x(0),y(0),z(0),time(0){};
	genvertex_t(Double_t tt, Double_t vvx, Double_t vvy, Double_t vvz):x(vvx),y(vvy),z(vvz),time(tt){;};
	Double_t x,y,z,time;
	std::vector<particle_t > particles;
	ClassDef(genvertex_t,2);
};

class genevent_t: public TObject {
public:
	genevent_t():TObject(),eventid(0),time(0){;};
	genevent_t(Int_t iid, Double_t ttime):eventid(iid),time(ttime){;};

	Int_t eventid;
	Double_t time;
	std::map<std::string, std::vector<genvertex_t> > generators;
	ClassDef(genevent_t,5);
};
#endif /* HIT_HH_ */
