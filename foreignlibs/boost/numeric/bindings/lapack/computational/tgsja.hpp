//
// Copyright (c) 2002--2010
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TGSJA_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TGSJA_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for tgsja is the netlib-compatible backend.
//
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * float value-type.
//
inline std::ptrdiff_t tgsja( const char jobu, const char jobv, const char jobq,
        const fortran_int_t m, const fortran_int_t p, const fortran_int_t n,
        const fortran_int_t k, const fortran_int_t l, float* a,
        const fortran_int_t lda, float* b, const fortran_int_t ldb,
        const float tola, const float tolb, float* alpha, float* beta,
        float* u, const fortran_int_t ldu, float* v, const fortran_int_t ldv,
        float* q, const fortran_int_t ldq, float* work,
        fortran_int_t& ncycle ) {
    fortran_int_t info(0);
    LAPACK_STGSJA( &jobu, &jobv, &jobq, &m, &p, &n, &k, &l, a, &lda, b, &ldb,
            &tola, &tolb, alpha, beta, u, &ldu, v, &ldv, q, &ldq, work,
            &ncycle, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t tgsja( const char jobu, const char jobv, const char jobq,
        const fortran_int_t m, const fortran_int_t p, const fortran_int_t n,
        const fortran_int_t k, const fortran_int_t l, double* a,
        const fortran_int_t lda, double* b, const fortran_int_t ldb,
        const double tola, const double tolb, double* alpha, double* beta,
        double* u, const fortran_int_t ldu, double* v,
        const fortran_int_t ldv, double* q, const fortran_int_t ldq,
        double* work, fortran_int_t& ncycle ) {
    fortran_int_t info(0);
    LAPACK_DTGSJA( &jobu, &jobv, &jobq, &m, &p, &n, &k, &l, a, &lda, b, &ldb,
            &tola, &tolb, alpha, beta, u, &ldu, v, &ldv, q, &ldq, work,
            &ncycle, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t tgsja( const char jobu, const char jobv, const char jobq,
        const fortran_int_t m, const fortran_int_t p, const fortran_int_t n,
        const fortran_int_t k, const fortran_int_t l, std::complex<float>* a,
        const fortran_int_t lda, std::complex<float>* b,
        const fortran_int_t ldb, const float tola, const float tolb,
        float* alpha, float* beta, std::complex<float>* u,
        const fortran_int_t ldu, std::complex<float>* v,
        const fortran_int_t ldv, std::complex<float>* q,
        const fortran_int_t ldq, std::complex<float>* work,
        fortran_int_t& ncycle ) {
    fortran_int_t info(0);
    LAPACK_CTGSJA( &jobu, &jobv, &jobq, &m, &p, &n, &k, &l, a, &lda, b, &ldb,
            &tola, &tolb, alpha, beta, u, &ldu, v, &ldv, q, &ldq, work,
            &ncycle, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t tgsja( const char jobu, const char jobv, const char jobq,
        const fortran_int_t m, const fortran_int_t p, const fortran_int_t n,
        const fortran_int_t k, const fortran_int_t l, std::complex<double>* a,
        const fortran_int_t lda, std::complex<double>* b,
        const fortran_int_t ldb, const double tola, const double tolb,
        double* alpha, double* beta, std::complex<double>* u,
        const fortran_int_t ldu, std::complex<double>* v,
        const fortran_int_t ldv, std::complex<double>* q,
        const fortran_int_t ldq, std::complex<double>* work,
        fortran_int_t& ncycle ) {
    fortran_int_t info(0);
    LAPACK_ZTGSJA( &jobu, &jobv, &jobq, &m, &p, &n, &k, &l, a, &lda, b, &ldb,
            &tola, &tolb, alpha, beta, u, &ldu, v, &ldv, q, &ldq, work,
            &ncycle, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to tgsja.
//
template< typename Value, typename Enable = void >
struct tgsja_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct tgsja_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename VectorALPHA,
            typename VectorBETA, typename MatrixU, typename MatrixV,
            typename MatrixQ, typename WORK >
    static std::ptrdiff_t invoke( const char jobu, const char jobv,
            const char jobq, const fortran_int_t k,
            const fortran_int_t l, MatrixA& a, MatrixB& b,
            const real_type tola, const real_type tolb, VectorALPHA& alpha,
            VectorBETA& beta, MatrixU& u, MatrixV& v, MatrixQ& q,
            fortran_int_t& ncycle, detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixU >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixV >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixQ >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorALPHA >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorBETA >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixV >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixQ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorALPHA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorBETA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixU >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixV >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixQ >::value) );
        BOOST_ASSERT( bindings::size(alpha) >= bindings::size_column(a) );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::size_minor(q) == 1 ||
                bindings::stride_minor(q) == 1 );
        BOOST_ASSERT( bindings::size_minor(u) == 1 ||
                bindings::stride_minor(u) == 1 );
        BOOST_ASSERT( bindings::size_minor(v) == 1 ||
                bindings::stride_minor(v) == 1 );
        BOOST_ASSERT( bindings::size_row(a) >= 0 );
        BOOST_ASSERT( bindings::size_row(b) >= 0 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_row(a)) );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                bindings::size_row(b)) );
        BOOST_ASSERT( jobq == 'Q' || jobq == 'I' || jobq == 'N' );
        BOOST_ASSERT( jobu == 'U' || jobu == 'I' || jobu == 'N' );
        BOOST_ASSERT( jobv == 'V' || jobv == 'I' || jobv == 'N' );
        return detail::tgsja( jobu, jobv, jobq, bindings::size_row(a),
                bindings::size_row(b), bindings::size_column(a), k, l,
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(b), bindings::stride_major(b), tola,
                tolb, bindings::begin_value(alpha),
                bindings::begin_value(beta), bindings::begin_value(u),
                bindings::stride_major(u), bindings::begin_value(v),
                bindings::stride_major(v), bindings::begin_value(q),
                bindings::stride_major(q),
                bindings::begin_value(work.select(real_type())), ncycle );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename MatrixB, typename VectorALPHA,
            typename VectorBETA, typename MatrixU, typename MatrixV,
            typename MatrixQ >
    static std::ptrdiff_t invoke( const char jobu, const char jobv,
            const char jobq, const fortran_int_t k,
            const fortran_int_t l, MatrixA& a, MatrixB& b,
            const real_type tola, const real_type tolb, VectorALPHA& alpha,
            VectorBETA& beta, MatrixU& u, MatrixV& v, MatrixQ& q,
            fortran_int_t& ncycle, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                bindings::size_column(a) ) );
        return invoke( jobu, jobv, jobq, k, l, a, b, tola, tolb, alpha, beta,
                u, v, q, ncycle, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixB, typename VectorALPHA,
            typename VectorBETA, typename MatrixU, typename MatrixV,
            typename MatrixQ >
    static std::ptrdiff_t invoke( const char jobu, const char jobv,
            const char jobq, const fortran_int_t k,
            const fortran_int_t l, MatrixA& a, MatrixB& b,
            const real_type tola, const real_type tolb, VectorALPHA& alpha,
            VectorBETA& beta, MatrixU& u, MatrixV& v, MatrixQ& q,
            fortran_int_t& ncycle, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( jobu, jobv, jobq, k, l, a, b, tola, tolb, alpha, beta,
                u, v, q, ncycle, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 2*n;
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct tgsja_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename VectorALPHA,
            typename VectorBETA, typename MatrixU, typename MatrixV,
            typename MatrixQ, typename WORK >
    static std::ptrdiff_t invoke( const char jobu, const char jobv,
            const char jobq, const fortran_int_t k,
            const fortran_int_t l, MatrixA& a, MatrixB& b,
            const real_type tola, const real_type tolb, VectorALPHA& alpha,
            VectorBETA& beta, MatrixU& u, MatrixV& v, MatrixQ& q,
            fortran_int_t& ncycle, detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixU >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixV >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixQ >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorALPHA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorBETA >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixV >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixQ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorALPHA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorBETA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixU >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixV >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixQ >::value) );
        BOOST_ASSERT( bindings::size(alpha) >= bindings::size_column(a) );
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::size_minor(q) == 1 ||
                bindings::stride_minor(q) == 1 );
        BOOST_ASSERT( bindings::size_minor(u) == 1 ||
                bindings::stride_minor(u) == 1 );
        BOOST_ASSERT( bindings::size_minor(v) == 1 ||
                bindings::stride_minor(v) == 1 );
        BOOST_ASSERT( bindings::size_row(a) >= 0 );
        BOOST_ASSERT( bindings::size_row(b) >= 0 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_row(a)) );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                bindings::size_row(b)) );
        BOOST_ASSERT( jobq == 'Q' || jobq == 'I' || jobq == 'N' );
        BOOST_ASSERT( jobu == 'U' || jobu == 'I' || jobu == 'N' );
        BOOST_ASSERT( jobv == 'V' || jobv == 'I' || jobv == 'N' );
        return detail::tgsja( jobu, jobv, jobq, bindings::size_row(a),
                bindings::size_row(b), bindings::size_column(a), k, l,
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(b), bindings::stride_major(b), tola,
                tolb, bindings::begin_value(alpha),
                bindings::begin_value(beta), bindings::begin_value(u),
                bindings::stride_major(u), bindings::begin_value(v),
                bindings::stride_major(v), bindings::begin_value(q),
                bindings::stride_major(q),
                bindings::begin_value(work.select(value_type())), ncycle );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename MatrixB, typename VectorALPHA,
            typename VectorBETA, typename MatrixU, typename MatrixV,
            typename MatrixQ >
    static std::ptrdiff_t invoke( const char jobu, const char jobv,
            const char jobq, const fortran_int_t k,
            const fortran_int_t l, MatrixA& a, MatrixB& b,
            const real_type tola, const real_type tolb, VectorALPHA& alpha,
            VectorBETA& beta, MatrixU& u, MatrixV& v, MatrixQ& q,
            fortran_int_t& ncycle, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                bindings::size_column(a) ) );
        return invoke( jobu, jobv, jobq, k, l, a, b, tola, tolb, alpha, beta,
                u, v, q, ncycle, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixB, typename VectorALPHA,
            typename VectorBETA, typename MatrixU, typename MatrixV,
            typename MatrixQ >
    static std::ptrdiff_t invoke( const char jobu, const char jobv,
            const char jobq, const fortran_int_t k,
            const fortran_int_t l, MatrixA& a, MatrixB& b,
            const real_type tola, const real_type tolb, VectorALPHA& alpha,
            VectorBETA& beta, MatrixU& u, MatrixV& v, MatrixQ& q,
            fortran_int_t& ncycle, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( jobu, jobv, jobq, k, l, a, b, tola, tolb, alpha, beta,
                u, v, q, ncycle, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 2*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the tgsja_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for tgsja. Its overload differs for
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename VectorALPHA,
        typename VectorBETA, typename MatrixU, typename MatrixV,
        typename MatrixQ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
tgsja( const char jobu, const char jobv, const char jobq,
        const fortran_int_t k, const fortran_int_t l, MatrixA& a,
        MatrixB& b, const typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type tola,
        const typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type tolb, VectorALPHA& alpha, VectorBETA& beta,
        MatrixU& u, MatrixV& v, MatrixQ& q, fortran_int_t& ncycle,
        Workspace work ) {
    return tgsja_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobu, jobv, jobq, k, l, a, b, tola,
            tolb, alpha, beta, u, v, q, ncycle, work );
}

//
// Overloaded function for tgsja. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename VectorALPHA,
        typename VectorBETA, typename MatrixU, typename MatrixV,
        typename MatrixQ >
inline typename boost::disable_if< detail::is_workspace< MatrixQ >,
        std::ptrdiff_t >::type
tgsja( const char jobu, const char jobv, const char jobq,
        const fortran_int_t k, const fortran_int_t l, MatrixA& a,
        MatrixB& b, const typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type tola,
        const typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type tolb, VectorALPHA& alpha, VectorBETA& beta,
        MatrixU& u, MatrixV& v, MatrixQ& q, fortran_int_t& ncycle ) {
    return tgsja_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobu, jobv, jobq, k, l, a, b, tola,
            tolb, alpha, beta, u, v, q, ncycle, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
