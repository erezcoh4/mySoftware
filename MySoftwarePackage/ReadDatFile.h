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

#include <iostream>

/**
   \class ReadDatFile
   User defined class ReadDatFile ... these comments are used to generate
   doxygen documentation!
 */
class ReadDatFile{

public:

  /// Default constructor
    ReadDatFile () = default;
    ReadDatFile (std::string fInFileName, std::string fOutFileName);
    
    void    Print () const;
    
    /// SETters
    void             SetInFileName (std::string fname)      {InFileName = fname;};
    void            SetOutFileName (std::string fname)      {OutFileName = fname;};
    
    
    // GETters
    
    
    
private:
    
    // std::string
    std::string       InFileName="", OutFileName="";

};

#endif
/** @} */ // end of doxygen group 

