/*
 * JediScatteringHelperFunctions.cc
 *
 *  Created on: 13.02.2017
 *      Author: pmaanen
 */

#include "JediScatteringHelperFunctions.hh"

#include "TMath.h"

#include <math.h>



//*********** Elastic  ***********
Double_t JediScatteringHelperFunctions::elastic::q(Double_t* x, Double_t* par) {
	Double_t w=log(par[0]);
	return pow(10,a1(w)+a2(w)*x[0]+(1+a5(w)*x[0])*(a3(w)*sin(a6(w)*x[0])+a4(w)*cos(a6(w)*x[0])));
}

Double_t JediScatteringHelperFunctions::elastic::q(Double_t q, Double_t e) {
	Double_t w=log(e);
	return pow(10,a1(w)+a2(w)*q+(1+a5(w)*q)*(a3(w)*sin(a6(w)*q)+a4(w)*cos(a6(w)*q)));

}

Double_t JediScatteringHelperFunctions::elastic::phi(Double_t* x, Double_t* par) {
	return 1+par[1]*ay(par[0],par[2])*cos(x[0]);
}

Double_t JediScatteringHelperFunctions::elastic::phi(Double_t phi, Double_t py, Double_t e, Double_t theta) {
	return 1+py*ay(e,theta)*cos(phi);
}


Double_t JediScatteringHelperFunctions::elastic::a1(Double_t x) {
	return -79.173+46.741*x-8.662*x*x+0.52986*x*x*x;
}

Double_t JediScatteringHelperFunctions::elastic::a2(Double_t x) {
	return 78.051-34.263*x+3.341*x*x;

}

Double_t JediScatteringHelperFunctions::elastic::a3(Double_t x) {
	return -38.231+19.774*x-3.1487*x*x+0.14791*x*x*x;
}

Double_t JediScatteringHelperFunctions::elastic::a4(Double_t x) {
	return 9.1111-3.2832*x+0.28525*x*x;
}

Double_t JediScatteringHelperFunctions::elastic::a5(Double_t x) {
	return -3.6126+0.18644*x;
}

Double_t JediScatteringHelperFunctions::elastic::a6(Double_t x) {
	return 23.91+0.66962*x;
}

Double_t JediScatteringHelperFunctions::elastic::ay(Double_t E, Double_t theta) {
	return (1/(1+900./pow(theta,4)))*
			(b4(E)-b1(E)/(1+exp((theta-b2(E))/b3(E)))+b5(E)*(1-theta/b6(E))*sin(b7(E)+b8(E)*theta));
}

Double_t JediScatteringHelperFunctions::elastic::b1(Double_t E) {
	return  1.1556+0.007182*(E-150)+1.3524e-5*pow(( E-150),2)-5.5448e-7*pow(( E-150),3);
}

Double_t JediScatteringHelperFunctions::elastic::b2(Double_t E) {
	return 16.029-0.24658*(E-150)+8.6972e-4*pow((E-150),2);
}

Double_t JediScatteringHelperFunctions::elastic::b3(Double_t E) {
	return 6.8319+0.052974*( E-150)+6.4864e-4*pow(E-150,2)-4.7648e-6*pow(E-150,3);
}

Double_t JediScatteringHelperFunctions::elastic::b4(Double_t E) {
	return 0.94964+8.2885e-4*( E-150)-5.4014e-6*pow(E-150,2);
}

Double_t JediScatteringHelperFunctions::elastic::b5(Double_t E) {
	return 0.21588+1.3908e-4*( E-150);
}

Double_t JediScatteringHelperFunctions::elastic::b6(Double_t E) {
	return 42.467-0.25468*( E-150)+0.0033973*pow(E-150,2);
}

Double_t JediScatteringHelperFunctions::elastic::b7(Double_t E) {
	return 58.573-0.41812*( E-150);
}

Double_t JediScatteringHelperFunctions::elastic::b8(Double_t E) {
	return 25.698+0.091205*( E-150)-1.8594e-4*pow(E-150,2);
}

//*********** Breakup ***********
Double_t JediScatteringHelperFunctions::breakup::sigma_unpol(Double_t E, Double_t theta,
		Double_t Ex) {
	if(Ex>(c2(theta,E)-c3(theta)*c4(theta)))
		return c1(theta,E)*exp(-pow(Ex-c2(theta,E),2)/(2*c3(theta)*c3(theta)));
	else
		return c1(theta,E)*exp(-c4(theta)*c4(theta)/2.)*exp(-(c5(theta)*(c2(theta,E)-c4(theta)*c3(theta)-Ex))/c3(theta));
}

