//-*-C++-*-
/***************************************************************************
 *
 *   Copyright (C) 2004 by Willem van Straten
 *   Licensed under the Academic Free License version 2.1
 *
 ***************************************************************************/

// dspsr/Kernel/Classes/dsp/FloatUnpacker.h

#ifndef __FloatUnpacker_h
#define __FloatUnpacker_h

#include "dsp/Unpacker.h"

namespace dsp {

  //! Unpacks floating point numbers stored in time-major order
  class FloatUnpacker: public Unpacker
  {

  public:

    //! Null constructor
    FloatUnpacker (const char* name = "FloatUnpacker");

    //! The unpacking routine
    void unpack ();

    //! Return true if we can convert the Observation
    bool matches (const Observation* observation);

    //! Return true if the output order is supported
    bool get_order_supported (TimeSeries::Order) const;

    //! Set the order of the dimensions in the output TimeSeries
    void set_output_order (TimeSeries::Order);

  };
}

#endif
