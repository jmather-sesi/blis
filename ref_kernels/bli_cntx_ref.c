/*

   BLIS
   An object-based framework for developing high-performance BLAS-like
   libraries.

   Copyright (C) 2014, The University of Texas at Austin
   Copyright (C) 2018 - 2020, Advanced Micro Devices, Inc.

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

// -- Instantiate kernel prototypes for the current architecture ---------------

// Define macros to construct the full symbol name from the operation name.
#undef  GENARNAME             // architecture, _ref (no bli_)
#define GENARNAME(opname)     PASTECH2(opname,BLIS_CNAME_INFIX,BLIS_REF_SUFFIX)
#undef  GENBARNAME            // bli_, architecture, _ref
#define GENBARNAME(opname)    PASTEMAC2(opname,BLIS_CNAME_INFIX,BLIS_REF_SUFFIX)
#undef  GENBAINAME            // bli_, architecture, _ind
#define GENBAINAME(opname)    PASTEMAC2(opname,BLIS_CNAME_INFIX,BLIS_IND_SUFFIX)

// -- Level-3 native micro-kernel prototype redefinitions ----------------------

// -- Prototypes for completely generic level-3 microkernels --

#undef  gemm_ukr_name
#define gemm_ukr_name       GENARNAME(gemm)
#undef  gemmtrsm_l_ukr_name
#define gemmtrsm_l_ukr_name GENARNAME(gemmtrsm_l)
#undef  gemmtrsm_u_ukr_name
#define gemmtrsm_u_ukr_name GENARNAME(gemmtrsm_u)
#undef  trsm_l_ukr_name
#define trsm_l_ukr_name     GENARNAME(trsm_l)
#undef  trsm_u_ukr_name
#define trsm_u_ukr_name     GENARNAME(trsm_u)

// Instantiate prototypes for above functions via the native micro-kernel API
// template.
#include "bli_l3_ukr.h"

// -- Level-3 virtual micro-kernel prototype redefinitions ---------------------

// -- Prototypes for induced method level-3 microkernels --

// -- 1m --

#undef  gemm1m_ukr_name
#define gemm1m_ukr_name        GENARNAME(gemm1m)
#undef  gemmtrsm1m_l_ukr_name
#define gemmtrsm1m_l_ukr_name  GENARNAME(gemmtrsm1m_l)
#undef  gemmtrsm1m_u_ukr_name
#define gemmtrsm1m_u_ukr_name  GENARNAME(gemmtrsm1m_u)

// Instantiate prototypes for above functions via the virtual micro-kernel API
// template.
#include "bli_l3_ind_ukr.h"

// -- Level-3 small/unpacked micro-kernel prototype definitions ----------------

// NOTE: This results in redundant prototypes for gemmsup_r and gemmsup_c
// kernels, but since they will be identical the compiler won't complain.

#undef  gemmsup_rv_ukr_name
#define gemmsup_rv_ukr_name   GENARNAME(gemmsup_r)
#undef  gemmsup_rg_ukr_name
#define gemmsup_rg_ukr_name   GENARNAME(gemmsup_r)
#undef  gemmsup_cv_ukr_name
#define gemmsup_cv_ukr_name   GENARNAME(gemmsup_c)
#undef  gemmsup_cg_ukr_name
#define gemmsup_cg_ukr_name   GENARNAME(gemmsup_c)

#undef  gemmsup_gx_ukr_name
#define gemmsup_gx_ukr_name   GENARNAME(gemmsup_g)

// Include the small/unpacked kernel API template.
#include "bli_l3_sup_ker.h"

// -- Level-1m (packm/unpackm) kernel prototype redefinitions ------------------

#undef  packm_mrxk_ker_name
#define packm_mrxk_ker_name  GENARNAME(packm_mrxk)
#undef  packm_nrxk_ker_name
#define packm_nrxk_ker_name  GENARNAME(packm_nrxk)

#undef  packm_mrxk_1er_ker_name
#define packm_mrxk_1er_ker_name  GENARNAME(packm_mrxk_1er)
#undef  packm_nrxk_1er_ker_name
#define packm_nrxk_1er_ker_name  GENARNAME(packm_nrxk_1er)

#undef  packm_mrxmr_diag_ker_name
#define packm_mrxmr_diag_ker_name  GENARNAME(packm_mrxmr_diag)
#undef  packm_nrxnr_diag_ker_name
#define packm_nrxnr_diag_ker_name  GENARNAME(packm_nrxnr_diag)

#undef  packm_mrxmr_diag_1er_ker_name
#define packm_mrxmr_diag_1er_ker_name  GENARNAME(packm_mrxmr_diag_1er)
#undef  packm_nrxnr_diag_1er_ker_name
#define packm_nrxnr_diag_1er_ker_name  GENARNAME(packm_nrxnr_diag_1er)

#undef  unpackm_mrxk_ker_name
#define unpackm_mrxk_ker_name  GENARNAME(unpackm_mrxk)
#undef  unpackm_nrxk_ker_name
#define unpackm_nrxk_ker_name  GENARNAME(unpackm_nrxk)

// Instantiate prototypes for above functions via the level-1m kernel API
// template.
#include "bli_l1m_ker.h"

// -- Level-1f kernel prototype redefinitions ----------------------------------

#undef  axpy2v_ker_name
#define axpy2v_ker_name     GENARNAME(axpy2v)
#undef  dotaxpyv_ker_name
#define dotaxpyv_ker_name   GENARNAME(dotaxpyv)
#undef  axpyf_ker_name
#define axpyf_ker_name      GENARNAME(axpyf)
#undef  dotxf_ker_name
#define dotxf_ker_name      GENARNAME(dotxf)
#undef  dotxaxpyf_ker_name
#define dotxaxpyf_ker_name  GENARNAME(dotxaxpyf)

// Instantiate prototypes for above functions via the level-1f kernel API
// template.
#include "bli_l1f_ker.h"

// -- Level-1v kernel prototype redefinitions ----------------------------------

// -- prototypes for completely generic level-1v kernels --

#undef  addv_ker_name
#define addv_ker_name      GENARNAME(addv)
#undef  amaxv_ker_name
#define amaxv_ker_name     GENARNAME(amaxv)
#undef  axpbyv_ker_name
#define axpbyv_ker_name    GENARNAME(axpbyv)
#undef  axpyv_ker_name
#define axpyv_ker_name     GENARNAME(axpyv)
#undef  copyv_ker_name
#define copyv_ker_name     GENARNAME(copyv)
#undef  dotv_ker_name
#define dotv_ker_name      GENARNAME(dotv)
#undef  dotxv_ker_name
#define dotxv_ker_name     GENARNAME(dotxv)
#undef  invertv_ker_name
#define invertv_ker_name   GENARNAME(invertv)
#undef  invscalv_ker_name
#define invscalv_ker_name  GENARNAME(invscalv)
#undef  scalv_ker_name
#define scalv_ker_name     GENARNAME(scalv)
#undef  scal2v_ker_name
#define scal2v_ker_name    GENARNAME(scal2v)
#undef  setv_ker_name
#define setv_ker_name      GENARNAME(setv)
#undef  subv_ker_name
#define subv_ker_name      GENARNAME(subv)
#undef  swapv_ker_name
#define swapv_ker_name     GENARNAME(swapv)
#undef  xpbyv_ker_name
#define xpbyv_ker_name     GENARNAME(xpbyv)

// Instantiate prototypes for above functions via the level-1v kernel API
// template.
#include "bli_l1v_ker.h"

// -- Macros to help concisely instantiate bli_func_init() ---------------------

#define gen_func_init_ro( func_p, opname ) \
do { \
	bli_func_init( func_p, PASTEMAC(s,opname), PASTEMAC(d,opname), \
	                       NULL,               NULL ); \
} while (0)

#define gen_func_init_co( func_p, opname ) \
do { \
	bli_func_init( func_p, NULL,               NULL, \
	                       PASTEMAC(c,opname), PASTEMAC(z,opname) ); \
} while (0)

#define gen_func_init( func_p, opname ) \
do { \
	bli_func_init( func_p, PASTEMAC(s,opname), PASTEMAC(d,opname), \
	                       PASTEMAC(c,opname), PASTEMAC(z,opname) ); \
} while (0)

#define gen_sup_func_init( func0_p, func1_p, opname ) \
do { \
	bli_func_init( func0_p, PASTEMAC(s,opname), PASTEMAC(d,opname), \
	                        PASTEMAC(c,opname), PASTEMAC(z,opname) ); \
	bli_func_init( func1_p, PASTEMAC(s,opname), PASTEMAC(d,opname), \
	                        PASTEMAC(c,opname), PASTEMAC(z,opname) ); \
} while (0)

// -- Helper function for 1m ---------------------------------------------------

void GENBAINAME(cntx_init_blkszs)
     (
       ind_t   method,
       num_t   dt,
       cntx_t* cntx
     );

// -----------------------------------------------------------------------------

void GENBARNAME(cntx_init)
     (
       cntx_t* cntx
     )
{
	blksz_t  blkszs[ BLIS_NUM_BLKSZS ];
	func_t*  funcs;
	mbool_t* mbools;
	dim_t    i;
	void_fp* vfuncs;


	// -- Clear the context ----------------------------------------------------

	bli_cntx_clear( cntx );


	// -- Set blocksizes -------------------------------------------------------

	// NOTE: The macro values for register blocksizes and packm broadcast factors are
	// used here as defined in the bli_kernel_defs_<family>.h or generic values from
	// bli_kernel_macro_defs.h otherwise. Configurations should also initialize the
	// blocksizes in the context explicitly, but using the correct values here helps
	// to prevent accidents.
	//                                                    s              d              c              z
	bli_blksz_init_easy( &blkszs[ BLIS_KR  ],             1,             1,             1,             1 );
	bli_blksz_init     ( &blkszs[ BLIS_MR  ],     BLIS_MR_s,     BLIS_MR_d,     BLIS_MR_c,     BLIS_MR_z,
	                                          BLIS_PACKMR_s, BLIS_PACKMR_d, BLIS_PACKMR_c, BLIS_PACKMR_z );
	bli_blksz_init     ( &blkszs[ BLIS_NR  ],     BLIS_NR_s,     BLIS_NR_d,     BLIS_NR_c,     BLIS_NR_z,
	                                          BLIS_PACKNR_s, BLIS_PACKNR_d, BLIS_PACKNR_c, BLIS_PACKNR_z );
	bli_blksz_init_easy( &blkszs[ BLIS_MC  ],           256,           128,           128,            64 );
	bli_blksz_init_easy( &blkszs[ BLIS_KC  ],           256,           256,           256,           256 );
	bli_blksz_init_easy( &blkszs[ BLIS_NC  ],          4096,          4096,          4096,          4096 );
	bli_blksz_init_easy( &blkszs[ BLIS_M2  ],          1000,          1000,          1000,          1000 );
	bli_blksz_init_easy( &blkszs[ BLIS_N2  ],          1000,          1000,          1000,          1000 );
	bli_blksz_init_easy( &blkszs[ BLIS_AF  ],             8,             8,             8,             8 );
	bli_blksz_init_easy( &blkszs[ BLIS_DF  ],             6,             6,             6,             6 );
	bli_blksz_init_easy( &blkszs[ BLIS_XF  ],             4,             4,             4,             4 );
	bli_blksz_init_easy( &blkszs[ BLIS_BBM ],    BLIS_BBM_s,    BLIS_BBM_d,    BLIS_BBM_c,    BLIS_BBM_z );
	bli_blksz_init_easy( &blkszs[ BLIS_BBN ],    BLIS_BBN_s,    BLIS_BBN_d,    BLIS_BBN_c,    BLIS_BBN_z );

	// -- Set level-3 small/unpacked thresholds --------------------------------

	// NOTE: The default thresholds are set to zero so that the sup framework
	// does not activate by default. Note that the semantic meaning of the
	// thresholds is that the sup code path is executed if a dimension is
	// strictly less than its corresponding threshold. So actually, the
	// thresholds specify the minimum dimension size that will still dispatch
	// the non-sup/large code path. This "strictly less than" behavior was
	// chosen over "less than or equal to" so that threshold values of 0 would
	// effectively disable sup (even for matrix dimensions of 0).
	//                                          s     d     c     z
	bli_blksz_init_easy( &blkszs[ BLIS_MT ],    0,    0,    0,    0 );
	bli_blksz_init_easy( &blkszs[ BLIS_NT ],    0,    0,    0,    0 );
	bli_blksz_init_easy( &blkszs[ BLIS_KT ],    0,    0,    0,    0 );

	// Initialize the context with the default blocksize objects and their
	// multiples.
	bli_cntx_set_blkszs
	(
	  cntx,
	  BLIS_NC,  &blkszs[ BLIS_NC  ], BLIS_NR,
	  BLIS_KC,  &blkszs[ BLIS_KC  ], BLIS_KR,
	  BLIS_MC,  &blkszs[ BLIS_MC  ], BLIS_MR,
	  BLIS_NR,  &blkszs[ BLIS_NR  ], BLIS_NR,
	  BLIS_MR,  &blkszs[ BLIS_MR  ], BLIS_MR,
	  BLIS_KR,  &blkszs[ BLIS_KR  ], BLIS_KR,
	  BLIS_M2,  &blkszs[ BLIS_M2  ], BLIS_M2,
	  BLIS_N2,  &blkszs[ BLIS_N2  ], BLIS_N2,
	  BLIS_AF,  &blkszs[ BLIS_AF  ], BLIS_AF,
	  BLIS_DF,  &blkszs[ BLIS_DF  ], BLIS_DF,
	  BLIS_XF,  &blkszs[ BLIS_XF  ], BLIS_XF,
	  BLIS_MT,  &blkszs[ BLIS_MT  ], BLIS_MT,
	  BLIS_NT,  &blkszs[ BLIS_NT  ], BLIS_NT,
	  BLIS_KT,  &blkszs[ BLIS_KT  ], BLIS_KT,
	  BLIS_BBM, &blkszs[ BLIS_BBM ], BLIS_BBM,
	  BLIS_BBN, &blkszs[ BLIS_BBN ], BLIS_BBN,
	  BLIS_VA_END
	);


	// -- Set level-3 virtual micro-kernels ------------------------------------

	funcs = cntx->ukrs;

	// NOTE: We set the virtual micro-kernel slots to contain the addresses
	// of the native micro-kernels. In general, the ukernels in the virtual
	// ukernel slots are always called, and if the function called happens to
	// be a virtual micro-kernel, it will then know to find its native ukernel
	// (i.e., in the native ukernel slots).
	gen_func_init( &funcs[ BLIS_GEMM_VIR_UKR ],       gemm_ukr_name       );
	gen_func_init( &funcs[ BLIS_GEMMTRSM_L_VIR_UKR ], gemmtrsm_l_ukr_name );
	gen_func_init( &funcs[ BLIS_GEMMTRSM_U_VIR_UKR ], gemmtrsm_u_ukr_name );
	gen_func_init( &funcs[ BLIS_TRSM_L_VIR_UKR ],     trsm_l_ukr_name     );
	gen_func_init( &funcs[ BLIS_TRSM_U_VIR_UKR ],     trsm_u_ukr_name     );


	// -- Set level-3 native micro-kernels and preferences ---------------------

	mbools = cntx->ukr_prefs;

	gen_func_init( &funcs[ BLIS_GEMM_UKR ],       gemm_ukr_name       );
	gen_func_init( &funcs[ BLIS_GEMMTRSM_L_UKR ], gemmtrsm_l_ukr_name );
	gen_func_init( &funcs[ BLIS_GEMMTRSM_U_UKR ], gemmtrsm_u_ukr_name );
	gen_func_init( &funcs[ BLIS_TRSM_L_UKR ],     trsm_l_ukr_name     );
	gen_func_init( &funcs[ BLIS_TRSM_U_UKR ],     trsm_u_ukr_name     );

	gen_func_init_ro( &funcs[ BLIS_GEMM1M_UKR ],       gemm1m_ukr_name       );
	gen_func_init_ro( &funcs[ BLIS_GEMMTRSM1M_L_UKR ], gemmtrsm1m_l_ukr_name );
	gen_func_init_ro( &funcs[ BLIS_GEMMTRSM1M_U_UKR ], gemmtrsm1m_u_ukr_name );

	//                                                           s      d      c      z
	bli_mbool_init( &mbools[ BLIS_GEMM_UKR_ROW_PREF ],        TRUE,  TRUE,  TRUE,  TRUE );
	bli_mbool_init( &mbools[ BLIS_GEMMTRSM_L_UKR_ROW_PREF ], FALSE, FALSE, FALSE, FALSE );
	bli_mbool_init( &mbools[ BLIS_GEMMTRSM_U_UKR_ROW_PREF ], FALSE, FALSE, FALSE, FALSE );
	bli_mbool_init( &mbools[ BLIS_TRSM_L_UKR_ROW_PREF ],     FALSE, FALSE, FALSE, FALSE );
	bli_mbool_init( &mbools[ BLIS_TRSM_U_UKR_ROW_PREF ],     FALSE, FALSE, FALSE, FALSE );


	// -- Set level-3 small/unpacked micro-kernels and preferences -------------

	gen_func_init( &funcs[ BLIS_GEMMSUP_RRR_UKR ], gemmsup_rv_ukr_name );
	gen_func_init( &funcs[ BLIS_GEMMSUP_RRC_UKR ], gemmsup_rv_ukr_name );
	gen_func_init( &funcs[ BLIS_GEMMSUP_RCR_UKR ], gemmsup_rv_ukr_name );
	gen_func_init( &funcs[ BLIS_GEMMSUP_RCC_UKR ], gemmsup_rv_ukr_name );
	gen_func_init( &funcs[ BLIS_GEMMSUP_CRR_UKR ], gemmsup_rv_ukr_name );
	gen_func_init( &funcs[ BLIS_GEMMSUP_CRC_UKR ], gemmsup_rv_ukr_name );
	gen_func_init( &funcs[ BLIS_GEMMSUP_CCR_UKR ], gemmsup_rv_ukr_name );
	gen_func_init( &funcs[ BLIS_GEMMSUP_CCC_UKR ], gemmsup_rv_ukr_name );

	// Register the general-stride/generic ukernel to the "catch-all" slot
	// associated with the BLIS_XXX enum value. This slot will be queried if
	// *any* operand is stored with general stride.
	gen_func_init( &funcs[ BLIS_GEMMSUP_XXX_UKR ], gemmsup_gx_ukr_name );


	// Set the l3 sup ukernel storage preferences.
	//                                                            s      d      c      z
	bli_mbool_init( &mbools[ BLIS_GEMMSUP_RRR_UKR_ROW_PREF ],  TRUE,  TRUE,  TRUE,  TRUE );
	bli_mbool_init( &mbools[ BLIS_GEMMSUP_RRC_UKR_ROW_PREF ],  TRUE,  TRUE,  TRUE,  TRUE );
	bli_mbool_init( &mbools[ BLIS_GEMMSUP_RCR_UKR_ROW_PREF ],  TRUE,  TRUE,  TRUE,  TRUE );
	bli_mbool_init( &mbools[ BLIS_GEMMSUP_RCC_UKR_ROW_PREF ],  TRUE,  TRUE,  TRUE,  TRUE );
	bli_mbool_init( &mbools[ BLIS_GEMMSUP_CRR_UKR_ROW_PREF ],  TRUE,  TRUE,  TRUE,  TRUE );
	bli_mbool_init( &mbools[ BLIS_GEMMSUP_CRC_UKR_ROW_PREF ],  TRUE,  TRUE,  TRUE,  TRUE );
	bli_mbool_init( &mbools[ BLIS_GEMMSUP_CCR_UKR_ROW_PREF ],  TRUE,  TRUE,  TRUE,  TRUE );
	bli_mbool_init( &mbools[ BLIS_GEMMSUP_CCC_UKR_ROW_PREF ],  TRUE,  TRUE,  TRUE,  TRUE );

	bli_mbool_init( &mbools[ BLIS_GEMMSUP_XXX_UKR_ROW_PREF ],  TRUE,  TRUE,  TRUE,  TRUE );


	// -- Set level-1f kernels -------------------------------------------------

	gen_func_init( &funcs[ BLIS_AXPY2V_KER ],    axpy2v_ker_name    );
	gen_func_init( &funcs[ BLIS_DOTAXPYV_KER ],  dotaxpyv_ker_name  );
	gen_func_init( &funcs[ BLIS_AXPYF_KER ],     axpyf_ker_name     );
	gen_func_init( &funcs[ BLIS_DOTXF_KER ],     dotxf_ker_name     );
	gen_func_init( &funcs[ BLIS_DOTXAXPYF_KER ], dotxaxpyf_ker_name );


	// -- Set level-1v kernels -------------------------------------------------

	gen_func_init( &funcs[ BLIS_ADDV_KER ],     addv_ker_name     );
	gen_func_init( &funcs[ BLIS_AMAXV_KER ],    amaxv_ker_name    );
	gen_func_init( &funcs[ BLIS_AXPBYV_KER ],   axpbyv_ker_name   );
	gen_func_init( &funcs[ BLIS_AXPYV_KER ],    axpyv_ker_name    );
	gen_func_init( &funcs[ BLIS_COPYV_KER ],    copyv_ker_name    );
	gen_func_init( &funcs[ BLIS_DOTV_KER ],     dotv_ker_name     );
	gen_func_init( &funcs[ BLIS_DOTXV_KER ],    dotxv_ker_name    );
	gen_func_init( &funcs[ BLIS_INVERTV_KER ],  invertv_ker_name  );
	gen_func_init( &funcs[ BLIS_INVSCALV_KER ], invscalv_ker_name );
	gen_func_init( &funcs[ BLIS_SCALV_KER ],    scalv_ker_name    );
	gen_func_init( &funcs[ BLIS_SCAL2V_KER ],   scal2v_ker_name   );
	gen_func_init( &funcs[ BLIS_SETV_KER ],     setv_ker_name     );
	gen_func_init( &funcs[ BLIS_SUBV_KER ],     subv_ker_name     );
	gen_func_init( &funcs[ BLIS_SWAPV_KER ],    swapv_ker_name    );
	gen_func_init( &funcs[ BLIS_XPBYV_KER ],    xpbyv_ker_name    );


	// -- Set level-1m (packm/unpackm) kernels ---------------------------------

	gen_func_init( &funcs[ BLIS_PACKM_MRXK_KER ],  packm_mrxk_ker_name );
	gen_func_init( &funcs[ BLIS_PACKM_NRXK_KER ],  packm_nrxk_ker_name );

	gen_func_init_co( &funcs[ BLIS_PACKM_MRXK_1ER_KER ],  packm_mrxk_1er_ker_name );
	gen_func_init_co( &funcs[ BLIS_PACKM_NRXK_1ER_KER ],  packm_nrxk_1er_ker_name );

	gen_func_init( &funcs[ BLIS_PACKM_MRXMR_DIAG_KER ],  packm_mrxmr_diag_ker_name );
	gen_func_init( &funcs[ BLIS_PACKM_NRXNR_DIAG_KER ],  packm_nrxnr_diag_ker_name );

	gen_func_init_co( &funcs[ BLIS_PACKM_MRXMR_DIAG_1ER_KER ],  packm_mrxmr_diag_1er_ker_name );
	gen_func_init_co( &funcs[ BLIS_PACKM_NRXNR_DIAG_1ER_KER ],  packm_nrxnr_diag_1er_ker_name );

	gen_func_init( &funcs[ BLIS_UNPACKM_MRXK_KER ],  unpackm_mrxk_ker_name );
	gen_func_init( &funcs[ BLIS_UNPACKM_NRXK_KER ],  unpackm_nrxk_ker_name );


	// -- Set level-3 small/unpacked handlers ----------------------------------

	vfuncs = cntx->l3_sup_handlers;

	// Initialize all of the function pointers to NULL;
	for ( i = 0; i < BLIS_NUM_LEVEL3_OPS; ++i ) vfuncs[ i ] = NULL;

	// The level-3 sup handlers are oapi-based, so we only set one slot per
	// operation.

	// Set the gemm slot to the default gemm sup handler.
	vfuncs[ BLIS_GEMM ]  = bli_gemmsup_ref;
	vfuncs[ BLIS_GEMMT ] = bli_gemmtsup_ref;


	// -- Set miscellaneous fields ---------------------------------------------

	bli_cntx_set_method( BLIS_NAT, cntx );
}

// -----------------------------------------------------------------------------

void GENBAINAME(cntx_init)
     (
       ind_t   method,
       cntx_t* cntx
     )
{
	func_t* funcs;

	// This function is designed to modify a copy of an existing native
	// context to enable computation via an induced method for complex
	// domain level-3 operations. It is called by bli_gks_query_ind_cntx()
	// on a context after its contexts are set by copying from the
	// architecture's native context.

	// -- Set induced method level-3 virtual micro-kernels ---------------------

	funcs = cntx->ukrs;

	if ( method == BLIS_1M )
	{
		//gen_func_init_ro( &funcs[ BLIS_GEMM_VIR_UKR ],       gemm1m_ukr_name       );
		//gen_func_init_ro( &funcs[ BLIS_GEMMTRSM_L_VIR_UKR ], gemmtrsm1m_l_ukr_name );
		//gen_func_init_ro( &funcs[ BLIS_GEMMTRSM_U_VIR_UKR ], gemmtrsm1m_u_ukr_name );
	}
	else // if ( method == BLIS_NAT )
	{
		gen_func_init_co( &funcs[ BLIS_GEMM_VIR_UKR ],       gemm_ukr_name       );
		gen_func_init_co( &funcs[ BLIS_GEMMTRSM_L_VIR_UKR ], gemmtrsm_l_ukr_name );
		gen_func_init_co( &funcs[ BLIS_GEMMTRSM_U_VIR_UKR ], gemmtrsm_u_ukr_name );
		gen_func_init_co( &funcs[ BLIS_TRSM_L_VIR_UKR ],     trsm_l_ukr_name     );
		gen_func_init_co( &funcs[ BLIS_TRSM_U_VIR_UKR ],     trsm_u_ukr_name     );
	}

	// For 1m, we employ an optimization which requires that we copy the native
	// real domain gemm ukernel function pointers to the corresponding real
	// domain slots in the virtual gemm ukernel func_t. This optimization allows
	// us to, under certain conditions, adjust various parameters within the gemm
	// macrokernel so that the real-domain macrokernel (which will query and use
	// the real-domain virtual gemm ukernel) can be called instead of calling the
	// complex-domain macrokernel and the corresponding complex-domain virtual
	// microkernel. The non-optimized code path would require an extra level of
	// function call overhead, which can be avoided in most cases (i.e., when
	// beta has a zero imaginary component and C is either row- or column-stored).
	if ( method == BLIS_1M )
	{
		func_t* gemm_nat_ukrs = ( func_t* )bli_cntx_get_ukrs( BLIS_GEMM_UKR, cntx );
		func_t* gemm_vir_ukrs = ( func_t* )bli_cntx_get_ukrs( BLIS_GEMM_VIR_UKR, cntx );

		bli_func_copy_dt( BLIS_FLOAT,  gemm_nat_ukrs, BLIS_FLOAT,  gemm_vir_ukrs );
		bli_func_copy_dt( BLIS_DOUBLE, gemm_nat_ukrs, BLIS_DOUBLE, gemm_vir_ukrs );
	}


	// -- Set induced method packm kernels -------------------------------------

	if ( method == BLIS_1M )
	{
		gen_func_init_co( &funcs[ BLIS_PACKM_MRXK_KER ],  packm_mrxk_1er_ker_name );
		gen_func_init_co( &funcs[ BLIS_PACKM_NRXK_KER ],  packm_nrxk_1er_ker_name );
	}
	else // if ( method == BLIS_NAT )
	{
		gen_func_init( &funcs[ BLIS_PACKM_MRXK_KER ],  packm_mrxk_ker_name );
		gen_func_init( &funcs[ BLIS_PACKM_NRXK_KER ],  packm_nrxk_ker_name );
	}

	gen_func_init_co( &funcs[ BLIS_PACKM_MRXK_1ER_KER ],  packm_mrxk_1er_ker_name );
	gen_func_init_co( &funcs[ BLIS_PACKM_NRXK_1ER_KER ],  packm_nrxk_1er_ker_name );

	gen_func_init( &funcs[ BLIS_UNPACKM_MRXK_KER ],  unpackm_mrxk_ker_name );
	gen_func_init( &funcs[ BLIS_UNPACKM_NRXK_KER ],  unpackm_nrxk_ker_name );


	// -- Set induced method cache and register blocksizes ---------------------

	// Modify the context with cache and register blocksizes (and multiples)
	// appropriate for the current induced method.
	if ( method == BLIS_1M )
	{
		//const bool is_pb = FALSE;

		// Call a helper function to initialize blocksizes for each complex
		// datatype.
		GENBAINAME(cntx_init_blkszs)( method, BLIS_SCOMPLEX, cntx );
		GENBAINAME(cntx_init_blkszs)( method, BLIS_DCOMPLEX, cntx );
	}
	else // if ( method == BLIS_NAT )
	{
		// No change in blocksizes needed for native execution.
	}
}

// -----------------------------------------------------------------------------

void GENBAINAME(cntx_init_blkszs)
     (
       ind_t   method,
       num_t   dt,
       cntx_t* cntx
     )
{
	// Set the induced method in the context.
	bli_cntx_set_method( method, cntx );

	num_t dt_r = bli_dt_proj_to_real( dt );

	// Initialize the blocksizes according to the micro-kernel preference as
	// well as the algorithm.
	//if ( bli_cntx_ukr_prefers_cols_dt( dt, BLIS_GEMM_UKR, cntx ) )
	if ( ! bli_cntx_get_ukr_prefs_dt( dt_r, BLIS_GEMM_UKR_ROW_PREF, cntx ) )
	{
		// This branch is used for algorithm 1m_c_bp.

		bli_cntx_set_ind_blkszs
		(
		  method, dt, cntx,
		  BLIS_NC, 1.0, 1.0,
		  BLIS_KC, 2.0, 2.0, // halve kc...
		  BLIS_MC, 2.0, 2.0, // halve mc...
		  BLIS_NR, 1.0, 1.0,
		  BLIS_MR, 2.0, 1.0, // ...and mr (but NOT packmr)
		  BLIS_KR, 1.0, 1.0,
		  BLIS_VA_END
		);
	}
	else // if ( bli_cntx_get_ukr_prefs_dt( dt, BLIS_GEMM_UKR_ROW_PREF, cntx ) )
	{
		// This branch is used for algorithm 1m_r_bp.

		bli_cntx_set_ind_blkszs
		(
		  method, dt, cntx,
		  BLIS_NC, 2.0, 2.0, // halve nc...
		  BLIS_KC, 2.0, 2.0, // halve kc...
		  BLIS_MC, 1.0, 1.0,
		  BLIS_NR, 2.0, 1.0, // ...and nr (but NOT packnr)
		  BLIS_MR, 1.0, 1.0,
		  BLIS_KR, 1.0, 1.0,
		  BLIS_VA_END
		);
	}
}