Double_t JediScatteringHelperFunctions::breakup::theta_ex(Double_t* x, Double_t* par) {
	/*
	 * x[0]=theta
	 * x[1]=Ex
	 * par[0]=E
	 *
	 * par[1,2]=Theta Min,Max
	 * par[3,4]=Ex Min,Max
	 *
	 *
	 */
	if (x[0]<par[1] or x[0]>par[2] or x[1]<par[3] or x[1]>par[4])
		return 0;
	if(x[1]>(c2(x[0],par[0])-c3(x[0])*c4(x[0])))
		return c1(x[0],par[0])*exp(-pow(x[1]-c2(x[0],par[0]),2)/(2*c3(x[0])*c3(x[0])));
	else
		return c1(x[0],par[0])*exp(-c4(x[0])*c4(x[0])/2.)*exp(-(c5(x[0])*(c2(x[0],par[0])-c4(x[0])*c3(x[0])-x[1]))/c3(x[0]));
}

double JediScatteringHelperFunctions::breakup::phi(Double_t* x, Double_t* par) {
	/*
	 * x[0]=Phi
	 * par[0]=Py
	 * par[1]=E
	 * par[2]=theta
	 * par[3]=Ex
	 */
	return 1+par[0]*ay(par[1],par[2]*TMath::RadToDeg(),par[3])*cos(x[0]);
}

Double_t JediScatteringHelperFunctions::breakup::c1(Double_t theta,Double_t E) {
	return sqrt(113./E)*exp(1.5586-0.07178*(theta-40.)+4.0733e-4*pow(theta-40.,2));
}

Double_t JediScatteringHelperFunctions::breakup::c2(Double_t theta, Double_t E) {
	return E/113*(62.214+0.30061*(theta-40)-0.004704*pow(theta-40.,2));
}

Double_t JediScatteringHelperFunctions::breakup::c3(Double_t theta) {
	return 14.384-0.048676*(theta-40);
}

Double_t JediScatteringHelperFunctions::breakup::c4(Double_t theta) {
	return 0.74342+0.0069414*(theta-40);
}

Double_t JediScatteringHelperFunctions::breakup::c5(Double_t theta) {
	return c3(theta)*(0.070367-3.3534e-4*(theta-40)+1.1845e-5*(theta-40)*(theta-40)+1.1436e-6*pow(theta-40,3));
}

Double_t JediScatteringHelperFunctions::breakup::ay(Double_t E, Double_t theta,
		Double_t Ex) {
	return d1(theta,E)+d2(theta,E)*(Ex-E/2.);
}

Double_t JediScatteringHelperFunctions::breakup::d1(Double_t theta, Double_t E) {
	return -1280./E/E+0.528*theta/E;
}

Double_t JediScatteringHelperFunctions::breakup::d2(Double_t theta, Double_t E) {
	return -7.35/pow(E,3./2.)+6.2e-5*(theta-40)+11.7/pow(E,3)*pow(theta-40,2)-3.1e-7*pow(theta-40,3);
}


//*********** Inelastic ***********
Double_t JediScatteringHelperFunctions::inelastic::q_ex(Double_t* x,
		Double_t*) {
	/*
	 * x[0]=Ex
	 * x[1]=q
	 */
	return pow(10,f1(x[0])+f2(x[0])*(x[1]-0.25)+f3(x[0])*pow(x[1]-0.25,2));
}

Double_t JediScatteringHelperFunctions::inelastic::phi(Double_t* x,
		Double_t* par) {
	/*
	 * x[0]=Phi
	 *par[0]=Py
	 *par[1]=q
	 *par[2]=Ex
	 */
	return 1+par[0]*ay(par[1],par[2])*cos(x[0]);
}

Double_t JediScatteringHelperFunctions::inelastic::f1(Double_t Ex) {
	return 0.81403*8.5131e-4*Ex;
}

Double_t JediScatteringHelperFunctions::inelastic::f2(Double_t Ex) {
	return -3.1246-0.068376*Ex+0.0014052*Ex*Ex;
}

Double_t JediScatteringHelperFunctions::inelastic::f3(Double_t Ex) {
	return -4.8934+0.028654*Ex;
}

Double_t JediScatteringHelperFunctions::inelastic::ay(Double_t q,
		Double_t Ex) {
	return g1(Ex)*(1-1/pow(1+exp((q-g2(Ex))/g3(Ex)),0.1));
}

Double_t JediScatteringHelperFunctions::inelastic::g1(Double_t Ex) {
	return 0.82579-0.0188*Ex+1.3928e-4*Ex*Ex;
}

Double_t JediScatteringHelperFunctions::inelastic::g2(Double_t Ex) {
	return 0.10278+0.0043333*Ex;
}

Double_t JediScatteringHelperFunctions::inelastic::g3(Double_t Ex) {
	return (16.933+0.24*Ex)/1000;
}
