// std 11 <-> 03/w-boost bridge compatiblity layer, plus a few macro utils.
// - rlyeh, boost licensed.

#ifndef __BRIDGE_HPP__
#define __BRIDGE_HPP__

#ifdef __SSE__
#   define BOOST_HAS_INT128 1
#   include <xmmintrin.h>
#endif

#if (__cplusplus < 201103L && !defined(_MSC_VER)) || (defined(_MSC_VER) && (_MSC_VER < 1700)) || (defined(__GLIBCXX__) && __GLIBCXX__ < 20130322L)
#   define BRIDGE_VERSION 2003
#   include <boost/functional.hpp> // if old libstdc++ or msc libs are found, use boost::function
#   include <boost/function.hpp>   // 
#   include <boost/thread.hpp>     // and boost::thread
#   include <boost/cstdint.hpp>
#   include <boost/type_traits.hpp>
#   include <boost/bind.hpp>
#   include <boost/bind/placeholders.hpp>
namespace std {
    namespace placeholders {
        //...
    }
    using namespace boost;
}
#else
#   define BRIDGE_VERSION 2011
#   include <functional>       // else assume modern c++11 and use std::function<> instead
#   include <mutex>            // and std::mutex
#   include <thread>           // and std::thread
#   include <cstdint>
#endif

#if BRIDGE_VERSION >= 2011
#define $cpp11          $yes
#define $cpp03          $no
#else
#define $cpp11          $no
#define $cpp03          $yes
#endif

// Thread Local Storage 

#if defined(__MINGW32__) || defined(__SUNPRO_C) || defined(__xlc__) || defined(__GNUC__) || defined(__clang__) || defined(__GNUC__) // __INTEL_COMPILER on linux
//   MingW, Solaris Studio C/C++, IBM XL C/C++,[3] GNU C,[4] Clang[5] and Intel C++ Compiler (Linux systems)
#    define $tls(x) __thread x
#else
//   Visual C++,[7] Intel C/C++ (Windows systems),[8] C++Builder, and Digital Mars C++
#    define $tls(x) __declspec(thread) x
#endif

// OS utils. Here is where the fun starts... good luck

#define $quote(...)     #__VA_ARGS__
#define $comment(...)   $no
#define $uncomment(...) $yes

#define $yes(...)     __VA_ARGS__
#define $no(...)

#define $on(v)        (0 v(+1))  // usage: #if $on($msvc)
#define $is           $on        // usage: #if $is($debug)
#define $has(...)     $clang(__has_feature(__VA_ARGS__)) $celse(__VA_ARGS__) // usage: #if $has(cxx_exceptions)

#if defined(_WIN32)
#   define $windows   $yes
#   define $welse     $no
#else
#   define $windows   $no
#   define $welse     $yes
#endif

#ifdef __APPLE__
#   define $apple     $yes
#   define $aelse     $no
#else
#   define $apple     $no
#   define $aelse     $yes
#endif

#ifdef __linux__
#   define $linux     $yes
#   define $lelse     $no
#else
#   define $linux     $no
#   define $lelse     $yes
#endif

// Compiler utils

#if defined(NDEBUG) || defined(_NDEBUG)
#   define $release   $yes
#   define $debug     $no
#else
#   define $release   $no
#   define $debug     $yes
#endif

#if defined(__GNUC__) || defined(__MINGW32__)
#   define $gnuc      $yes
#   define $gelse     $no
#else
#   define $gnuc      $no
#   define $gelse     $yes
#endif

#ifdef _MSC_VER
#   define $msvc      $yes
#   define $melse     $no
#else
#   define $msvc      $no
#   define $melse     $yes
#endif

#ifdef __clang__
#   define $clang     $yes
#   define $celse     $no
#else
#   define $clang     $no
#   define $celse     $yes
#endif

#if $on($msvc) || $on($gnuc) || $on($clang)
#   define $undefined_compiler $no
#else
#   define $undefined_compiler $yes
#endif

#if $on($windows) || $on($linux) || $on($apple)
#   define $undefined_os $no
#else
#   define $undefined_os $yes
#endif

// try to detect if exceptions are enabled...

#if (defined(_HAS_EXCEPTIONS) && (_HAS_EXCEPTIONS > 0)) || \
    (defined(_STLP_USE_EXCEPTIONS) && (_STLP_USE_EXCEPTIONS > 0)) || \
    (defined(HAVE_EXCEPTIONS)) || \
    (defined(__EXCEPTIONS)) || \
    (defined(_CPPUNWIND)) || \
    ($has(cxx_exceptions)) /*(__has_feature(cxx_exceptions))*/
#   define $throw     $yes
#   define $telse     $no
#else
#   define $throw     $no
#   define $telse     $yes
#endif

// create a $warning(...) macro
// usage: $warning("this is shown at compile time")
#if $on($msvc)
#   define $warning(msg) __pragma( message( msg ) )
#elif $on($gnuc) || $on($clang)
#   define $$warning$impl(msg) _Pragma(#msg)
#   define $warning(msg) $$warning$impl( message( msg ) )
#else
#   define $warning(msg)
#endif

// create a $warning(...) macro
// usage: $warning("this is shown at compile time")
#define $$todo$stringize$impl(X) #X
#define $$todo$stringize(X) $$todo$stringize$impl(X)
#define $todo(...) $warning( __FILE__ "(" $$todo$stringize(__LINE__)") : $todo - " #__VA_ARGS__ " - [ "__func__ " ]" )

#endif // __BRIDGE_HPP__
