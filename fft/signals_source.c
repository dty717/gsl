#include "signals.h"

int
FUNCTION(fft_signal,complex_pulse) (const size_t k,
				    const size_t n,
				    const size_t stride,
				    const double z_real,
				    const double z_imag,
				    BASE data[],
				    BASE fft[])
{
  size_t j;

  if (n == 0)
    {
      GSL_ERROR ("length n must be positive integer", GSL_EDOM);
    }

  /* gsl_complex pulse at position k,  data[j] = z * delta_{jk} */

  for (j = 0; j < n; j++)
    {
      REAL(data,stride,j) = 0.0;
      IMAG(data,stride,j) = 0.0;
    }

  REAL(data,stride,k % n) = z_real;
  IMAG(data,stride,k % n) = z_imag;

  /* fourier transform, fft[j] = z * exp(-2 pi i j k / n) */

  for (j = 0; j < n; j++)
    {
      const double arg = -2 * M_PI * ((double) ((j * k) % n)) / ((double) n);
      const double w_real = cos (arg);
      const double w_imag = sin (arg);
      REAL(fft,stride,j) = w_real * z_real - w_imag * z_imag;
      IMAG(fft,stride,j) = w_real * z_imag + w_imag * z_real;
    }

  return 0;

}


int
FUNCTION(fft_signal,complex_constant) (const size_t n,
				       const size_t stride,
				       const double z_real,
				       const double z_imag,
				       BASE data[],
				       BASE fft[])
{
  size_t j;

  if (n == 0)
    {
      GSL_ERROR ("length n must be positive integer", GSL_EDOM);
    }

  /* constant, data[j] = z */

  for (j = 0; j < n; j++)
    {
      REAL(data,stride,j) = z_real;
      IMAG(data,stride,j) = z_imag;
    }

  /* fourier transform, fft[j] = n z delta_{j0} */

  for (j = 0; j < n; j++)
    {
      REAL(fft,stride,j) = 0.0;
      IMAG(fft,stride,j) = 0.0;
    }

  REAL(fft,stride,0) = ((double) n) * z_real;
  IMAG(fft,stride,0) = ((double) n) * z_imag;

  return 0;

}


int
FUNCTION(fft_signal,complex_exp) (const int k,
				  const size_t n,
				  const size_t stride,
				  const double z_real,
				  const double z_imag,
				  BASE data[],
				  BASE fft[])
{
  size_t j;

  if (n == 0)
    {
      GSL_ERROR ("length n must be positive integer", GSL_EDOM);
    }

  /* exponential,  data[j] = z * exp(2 pi i j k) */

  for (j = 0; j < n; j++)
    {
      const double arg = 2 * M_PI * ((double) ((j * k) % n)) / ((double) n);
      const double w_real = cos (arg);
      const double w_imag = sin (arg);
      REAL(data,stride,j) = w_real * z_real - w_imag * z_imag;
      IMAG(data,stride,j) = w_real * z_imag + w_imag * z_real;
    }

  /* fourier transform, fft[j] = z * delta{(j - k),0} */

  for (j = 0; j < n; j++)
    {
      REAL(fft,stride,j) = 0.0;
      IMAG(fft,stride,j) = 0.0;
    }

  {
    int freq;

    if (k <= 0)
      {
	freq = (n-k) % n ;
      }
    else
      {
	freq = (k % n);
      };

    REAL(fft,stride,freq) = ((double) n) * z_real;
    IMAG(fft,stride,freq) = ((double) n) * z_imag;
  }

  return 0;

}


int
FUNCTION(fft_signal,complex_exppair) (const int k1,
				      const int k2,
				      const size_t n,
				      const size_t stride,
				      const double z1_real,
				      const double z1_imag,
				      const double z2_real,
				      const double z2_imag,
				      BASE data[],
				      BASE fft[])
{
  size_t j;

  if (n == 0)
    {
      GSL_ERROR ("length n must be positive integer", GSL_EDOM);
    }

  /* exponential,  data[j] = z1 * exp(2 pi i j k1) + z2 * exp(2 pi i j k2) */

  for (j = 0; j < n; j++)
    {
      const double arg1 = 2 * M_PI * ((double) ((j * k1) % n)) / ((double) n);
      const double w1_real = cos (arg1);
      const double w1_imag = sin (arg1);
      const double arg2 = 2 * M_PI * ((double) ((j * k2) % n)) / ((double) n);
      const double w2_real = cos (arg2);
      const double w2_imag = sin (arg2);
      REAL(data,stride,j) = w1_real * z1_real - w1_imag * z1_imag;
      IMAG(data,stride,j) = w1_real * z1_imag + w1_imag * z1_real;
      REAL(data,stride,j) += w2_real * z2_real - w2_imag * z2_imag;
      IMAG(data,stride,j) += w2_real * z2_imag + w2_imag * z2_real;
    }

  /* fourier transform, fft[j] = z1 * delta{(j - k1),0} + z2 *
     delta{(j - k2,0)} */

  for (j = 0; j < n; j++)
    {
      REAL(fft,stride,j) = 0.0;
      IMAG(fft,stride,j) = 0.0;
    }

  {
    int freq1, freq2;

    if (k1 <= 0)
      {
	freq1 = (n - k1) % n;
      }
    else
      {
	freq1 = (k1 % n);
      };

    if (k2 <= 0)
      {
	freq2 = (n - k2) % n;
      }
    else
      {
	freq2 = (k2 % n);
      };

    REAL(fft,stride,freq1) += ((double) n) * z1_real;
    IMAG(fft,stride,freq1) += ((double) n) * z1_imag;
    REAL(fft,stride,freq2) += ((double) n) * z2_real;
    IMAG(fft,stride,freq2) += ((double) n) * z2_imag;
  }

  return 0;

}


int
FUNCTION(fft_signal,complex_noise) (const size_t n,
				    const size_t stride,
				    BASE data[],
				    BASE fft[])
{
  size_t i;
  int status;

  if (n == 0)
    {
      GSL_ERROR ("length n must be positive integer", GSL_EDOM);
    }

  for (i = 0; i < n; i++)
    {
      REAL(data,stride,i) = ((double) rand ()) / RAND_MAX;
      IMAG(data,stride,i) = ((double) rand ()) / RAND_MAX;
    }

  /* compute the dft */
  status = FUNCTION(gsl_dft_complex,forward) (data, stride, n, fft);

  return status;
}


int
FUNCTION(fft_signal,real_noise) (const size_t n,
				 const size_t stride,
				 BASE data[],
				 BASE fft[])
{
  size_t i;
  int status;

  if (n == 0)
    {
      GSL_ERROR ("length n must be positive integer", GSL_EDOM);
    }

  for (i = 0; i < n; i++)
    {
      REAL(data,stride,i) = ((double) rand ()) / RAND_MAX;
      IMAG(data,stride,i) = 0.0;
    }

  /* compute the dft */
  status = FUNCTION(gsl_dft_complex,forward) (data, stride, n, fft);

  return status;
}

