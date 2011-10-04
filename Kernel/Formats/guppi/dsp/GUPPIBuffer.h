//-*-C++-*-
/***************************************************************************
 *
 *   Copyright (C) 2011 by Paul Demorest
 *   Licensed under the Academic Free License version 2.1
 *
 ***************************************************************************/

#ifndef __GUPPIBuffer_h
#define __GUPPIBuffer_h

#include "dsp/GUPPIBlockFile.h"

namespace dsp {

  //! Loads BitSeries data from guppi_daq shared memory 
  class GUPPIBuffer : public GUPPIBlockFile
  {
  public:
	  
    //! Construct and open file	  
    GUPPIBuffer (const char* filename=0);
	  
    //! Destructor
    ~GUPPIBuffer ();
	  
    //! Returns true if filename is a valid GUPPI buffer description
    bool is_valid (const char* filename) const;

  protected:

    //! Open the file
    void open_file (const char* filename);

    //! Load the next hdr/data block
    int load_next_block ();

  };

}

#endif // !defined(__GUPPIBuffer_h)