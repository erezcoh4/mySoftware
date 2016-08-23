/**
 * \file myIncludes.h
 *
 * \ingroup MySoftwarePackage
 * 
 * \brief Class def header for a class myIncludes
 *
 * @author erezcohen
 */

/** \addtogroup MySoftwarePackage

    @{*/
#ifndef MYINCLUDES_H
#define MYINCLUDES_H

#include <iostream>

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <functional>
#include "TRotation.h"
#include <TTimeStamp.h>
#include <TStopwatch.h>
#include <TString.h>
#include <TSystem.h>
#include <TLine.h>
#include <TArrow.h>
#include <TFile.h>
#include <TTree.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TF2.h>
#include <TF12.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TProfile.h>
#include <TPad.h>
#include <TStyle.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include <TChain.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TMath.h>
#include <TCut.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TVector3.h>
#include <TPie.h>
#include <TLatex.h>
#include <TEllipse.h>
#include <TPolyLine3D.h>
#include <TRandom2.h>
#include <THStack.h>
#include <TSpectrum.h>
#include <TSpectrum2.h>
#include <TUnfoldSys.h>
#include <TCutG.h>
#include <TGeoSphere.h>
#include <TBox.h>
#include "TGaxis.h"
#include <TRandom3.h>
#include <typeinfo>       // operator typeid



#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
#include "RooGenericPdf.h"
#include "RooPolynomial.h"
#include "RooChi2Var.h"
#include "RooMinuit.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TMatrix.h"
#include "RooPlot.h"


using namespace std;

// important prints....
#define EndEventBlock() cout << "\033[32m"<< "....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......" << "\033[0m"<< endl;

#define PrintLine() std::cout << "-------------------------------" << std::endl;


#define SHOW3(a,b,c) cout  << "\033[36m"<<#a<<": "<<(a)<<"," << #b <<": "<<(b)<<","<<#c<<": "<<(c)<< "\033[0m"<< endl;


#define SHOW(a) std::cout  << setprecision(2) << fixed << #a << ": " << (a) << std::endl
#define PrintPhys(a,units) std::cout  << setprecision(2) << fixed << #a << ": " << (a) <<  " " << (units) << std::endl

#define SHOWTLorentzVector(v) std::cout << #v << ": " << "\t(" << setprecision(2) << fixed << v.Px() << ","  << v.Py() << "," << v.Pz()  << "," << v.E() << ")" << ", P = " << v.P() << ", M = " << v.M() << std::endl


#define SHOWstdTVector3(v) { if (v.size()<1) {cout << #v << " is empty" << endl;} else {std::cout << #v << "( " << v.size() << " entries ):\t";     for (std::vector<TVector3>::iterator it=v.begin(); it!=v.end(); ++it) std::cout << setprecision(2) << fixed << "\n\t(" << it -> X() << ","  << it -> Y() << "," << it -> Z() << ")\t"; std::cout << '\n';}}

#define SHOWvectorTLorentzVector(v) { if (v.size()<1) {cout << #v << " is empty" << endl;} else {std::cout << #v << "( " << v.size() << " entries ):\t";     for (std::vector<TLorentzVector>::iterator it=v.begin(); it!=v.end(); ++it) std::cout << setprecision(2) << fixed << "\n\t(" << it -> Px() << ","  << it -> Py() << "," << it -> Pz()  << "," << it -> E() << ")" << ", P = " << it -> P() << ", M = " << it -> M(); std::cout << '\n';}}

#define SHOWstdVector(v){ if (v.size()<1) {cout << #v << " is empty" << endl;} else {cout << #v << "( " << v.size() << " entries):\t"; for (auto it:v) cout << it << ",\t"; cout << endl;}}
#define SHOWTVector3(v){ cout << #v << ": (" << v.X() << "," << v.Y() << "," << v.Z() << "), |" << #v << "| = " << v.Mag() << endl;}

/**
   \class myIncludes
   User defined class myIncludes ... these comments are used to generate
   doxygen documentation!
 */
class myIncludes{

public:

  /// Default constructor
  myIncludes(){}

  /// Default destructor
  ~myIncludes(){}

};

#endif
/** @} */ // end of doxygen group 

