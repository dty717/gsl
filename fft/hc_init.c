TYPE(gsl_fft_wavetable_halfcomplex) *
FUNCTION(gsl_fft_halfcomplex,alloc) (size_t n)
{
  int status;
  size_t i;
  size_t n_factors;
  size_t t, product, product_1, q;
  double d_theta;

  TYPE(gsl_fft_wavetable_halfcomplex) * wavetable ;

  if (n == 0)
    {
      GSL_ERROR_RETURN ("length n must be positive integer", GSL_EDOM, 0);
    }

  wavetable = (TYPE(gsl_fft_wavetable_halfcomplex) *) 
    malloc(sizeof(TYPE(gsl_fft_wavetable_halfcomplex)));

  if (wavetable == NULL)
    {
      GSL_ERROR_RETURN ("failed to allocate struct", GSL_ENOMEM, 0);
    }

  wavetable->scratch = (BASE *) malloc (2 * n * sizeof (BASE));

  if (wavetable->scratch == NULL)
    {
      /* error in constructor, prevent memory leak */

      free(wavetable) ; 

      GSL_ERROR_RETURN ("failed to allocate scratch space", GSL_ENOMEM, 0);
    }

  wavetable->trig = (gsl_complex *) malloc (n * sizeof (gsl_complex));

  if (wavetable->trig == NULL)
    {
      /* error in constructor, prevent memory leak */

      free(wavetable->scratch) ; 
      free(wavetable) ; 

      GSL_ERROR_RETURN ("failed to allocate trigonometric lookup table", 
			GSL_ENOMEM, 0);
    }

  wavetable->n = n ;

  status = fft_halfcomplex_factorize (n, &n_factors, wavetable->factor);

  if (status)
    {
      /* error in constructor, prevent memory leak */

      free(wavetable->trig) ; 
      free(wavetable->scratch) ; 
      free(wavetable) ; 

      GSL_ERROR_RETURN ("factorization failed", GSL_EFACTOR, 0);
    }

  wavetable->nf = n_factors;

  d_theta = 2.0 * M_PI / ((double) n);

  t = 0;
  product = 1;
  for (i = 0; i < n_factors; i++)
    {
      size_t j;
      const size_t factor = wavetable->factor[i];
      wavetable->twiddle[i] = wavetable->trig + t;
      product_1 = product;	/* product_1 = p_(i-1) */
      product *= factor;
      q = n / product;

      for (j = 1; j < factor; j++)
	{
	  size_t k;
	  size_t m = 0;
	  for (k = 1; k < (q + 1) / 2; k++)
	    {
	      double theta;
	      m = m + j * product_1;
	      m = m % n;
	      theta = d_theta * m;	/*  d_theta*j*k*product_1 */
	      GSL_REAL(wavetable->trig[t]) = cos (theta);
	      GSL_IMAG(wavetable->trig[t]) = sin (theta);

	      t++;
	    }
	}
    }

  if (t > (n / 2))
    {
      /* error in constructor, prevent memory leak */

      free(wavetable->trig) ; 
      free(wavetable->scratch) ; 
      free(wavetable) ; 

      GSL_ERROR_RETURN ("overflowed trigonometric lookup table", GSL_ESANITY, 0);
    }

  return wavetable;
}


void
FUNCTION(gsl_fft_halfcomplex,free) (TYPE(gsl_fft_wavetable_halfcomplex) * wavetable)
{

  /* release scratch space and trigonometric lookup tables */

  free (wavetable->scratch);
  wavetable->scratch = NULL;

  free (wavetable->trig);
  wavetable->trig = NULL;

  free (wavetable);
}
