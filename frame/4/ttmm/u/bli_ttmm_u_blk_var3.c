/*

   BLIS
   An object-based framework for developing high-performance BLAS-like
   libraries.

   Copyright (C) 2022, The University of Texas at Austin
   Copyright (C) 2022, Oracle Labs, Oracle Corporation

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    - Neither the name(s) of the copyright holder(s) nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "blis.h"

#ifdef BLIS_ENABLE_LEVEL4

err_t bli_ttmm_u_blk_var3
     (
       const obj_t*  a,
       const cntx_t* cntx,
             rntm_t* rntm,
             cntl_t* cntl
     )
{
	const dim_t m = bli_obj_length( a );

	dim_t b_alg;

	      /* a00    a01    a02 */
	obj_t           a11,   a12;
	obj_t                  a22;

	for ( dim_t ij = 0; ij < m; ij += b_alg )
	{
		b_alg = bli_ttmm_determine_blocksize( ij, m, a, cntx, cntl );

		bli_acquire_mparts_tl2br( ij, b_alg, a,
		                          NULL, NULL, NULL,
		                          NULL, &a11, &a12,
		                          NULL, NULL, &a22 );

		// A11 = triu( A11 ) * triu( A11 )';
		bli_ttmm_int( &a11, cntx, rntm, bli_cntl_sub_node( cntl ) );

		// A11 = A11 + A12 * A12';
		bli_obj_set_struc( BLIS_HERMITIAN, &a11 );
		bli_obj_set_struc( BLIS_GENERAL, &a12 );
		bli_herk_ex( &BLIS_ONE, &a12, &BLIS_ONE, &a11, cntx, rntm );

		// A12 = A21 * triu( A22 )';
		bli_obj_set_conjtrans( BLIS_CONJ_TRANSPOSE, &a22 );
		bli_trmm_ex( BLIS_RIGHT, &BLIS_ONE, &a22, &a12, cntx, rntm );
	}

	return BLIS_SUCCESS;
}

#endif
