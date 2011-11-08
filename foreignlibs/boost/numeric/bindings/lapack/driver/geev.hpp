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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GEEV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GEEV_HPP

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
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for geev is the netlib-compatible backend.
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
inline std::ptrdiff_t geev( const char jobvl, const char jobvr,
        const fortran_int_t n, float* a, const fortran_int_t lda, float* wr,
        float* wi, float* vl, const fortran_int_t ldvl, float* vr,
        const fortran_int_t ldvr, float* work, const fortran_int_t lwork ) {
    fortran_int_t info(0);
    LAPACK_SGEEV( &jobvl, &jobvr, &n, a, &lda, wr, wi, vl, &ldvl, vr, &ldvr,
            work, &lwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t geev( const char jobvl, const char jobvr,
        const fortran_int_t n, double* a, const fortran_int_t lda, double* wr,
        double* wi, double* vl, const fortran_int_t ldvl, double* vr,
        const fortran_int_t ldvr, double* work, const fortran_int_t lwork ) {
    fortran_int_t info(0);
    LAPACK_DGEEV( &jobvl, &jobvr, &n, a, &lda, wr, wi, vl, &ldvl, vr, &ldvr,
            work, &lwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t geev( const char jobvl, const char jobvr,
        const fortran_int_t n, std::complex<float>* a,
        const fortran_int_t lda, std::complex<float>* w,
        std::complex<float>* vl, const fortran_int_t ldvl,
        std::complex<float>* vr, const fortran_int_t ldvr,
        std::complex<float>* work, const fortran_int_t lwork, float* rwork ) {
    fortran_int_t info(0);
    LAPACK_CGEEV( &jobvl, &jobvr, &n, a, &lda, w, vl, &ldvl, vr, &ldvr, work,
            &lwork, rwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t geev( const char jobvl, const char jobvr,
        const fortran_int_t n, std::complex<double>* a,
        const fortran_int_t lda, std::complex<double>* w,
        std::complex<double>* vl, const fortran_int_t ldvl,
        std::complex<double>* vr, const fortran_int_t ldvr,
        std::complex<double>* work, const fortran_int_t lwork,
        double* rwork ) {
    fortran_int_t info(0);
    LAPACK_ZGEEV( &jobvl, &jobvr, &n, a, &lda, w, vl, &ldvl, vr, &ldvr, work,
            &lwork, rwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to geev.
//
template< typename Value, typename Enable = void >
struct geev_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct geev_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorWR, typename VectorWI,
            typename MatrixVL, typename MatrixVR, typename WORK >
    static std::ptrdiff_t invoke( const char jobvl, const char jobvr,
            MatrixA& a, VectorWR& wr, VectorWI& wi, MatrixVL& vl,
            MatrixVR& vr, detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVL >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVR >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorWR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorWI >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixVL >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixVR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorWR >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorWI >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVL >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVR >::value) );
        BOOST_ASSERT( bindings::size(wi) >= bindings::size_column(a) );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( jobvl, jobvr, bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size(wr) >= bindings::size_column(a) );
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(vl) == 1 ||
                bindings::stride_minor(vl) == 1 );
        BOOST_ASSERT( bindings::size_minor(vr) == 1 ||
                bindings::stride_minor(vr) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( jobvl == 'N' || jobvl == 'V' );
        BOOST_ASSERT( jobvr == 'N' || jobvr == 'V' );
        return detail::geev( jobvl, jobvr, bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(wr), bindings::begin_value(wi),
                bindings::begin_value(vl), bindings::stride_major(vl),
                bindings::begin_value(vr), bindings::stride_major(vr),
                bindings::begin_value(work.select(real_type())),
                bindings::size(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename VectorWR, typename VectorWI,
            typename MatrixVL, typename MatrixVR >
    static std::ptrdiff_t invoke( const char jobvl, const char jobvr,
            MatrixA& a, VectorWR& wr, VectorWI& wi, MatrixVL& vl,
            MatrixVR& vr, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work( jobvl,
                jobvr, bindings::size_column(a) ) );
        return invoke( jobvl, jobvr, a, wr, wi, vl, vr,
                workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename VectorWR, typename VectorWI,
            typename MatrixVL, typename MatrixVR >
    static std::ptrdiff_t invoke( const char jobvl, const char jobvr,
            MatrixA& a, VectorWR& wr, VectorWI& wi, MatrixVL& vl,
            MatrixVR& vr, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        real_type opt_size_work;
        detail::geev( jobvl, jobvr, bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(wr), bindings::begin_value(wi),
                bindings::begin_value(vl), bindings::stride_major(vl),
                bindings::begin_value(vr), bindings::stride_major(vr),
                &opt_size_work, -1 );
        bindings::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        return invoke( jobvl, jobvr, a, wr, wi, vl, vr,
                workspace( tmp_work ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const char jobvl, const char jobvr,
            const std::ptrdiff_t n ) {
        if ( jobvl == 'V' || jobvr == 'V' )
            return std::max< std::ptrdiff_t >( 1, 4*n );
        else
            return std::max< std::ptrdiff_t >( 1, 3*n );
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct geev_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorW, typename MatrixVL,
            typename MatrixVR, typename WORK, typename RWORK >
    static std::ptrdiff_t invoke( const char jobvl, const char jobvr,
            MatrixA& a, VectorW& w, MatrixVL& vl, MatrixVR& vr,
            detail::workspace2< WORK, RWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVL >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVR >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorW >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixVL >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixVR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorW >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVL >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVR >::value) );
        BOOST_ASSERT( bindings::size(w) >= bindings::size_column(a) );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_rwork( bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(vl) == 1 ||
                bindings::stride_minor(vl) == 1 );
        BOOST_ASSERT( bindings::size_minor(vr) == 1 ||
                bindings::stride_minor(vr) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( jobvl == 'N' || jobvl == 'V' );
        BOOST_ASSERT( jobvr == 'N' || jobvr == 'V' );
        return detail::geev( jobvl, jobvr, bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(w), bindings::begin_value(vl),
                bindings::stride_major(vl), bindings::begin_value(vr),
                bindings::stride_major(vr),
                bindings::begin_value(work.select(value_type())),
                bindings::size(work.select(value_type())),
                bindings::begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename VectorW, typename MatrixVL,
            typename MatrixVR >
    static std::ptrdiff_t invoke( const char jobvl, const char jobvr,
            MatrixA& a, VectorW& w, MatrixVL& vl, MatrixVR& vr,
            minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                bindings::size_column(a) ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                bindings::size_column(a) ) );
        return invoke( jobvl, jobvr, a, w, vl, vr, workspace( tmp_work,
                tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename VectorW, typename MatrixVL,
            typename MatrixVR >
    static std::ptrdiff_t invoke( const char jobvl, const char jobvr,
            MatrixA& a, VectorW& w, MatrixVL& vl, MatrixVR& vr,
            optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        value_type opt_size_work;
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                bindings::size_column(a) ) );
        detail::geev( jobvl, jobvr, bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(w), bindings::begin_value(vl),
                bindings::stride_major(vl), bindings::begin_value(vr),
                bindings::stride_major(vr), &opt_size_work, -1,
                bindings::begin_value(tmp_rwork) );
        bindings::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        return invoke( jobvl, jobvr, a, w, vl, vr, workspace( tmp_work,
                tmp_rwork ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return std::max< std::ptrdiff_t >( 1, 2*n );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array rwork.
    //
    static std::ptrdiff_t min_size_rwork( const std::ptrdiff_t n ) {
        return 2*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the geev_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for geev. Its overload differs for
// * User-defined workspace
//
template< typename MatrixA, typename VectorWR, typename VectorWI,
        typename MatrixVL, typename MatrixVR, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
geev( const char jobvl, const char jobvr, MatrixA& a, VectorWR& wr,
        VectorWI& wi, MatrixVL& vl, MatrixVR& vr, Workspace work ) {
    return geev_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvl, jobvr, a, wr, wi, vl, vr, work );
}

//
// Overloaded function for geev. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorWR, typename VectorWI,
        typename MatrixVL, typename MatrixVR >
inline typename boost::disable_if< detail::is_workspace< MatrixVR >,
        std::ptrdiff_t >::type
geev( const char jobvl, const char jobvr, MatrixA& a, VectorWR& wr,
        VectorWI& wi, MatrixVL& vl, MatrixVR& vr ) {
    return geev_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvl, jobvr, a, wr, wi, vl, vr,
            optimal_workspace() );
}
//
// Overloaded function for geev. Its overload differs for
// * User-defined workspace
//
template< typename MatrixA, typename VectorW, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
geev( const char jobvl, const char jobvr, MatrixA& a, VectorW& w,
        MatrixVL& vl, MatrixVR& vr, Workspace work ) {
    return geev_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvl, jobvr, a, w, vl, vr, work );
}

//
// Overloaded function for geev. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorW, typename MatrixVL,
        typename MatrixVR >
inline typename boost::disable_if< detail::is_workspace< MatrixVR >,
        std::ptrdiff_t >::type
geev( const char jobvl, const char jobvr, MatrixA& a, VectorW& w,
        MatrixVL& vl, MatrixVR& vr ) {
    return geev_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvl, jobvr, a, w, vl, vr,
            optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
