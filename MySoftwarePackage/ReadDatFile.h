/**
 * \file ReadDatFile.h
 *
 * \ingroup MySoftwarePackage
 * 
 * \brief Class def header for a class ReadDatFile
 *
 * @author erezcohen
 */

/** \addtogroup MySoftwarePackage

    @{*/
#ifndef READDATFILE_H
#define READDATFILE_H

#include "myIncludes.h"
#include <iostream>
#define NMAX 250

/**
   \class ReadDatFile
   User defined class ReadDatFile ... these comments are used to generate
   doxygen documentation!
 */
class ReadDatFile{

public:

  /// Default constructor
    ReadDatFile () = default;
    ReadDatFile (std::string fInFileName, std::string fOutFileName, std::string fInFileType);
    
    void              Print () const;
    void    ReadDatFromFile (  int Nlines=-1 // -1 is all
                             , int debug=0
                             , int NeventsToRead=-1 // -1 = all
                             );
    void      HeaderCSVfile ();

    /// SETters
    void             SetInFileName (std::string fname)      {InFileName = fname;};
    void            SetOutFileName (std::string fname)      {OutFileName = fname;};
    
    // GETters
    
    
    
private:
    
    // std::string
    std::string     InFileName="", OutFileName="";
    std::string     InFileType="";
    
    int     tmp_i;
    int     Ensemb[NMAX],Index[NMAX],Number[NMAX],ID[NMAX],IQ[NMAX];
    int     parents_1[NMAX] , parents_2[NMAX] , parents_3[NMAX];
    int     particle_id, parent1, parent2, charge, indFree, event;
    
    double  Mass;
    double  P0 , P1 , P2 , P3;
    double  Weight;
    double  mass[NMAX];
    double  ScaleCS[NMAX], firstEvent[NMAX], event_1[NMAX], event_2[NMAX], perWeight[NMAX], formationTime[NMAX];
    double  productionTime[NMAX], lastCollisionTime[NMAX];
    double  E[NMAX] , Px[NMAX] , Py[NMAX] , Pz[NMAX] , X[NMAX] , Y[NMAX] , Z[NMAX];

    char    Anti[NMAX],in_Formation[NMAX];
    
    ofstream outcsvfile;

    

};

#endif
/** @} */ // end of doxygen group

