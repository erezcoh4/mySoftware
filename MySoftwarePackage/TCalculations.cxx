//  TCalculations.cpp
//  Created by Erez Cohen on 8/10/15.

#include "TCalculations.h"




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TVector3 TCalculations::EnergyLossCorrrection(TVector3 p){ // following Or Hen Analysis
    Double_t Pmeasured = p.Mag();
    Double_t CorrFactor= sqrt( pow((0.00135272 + 0.000845728/(pow((0.0746518+Pmeasured),2))+sqrt(pow(p.Mag(),2)+pow(Mp,2))),2)-pow(Mp,2))/p.Mag();
    return (CorrFactor*p);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TVector3 TCalculations::CoulombCorrection(TVector3 p , Float_t CoulombDeltaE){
    // following Or Hen Analysis : p' = p x √(√((m^2+p^2)^2+∆E^2) - m^2)
    return (sqrt(pow(sqrt(pow(Mp,2)+pow(p.Mag(),2))+CoulombDeltaE,2) - pow(Mp,2))/p.Mag())*p;
}


// Missing Mass....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TCalculations::MmissNpNn(TLorentzVector q, TVector3 Plead , int Np , int Nn){
    // If the electron scatters from a group of N protons and N neutrons at rest (i.e., Pc.m. = 0) the missing mass of the (e,e'p) reaction is
    TLorentzVector  pLead4Vec , TargetRest , miss4Vec;
    pLead4Vec       .SetVectM( Plead            , Mp );                     // struck proton
    TargetRest      .SetVectM( TVector3(0,0,0)  , Np*Mp + Nn*Mn );          // target at rest
    miss4Vec        = q + TargetRest - pLead4Vec;
    return miss4Vec.Mag();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TCalculations::ppMmissHe3(TLorentzVector q, TVector3 Plead , TVector3 Precoil){
    // If the electron scatters from a group of N protons and N neutrons at rest (i.e., Pc.m. = 0) the missing mass of the (e,e'p) reaction is
    TLorentzVector  pLead4Vec , pRec4Vec , He3AtRest , miss4Vec;
    pLead4Vec       .SetVectM( Plead            , Mp );                     // struck proton
    pRec4Vec        .SetVectM( Precoil          , Mp );                     // recoiling proton
    He3AtRest       .SetVectM( TVector3(0,0,0)  , 2*Mp + 1*Mn );            // target at rest
    miss4Vec        = q + He3AtRest - pLead4Vec - pRec4Vec;
    return miss4Vec.Mag();
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TString TCalculations::TargetAsString(int A){
    switch (A) {
        case 12:
            return "C12";
            break;
        case 27:
            return "Al27";
            break;
        case 56:
            return "Fe56";
            break;
        case 208:
            return "Pb208";
            break;
        default:
            return "No Target Found";
            break;
    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TCalculations::TargetMassAndDeltaE(int A , float *mA , float *CoulombDeltaE){
    // return MassDE[0] = mass and MassDE[1] = DeltaE
    switch (A) {
        case 12:            // carbon (C12)
            *mA              = 12.0107*0.931494;
            *CoulombDeltaE   = 0.0029;
            break;
        case 27:            // Aluminium (Al27)
            *mA              = 26.982*0.931494;
            *CoulombDeltaE   = 0.0056;
            break;
        case 56:            // iron (Fe56)
            *mA              = 55.9349375*0.93149;
            *CoulombDeltaE   = 0.0094;
            break;
        default:            // lead (Pb208)
            *mA              = 207.2*0.93149;
            *CoulombDeltaE   = 0.0203;
            break;
    }
}





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
    Double_t F  = Sum( N , yi   , 2 , si , -2 );
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
Double_t TCalculations::Distance(TVector3 v1 , TVector3 v2 , bool PrintOutResults){
    if(PrintOutResults){
        plot->PrintOut3Vector(v1,"v1");
        plot->PrintOut3Vector(v2,"v2");
        Printf("distance = %g",(v2-v1).Mag());
    }
    return (v2-v1).Mag();
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




