//-*-C++-*-

/* $Source: /cvsroot/dspsr/dspsr/Kernel/Classes/dsp/File.h,v $
   $Revision: 1.23 $
   $Date: 2003/10/25 06:47:08 $
   $Author: hknight $ */


#ifndef __File_h
#define __File_h

#include "Reference.h"

namespace dsp {
  class File;
}

#include "Registry.h"
#include "dsp/Seekable.h"

namespace dsp {

  class PseudoFile;

  //! Loads BitSeries data from file
  /*! This class is used in conjunction with the Unpacker class in
    order to add new file formats to the baseband/dsp library.
    Inherit either dsp::File or one of its derived classes and
    implement the two pure virtual methods:

    <UL>
    <LI> bool is_valid()
    <LI> void open_file(const char* filename)
    </UL>

    then register the new class in File_registry.C
  */
  class File : public Seekable
  {
    friend class MultiFile;
    friend class HoleyFile;
    friend class RingBuffer;
    
  public:
    
    //! Return a pointer to a new instance of the appropriate sub-class
    /*! This is the entry point for creating new instances of File objects
      from input data files of an arbitrary format. */
    static File* create (const char* filename,int _bs_index=0);

    //! Convenience interface to File::create (const char*)
    static File* create (const string& filename,int _bs_index=0)
    { return create (filename.c_str(),_bs_index); }

    //! Constructor
    File (const char* name);
    
    //! Destructor
    virtual ~File ();

    //! Return true if filename contains data in the recognized format
    /*! Derived classes must define the conditions under which they can
      be used to parse the given data file */
    virtual bool is_valid (const char* filename, int _bs_index=0) const = 0;

    //! Open the file
    void open (const char* filename,int _bs_index=0);

    //! Convenience interface to File::open (const char*)
    void open (const string& filename,int _bs_index=0) 
    { open (filename.c_str(),_bs_index); }

    //! Open from a PseudoFile
    /*! Resets attributes without calling open_file */
    void open (const PseudoFile& file);

    //! Close the file
    virtual void close ();

    //! Return the name of the file from which this instance was created
    string get_filename () const { return current_filename; }
    string get_current_filename(){ return current_filename; }

    //! Inquire how many bytes are in the header
    int get_header_bytes() const{ return header_bytes; }

    //! Inquire the index of the BitSeries to be loaded
    //! This variable is generally set through a call to open(), is_valid() or create()
    int get_bs_index() const { return bs_index; }
    
    //! Return a PseudoFile constructed from this File
    PseudoFile get_pseudofile();

  protected:
    
    //! Open the file specified by filename for reading
    /*! Derived classes must open the file for reading and set the File::fd,
      File::header_bytes, Input::info, and Input::resolution attributes. */
    virtual void open_file (const char* filename) = 0;  

    //! Return ndat given the file and header sizes, nchan, npol, and ndim
    /*! Called by open_file for some file types, to determine that the
    header ndat matches the file size.  Requires 'info' parameters
    nchan, npol, and ndim as well as header_bytes to be correctly set */
    virtual int64 fstat_file_ndat(uint64 tailer_bytes=0);

    /** @name Derived Class Defined
     *  These attributes must be set by the open_file method of the
     *  derived class.  */
    //@{
    
    //! The file descriptor
    int fd;
    
    //! The size of the header in bytes
    int header_bytes;

    //@}

    //! The name of the currently opened file, set by open()
    string current_filename;

    //! Stores the index of the BitSeries to be loaded.  A file loader that whose files can store more than one BitSeries stream should have this number >=0
    int bs_index;

    //! Load nbyte bytes of sampled data from the device into buffer
    /*! If the data stored on the device contains information other
      than the sampled data, this method should be overloaded and the
      additional information should be filtered out. */
    virtual int64 load_bytes (unsigned char* buffer, uint64 nbytes);
    
    //! Set the file pointer to the absolute number of sampled data bytes
    /*! If the header_bytes attribute is set, this number of bytes
      will be subtracted by File::seek_bytes before seeking.  If the
      data stored on the device after the header contains information
      other than the sampled data, this method should be overloaded
      and the additional information should be skipped. */
    virtual int64 seek_bytes (uint64 bytes);
    
    //! Calculates the total number of samples in the file, based on its size
    virtual void set_total_samples ();

    //! List of registered sub-classes
    static Registry::List<File> registry;

    // Declare friends with Registry entries
    friend class Registry::Entry<File>;

  private:

    //! Worker function for both forms of open
    void open (const char* filename, const PseudoFile* file);

    //! Initialize variables to sensible null values
    void init();


  };

}

#endif // !defined(__File_h)
  

