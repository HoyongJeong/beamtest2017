/*
 * JediScatteringHelperFunctions.hh
 *
 *  Created on: 13.02.2017
 *      Author: pmaanen
 *
 *      Namespace with functions from ed's models (See Jedi Internal Note 8/2015).
 *      Makes it easier to export these functions into an external library for use
 *      in e.g. the root shell.
 *
 */

#ifndef INCLUDE_JEDISCATTERINGHELPERFUNCTIONS_HH_
#define INCLUDE_JEDISCATTERINGHELPERFUNCTIONS_HH_

#include "Rtypes.h"

namespace JediScatteringHelperFunctions {
//*********** Elastic Scattering ***********
namespace elastic{
Double_t sigma(Double_t*,Double_t*);
Double_t q(Double_t*, Double_t*);
Double_t q(Double_t q, Double_t e);
Double_t phi(Double_t*, Double_t*);
Double_t phi(Double_t phi, Double_t py, Double_t e, Double_t theta);

//Parameters for ds/dOmega. x is ln(E)
Double_t a1(Double_t x);
Double_t a2(Double_t x);
Double_t a3(Double_t x);
Double_t a4(Double_t x);
Double_t a5(Double_t x);
Double_t a6(Double_t x);

//Parameters for Ay.
Double_t ay(Double_t E, Double_t theta);
Double_t b1(Double_t E);
Double_t b2(Double_t E);
Double_t b3(Double_t E);
Double_t b4(Double_t E);
Double_t b5(Double_t E);
Double_t b6(Double_t E);
Double_t b7(Double_t E);
Double_t b8(Double_t E);
}
//*********** Breakup ***********
namespace breakup {
Double_t sigma(Double_t theta, Double_t phi, Double_t Ex);
Double_t sigma_unpol(Double_t, Double_t, Double_t);
Double_t theta_ex(Double_t* x, Double_t* par);
Double_t phi(Double_t*, Double_t*);

Double_t c1(Double_t theta, Double_t E);
Double_t c2(Double_t theta, Double_t E);
Double_t c3(Double_t theta);
Double_t c4(Double_t theta);
Double_t c5(Double_t theta);

Double_t ay(Double_t, Double_t, Double_t);
Double_t d1(Double_t theta, Double_t E);
Double_t d2(Double_t theta, Double_t E);
}
//*********** Inelastic scattering ***********
namespace inelastic {
Double_t q_ex(Double_t* x, Double_t* par);
Double_t phi(Double_t* x, Double_t* par);
Double_t f1(Double_t Ex);
Double_t f2(Double_t Ex);
Double_t f3(Double_t Ex);

Double_t ay(Double_t q, Double_t Ex);

Double_t g1(Double_t Ex);
Double_t g2(Double_t Ex);
Double_t g3(Double_t Ex);
}
}




#endif /* INCLUDE_JEDISCATTERINGHELPERFUNCTIONS_HH_ */
