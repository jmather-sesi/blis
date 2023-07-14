/* f2c_ilaclc.f -- translated by f2c (version 20100827). You must link the resulting object file with libf2c: on Microsoft Windows system, link with libf2c.lib;
 on Linux or Unix systems, link with .../path/to/libf2c.a -lm or, if you install libf2c.a in a standard place, with -lf2c -lm -- in that order, at the end of the command line, as in cc *.o -lf2c -lm Source for libf2c is in /netlib/f2c/libf2c.zip, e.g., http://www.netlib.org/f2c/libf2c.zip */
 #include "blis.h" /* > \brief \b ILACLC scans a matrix for its last non-zero column. */
 /* =========== DOCUMENTATION =========== */
 /* Online html documentation available at */
 /* http://www.netlib.org/lapack/explore-html/ */
 /* > \htmlonly */
 /* > Download ILACLC + dependencies */
 /* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/ilaclc. f"> */
 /* > [TGZ]</a> */
 /* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/ilaclc. f"> */
 /* > [ZIP]</a> */
 /* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/ilaclc. f"> */
 /* > [TXT]</a> */
 /* > \endhtmlonly */
 /* Definition: */
 /* =========== */
 /* INTEGER FUNCTION ILACLC( M, N, A, LDA ) */
 /* .. Scalar Arguments .. */
 /* INTEGER M, N, LDA */
 /* .. */
 /* .. Array Arguments .. */
 /* COMPLEX A( LDA, * ) */
 /* .. */
 /* > \par Purpose: */
 /* ============= */
 /* > */
 /* > \verbatim */
 /* > */
 /* > ILACLC scans A for its last non-zero column. */
 /* > \endverbatim */
 /* Arguments: */
 /* ========== */
 /* > \param[in] M */
 /* > \verbatim */
 /* > M is INTEGER */
 /* > The number of rows of the matrix A. */
 /* > \endverbatim */
 /* > */
 /* > \param[in] N */
 /* > \verbatim */
 /* > N is INTEGER */
 /* > The number of columns of the matrix A. */
 /* > \endverbatim */
 /* > */
 /* > \param[in] A */
 /* > \verbatim */
 /* > A is COMPLEX array, dimension (LDA,N) */
 /* > The m by n matrix A. */
 /* > \endverbatim */
 /* > */
 /* > \param[in] LDA */
 /* > \verbatim */
 /* > LDA is INTEGER */
 /* > The leading dimension of the array A. LDA >= bla_a_max(1,M). */
 /* > \endverbatim */
 /* Authors: */
 /* ======== */
 /* > \author Univ. of Tennessee */
 /* > \author Univ. of California Berkeley */
 /* > \author Univ. of Colorado Denver */
 /* > \author NAG Ltd. */
 /* > \ingroup bla_scomplexOTHERauxiliary */
 /* ===================================================================== */
 bla_integer f2c_ilaclc_(bla_integer *m, bla_integer *n, bla_scomplex *a, bla_integer *lda) {
 /* System generated locals */
 bla_integer a_dim1, a_offset, ret_val, i__1, i__2;
 /* Local variables */
 bla_integer i__;
 /* -- LAPACK auxiliary routine -- */
 /* -- LAPACK is a software package provided by Univ. of Tennessee, -- */
 /* -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
 /* .. Scalar Arguments .. */
 /* .. */
 /* .. Array Arguments .. */
 /* .. */
 /* ===================================================================== */
 /* .. Parameters .. */
 /* .. */
 /* .. Local Scalars .. */
 /* .. */
 /* .. Executable Statements .. */
 /* Quick test for the common case where one corner is non-zero. */
 /* Parameter adjustments */
 a_dim1 = *lda;
 a_offset = 1 + a_dim1;
 a -= a_offset;
 /* Function Body */
 if (*n == 0) {
 ret_val = *n;
 }
 else /* if(complicated condition) */
 {
 i__1 = *n * a_dim1 + 1;
 i__2 = *m + *n * a_dim1;
 if (a[i__1].real != 0.f || a[i__1].imag != 0.f || (a[i__2].real != 0.f || a[ i__2].imag != 0.f)) {
 ret_val = *n;
 }
 else {
 /* Now scan each column from the end, returning with the first non-zero. */
 for (ret_val = *n;
 ret_val >= 1;
 --ret_val) {
 i__1 = *m;
 for (i__ = 1;
 i__ <= i__1;
 ++i__) {
 i__2 = i__ + ret_val * a_dim1;
 if (a[i__2].real != 0.f || a[i__2].imag != 0.f) {
 return ret_val;
 }
 }
 }
 }
 }
 return ret_val;
 }
 /* f2c_ilaclc_ */
 
