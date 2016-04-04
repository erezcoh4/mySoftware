//  TCalculations.cpp
//  Created by Erez Cohen on 8/10/15.

#include "TCalculations.h"




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Float_t TCalculations::DistanceFromPointToLine( Double_t x0 , Double_t y0 , Double_t m , Double_t n ){
    // calculate the distance of the point (x0,y0) from the line y = mx + n
    return ( fabs( ( y0 - (m*x0 + n) ) / sqrt(m*m+1)) );
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Float_t TCalculations::Chi2FitStraightLine( const int N ,Double_t yi[N] ,Double_t xi[N] ,Double_t si[N] ,Double_t a[2] ,Double_t aErr[3] ){
    // fit y = a[0] + a[1]*x [reference: http://ned.ipac.caltech.edu/level5/Leo/Stats7_2.html]
    // result: a[2] are the parameters: y = a[0] + a[1]x , aErr[2] are the uncertainties in a[2], aErr[3] is the covariance a[0]-a[1]
    Double_t Ri[3] , XiYi[3] ;
    for (int j = 0 ; j < N ; j++)
        XiYi[j] = yi[j]*xi[j];
    Double_t A  = Sum( N , xi   , 1 , si , -2 );
    Double_t B  = Sum( N , xi   , 0 , si , -2 );
    Double_t C  = Sum( N , yi   , 1 , si , -2 );
    Double_t D  = Sum( N , xi   , 2 , si , -2 );
    Double_t E  = Sum( N , XiYi , 1 , si , -2 );
    //    Double_t F  = Sum( N , yi   , 2 , si , -2 );
    a[0]        = (D*C-E*A)/(D*B-A*A);
    aErr[0]     = D/(D*B-A*A);
    a[1]        = (E*B-C*A)/(D*B-A*A);
    aErr[1]     = B/(D*B-A*A);
    aErr[2]     = -A/(D*B-A*A);
    for (int j = 0 ; j < N ; j++)
        Ri[j]   = yi[j] - a[0] - a[1]*xi[j];
    Double_t chi2 = Sum( N , Ri , 2 , si , -2  );
    return chi2;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TCalculations::Sum( const int N , Double_t n[N] , Double_t x , Double_t m[N] , Double_t y ){
    // return ∑[(n^x)(m^y)]
    Double_t res = 0;
    for (int i = 0 ; i < N ; i++){
        res += pow(n[i],x) * pow(m[i],y);
    }
    return res;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
float TCalculations::RadiationLength(int Z, int A, float density){
    // approximate formula for a given material consisting of a single type of nuclei
    float RL    = (716.4*A
                   /(Z*(Z+1)*TMath::Log(287./sqrt(Z)))); // [in g/cm²]
    float RLcm  = RL/density;
    Printf("radiation length of (Z=%d,A=%d) is %f g/cm²",Z,A,RL);
    Printf("using density of %.2f g/cm³, one radiation length of target material is %f cm",density,RLcm);
    return RL;
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
float TCalculations::TwoIdenticalSpheresOverlapVolume(float R, float d){
    // reutrn the overlap volumes for two identical spheres of radius R seperated by a distance d
    // [http://mathworld.wolfram.com/Sphere-SphereIntersection.html]
    return (TMath::Pi()/12.) * (4.*R+d) * (2.*R-d)*(2.*R-d) ;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TF1* TCalculations::CFGMomentumDist(bool DoPlot){ // April-04
    
    // Correlated Fermi Gas (CFG) distribution
    TH1F* hCFG;
    
    Double_t        c0 = 4.16 ; // +/- 0.95..
    Double_t       k_F = 250 ;
    Double_t       E_F = k_F * k_F / (2. * 940.); // non relativistic
    Double_t      E_F0 = 12.5 / ( ( pow(2.,2./3) - 1 ) * (3./5.));
    Double_t      k_F0 = sqrt( 2. * 940. * E_F0 );
    Double_t  rho2rho0 = pow( ( pow(2.,2./3) - 1 ) * (3./5.) * (E_F/12.5)   , 3./2.);
    Double_t    lambda = 2.75 ;// +/- 0.25 high-momentum cutoff
    Double_t       pi2 = pow(TMath::Pi(),2);
    Double_t        A0 = (3 * pi2 / pow(k_F0,3)) * (1./rho2rho0) * (1 - (1 - (1./lambda)*pow(rho2rho0,1./3.)) * (c0 / pi2 ));
   TF1 * SRCk4Tail = new TF1("tail",Form("%f*%f/(x**4)",c0,k_F),k_F,lambda*k_F0);
    
    int Nbins = 100;
    float bin_content , k;
    
    // Correlated Fermi Gas momentum dist.
    hCFG = new TH1F("hCFG" , "Correlated Fermi Gas momentum dist." , Nbins , 0 , lambda*k_F0 );
    for (int bin = 0; bin < Nbins ; bin++){
        k = hCFG -> GetXaxis() -> GetBinCenter( bin );
        bin_content = ( k < k_F ) ? A0 : SRCk4Tail -> Eval(k);
        hCFG -> SetBinContent( bin , bin_content );
    }
    
    plot->SetFrame(hCFG,"n momentum dist. - Correlated Fermi Gas","neutron momentum [GeV/c]","#rho [a.u.]", 1,46);
    if (DoPlot){
        hCFG -> Draw();
    }
    return SRCk4Tail;
}


