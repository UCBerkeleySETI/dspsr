//-*-C++-*-

/* $Source: /cvsroot/dspsr/dspsr/Signal/General/dsp/Attic/TwoBitStatsPlotter.h,v $
   $Revision: 1.4 $
   $Date: 2002/08/05 19:58:57 $
   $Author: pulsar $ */

#ifndef __TwoBitStatsPlotter_h
#define __TwoBitStatsPlotter_h

#include <vector>

#include "ReferenceTo.h"

namespace dsp {
  
  class TwoBitCorrection;

  //! Plots the histograms maintained by TwoBitCorrection
  class TwoBitStatsPlotter {

  public:

    //! Null constructor
    TwoBitStatsPlotter ();

    //! Virtual destructor
    virtual ~TwoBitStatsPlotter ();

    //! Set the data to be plotted
    void set_data (const TwoBitCorrection* stats);

    //! Set the device-normalized coordinates of viewport frame
    void set_viewport (float xmin, float xmax, float ymin, float ymax);

    //! Set the plot colour used for each digitizer channel
    void set_colours (const vector<int>& colours);

    //! Get the colour used to plot the theoretical distribution
    int get_theory_colour () { return theory_colour; };

    //! Plot the data in the currently open viewport
    void plot ();

    //! Get a measure of the difference between the histogram and the theory
    double get_chi_squared (int chan);

    //! Plot vertical bars to indicate the cut-off thresholds
    bool show_cutoff_sigma;

    //! Plot vertical bars to indicate the cut-off thresholds
    bool plot_only_range;

   //! Plot the two polarizations beside eachother
    bool horizontal;

    //! Plot the entire x-axis of the histogram
    bool full_xscale;

    //! Fraction of histogram maximum below which points are ignored
    float hist_min;

  protected:

    //! Where individual histograms are kept for plotting
    vector<float> histogram;

    //! Theoretical, optimal histogram
    vector<float> theory;

    //! Maxmimum value of theory
    float theory_max;

    //! Set true when the theoretical, optimal histogram is calculated
    bool theory_calculated;

    //! Colour used when plotting theoretical
    int theory_colour;

    //! Colour used when plotting histogram from each channel
    vector <int> colours;

    //! Device normalized coordinates of viewport frame
    float vpxmin;
    float vpxmax;
    float vpymin;
    float vpymax;

    //! Data to be plotted
    Reference::To<const TwoBitCorrection> data;

    //!
    void calculate_theory ();

    //! Label the plot
    void pglabel ();

    void pgplot (int poln);

    void set_theory_colour ();

    void check_colours ();

  };
  
}

#endif
