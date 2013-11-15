/**
 * @file bob/sp/FFT2D.h
 * @date Wed Apr 13 23:08:13 2011 +0200
 * @author Laurent El Shafey <Laurent.El-Shafey@idiap.ch>
 *
 * @brief Implement a blitz-based 2D Fast Fourier Transform using FFTW
 * functions
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 */

#ifndef BOB_SP_FFT2D_H
#define BOB_SP_FFT2D_H

#include <complex>
#include <blitz/array.h>

namespace bob { namespace sp {
/**
 * @ingroup SP
 * @{
 */

/**
 * @brief This class implements a Discrete Fourier Transform based on the
 * FFTW library. It is used as a base class for FFT2D and IFFT2D classes.
 */
class FFT2DAbstract
{
  public:
    /**
     * @brief Constructor: Initialize working arrays
     */
    FFT2DAbstract(const size_t height, const size_t width);

    /**
     * @brief Copy constructor
     */
    FFT2DAbstract(const FFT2DAbstract& other);

    /**
     * @brief Destructor
     */
    virtual ~FFT2DAbstract();

    /**
     * @brief Assignment operator
     */
    FFT2DAbstract& operator=(const FFT2DAbstract& other);

    /**
     * @brief Equal operator
     */
    bool operator==(const FFT2DAbstract& other) const;

    /**
     * @brief Not equal operator
     */
    bool operator!=(const FFT2DAbstract& other) const;

    /**
     * @brief process an array by applying the FFT
     */
    virtual void operator()(const blitz::Array<std::complex<double>,2>& src, 
      blitz::Array<std::complex<double>,2>& dst) const = 0;

    /**
     * @brief process an array by applying the FFT inplace
     */
    virtual void operator()(blitz::Array<std::complex<double>,2>& src_dst) const = 0;

    /**
     * @brief Reset the FFT2D object for the given 2D shape
     */
    void reset(const size_t height, const size_t width);

    /**
     * @brief Getters
     */
    size_t getHeight() const { return m_height; }
    size_t getWidth() const { return m_width; }

    /**
     * @brief Setters
     */
    void setHeight(const size_t height);
    void setWidth(const size_t width);

  protected:
    /**
     * Private attributes
     */
    size_t m_height;
    size_t m_width;
};


/**
 * @brief This class implements a direct 2D Discrete Fourier Transform 
 * based on the FFTW library
 */
class FFT2D: public FFT2DAbstract
{
  public:
    /**
     * @brief Constructor
     */ 
    FFT2D();

    /**
     * @brief Constructor: Initialize working arrays
     */ 
    FFT2D(const size_t height, const size_t width);

    /**
     * @brief Copy constructor
     */
    FFT2D(const FFT2D& other);

    /**
     * @brief Destructor
     */
    virtual ~FFT2D();

    /**
     * @brief process an array by applying the direct FFT
     */
    virtual void operator()(const blitz::Array<std::complex<double>,2>& src, 
      blitz::Array<std::complex<double>,2>& dst) const;

    /**
     * @brief process an array by applying the FFT inplace
     */
    virtual void operator()(blitz::Array<std::complex<double>,2>& src_dst) const;
};


/**
 * @brief This class implements a inverse 2D Discrete Fourier Transform 
 * based on the FFTW library
 */
class IFFT2D: public FFT2DAbstract
{
  public:
    /**
     * @brief Constructor
     */ 
    IFFT2D();

    /**
     * @brief Constructor: Initialize working arrays
     */ 
    IFFT2D(const size_t height, const size_t width);

    /**
     * @brief Copy constructor
     */
    IFFT2D(const IFFT2D& other);

    /**
     * @brief Destructor
     */
    virtual ~IFFT2D();

    /**
     * @brief process an array by applying the inverse FFT
     */
    virtual void operator()(const blitz::Array<std::complex<double>,2>& src, 
      blitz::Array<std::complex<double>,2>& dst) const;

    /**
     * @brief process an array by applying the inverse FFT inplace
     */
    virtual void operator()(blitz::Array<std::complex<double>,2>& src_dst) const;
};

/**
 * @}
 */
}}

#endif /* BOB_SP_FFT2D_H */
