#define GEOGRAM_PSM
#ifndef GEO_STATIC_LIBS
#define GEO_DYNAMIC_LIBS
#endif
/*
 *  Copyright (c) 2000-2022 Inria
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution.
 *  * Neither the name of the ALICE Project-Team nor the names of its
 *  contributors may be used to endorse or promote products derived from this
 *  software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *  Contact: Bruno Levy
 *
 *     https://www.inria.fr/fr/bruno-levy
 *
 *     Inria,
 *     Domaine de Voluceau,
 *     78150 Le Chesnay - Rocquencourt
 *     FRANCE
 *
 */


/*
 *  This file is a PSM (pluggable software module)
 *   generated from the distribution of Geogram.
 *
 *  See Geogram documentation on:
 *   http://alice.loria.fr/software/geogram/doc/html/index.html
 *
 *  See documentation of the functions bundled in this PSM on:
 *   http://alice.loria.fr/software/geogram/doc/html/classGEO_1_1Delaunay.html
 */



/******* extracted from ../api/defs.h *******/

#ifndef GEOGRAM_API_DEFS
#define GEOGRAM_API_DEFS


/*
 * Deactivate warnings about documentation
 * We do that, because CLANG's doxygen parser does not know
 * some doxygen commands that we use (retval, copydoc) and
 * generates many warnings for them...
 */
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif


#if defined(GEO_DYNAMIC_LIBS)
#if defined(_MSC_VER)
#define GEO_IMPORT __declspec(dllimport)
#define GEO_EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
#define GEO_IMPORT
#define GEO_EXPORT __attribute__ ((visibility("default")))
#else
#define GEO_IMPORT
#define GEO_EXPORT
#endif
#else
#define GEO_IMPORT
#define GEO_EXPORT
#endif

#ifdef geogram_EXPORTS
#define GEOGRAM_API GEO_EXPORT
#else
#define GEOGRAM_API GEO_IMPORT
#endif


#define NO_GEOGRAM_API

typedef int GeoMesh;

typedef unsigned char geo_coord_index_t;

/*
 * If GARGANTUA is defined, then geogram is compiled
 * with 64 bit indices.
 */
#ifdef GARGANTUA

#include <stdint.h>

typedef uint64_t geo_index_t;

typedef int64_t geo_signed_index_t;

#else

typedef unsigned int geo_index_t;

typedef int geo_signed_index_t;

#endif

typedef double geo_coord_t;

typedef int geo_boolean;

enum {
    GEO_FALSE = 0,
    GEO_TRUE = 1
};

#endif

/******* extracted from ../basic/common.h *******/

#ifndef GEOGRAM_BASIC_COMMON
#define GEOGRAM_BASIC_COMMON


// iostream should be included before anything else,
// otherwise 'cin', 'cout' and 'cerr' will be uninitialized.
#include <iostream>



namespace GEO {

    enum {
        /// Do not install error handlers
        GEOGRAM_INSTALL_NONE = 0,
        /// Install Geogram's signal handlers
        GEOGRAM_INSTALL_HANDLERS = 1,
        /// Sets the locale to POSIX
        GEOGRAM_INSTALL_LOCALE = 2,
        /// Reset errno to 0
        GEOGRAM_INSTALL_ERRNO = 4,
        /// Enable or disable FPE during initialization
        GEOGRAM_INSTALL_FPE = 8,
        /// Enable global citation database
        GEOGRAM_INSTALL_BIBLIO = 16,
        /// Install everything
        GEOGRAM_INSTALL_ALL = GEOGRAM_INSTALL_HANDLERS
        | GEOGRAM_INSTALL_LOCALE
        | GEOGRAM_INSTALL_ERRNO
        | GEOGRAM_INSTALL_FPE
        | GEOGRAM_INSTALL_BIBLIO
    };

    void GEOGRAM_API initialize(int flags = GEOGRAM_INSTALL_NONE);

    void GEOGRAM_API terminate();
}


#if (defined(NDEBUG) || defined(GEOGRAM_PSM)) && !defined(GEOGRAM_PSM_DEBUG)
#undef GEO_DEBUG
#undef GEO_PARANOID
#else
#define GEO_DEBUG
#define GEO_PARANOID
#endif

// =============================== LINUX defines ===========================

#if defined(__ANDROID__)
#define GEO_OS_ANDROID
#endif

#if defined(__linux__)

#define GEO_OS_LINUX
#define GEO_OS_UNIX

#ifndef GEO_OS_ANDROID
#define GEO_OS_X11
#endif

#if defined(_OPENMP)
#  define GEO_OPENMP
#endif

#if defined(__INTEL_COMPILER)
#  define GEO_COMPILER_INTEL
#elif defined(__clang__)
#  define GEO_COMPILER_CLANG
#elif defined(__GNUC__)
#  define GEO_COMPILER_GCC
#else
#  error "Unsupported compiler"
#endif

// The following works on GCC and ICC
#if defined(__x86_64)
#  define GEO_ARCH_64
#  define GEO_PROCESSOR_X86
#else
#  define GEO_ARCH_32
#endif

// =============================== WINDOWS defines =========================

#elif defined(_WIN32) || defined(_WIN64)

#define GEO_OS_WINDOWS
#define GEO_PROCESSOR_X86

#if defined(_OPENMP)
#  define GEO_OPENMP
#endif

#if defined(_MSC_VER)
#  define GEO_COMPILER_MSVC
#elif defined(__MINGW32__) || defined(__MINGW64__)
#  define GEO_COMPILER_MINGW
#endif

#if defined(_WIN64)
#  define GEO_ARCH_64
#else
#  define GEO_ARCH_32
#endif

// =============================== APPLE defines ===========================

#elif defined(__APPLE__)

#define GEO_OS_APPLE
#define GEO_OS_UNIX

#if defined(_OPENMP)
#  define GEO_OPENMP
#endif

#if defined(__clang__)
#  define GEO_COMPILER_CLANG
#elif defined(__GNUC__)
#  define GEO_COMPILER_GCC
#else
#  error "Unsupported compiler"
#endif

#if defined(__x86_64) || defined(__ppc64__) || defined(__arm64__) || defined(__aarch64__) || (defined(__riscv) && __riscv_xlen == 64) || defined(__loongarch_lp64)
#  define GEO_ARCH_64
#else
#  define GEO_ARCH_32
#endif

// =============================== Emscripten defines  ======================

#elif defined(__EMSCRIPTEN__)

#define GEO_OS_UNIX
#define GEO_OS_LINUX
#define GEO_OS_EMSCRIPTEN
#define GEO_ARCH_64
#define GEO_COMPILER_EMSCRIPTEN
#define GEO_COMPILER_CLANG

// =============================== Unsupported =============================
#else
#error "Unsupported operating system"
#endif

#if defined(GEO_COMPILER_GCC)   ||              \
    defined(GEO_COMPILER_CLANG) ||              \
    defined(GEO_COMPILER_MINGW) ||              \
    defined(GEO_COMPILER_EMSCRIPTEN)
#define GEO_COMPILER_GCC_FAMILY
#endif

#ifdef DOXYGEN_ONLY
// Keep doxygen happy
#define GEO_OS_WINDOWS
#define GEO_OS_APPLE
#define GEO_OS_ANDROID
#define GEO_ARCH_32
#define GEO_COMPILER_INTEL
#define GEO_COMPILER_MSVC
#endif

#define CPP_CONCAT_(A, B) A ## B

#define CPP_CONCAT(A, B) CPP_CONCAT_(A, B)

#if defined(GOMGEN)
#define GEO_NORETURN
#elif defined(GEO_COMPILER_GCC_FAMILY) ||       \
    defined(GEO_COMPILER_INTEL)
#define GEO_NORETURN __attribute__((noreturn))
#else
#define GEO_NORETURN
#endif

#if defined(GOMGEN)
#define GEO_NORETURN_DECL
#elif defined(GEO_COMPILER_MSVC)
#define GEO_NORETURN_DECL __declspec(noreturn)
#else
#define GEO_NORETURN_DECL
#endif

#if defined(GEO_COMPILER_CLANG) || defined(GEO_COMPILER_EMSCRIPTEN)
#if __has_feature(cxx_noexcept)
#define GEO_NOEXCEPT noexcept
#endif
#endif

// For Graphite GOM generator (swig is confused by throw() specifier)
#ifdef GOMGEN
#define GEO_NOEXCEPT
#endif

#ifndef GEO_NOEXCEPT
#define GEO_NOEXCEPT throw()
#endif

#define FOR(I,UPPERBND) for(index_t I = 0; I<index_t(UPPERBND); ++I)

// Silence warnings for alloca()
// We use it at different places to allocate objects on the stack
// (for instance, in multi-precision predicates).
#ifdef GEO_COMPILER_CLANG
#pragma GCC diagnostic ignored "-Walloca"
#endif

#endif

/******* extracted from ../basic/assert.h *******/

#ifndef GEOGRAM_BASIC_ASSERT
#define GEOGRAM_BASIC_ASSERT

#include <string>


namespace GEO {

    enum AssertMode {
        
        ASSERT_THROW,
        
        ASSERT_ABORT,
        
        ASSERT_BREAKPOINT
    };

    void GEOGRAM_API set_assert_mode(AssertMode mode);

    AssertMode GEOGRAM_API assert_mode();

    GEO_NORETURN_DECL void GEOGRAM_API geo_abort() GEO_NORETURN;

    GEO_NORETURN_DECL void GEOGRAM_API geo_breakpoint() GEO_NORETURN;

    GEO_NORETURN_DECL void GEOGRAM_API geo_assertion_failed(
        const std::string& condition_string,
        const std::string& file, int line
    ) GEO_NORETURN;

    GEO_NORETURN_DECL void GEOGRAM_API geo_range_assertion_failed(
        double value, double min_value, double max_value,
        const std::string& file, int line
    ) GEO_NORETURN;

    GEO_NORETURN_DECL void GEOGRAM_API geo_should_not_have_reached(
        const std::string& file, int line
    ) GEO_NORETURN;
}

// Three levels of assert:
// use geo_assert() and geo_range_assert()               non-expensive asserts
// use geo_debug_assert() and geo_debug_range_assert()   expensive asserts
// use geo_parano_assert() and geo_parano_range_assert() very exensive asserts

#define geo_assert(x) {                                         \
        if(!(x)) {                                              \
            GEO::geo_assertion_failed(#x, __FILE__, __LINE__);  \
        }                                                       \
    }

#define geo_range_assert(x, min_val, max_val) {                         \
        if(((x) < (min_val)) || ((x) > (max_val))) {                    \
            GEO::geo_range_assertion_failed(x, min_val, max_val,        \
                                            __FILE__, __LINE__          \
                                           );                           \
        }                                                               \
    }

#define geo_assert_not_reached {                                \
        GEO::geo_should_not_have_reached(__FILE__, __LINE__);   \
    }

#ifdef GEO_DEBUG
#define geo_debug_assert(x) geo_assert(x)
#define geo_debug_range_assert(x, min_val, max_val) geo_range_assert(x, min_val, max_val)
#define geo_debug(x) x
#else
#define geo_debug_assert(x)
#define geo_debug_range_assert(x, min_val, max_val)
#define geo_debug(x)
#endif

#ifdef GEO_PARANOID
#define geo_parano_assert(x) geo_assert(x)
#define geo_parano_range_assert(x, min_val, max_val) geo_range_assert(x, min_val, max_val)
#else
#define geo_parano_assert(x)
#define geo_parano_range_assert(x, min_val, max_val)
#endif

#endif

/******* extracted from ../basic/argused.h *******/

#ifndef GEOGRAM_BASIC_ARGUSED
#define GEOGRAM_BASIC_ARGUSED



namespace GEO {

    template <class T>
    inline void geo_argused(const T&) {
    }
}

#endif

/******* extracted from ../basic/numeric.h *******/

#ifndef GEOGRAM_BASIC_NUMERIC
#define GEOGRAM_BASIC_NUMERIC

#include <cmath>
#include <float.h>
#include <limits.h>
#include <algorithm> // for std::min / std::max
#include <stdint.h>
#include <limits>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


namespace GEO {

    enum Sign {
        
        NEGATIVE = -1,
        
        ZERO = 0,
        
        POSITIVE = 1
    };

    template <class T>
    inline Sign geo_sgn(const T& x) {
        return (x > 0) ? POSITIVE : (
            (x < 0) ? NEGATIVE : ZERO
        );
    }

    template <class T>
    inline Sign geo_cmp(const T& a, const T& b) {
        return Sign((a > b) * POSITIVE + (a < b) * NEGATIVE);
    }

    namespace Numeric {

        
        typedef void* pointer;

        
        typedef int8_t int8;

        
        typedef int16_t int16;

        
        typedef int32_t int32;

        
        typedef int64_t int64;

        
        typedef uint8_t uint8;

        
        typedef uint16_t uint16;

        
        typedef uint32_t uint32;

        
        typedef uint64_t uint64;

        
        typedef float float32;

        
        typedef double float64;

        inline float32 max_float32() {
            return std::numeric_limits<float32>::max();
        }

        inline float32 min_float32() {
            // Note: numeric_limits<>::min() is not
            // what we want (it returns the smallest
            // positive non-denormal).
            return -max_float32();
        }

        inline float64 max_float64() {
            return std::numeric_limits<float64>::max();
        }

        inline float64 min_float64() {
            // Note: numeric_limits<>::min() is not
            // what we want (it returns the smallest
            // positive non-denormal).
            return -max_float64();
        }

        bool GEOGRAM_API is_nan(float32 x);

        bool GEOGRAM_API is_nan(float64 x);

        void GEOGRAM_API random_reset();

        int32 GEOGRAM_API random_int32();

        float32 GEOGRAM_API random_float32();

        float64 GEOGRAM_API random_float64();

        template <class T, bool is_numeric>
        struct LimitsHelper : std::numeric_limits<T> {
        };

        template <class T>
        struct LimitsHelper<T, true> : std::numeric_limits<T> {
            
            static const size_t size = sizeof(T);
            
            static const size_t numbits = 8 * sizeof(T);
        };

        template <class T>
        struct Limits :
            LimitsHelper<T, std::numeric_limits<T>::is_specialized> {
        };

        template <class T> inline void optimize_number_representation(T& x) {
            geo_argused(x);
        }

        template <class T> inline Sign ratio_compare(
            const T& a_num, const T& a_denom, const T& b_num, const T& b_denom
        ) {
            if(a_denom == b_denom) {
                return Sign(geo_cmp(a_num,b_num)*geo_sgn(a_denom));
            }
            return Sign(
                geo_cmp(a_num*b_denom, b_num*a_denom) *
                geo_sgn(a_denom) * geo_sgn(b_denom)
            );
        }
    }

    


    template <class T>
    inline T geo_sqr(T x) {
        return x * x;
    }

    template <class T>
    inline void geo_clamp(T& x, T min, T max) {
        if(x < min) {
            x = min;
        } else if(x > max) {
            x = max;
        }
    }

    typedef geo_index_t index_t;

    inline index_t max_index_t() {
        return std::numeric_limits<index_t>::max();
    }

    typedef geo_signed_index_t signed_index_t;

    inline signed_index_t max_signed_index_t() {
        return std::numeric_limits<signed_index_t>::max();
    }

    inline signed_index_t min_signed_index_t() {
        return std::numeric_limits<signed_index_t>::min();
    }

    typedef geo_coord_index_t coord_index_t;

    inline double round(double x) {
        return ((x - floor(x)) > 0.5 ? ceil(x) : floor(x));
    }

    

    static constexpr index_t NO_INDEX = index_t(-1);

    
}

#endif

/******* extracted from ../basic/memory.h *******/

#ifndef GEOGRAM_BASIC_MEMORY
#define GEOGRAM_BASIC_MEMORY

#include <vector>
#include <string.h>
#include <stdlib.h>

#ifdef GEO_OS_WINDOWS

#include <windows.h>
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#else

#include <unistd.h>

#endif

// Stack size depending on OS:
// Linux: 10 Mb
// Windows: 1 Mb
// Mac OSX: 512 Kb
// GEO_HAS_BIG_STACK is defined under Linux
// and lets some of the functions that
// manipulate exact precision numbers
// allocate temporaries on the stack.

#ifdef GEO_OS_LINUX
#define GEO_HAS_BIG_STACK
#endif


namespace GEO {

    namespace Memory {
        
        typedef unsigned char byte;

        
        typedef unsigned char word8;

        
        typedef unsigned short word16;

        
        typedef unsigned int word32;

        
        typedef byte* pointer;

        
        typedef void (*function_pointer)();

        inline void clear(void* addr, size_t size) {
            ::memset(addr, 0, size);
        }

        inline void copy(void* to, const void* from, size_t size) {
            ::memcpy(to, from, size);
        }

        inline pointer function_pointer_to_generic_pointer(
            function_pointer fptr
        ) {
            // I know this is ugly, but I did not find a simpler warning-free
            // way that is portable between all compilers.
            pointer result = nullptr;
            ::memcpy(&result, &fptr, sizeof(pointer));
            return result;
        }

        inline function_pointer generic_pointer_to_function_pointer(
            pointer ptr
        ) {
            // I know this is ugly, but I did not find a simpler warning-free
            // way that is portable between all compilers.
            function_pointer result = nullptr;
            ::memcpy(&result, &ptr, sizeof(pointer));
            return result;
        }

        inline function_pointer generic_pointer_to_function_pointer(void* ptr) {
            // I know this is ugly, but I did not find a simpler warning-free
            // way that is portable between all compilers.
            function_pointer result = nullptr;
            ::memcpy(&result, &ptr, sizeof(pointer));
            return result;
        }

#define GEO_MEMORY_ALIGNMENT 64

        template <int DIM>
        struct PointAlignment {
            static const size_t value = 1;
        };

        template <>
        struct PointAlignment<2> {
            static const size_t value = 16;
        };

        template <>
        struct PointAlignment<3> {
            static const size_t value = 8;
        };

        template <>
        struct PointAlignment<4> {
            static const size_t value = 32;
        };

        template <>
        struct PointAlignment<6> {
            static const size_t value = 16;
        };

        template <>
        struct PointAlignment<8> {
            static const size_t value = 64;
        };

#define geo_dim_alignment(dim) GEO::Memory::PointAlignment<dim>::value

        inline void* aligned_malloc(
            size_t size, size_t alignment = GEO_MEMORY_ALIGNMENT
        ) {
#if   defined(GEO_OS_ANDROID)
            // Alignment not supported under Android.
            geo_argused(alignment);
            return malloc(size);
#elif defined(GEO_COMPILER_INTEL)
            return _mm_malloc(size, alignment);
#elif defined(GEO_COMPILER_GCC) || defined(GEO_COMPILER_CLANG)
            void* result;
            return posix_memalign(&result, alignment, size) == 0
                ? result : nullptr;
#elif defined(GEO_COMPILER_MSVC)
            return _aligned_malloc(size, alignment);
#else
            geo_argused(alignment);
            return malloc(size);
#endif
        }

        inline void aligned_free(void* p) {
#if   defined(GEO_OS_ANDROID)
            // Alignment not supported under Android.
            free(p);
#elif defined(GEO_COMPILER_INTEL)
            _mm_free(p);
#elif defined(GEO_COMPILER_GCC_FAMILY)
            free(p);
#elif defined(GEO_COMPILER_MSVC)
            _aligned_free(p);
#else
            free(p);
#endif
        }

#if   defined(GEO_OS_ANDROID)
#define geo_decl_aligned(var) var
#elif defined(GEO_COMPILER_INTEL)
#define geo_decl_aligned(var) __declspec(aligned(GEO_MEMORY_ALIGNMENT)) var
#elif defined(GEO_COMPILER_GCC_FAMILY)
#define geo_decl_aligned(var) var __attribute__((aligned(GEO_MEMORY_ALIGNMENT)))
#elif defined(GEO_COMPILER_MSVC)
#define geo_decl_aligned(var) __declspec(align(GEO_MEMORY_ALIGNMENT)) var
#elif defined(GEO_COMPILER_EMSCRIPTEN)
#define geo_decl_aligned(var) var
#endif

#if   defined(GEO_OS_ANDROID)
#define geo_assume_aligned(var, alignment)
#elif defined(GEO_COMPILER_INTEL)
#define geo_assume_aligned(var, alignment)      \
        __assume_aligned(var, alignment)
#elif defined(GEO_COMPILER_CLANG)
#define geo_assume_aligned(var, alignment)
        // GCC __builtin_assume_aligned is not yet supported by clang-3.3
#elif defined(GEO_COMPILER_GCC)
#if __GNUC__ >= 4 && __GNUC_MINOR__ >= 7
#define geo_assume_aligned(var, alignment)                              \
        *(void**) (&var) = __builtin_assume_aligned(var, alignment)
        // the GCC way of specifying that a pointer is aligned returns
        // the aligned pointer (I can't figure out why). It needs to be
        // affected otherwise it is not taken into account (verified by
        // looking at the output of gcc -S)
#else
#define geo_assume_aligned(var, alignment)
#endif
#elif defined(GEO_COMPILER_MSVC)
#define geo_assume_aligned(var, alignment)
        // TODO: I do not know how to do that with MSVC
#elif defined(GEO_COMPILER_EMSCRIPTEN)
#define geo_assume_aligned(var, alignment)
#elif defined(GEO_COMPILER_MINGW)
#define geo_assume_aligned(var, alignment)
#endif

#if   defined(GEO_COMPILER_INTEL)
#define geo_restrict __restrict
#elif defined(GEO_COMPILER_GCC_FAMILY)
#define geo_restrict __restrict__
#elif defined(GEO_COMPILER_MSVC)
#define geo_restrict __restrict
#elif defined(GEO_COMPILER_EMSCRIPTEN)
#define geo_restrict
#endif

        inline bool is_aligned(
            void* p, size_t alignment = GEO_MEMORY_ALIGNMENT
        ) {
            return (reinterpret_cast<size_t>(p) & (alignment - 1)) == 0;
        }

        inline void* align(void* p) {
            size_t offset = (
                GEO_MEMORY_ALIGNMENT -
                (reinterpret_cast<size_t>(p) & (GEO_MEMORY_ALIGNMENT - 1))
            ) & (GEO_MEMORY_ALIGNMENT - 1);
            return reinterpret_cast<char*>(p) + offset;
        }

#define geo_aligned_alloca(size)                                        \
        GEO::Memory::align(alloca(size + GEO_MEMORY_ALIGNMENT - 1))

        template <class T, int ALIGN = GEO_MEMORY_ALIGNMENT>
        class aligned_allocator {
        public:
            
            typedef T value_type;

            
            typedef T* pointer;

            
            typedef T& reference;

            
            typedef const T* const_pointer;

            
            typedef const T& const_reference;

            
            typedef ::std::size_t size_type;

            
            typedef ::std::ptrdiff_t difference_type;

	    
	    static constexpr int ALIGNMENT = ALIGN;

            template <class U>
            struct rebind {
                
                typedef aligned_allocator<U> other;
            };

            pointer address(reference x) {
                return &x;
            }

            const_pointer address(const_reference x) {
                return &x;
            }

            pointer allocate(
                size_type nb_elt, const void* hint = nullptr
            ) {
		nb_elt = std::max(nb_elt,size_type(1));
                geo_argused(hint);
		while(true) {
		    pointer result = static_cast<pointer>(
			aligned_malloc(sizeof(T) * nb_elt, ALIGNMENT)
		    );
		    if(result != nullptr) {
			return result;
		    }
		    // under Linux, a process requesting more mem than available
		    // is killed (and there is nothing we can capture). Under
		    // other OSes, the standard mechanism to let the runtime
		    // know is as follows:
		    // see: https://stackoverflow.com/questions/7194127/
		    // how-should-i-write-iso-c-standard-conformant-custom-
		    // new-and-delete-operators
		    // (if there is a handler, call it repeatedly until
		    // allocation succeeds, else throw a bad_alloc exception)
		    std::new_handler handler = std::get_new_handler();
		    if(handler != nullptr) {
			(*handler)();
		    } else {
			throw std::bad_alloc();
		    }
		}
            }

            void deallocate(pointer p, size_type nb_elt) {
                geo_argused(nb_elt);
                aligned_free(p);
            }

            size_type max_size() const {
                ::std::allocator<char> a;
                return std::allocator_traits<decltype(a)>::max_size(a) /
		    sizeof(T);
            }

            void construct(pointer p, const_reference val) {
                new (static_cast<void*>(p))value_type(val);
            }

            void destroy(pointer p) {
                p->~value_type();
#ifdef GEO_COMPILER_MSVC
                (void) p; // to avoid a "unreferenced variable" warning
#endif
            }

            template <class T2, int A2> operator aligned_allocator<T2, A2>() {
                return aligned_allocator<T2,A2>();
            }
        };

        template <typename T1, int A1, typename T2, int A2>
        inline bool operator== (
            const aligned_allocator<T1, A1>&, const aligned_allocator<T2, A2>&
        ) {
            return true;
        }

        template <typename T1, int A1, typename T2, int A2>
        inline bool operator!= (
            const aligned_allocator<T1, A1>&, const aligned_allocator<T2, A2>&
        ) {
            return false;
        }
    }

    

    template <class T>
    class vector : public ::std::vector<T, Memory::aligned_allocator<T> > {
	typedef Memory::aligned_allocator<T> allocator;

        typedef ::std::vector<T, Memory::aligned_allocator<T> > baseclass;



    public:
        vector() :
            baseclass() {
        }

        explicit vector(index_t size) :
            baseclass(size) {
        }

        explicit vector(index_t size, const T& val) :
            baseclass(size, val) {
        }

        index_t size() const {
            //   casts baseclass::size() from size_t (64 bits)
            //   to index_t (32 bits), because all
            //   indices in Vorpaline are supposed to fit in 32 bits (index_t).
            // TODO: geo_debug_assert(baseclass::size() < max index_t)
            return index_t(baseclass::size());
        }

        T& operator[] (index_t i) {
            geo_debug_assert(i < size());
            return baseclass::operator[] (i);
        }

        const T& operator[] (index_t i) const {
            geo_debug_assert(i < size());
            return baseclass::operator[] (i);
        }

        T& operator[] (signed_index_t i) {
            geo_debug_assert(i >= 0 && index_t(i) < size());
            return baseclass::operator[] (index_t(i));
        }

        const T& operator[] (signed_index_t i) const {
            geo_debug_assert(i >= 0 && index_t(i) < size());
            return baseclass::operator[] (index_t(i));
        }


#ifdef GARGANTUA // If compiled with 64 bits index_t

        T& operator[] (int i) {
            geo_debug_assert(i >= 0 && index_t(i) < size());
            return baseclass::operator[] (index_t(i));
        }

        const T& operator[] (int i) const {
            geo_debug_assert(i >= 0 && index_t(i) < size());
            return baseclass::operator[] (index_t(i));
        }

        T& operator[] (unsigned int i) {
            geo_debug_assert(index_t(i) < size());
            return baseclass::operator[] (index_t(i));
        }

        const T& operator[] (unsigned int i) const {
            geo_debug_assert(index_t(i) < size());
            return baseclass::operator[] (index_t(i));
        }
#endif

        T* data() {
            T* result = baseclass::data();
	    // Tell the compiler that the pointer is aligned, to enable AVX
	    // vectorization, can be useful when using vector<double>
	    // with blas-like operations. I hope the hint will propagate to
	    // the caller (not sure...)
	    geo_assume_aligned(result, allocator::ALIGNMENT);
	    return result;
        }

        const T* data() const {
            const T* result = baseclass::data();
	    // Tell the compiler that the pointer is aligned, to enable AVX
	    // vectorization, can be useful when using vector<double>
	    // with blas-like operations. I hope the hint will propagate to
	    // the caller (not sure...)
	    geo_assume_aligned(result, allocator::ALIGNMENT);
	    return result;
        }


	void clear_and_deallocate() {
	    vector<T> other;
	    this->swap(other);
	}
    };

    template <>
    class vector<bool> : public ::std::vector<bool> {
        typedef ::std::vector<bool> baseclass;

    public:
        
        vector() :
            baseclass() {
        }

        
        explicit vector(index_t size) :
            baseclass(size) {
        }

        
        explicit vector(index_t size, bool val) :
            baseclass(size, val) {
        }

        
        index_t size() const {
            //   casts baseclass::size() from size_t (64 bits)
            //   to index_t (32 bits), because all
            //   indices in Vorpaline are supposed to fit in 32 bits (index_t).
            // TODO: geo_debug_assert(baseclass::size() < max index_t)
            return index_t(baseclass::size());
        }

        // TODO: operator[] with bounds checking (more complicated
        // than just returning bool&, check implementation in STL).
    };
}

#endif

/******* extracted from ../basic/counted.h *******/

#ifndef GEOGRAM_BASIC_COUNTED
#define GEOGRAM_BASIC_COUNTED



namespace GEO {

    class GEOGRAM_API Counted {
    public:
    void ref() const {
        ++nb_refs_;
    }

    void unref() const {
        --nb_refs_;
        geo_debug_assert(nb_refs_ >= 0);
        if(nb_refs_ == 0) {
            delete this;
        }
    }

    bool is_shared() const {
        return nb_refs_ > 1;
    }

    int nb_refs() const {
        return nb_refs_;
    }

    static void ref(const Counted* counted) {
        if(counted != nullptr) {
            counted->ref();
        }
    }

    static void unref(const Counted* counted) {
        if(counted != nullptr) {
            counted->unref();
        }
    }

    protected:
    Counted() :
    nb_refs_(0) {
    }

    virtual ~Counted();

    private:
    
    Counted(const Counted&);
    
    Counted& operator= (const Counted&);

    mutable int nb_refs_;
    };
}

#endif

/******* extracted from ../basic/smart_pointer.h *******/

#ifndef GEOGRAM_BASIC_SMART_POINTER
#define GEOGRAM_BASIC_SMART_POINTER



namespace GEO {

    

    template <class T>
    class SmartPointer {
    public:
        SmartPointer() :
            pointer_(nullptr) {
        }

        SmartPointer(T* ptr) :
            pointer_(ptr) {
            T::ref(pointer_);
        }

        SmartPointer(const SmartPointer<T>& rhs) :
            pointer_(rhs) {
            T::ref(pointer_);
        }

        ~SmartPointer() {
            T::unref(pointer_);
        }

        SmartPointer<T>& operator= (T* ptr) {
            if(ptr != pointer_) {
                T::unref(pointer_);
                pointer_ = ptr;
                T::ref(pointer_);
            }
            return *this;
        }

        SmartPointer<T>& operator= (const SmartPointer<T>& rhs) {
            T* rhs_p = rhs.get();
            if(rhs_p != pointer_) {
                T::unref(pointer_);
                pointer_ = rhs_p;
                T::ref(pointer_);
            }
            return *this;
        }

        void reset() {
            T::unref(pointer_);
            pointer_ = nullptr;
        }

        T* operator-> () const {
            geo_assert(pointer_ != nullptr);
            return pointer_;
        }

        T& operator* () const {
            geo_assert(pointer_ != nullptr);
            return *pointer_;
        }

        operator T* () const {
            return pointer_;
        }

        T* get() const {
            return pointer_;
        }

        bool is_null() const {
            return pointer_ == nullptr;
        }

    private:
        T* pointer_;
    };

    template <class T1, class T2>
    inline bool operator== (const SmartPointer<T1>& lhs, const SmartPointer<T2>& rhs) {
        return lhs.get() == rhs.get();
    }

    template <class T1, class T2>
    inline bool operator!= (const SmartPointer<T1>& lhs, const SmartPointer<T2>& rhs) {
        return lhs.get() != rhs.get();
    }

    template <class T1, class T2>
    inline bool operator< (const SmartPointer<T1>& lhs, const SmartPointer<T2>& rhs) {
        return lhs.get() < rhs.get();
    }

    template <class T1, class T2>
    inline bool operator<= (const SmartPointer<T1>& lhs, const SmartPointer<T2>& rhs) {
        return lhs.get() <= rhs.get();
    }

    template <class T1, class T2>
    inline bool operator> (const SmartPointer<T1>& lhs, const SmartPointer<T2>& rhs) {
        return lhs.get() > rhs.get();
    }

    template <class T1, class T2>
    inline bool operator>= (const SmartPointer<T1>& lhs, const SmartPointer<T2>& rhs) {
        return lhs.get() >= rhs.get();
    }
}

#endif

/******* extracted from ../basic/environment.h *******/

#ifndef GEOGRAM_BASIC_ENVIRONMENT
#define GEOGRAM_BASIC_ENVIRONMENT

#include <string>
#include <vector>
#include <map>


namespace GEO {

    class Environment;

    

    class GEOGRAM_API VariableObserver {
    public:
    VariableObserver(const std::string& var_name);

    virtual void value_changed(const std::string& new_value) = 0;

    virtual ~VariableObserver();

    const std::string& observed_variable() const {
        return observed_variable_;
    }

    private:
    std::string observed_variable_;
    Environment* environment_;
    };

    

    class GEOGRAM_API VariableObserverList {
    public:
    VariableObserverList() :
    block_notify_(false) {
    }

    void notify_observers(const std::string& value);

    void add_observer(VariableObserver* observer);

    void remove_observer(VariableObserver* observer);

    private:
    
    typedef std::vector<VariableObserver*> Observers;
    Observers observers_;
    bool block_notify_;
    };

    

    class GEOGRAM_API Environment : public Counted {
    public:
        static Environment* instance();

        static void terminate();

        virtual bool add_environment(Environment* env);

        bool has_value(const std::string& name) const;

        virtual bool get_value(
            const std::string& name, std::string& value
        ) const;

        std::string get_value(const std::string& name) const;

        virtual bool set_value(
            const std::string& name, const std::string& value
        );

        virtual Environment* find_environment(const std::string& name);

        virtual bool add_observer(
            const std::string& name, VariableObserver* observer
        );

        virtual bool remove_observer(
            const std::string& name, VariableObserver* observer
        );

        virtual bool notify_observers(
            const std::string& name, bool recursive = false
        );

    protected:
        ~Environment() override;

        virtual bool get_local_value(
            const std::string& name, std::string& value
        ) const = 0;

        virtual bool set_local_value(
            const std::string& name, const std::string& value
        ) = 0;

        bool notify_observers(
            const std::string& name, const std::string& value,
            bool recursive
        );

        bool notify_local_observers(
            const std::string& name, const std::string& value
        );

    private:
        
        typedef SmartPointer<Environment> Environment_var;

        
        typedef std::vector<Environment_var> Environments;

        
        typedef std::map<std::string, VariableObserverList> ObserverMap;

        static Environment_var instance_;
        Environments environments_;
        ObserverMap observers_;
    };

    

    class SystemEnvironment : public Environment {
    protected:
        
        ~SystemEnvironment() override;

        bool set_local_value(
            const std::string& name, const std::string& value
        ) override;

        bool get_local_value(
            const std::string& name, std::string& value
        ) const override;
    };
}

#endif

/******* extracted from ../basic/logger.h *******/

#ifndef GEOGRAM_BASIC_LOGGER
#define GEOGRAM_BASIC_LOGGER

#ifdef __cplusplus

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <stdlib.h>


namespace GEO {

    class Logger;
    class LoggerStream;

    class NO_GEOGRAM_API LoggerStreamBuf : public std::stringbuf {
    public:
        LoggerStreamBuf(LoggerStream* loggerStream) :
            loggerStream_(loggerStream) {
        }

    private:
        int sync() override;

    private:
        LoggerStream* loggerStream_;
    };

    

    class NO_GEOGRAM_API LoggerStream : public std::ostream {
    public:
        LoggerStream(Logger* logger);

        ~LoggerStream() override;

    protected:
        void notify(const std::string& str);

    private:
        Logger* logger_;
        friend class LoggerStreamBuf;
    };

    

    class GEOGRAM_API LoggerClient : public Counted {
    public:
        virtual void div(const std::string& title) = 0;

        virtual void out(const std::string& str) = 0;

        virtual void warn(const std::string& str) = 0;

        virtual void err(const std::string& str) = 0;

        virtual void status(const std::string& str) = 0;

        ~LoggerClient() override;
    };

    
    typedef SmartPointer<LoggerClient> LoggerClient_var;

    

    class GEOGRAM_API ConsoleLogger : public LoggerClient {
    public:
        ConsoleLogger();

        void div(const std::string& title) override;

        void out(const std::string& str) override;

        void warn(const std::string& str) override;

        void err(const std::string& str) override;

        void status(const std::string& str) override;

    protected:
        ~ConsoleLogger() override;
    };

    

    class GEOGRAM_API FileLogger : public LoggerClient {
    public:
        FileLogger();

        FileLogger(const std::string& file_name);

        void div(const std::string& title) override;

        void out(const std::string& str) override;

        void warn(const std::string& str) override;

        void err(const std::string& str) override;

        void status(const std::string& str) override;

    protected:
        ~FileLogger() override;

        void set_file_name(const std::string& file_name);

    private:
        std::string log_file_name_;
        std::ostream* log_file_;
    };

    

    class GEOGRAM_API Logger : public Environment {
    public:
        static void initialize();

        static void terminate();

        static Logger* instance();


        static bool is_initialized();


        static std::ostream& div(const std::string& title);

        static std::ostream& out(const std::string& feature);

        static std::ostream& err(const std::string& feature);

        static std::ostream& warn(const std::string& feature);

        static std::ostream& status();

        void register_client(LoggerClient* client);

        void unregister_client(LoggerClient* client);

        void unregister_all_clients();

        bool is_client(LoggerClient* client) const;

        void set_quiet(bool flag);

        bool is_quiet() const {
            return quiet_;
        }


        void set_minimal(bool flag);

        bool is_minimal() const {
            return minimal_;
        }

        void set_pretty(bool flag);

        bool is_pretty() const {
            return pretty_;
        }

    protected:
        Logger();

        ~Logger() override;

        
        std::ostream& div_stream(const std::string& title);

        
        std::ostream& out_stream(const std::string& feature);

        
        std::ostream& err_stream(const std::string& feature);

        
        std::ostream& warn_stream(const std::string& feature);

        
        std::ostream& status_stream();

        std::ostream& err_console();

        void notify(LoggerStream* sender, const std::string& message);

        void notify_out(const std::string& message);

        void notify_warn(const std::string& message);

        void notify_err(const std::string& message);

        void notify_status(const std::string& message);

        bool set_local_value(
            const std::string& name, const std::string& value
        ) override;

        bool get_local_value(
            const std::string& name, std::string& value
        ) const override;


	void indent() {
	    ++indent_;
	}

	void unindent() {
	    geo_debug_assert(indent_ != 0);
	    --indent_;
	}

    private:
        static SmartPointer<Logger> instance_;

        LoggerStream out_;
        LoggerStream warn_;
        LoggerStream err_;
        LoggerStream status_;

        std::ostream* err_console_;

        // features we want or don't want to log (only applies to 'out').

        
        typedef std::set<std::string> FeatureSet;
        FeatureSet log_features_;
        FeatureSet log_features_exclude_;
        bool log_everything_;
        std::string log_file_name_;

        std::string current_feature_;
        bool current_feature_changed_;

        
        typedef std::set<LoggerClient_var> LoggerClients;
        LoggerClients clients_; // list of registered clients

        bool quiet_;
        bool pretty_;
        bool minimal_;
        bool notifying_error_;

	index_t indent_;

        friend class LoggerStream;
        friend class LoggerStreamBuf;
	friend class Stopwatch;
    };

    

}

extern "C" {
    int GEOGRAM_API geogram_printf(const char* format, ...);

    int GEOGRAM_API geogram_fprintf(FILE* out, const char* format, ...);
}

#else

#include <stdlib.h>

#ifndef GEOGRAM_API
#define GEOGRAM_API
#endif

extern int GEOGRAM_API geogram_printf(const char* format, ...);

extern int GEOGRAM_API geogram_fprintf(FILE* out, const char* format, ...);

#endif

#endif

/******* extracted from ../basic/thread_sync.h *******/

#ifndef GEOGRAM_BASIC_THREAD_SYNC
#define GEOGRAM_BASIC_THREAD_SYNC


#include <vector>
#include <atomic>

// On Windows/MSCV, we need to use a special implementation
// of spinlocks because std::atomic_flag in MSVC's stl does
// not fully implement the norm (lacks a constructor).
#ifdef GEO_OS_WINDOWS
#include <windows.h>
#include <intrin.h>
#pragma intrinsic(_InterlockedCompareExchange16)
#pragma intrinsic(_WriteBarrier)
#endif

// On MacOS, I get many warnings with atomic_flag initialization,
// such as std::atomic_flag f = ATOMIC_FLAG_INIT
#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wbraced-scalar-init"
#endif

inline void geo_pause() {
#ifdef GEO_OS_WINDOWS
    YieldProcessor();
#else
#  ifdef GEO_PROCESSOR_X86
#    ifdef __ICC
    _mm_pause();
#    else
    __builtin_ia32_pause();
#    endif
#  endif
#endif
}



#ifdef GEO_OS_WINDOWS

// Windows-specific spinlock implementation.
// I'd have prefered to use std::atomic_flag for everybody,
// unfortunately atomic_flag's constructor is not implemented in MSCV's stl,
// so we reimplement them using atomic compare-exchange functions...

namespace GEO {
    namespace Process {
        
        typedef short spinlock;

        
#       define GEOGRAM_SPINLOCK_INIT 0
        inline void acquire_spinlock(volatile spinlock& x) {
            while(_InterlockedCompareExchange16(&x, 1, 0) == 1) {
                // Intel recommends to have a PAUSE asm instruction
                // in the spinlock loop. Under MSVC/Windows,
                // YieldProcessor() is a macro that calls the
                // (undocumented) _mm_pause() intrinsic function
                // that generates a PAUSE opcode.
                YieldProcessor();
            }
            // We do not need _ReadBarrier() here since
            // _InterlockedCompareExchange16
            // "acts as a full barrier in VC2005" according to the doc
        }

        inline void release_spinlock(volatile spinlock& x) {
            _WriteBarrier(); // prevents compiler reordering
            x = 0;
        }

    }
}



#else

namespace GEO {
    namespace Process {

        
        // Note: C++20 does not need it anymore, in C++20
        // std::atomic_flag's constructor initializes it,
        // we keep it because
        // - we are using C++17
        // - the Windows implementation that uses integers rather than
        //   std::atomic_flag needs an initialization value.
#define GEOGRAM_SPINLOCK_INIT ATOMIC_FLAG_INIT

        typedef std::atomic_flag spinlock;

        inline void acquire_spinlock(volatile spinlock& x) {
            for (;;) {
                if (!x.test_and_set(std::memory_order_acquire)) {
                    break;
                }
// If compiling in C++20 we can be slightly more efficient when spinning
// (avoid unrequired atomic operations, just "peek" the flag)
#if defined(__cpp_lib_atomic_flag_test)
                while (x.test(std::memory_order_relaxed))
#endif
                    geo_pause();
            }
        }

        inline void release_spinlock(volatile spinlock& x) {
            x.clear(std::memory_order_release);
        }

    }
}
#endif



namespace GEO {
    namespace Process {

        class BasicSpinLockArray {
        public:
            BasicSpinLockArray() : spinlocks_(nullptr), size_(0) {
            }

            BasicSpinLockArray(index_t size_in) : spinlocks_(nullptr), size_(0) {
                resize(size_in);
            }

            BasicSpinLockArray(const BasicSpinLockArray& rhs) = delete;

            BasicSpinLockArray& operator=(
                const BasicSpinLockArray& rhs
            ) = delete;

            void resize(index_t size_in) {
                delete[] spinlocks_;
                spinlocks_ = new spinlock[size_in];
                size_ = size_in;
                // Need to initialize the spinlocks to false (dirty !)
                // (maybe use placement new on each item..., to be tested)
                for(index_t i=0; i<size_; ++i) {
                    Process::release_spinlock(spinlocks_[i]);
                }
            }

            void clear() {
                delete[] spinlocks_;
                spinlocks_ = nullptr;
            }

            index_t size() const {
                return size_;
            }

            void acquire_spinlock(index_t i) {
                geo_debug_assert(i < size());
                GEO::Process::acquire_spinlock(spinlocks_[i]);
            }

            void release_spinlock(index_t i) {
                geo_debug_assert(i < size());
                GEO::Process::release_spinlock(spinlocks_[i]);
            }

        private:
            // Cannot use a std::vector because std::atomic_flag does not
            // have copy ctor nor assignment operator.
            spinlock* spinlocks_;
            index_t size_;
        };
    }
}



namespace GEO {
    namespace Process {

        class CompactSpinLockArray {
        public:
            CompactSpinLockArray() : spinlocks_(nullptr), size_(0) {
            }

            CompactSpinLockArray(index_t size_in) : spinlocks_(nullptr),size_(0){
                resize(size_in);
            }

            ~CompactSpinLockArray() {
                clear();
            }

            CompactSpinLockArray(const CompactSpinLockArray& rhs) = delete;

            CompactSpinLockArray& operator=(
                const CompactSpinLockArray& rhs
            ) = delete;

            void resize(index_t size_in) {
                if(size_ != size_in) {
                    size_ = size_in;
                    index_t nb_words = (size_ >> 5) + 1;
                    delete[] spinlocks_;
                    spinlocks_ = new std::atomic<uint32_t>[nb_words];
                    for(index_t i=0; i<nb_words; ++i) {
                        // Note: std::atomic_init() is deprecated in C++20
                        // that can initialize std::atomic through its
                        // non-default constructor. We'll need to do something
                        // else when we'll switch to C++20 (placement new...)
                        std::atomic_init<uint32_t>(&spinlocks_[i],0u);
                    }
                }
// Test at compile time that we are using atomic uint32_t operations (and not
// using an additional lock which would be catastrophic in terms of performance)
#ifdef __cpp_lib_atomic_is_always_lock_free
                static_assert(std::atomic<uint32_t>::is_always_lock_free);
#else
// If we cannot test that at compile time, we test that at runtime in debug
// mode (so that we will be notified in the non-regression test if one of
// the platforms has the problem, which is very unlikely though...)
                geo_debug_assert(size_ == 0 || spinlocks_[0].is_lock_free());
#endif
            }

            index_t size() const {
                return size_;
            }

            void clear() {
                delete[] spinlocks_;
                size_ = 0;
            }

            void acquire_spinlock(index_t i) {
                geo_debug_assert(i < size());
                index_t  w = i >> 5;
                uint32_t b = uint32_t(i & 31);
                uint32_t mask = (1u << b);
                while(
                    (spinlocks_[w].fetch_or(
                        mask, std::memory_order_acquire
                    ) & mask) != 0
                ) {
                    geo_pause();
                }
            }

            void release_spinlock(index_t i) {
                geo_debug_assert(i < size());
                index_t  w = i >> 5;
                uint32_t b = uint32_t(i & 31);
                uint32_t mask = ~(1u << b);
                spinlocks_[w].fetch_and(mask, std::memory_order_release);
            }

        private:
            // Cannot use a std::vector because std::atomic<> does not
            // have copy ctor nor assignment operator.
            std::atomic<uint32_t>* spinlocks_;
            index_t size_;
        };

    }
}



namespace GEO {
    namespace Process {
        typedef CompactSpinLockArray SpinLockArray;
    }
}



#endif

/******* extracted from ../basic/packed_arrays.h *******/

#ifndef GEOGRAM_BASIC_PACKED_ARRAYS
#define GEOGRAM_BASIC_PACKED_ARRAYS



namespace GEO {

    class GEOGRAM_API PackedArrays {
    public:
    PackedArrays();

    ~PackedArrays();

    bool thread_safe() const {
        return thread_safe_;
    }

    void set_thread_safe(bool flag);

    void init(
        index_t nb_arrays,
        index_t Z1_block_size,
        bool static_mode = false
    );

    void clear();

    index_t nb_arrays() const {
        return nb_arrays_;
    }

    index_t array_size(index_t array_index) const {
        geo_debug_assert(array_index < nb_arrays_);
        return Z1_[array_index * Z1_stride_];
    }

    void get_array(
        index_t array_index, vector<index_t>& array, bool lock = true
    ) const {
        if(lock) {
            lock_array(array_index);
        }
        array.resize(array_size(array_index));
        if(array.size() != 0) {
            get_array(array_index, &array[0], false);
        }
        if(lock) {
            unlock_array(array_index);
        }
    }

    void get_array(
        index_t array_index, index_t* array, bool lock = true
    ) const;

    void set_array(
        index_t array_index,
        index_t array_size, const index_t* array_elements,
        bool lock = true
    );

    void set_array(
        index_t array_index,
        const vector<index_t>& array,
        bool lock = true
    ) {
        if(array.size() == 0) {
            set_array(array_index, 0, nullptr, lock);
        } else {
            set_array(
                array_index, index_t(array.size()), &array[0], lock
            );
        }
    }

    void resize_array(
        index_t array_index, index_t array_size, bool lock
    );

    void lock_array(index_t array_index) const {
        if(thread_safe_) {
            Z1_spinlocks_.acquire_spinlock(array_index);
        }
    }

    void unlock_array(index_t array_index) const {
        if(thread_safe_) {
            Z1_spinlocks_.release_spinlock(array_index);
        }
    }

    void show_stats();

    protected:
    bool static_mode() const {
        return ZV_ == nullptr;
    }

    private:
    
    PackedArrays(const PackedArrays& rhs);

    
    PackedArrays& operator= (const PackedArrays& rhs);

    private:
    index_t nb_arrays_;
    index_t Z1_block_size_;
    index_t Z1_stride_;
    index_t* Z1_;
    index_t** ZV_;
    bool thread_safe_;
    mutable Process::SpinLockArray Z1_spinlocks_;
    };
}

#endif

/******* extracted from ../basic/progress.h *******/

#ifndef GEOGRAM_BASIC_PROGRESS
#define GEOGRAM_BASIC_PROGRESS



namespace GEO {

    class GEOGRAM_API ProgressClient : public Counted {
    public:
        virtual void begin() = 0;

        virtual void progress(index_t step, index_t percent) = 0;

        virtual void end(bool canceled) = 0;

    protected:
        
        ~ProgressClient() override;
    };

    
    typedef SmartPointer<ProgressClient> ProgressClient_var;

    

    struct GEOGRAM_API TaskCanceled : std::exception {
        const char* what() const GEO_NOEXCEPT override;
    };

    

    class ProgressTask;

    namespace Progress {
        void GEOGRAM_API initialize();

        void GEOGRAM_API terminate();

        void GEOGRAM_API set_client(ProgressClient* client);

        GEOGRAM_API const ProgressTask* current_progress_task();

        void GEOGRAM_API cancel();

        bool GEOGRAM_API is_canceled();

        void GEOGRAM_API clear_canceled();
    }

    

    class GEOGRAM_API ProgressTask {
    public:
    ProgressTask(
        const std::string& task_name, index_t max_steps,
        bool quiet
    );

    ProgressTask(
        const std::string& task_name = "", index_t max_steps = 100
    );

    virtual ~ProgressTask();

    virtual void progress(index_t step);

    virtual void next();

    bool is_canceled() const;

    void reset();

    void reset(index_t max_steps);

    const std::string& task_name() const {
        return task_name_;
    }

    double start_time() const {
        return start_time_;
    }

    index_t max_steps() const {
        return max_steps_;
    }

    index_t step() const {
        return step_;
    }

    index_t percent() const {
        return percent_;
    }

    protected:
    virtual void update();

    private:
    std::string task_name_;
    double start_time_;
    bool quiet_;
    index_t max_steps_;
    index_t step_;
    index_t percent_;
    };
}

#endif

/******* extracted from ../basic/process.h *******/

#ifndef GEOGRAM_BASIC_PROCESS
#define GEOGRAM_BASIC_PROCESS

#include <functional>


namespace GEO {

    class GEOGRAM_API Thread : public Counted {
    public:

        Thread() : id_(0) {
        }

        virtual void run() = 0;

        index_t id() const {
            return id_;
        }

        static Thread* current();

        static index_t current_id() {
            return current() == nullptr ? 0 : current()->id();
        }

    protected:
        
        ~Thread() override;


    private:
        void set_id(index_t id_in) {
            id_ = id_in;
        }

        static void set_current(Thread* thread);

        index_t id_;

        // ThreadManager needs to access set_current() and
        // set_id().
        friend class ThreadManager;
    };

    
    typedef SmartPointer<Thread> Thread_var;

    typedef std::vector<Thread_var> ThreadGroup;

    template <class THREAD>
    class TypedThreadGroup : public ThreadGroup {
    public:
        TypedThreadGroup() {
        }

        THREAD* operator[] (index_t i) {
            geo_debug_assert(i < size());
            Thread* result = ThreadGroup::operator[] (i);
            return static_cast<THREAD*>(result);
        }
    };

    class GEOGRAM_API ThreadManager : public Counted {
    public:
        virtual void run_threads(ThreadGroup& threads);

        virtual index_t maximum_concurrent_threads() = 0;

    protected:
        virtual void run_concurrent_threads(
            ThreadGroup& threads, index_t max_threads
        ) = 0;


        static void set_thread_id(Thread* thread, index_t id) {
            thread->set_id(id);
        }

        static void set_current_thread(Thread* thread) {
            Thread::set_current(thread);
        }

        
        ~ThreadManager() override;
    };

    
    typedef SmartPointer<ThreadManager> ThreadManager_var;

    class GEOGRAM_API MonoThreadingThreadManager : public ThreadManager {
    public:
        index_t maximum_concurrent_threads() override;

    protected:
        
        ~MonoThreadingThreadManager() override;

        void run_concurrent_threads(
            ThreadGroup& threads, index_t max_threads
        ) override;
    };

    namespace Process {

        void GEOGRAM_API initialize(int flags);

        void GEOGRAM_API terminate();


        void GEOGRAM_API sleep(index_t microseconds);

        void GEOGRAM_API show_stats();

        void GEOGRAM_API brute_force_kill();

        index_t GEOGRAM_API maximum_concurrent_threads();

        void GEOGRAM_API run_threads(ThreadGroup& threads);

        index_t GEOGRAM_API number_of_cores();

        void GEOGRAM_API set_thread_manager(ThreadManager* thread_manager);

        bool GEOGRAM_API is_running_threads();

        void GEOGRAM_API enable_FPE(bool flag);

        bool GEOGRAM_API FPE_enabled();

        void GEOGRAM_API enable_multithreading(bool flag);

        bool GEOGRAM_API multithreading_enabled();

        void GEOGRAM_API set_max_threads(index_t num_threads);

        index_t GEOGRAM_API max_threads();

        void GEOGRAM_API enable_cancel(bool flag);

        bool GEOGRAM_API cancel_enabled();

        size_t GEOGRAM_API used_memory();

        size_t GEOGRAM_API max_used_memory();

        std::string GEOGRAM_API executable_filename();

        void print_stack_trace();
    }

    void GEOGRAM_API parallel_for(
        index_t from, index_t to, std::function<void(index_t)> func,
        index_t threads_per_core = 1,
        bool interleaved = false
    );

    void GEOGRAM_API parallel_for_slice(
        index_t from, index_t to, std::function<void(index_t, index_t)> func,
        index_t threads_per_core = 1
    );

    void GEOGRAM_API parallel(
        std::function<void()> f1,
        std::function<void()> f2
    );

    void GEOGRAM_API parallel(
        std::function<void()> f1,
        std::function<void()> f2,
        std::function<void()> f3,
        std::function<void()> f4
    );

    void GEOGRAM_API parallel(
        std::function<void()> f1,
        std::function<void()> f2,
        std::function<void()> f3,
        std::function<void()> f4,
        std::function<void()> f5,
        std::function<void()> f6,
        std::function<void()> f7,
        std::function<void()> f8
    );

}

#endif

/******* extracted from ../basic/psm.h *******/

#ifndef GEOGRAM_BASIC_PSM
#define GEOGRAM_BASIC_PSM


#include <assert.h>
#include <iostream>
#include <string>

#ifndef GEOGRAM_PSM
#define GEOGRAM_PSM
#endif

#ifndef GEOGRAM_BASIC_ASSERT

#define geo_assert(x) assert(x)
#define geo_range_assert(x, min_val, max_val)           \
    assert((x) >= (min_val) && (x) <= (max_val))
#define geo_assert_not_reached assert(0)

#ifdef GEO_DEBUG
#define geo_debug_assert(x) assert(x)
#define geo_debug_range_assert(x, min_val, max_val)     \
    assert((x) >= (min_val) && (x) <= (max_val))
#else
#define geo_debug_assert(x)
#define geo_debug_range_assert(x, min_val, max_val)
#endif

#ifdef GEO_PARANOID
#define geo_parano_assert(x) geo_assert(x)
#define geo_parano_range_assert(x, min_val, max_val)    \
    geo_range_assert(x, min_val, max_val)
#else
#define geo_parano_assert(x)
#define geo_parano_range_assert(x, min_val, max_val)
#endif

#endif

#ifndef geo_cite
#define geo_cite(x)
#endif

#ifndef geo_cite_with_info
#define geo_cite_with_info(x,y)
#endif

#ifndef GEOGRAM_BASIC_LOGGER

namespace GEO {
    namespace Logger {
        inline std::ostream& out(const std::string& name) {
            return std::cout << " [" << name << "]";
        }

        inline std::ostream& err(const std::string& name) {
            return std::cerr << "E[" << name << "]";
        }

        inline std::ostream& warn(const std::string& name) {
            return std::cerr << "W[" << name << "]";
        }
    }

}

#endif

#ifndef FPG_UNCERTAIN_VALUE
#define FPG_UNCERTAIN_VALUE 0
#endif

#define GEOGRAM_WITH_PDEL

#endif

/******* extracted from ../basic/factory.h *******/

#ifndef GEOGRAM_BASIC_FACTORY
#define GEOGRAM_BASIC_FACTORY

#include <string>
#include <map>
#include <vector>
#include <typeinfo>


namespace GEO {

    class GEOGRAM_API InstanceRepo {
    public:
    typedef Counted Instance;

    template <class InstanceType>
    static InstanceType& instance() {
        const std::string name = typeid(InstanceType).name();
        Instance* instance = get(name);
        if(instance == nullptr) {
            instance = new InstanceType;
            add(name, instance);
        }
        return *static_cast<InstanceType*>(instance);
    }

    private:
    static void add(const std::string& name, Instance* instance);

    static Instance* get(const std::string& name);
    };

    

    template <class FactoryCreator>
    class Factory : public InstanceRepo::Instance {
    public:
        typedef typename FactoryCreator::CreatorType CreatorType;

        template <class ConcreteType>
        static void register_creator(const std::string& name) {
            Factory& self = instance();
            self.registry_[name] =
                FactoryCreator::template create<ConcreteType>;
        }

        static CreatorType find_creator(const std::string& name) {
            Factory& self = instance();
            auto i = self.registry_.find(name);
            return i == self.registry_.end() ? nullptr : i->second;
        }

        static void list_creators(std::vector<std::string>& names) {
            Factory& self = instance();
            for(auto& it : self.registry_) {
                names.push_back(it.first);
            }
        }

        static bool has_creator(const std::string& name) {
            Factory& self = instance();
            for(auto& it : self.registry_) {
                if(it.first == name) {
                    return true;
                }
            }
            return false;
        }

        template <class ConcreteType>
        struct RegisterCreator {
            RegisterCreator(const std::string& name) {
                Factory::template register_creator<ConcreteType>(name);
            }
        };

    protected:
        ~Factory() override {
        }

    private:
        static inline Factory& instance() {
            return InstanceRepo::instance<Factory>();
        }

        typedef std::map<std::string, CreatorType> Registry;
        Registry registry_;
    };

    template <class Type>
    struct FactoryCreator0 {
        typedef Type* (* CreatorType)();

        template <class ConcreteType>
        static Type* create() {
            return new ConcreteType;
        }
    };

    template <class Type>
    class Factory0 : public Factory<FactoryCreator0<Type> > {
        typedef Factory<FactoryCreator0<Type> > BaseClass;

    public:
        static Type* create_object(const std::string& name) {
            typename BaseClass::CreatorType creator =
                BaseClass::find_creator(name);
            return creator == nullptr ? nullptr : (* creator)();
        }
    };

    template <class Type, class Param1>
    struct FactoryCreator1 {
        typedef Type* (* CreatorType)(const Param1&);

        template <class ConcreteType>
        static Type* create(const Param1& param1) {
            return new ConcreteType(param1);
        }
    };

    template <class Type, class Param1>
    class Factory1 : public Factory<FactoryCreator1<Type, Param1> > {
        typedef Factory<FactoryCreator1<Type, Param1> > BaseClass;

    public:
        static Type* create_object(const std::string& name, const Param1& param1) {
            typename BaseClass::CreatorType creator =
                BaseClass::find_creator(name);
            return creator == nullptr ? nullptr : (* creator)(param1);
        }
    };

#define geo_register_creator(FactoryType, ConcreteType, name)           \
    static FactoryType::RegisterCreator<ConcreteType>                   \
    CPP_CONCAT(Factory_register_creator_, __LINE__) (name);             \
    geo_argused(CPP_CONCAT(Factory_register_creator_, __LINE__))
}

#endif

/******* extracted from ../basic/determinant.h *******/

#ifndef GEOGRAM_BASIC_DETERMINANT
#define GEOGRAM_BASIC_DETERMINANT



namespace GEO {

    

    template <class T>
    inline T det2x2(
        const T& a11, const T& a12,
        const T& a21, const T& a22
    ) {
        return a11*a22-a12*a21 ;
    }

    template <class T>
    inline T det3x3(
        const T& a11, const T& a12, const T& a13,
        const T& a21, const T& a22, const T& a23,
        const T& a31, const T& a32, const T& a33
    ) {
        return
            a11*det2x2(a22,a23,a32,a33)
            -a21*det2x2(a12,a13,a32,a33)
            +a31*det2x2(a12,a13,a22,a23);
    }


    template <class T>
    inline T det4x4(
        const T& a11, const T& a12, const T& a13, const T& a14,
        const T& a21, const T& a22, const T& a23, const T& a24,
        const T& a31, const T& a32, const T& a33, const T& a34,
        const T& a41, const T& a42, const T& a43, const T& a44
    ) {
        T m12 = a21*a12 - a11*a22;
        T m13 = a31*a12 - a11*a32;
        T m14 = a41*a12 - a11*a42;
        T m23 = a31*a22 - a21*a32;
        T m24 = a41*a22 - a21*a42;
        T m34 = a41*a32 - a31*a42;

        T m123 = m23*a13 - m13*a23 + m12*a33;
        T m124 = m24*a13 - m14*a23 + m12*a43;
        T m134 = m34*a13 - m14*a33 + m13*a43;
        T m234 = m34*a23 - m24*a33 + m23*a43;

        return (m234*a14 - m134*a24 + m124*a34 - m123*a44);
    }
}

#endif

/******* extracted from ../basic/rationalg.h *******/

#ifndef GEOGRAM_BASIC_RATIONALG
#define GEOGRAM_BASIC_RATIONALG



namespace GEO {

    template <class T> class rationalg {
    public:
        typedef T value_type;

        rationalg() = default;

        explicit rationalg(double x) : num_(x), denom_(1.0) {
        }

        explicit rationalg(const T& x) : num_(x), denom_(1.0) {
        }

        explicit rationalg(T&& x) : num_(x), denom_(1.0) {
        }

        explicit rationalg(double num, double denom)
            : num_(num), denom_(denom) {
        }

        explicit rationalg(const T& num, const T& denom)
            : num_(num), denom_(denom) {
        }

        explicit rationalg(
            T&& num, T&& denom
        ) : num_(num), denom_(denom) {
        }

        rationalg(const rationalg<T>& rhs) = default;

        rationalg(rationalg<T>&& rhs) = default;

        rationalg<T>& operator= (const rationalg<T>& rhs) = default;

        rationalg<T>& operator= (rationalg<T>&& rhs) = default;

        const T& num() const {
            return num_;
        }

        const T& denom() const {
            return denom_;
        }

        T& num() {
            return num_;
        }

        T& denom() {
            return denom_;
        }

        void optimize() {
            Numeric::optimize_number_representation(num_);
            Numeric::optimize_number_representation(denom_);
        }

        

        rationalg<T>& operator+= (const rationalg<T>& rhs) {
            if(has_same_denom(rhs)) {
                num_ += rhs.num_;
            } else {
                num_ = num_ * rhs.denom_ + rhs.num_ * denom_;
                denom_ *= rhs.denom_;
            }
            return *this;
        }

        rationalg<T>& operator-= (const rationalg<T>& rhs) {
            if(has_same_denom(rhs)) {
                num_ -= rhs.num_;
            } else {
                num_ = num_ * rhs.denom_ - rhs.num_ * denom_;
                denom_ *= rhs.denom_;
            }
            return *this;
        }

        rationalg<T>& operator*= (const rationalg<T>& rhs) {
            num_ *= rhs.num_;
            denom_ *= rhs.denom_;
            return *this;
        }

        rationalg<T>& operator/= (const rationalg<T>& rhs) {
            num_ *= rhs.denom_;
            denom_ *= rhs.num_;
            return *this;
        }

        rationalg<T>& operator+= (double rhs) {
            num_ += denom_ * T(rhs);
            return *this;
        }

        rationalg<T>& operator-= (double rhs) {
            num_ -= denom_ * T(rhs);
            return *this;
        }

        rationalg<T>& operator*= (double rhs) {
            num_ *= T(rhs);
            return *this;
        }

        rationalg<T>& operator/= (double rhs) {
            denom_ *= T(rhs);
            return *this;
        }

        

        rationalg<T> operator+ (const rationalg<T>& rhs) const {
            if(has_same_denom(rhs)) {
                return rationalg(
                    num_ + rhs.num_,
                    denom_
                );
            }
            return rationalg(
                num_ * rhs.denom_ + rhs.num_ * denom_,
                denom_ * rhs.denom_
            );
        }

        rationalg<T> operator- (const rationalg<T>& rhs) const {
            if(has_same_denom(rhs)) {
                return rationalg(
                    num_ - rhs.num_,
                    denom_
                );
            }
            return rationalg(
                num_ * rhs.denom_ - rhs.num_ * denom_,
                denom_ * rhs.denom_
            );
        }

        rationalg<T> operator* (const rationalg<T>& rhs) const {
            return rationalg(
                num_ * rhs.num_,
                denom_ * rhs.denom_
            );
        }

        rationalg<T> operator/ (const rationalg<T>& rhs) const {
            return rationalg(
                num_ * rhs.denom_,
                denom_ * rhs.num_
            );
        }


        rationalg<T> operator+ (double rhs) const {
            return rationalg(
                num_ + T(rhs) * denom_,
                denom_
            );
        }

        rationalg<T> operator- (double rhs) const {
            return rationalg(
                num_ - T(rhs) * denom_,
                denom_
            );
        }

        rationalg<T> operator* (double rhs) const {
            return rationalg(
                num_ * T(rhs),
                denom_
            );
        }

        rationalg<T> operator/ (double rhs) const {
            return rationalg(
                num_,
                denom_* T(rhs)
            );
        }

        

        rationalg<T> operator- () const {
            return rationalg(
                -num_,
                denom_
            );
        }

        

        Sign sign() const {
            geo_debug_assert(denom_.sign() != ZERO);
            return Sign(num_.sign() * denom_.sign());
        }

        

        Sign compare(const rationalg<T>& rhs) const {
            if(sign() != rhs.sign()){
                return Sign(sign()-rhs.sign());
            }
            if(has_same_denom(rhs)) {
                return Sign(num_.compare(rhs.num_) * denom_.sign());
            }
            return Sign(
                (num_ * rhs.denom_).compare(rhs.num_ * denom_) *
                denom_.sign() * rhs.denom_.sign()
            );
        }

        Sign compare(double rhs) const {
            return Sign(
                num_.compare(T(rhs)*denom_) * denom_.sign()
            );
        }

        bool operator> (const rationalg<T>& rhs) const {
            return (int(compare(rhs))>0);
        }

        bool operator>= (const rationalg<T>& rhs) const {
            return (int(compare(rhs))>=0);
        }

        bool operator< (const rationalg<T>& rhs) const {
            return (int(compare(rhs))<0);
        }

        bool operator<= (const rationalg<T>& rhs) const {
            return (int(compare(rhs))<=0);
        }

        bool operator> (double rhs) const {
            return (int(compare(rhs))>0);
        }

        bool operator>= (double rhs) const {
            return (int(compare(rhs))>=0);
        }

        bool operator< (double rhs) const {
            return (int(compare(rhs))<0);
        }

        bool operator<= (double rhs) const {
            return (int(compare(rhs))<=0);
        }

        

        double estimate() const {
            return num_.estimate() / denom_.estimate();
        }

    protected:
        void copy(const rationalg<T>& rhs) {
            num_ = rhs.num_;
            denom_ = rhs.denom_;
        }

        bool has_same_denom(const rationalg<T>& rhs) const {
            return denom_ == rhs.denom_;
        }

    private:
        T num_;
        T denom_;
    };

    

    template <class T>
    inline rationalg<T> operator+ (double a, const rationalg<T>& b) {
        return b + a;
    }

    template <class T>
    inline rationalg<T> operator- (double a, const rationalg<T>& b) {
        rationalg<T> result = b - a;
        result.num().negate();
        return result;
    }

    template <class T>
    inline rationalg<T> operator* (double a, const rationalg<T>& b) {
        return b * a;
    }

    template <class T>
    inline rationalg<T> operator/ (double a, const rationalg<T>& b) {
        return rationalg<T>(
            T(a)*b.denom(),
            b.num()
        );
    }

    template <class T>
    inline bool operator== (const rationalg<T>& a, const rationalg<T>& b) {
        return (a.compare(b) == ZERO);
    }

    template <class T>
    inline bool operator== (const rationalg<T>& a, double b) {
        return (a.compare(b) == ZERO);
    }

    template <class T>
    inline bool operator== (double a, const rationalg<T>& b) {
        return (b.compare(a) == ZERO);
    }

    template <class T>
    inline bool operator!= (const rationalg<T>& a, const rationalg<T>& b) {
        return (a.compare(b) != ZERO);
    }

    template <class T>
    inline bool operator!= (const rationalg<T>& a, double b) {
        return (a.compare(b) != ZERO);
    }

    template <class T>
    inline bool operator!= (double a, const rationalg<T>& b) {
        return (b.compare(a) != ZERO);
    }

    

    template <class T> inline Sign geo_sgn(const rationalg<T>& x) {
        return x.sign();
    }

    template <class T> inline Sign geo_cmp(
        const rationalg<T>& a, const rationalg<T>& b
    ) {
        return a.compare(b);
    }

    namespace Numeric {

        template <class T> inline void optimize_number_representation(
            rationalg<T>& x
        ) {
            x.optimize();
        }

    }

    

}

#endif

/******* extracted from ../basic/vecg.h *******/

#ifndef GEOGRAM_BASIC_VECG
#define GEOGRAM_BASIC_VECG

#include <initializer_list>

#include <iostream>
#include <cfloat>
#include <cmath>


namespace GEO {

    template <index_t DIM, class T>
    class vecng {
    public:
        
        static constexpr index_t dim = DIM;

        
        typedef vecng<DIM, T> vector_type;

        
        typedef T value_type;

        vecng() {
            for(index_t i = 0; i < DIM; i++) {
                data_[i] = T(0);
            }
        }

        // This one should never be called :
        // a template constructor cannot be a copy constructor

        template <class T2>
        explicit vecng(const vecng<DIM, T2>& v) {
            for(index_t i = 0; i < DIM; i++) {
                data_[i] = T(v[i]);
            }
        }

        // to avoid compilation problems
        template <class T2, index_t DIM2>
        explicit vecng(
            const vecng<DIM2, T2>& v
        ) {
            geo_debug_assert(DIM2 == DIM);
            for(index_t i = 0; i < DIM; i++) {
                data_[i] = T(v[i]);
            }
        }

        template <class T2>
        explicit vecng(const T2* v) {
            for(index_t i = 0; i < DIM; i++) {
                data_[i] = T(v[i]);
            }
        }

        vecng(const std::initializer_list<T>& Vi) {
            index_t i = 0;
            for(auto& it: Vi) {
                geo_debug_assert(i < DIM);
                data()[i] = it;
                ++i;
            }
        }

        index_t dimension() const {
            return DIM;
        }

        T* data() {
            return data_;
        }

        const T* data() const {
            return data_;
        }

        inline T& operator[] (index_t i) {
            geo_debug_assert(i < DIM);
            return data()[i];
        }

        inline const T& operator[] (index_t i) const {
            geo_debug_assert(i < DIM);
            return data()[i];
        }

        inline T length2() const {
            T result = T(0);
            for(index_t i = 0; i < DIM; i++) {
                result += data_[i] * data_[i];
            }
            return result;
        }

        inline T length() const {
            return sqrt(length2());
        }

        inline T distance2(const vector_type& v) const {
            T result(0);
            for(index_t i = 0; i < DIM; i++) {
                result += geo_sqr(v.data_[i] - data_[i]);
            }
            return result;
        }

        inline T distance(const vector_type& v) const {
            return sqrt(distance2(v));
        }

        // operators

        inline vector_type& operator+= (const vector_type& v) {
            for(index_t i = 0; i < DIM; i++) {
                data_[i] += v.data_[i];
            }
            return *this;
        }

        inline vector_type& operator-= (const vector_type& v) {
            for(index_t i = 0; i < DIM; i++) {
                data_[i] -= v.data_[i];
            }
            return *this;
        }

        template <class T2>
        inline vector_type& operator*= (T2 s) {
            for(index_t i = 0; i < DIM; i++) {
                data_[i] *= T(s);
            }
            return *this;
        }

        template <class T2>
        inline vector_type& operator/= (T2 s) {
            for(index_t i = 0; i < DIM; i++) {
                data_[i] /= T(s);
            }
            return *this;
        }

        inline vector_type operator+ (const vector_type& v) const {
            vector_type result(*this);
            for(index_t i = 0; i < DIM; i++) {
                result.data_[i] += v.data_[i];
            }
            return result;
        }

        inline vector_type operator- (const vector_type& v) const {
            vector_type result(*this);
            for(index_t i = 0; i < DIM; i++) {
                result.data_[i] -= v.data_[i];
            }
            return result;
        }

        template <class T2>
        inline vector_type operator* (T2 s) const {
            vector_type result(*this);
            for(index_t i = 0; i < DIM; i++) {
                result.data_[i] *= T(s);
            }
            return result;
        }

        template <class T2>
        inline vector_type operator/ (T2 s) const {
            vector_type result(*this);
            for(index_t i = 0; i < DIM; i++) {
                result.data_[i] /= T(s);
            }
            return result;
        }

        inline vector_type operator- () const {
            vector_type result;
            for(index_t i = 0; i < DIM; i++) {
                result.data_[i] = -data_[i];
            }
            return result;
        }

    private:
        T data_[DIM];
    };

    template <index_t DIM, class T>
    inline T dot(
        const vecng<DIM, T>& v1, const vecng<DIM, T>& v2
    ) {
        T result = 0;
        for(index_t i = 0; i < DIM; i++) {
            result += v1[i] * v2[i];
        }
        return result;
    }

    template <class T2, index_t DIM, class T>
    inline vecng<DIM, T> operator* (
        T2 s, const vecng<DIM, T>& v
    ) {
        vecng<DIM, T> result;
        for(index_t i = 0; i < DIM; i++) {
            result[i] = T(s) * v[i];
        }
        return result;
    }

    // Compatibility with GLSL

    template <index_t DIM, class T>
    inline T length(const vecng<DIM, T>& v) {
        return v.length();
    }

    template <index_t DIM, class T>
    inline T length2(const vecng<DIM, T>& v) {
        return v.length2();
    }

    template <index_t DIM, class T>
    inline T distance2(
        const vecng<DIM, T>& v1, const vecng<DIM, T>& v2
    ) {
        return v2.distance2(v1);
    }

    template <index_t DIM, class T>
    inline T distance(
        const vecng<DIM, T>& v1, const vecng<DIM, T>& v2
    ) {
        return v2.distance(v1);
    }

    template <index_t DIM, class T>
    inline vecng<DIM, T> normalize(
        const vecng<DIM, T>& v
    ) {
        T s = length(v);
        if(s > 1e-30) {
            s = T(1) / s;
        }
        return s * v;
    }

    template <index_t DIM, class T>
    inline vecng<DIM, T> mix(
        const vecng<DIM, T>& v1, const vecng<DIM, T>& v2, T s
    ) {
        return (T(1) - s) * v1 + s * v2;
    }

    

    template <class T>
    class vecng<2, T> {
    public:
        
        static constexpr index_t dim = 2;

        
        typedef vecng<dim, T> vector_type;

        
        typedef T value_type;

        
        vecng() :
            x(0),
            y(0) {
        }

        vecng(T x_in, T y_in) :
            x(x_in),
            y(y_in) {
        }

        
        template <class T2>
        explicit vecng(const vecng<dim, T2>& v) :
            x(v.x),
            y(v.y) {
        }

        
        template <class T2>
        explicit vecng(const T2* v) :
            x(v[0]),
            y(v[1]) {
        }

        
        vecng(const std::initializer_list<T>& Vi) {
            index_t i = 0;
            for(auto& it: Vi) {
                geo_debug_assert(i < dim);
                data()[i] = it;
                ++i;
            }
        }

        
        inline T length2() const {
            return x * x + y * y;
        }

        
        inline T length() const {
            return sqrt(x * x + y * y);
        }

        
        inline T distance2(const vector_type& v) const {
            T dx = v.x - x;
            T dy = v.y - y;
            return dx * dx + dy * dy;
        }

        
        inline T distance(const vector_type& v) const {
            return sqrt(distance2(v));
        }

        
        inline vector_type& operator+= (const vector_type& v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        
        inline vector_type& operator-= (const vector_type& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        
        template <class T2>
        inline vector_type& operator*= (T2 s) {
            x *= T(s);
            y *= T(s);
            return *this;
        }

        
        template <class T2>
        inline vector_type& operator/= (T2 s) {
            x /= T(s);
            y /= T(s);
            return *this;
        }

        
        inline vector_type operator+ (const vector_type& v) const {
            return vector_type(x + v.x, y + v.y);
        }

        
        inline vector_type operator- (const vector_type& v) const {
            return vector_type(x - v.x, y - v.y);
        }

        
        template <class T2>
        inline vector_type operator* (T2 s) const {
            return vector_type(x * T(s), y * T(s));
        }

        
        template <class T2>
        inline vector_type operator/ (T2 s) const {
            return vector_type(x / T(s), y / T(s));
        }

        
        inline vector_type operator- () const {
            return vector_type(-x, -y);
        }

        
        index_t dimension() const {
            return dim;
        }

        
        T* data() {
            return &x;
        }

        
        const T* data() const {
            return &x;
        }

        
        inline T& operator[] (index_t i) {
            geo_debug_assert(i < dim);
            return data()[i];
        }

        
        inline const T& operator[] (index_t i) const {
            geo_debug_assert(i < dim);
            return data()[i];
        }

        
        void optimize() {
            Numeric::optimize_number_representation(x);
            Numeric::optimize_number_representation(y);
        }

        
        T x;
        
        T y;
    };

    template <class T>
    inline T dot(
        const vecng<2, T>& v1, const vecng<2, T>& v2
    ) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    template <class T>
    inline T det(
        const vecng<2, T>& v1, const vecng<2, T>& v2
    ) {
        return v1.x * v2.y - v1.y * v2.x;
    }

    template <class T2, class T>
    inline vecng<2, T> operator* (
        T2 s, const vecng<2, T>& v
    ) {
        return vecng<2, T>(T(s) * v.x, T(s) * v.y);
    }

    

    template <class T>
    class vecng<3, T> {
    public:
        
        static constexpr index_t dim = 3;

        
        typedef vecng<dim, T> vector_type;

        
        typedef T value_type;

        
        vecng() :
            x(T(0.0)),
            y(T(0.0)),
            z(T(0.0)) {
        }

        vecng(T x_in, T y_in, T z_in) :
            x(x_in),
            y(y_in),
            z(z_in) {
        }

        
        template <class T2>
        explicit vecng(const vecng<dim, T2>& v) :
            x(v.x),
            y(v.y),
            z(v.z) {
        }

        
        template <class T2>
        explicit vecng(const T2* v) :
            x(v[0]),
            y(v[1]),
            z(v[2]) {
        }

        
        vecng(const std::initializer_list<T>& Vi) {
            index_t i = 0;
            for(auto& it: Vi) {
                geo_debug_assert(i < dim);
                data()[i] = it;
                ++i;
            }
        }

        
        inline T length2() const {
            return x * x + y * y + z * z;
        }

        
        inline T length() const {
            return sqrt(x * x + y * y + z * z);
        }

        
        inline T distance2(const vector_type& v) const {
            T dx = v.x - x;
            T dy = v.y - y;
            T dz = v.z - z;
            return dx * dx + dy * dy + dz * dz;
        }

        
        inline T distance(const vector_type& v) const {
            return sqrt(distance2(v));
        }

        
        inline vector_type& operator+= (const vector_type& v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        
        inline vector_type& operator-= (const vector_type& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        
        template <class T2>
        inline vector_type& operator*= (T2 s) {
            x *= T(s);
            y *= T(s);
            z *= T(s);
            return *this;
        }

        
        template <class T2>
        inline vector_type& operator/= (T2 s) {
            x /= T(s);
            y /= T(s);
            z /= T(s);
            return *this;
        }

        
        inline vector_type operator+ (const vector_type& v) const {
            return vector_type(x + v.x, y + v.y, z + v.z);
        }

        
        inline vector_type operator- (const vector_type& v) const {
            return vector_type(x - v.x, y - v.y, z - v.z);
        }

        
        template <class T2>
        inline vector_type operator* (T2 s) const {
            return vector_type(x * T(s), y * T(s), z * T(s));
        }

        
        template <class T2>
        inline vector_type operator/ (T2 s) const {
            return vector_type(x / T(s), y / T(s), z / T(s));
        }

        
        inline vector_type operator- () const {
            return vector_type(-x, -y, -z);
        }

        
        index_t dimension() const {
            return dim;
        }

        
        T* data() {
            return &x;
        }

        
        const T* data() const {
            return &x;
        }

        
        inline T& operator[] (index_t i) {
            geo_debug_assert(i < dim);
            return data()[i];
        }

        
        inline const T& operator[] (index_t i) const {
            geo_debug_assert(i < dim);
            return data()[i];
        }

        
        void optimize() {
            Numeric::optimize_number_representation(x);
            Numeric::optimize_number_representation(y);
            Numeric::optimize_number_representation(z);
        }

        
        T x;
        
        T y;
        
        T z;
    };

    template <class T>
    inline T dot(
        const vecng<3, T>& v1, const vecng<3, T>& v2
    ) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    template <class T>
    inline vecng<3, T> cross(
        const vecng<3, T>& v1, const vecng<3, T>& v2
    ) {
        return vecng<3, T>(
            det2x2(v1.y, v2.y, v1.z, v2.z),
            det2x2(v1.z, v2.z, v1.x, v2.x),
            det2x2(v1.x, v2.x, v1.y, v2.y)
        );
    }

    template <class T2, class T>
    inline vecng<3, T> operator* (
        T2 s, const vecng<3, T>& v
    ) {
        return vecng<3, T>(T(s) * v.x, T(s) * v.y, T(s) * v.z);
    }

    

    template <class T>
    class vecng<4, T> {
    public:
        
        static constexpr index_t dim = 4;

        
        typedef vecng<dim, T> vector_type;

        
        typedef T value_type;

        
        vecng() :
            x(0),
            y(0),
            z(0),
            w(0) {
        }

        vecng(T x_in, T y_in, T z_in, T w_in) :
            x(x_in),
            y(y_in),
            z(z_in),
            w(w_in) {
        }

        
        template <class T2>
        explicit vecng(const vecng<dim, T2>& v) :
            x(v.x),
            y(v.y),
            z(v.z),
            w(v.w) {
        }

        
        template <class T2>
        explicit vecng(const T2* v) :
            x(v[0]),
            y(v[1]),
            z(v[2]),
            w(v[3]) {
        }

        
        vecng(const std::initializer_list<T>& Vi) {
            index_t i = 0;
            for(auto& it: Vi) {
                geo_debug_assert(i < dim);
                data()[i] = it;
                ++i;
            }
        }

        
        inline T length2() const {
            return x * x + y * y + z * z + w * w;
        }

        
        inline T length() const {
            return sqrt(x * x + y * y + z * z + w * w);
        }

        
        inline T distance2(const vector_type& v) const {
            T dx = v.x - x;
            T dy = v.y - y;
            T dz = v.z - z;
            T dw = v.w - w;
            return dx * dx + dy * dy + dz * dz + dw * dw;
        }

        
        inline T distance(const vector_type& v) const {
            return sqrt(distance2(v));
        }

        
        index_t dimension() const {
            return dim;
        }

        
        inline vector_type& operator+= (const vector_type& v) {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this;
        }

        
        inline vector_type& operator-= (const vector_type& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this;
        }

        
        template <class T2>
        inline vector_type& operator*= (T2 s) {
            x *= T(s);
            y *= T(s);
            z *= T(s);
            w *= T(s);
            return *this;
        }

        
        template <class T2>
        inline vector_type& operator/= (T2 s) {
            x /= T(s);
            y /= T(s);
            z /= T(s);
            w /= T(s);
            return *this;
        }

        
        inline vector_type operator+ (const vector_type& v) const {
            return vector_type(x + v.x, y + v.y, z + v.z, w + v.w);
        }

        
        inline vector_type operator- (const vector_type& v) const {
            return vector_type(x - v.x, y - v.y, z - v.z, w - v.w);
        }

        
        template <class T2>
        inline vector_type operator* (T2 s) const {
            return vector_type(x * T(s), y * T(s), z * T(s), w * T(s));
        }

        
        template <class T2>
        inline vector_type operator/ (T2 s) const {
            return vector_type(x / T(s), y / T(s), z / T(s), w / T(s));
        }

        
        inline vector_type operator- () const {
            return vector_type(-x, -y, -z, -w);
        }

        
        T* data() {
            return &x;
        }

        
        const T* data() const {
            return &x;
        }

        
        inline T& operator[] (index_t i) {
            geo_debug_assert(i < dim);
            return data()[i];
        }

        
        inline const T& operator[] (index_t i) const {
            geo_debug_assert(i < dim);
            return data()[i];
        }

        
        T x;
        
        T y;
        
        T z;
        
        T w;
    };

    template <class T>
    inline T dot(
        const vecng<4, T>& v1, const vecng<4, T>& v2
    ) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }

    template <class T2, class T>
    inline vecng<4, T> operator* (
        T2 s, const vecng<4, T>& v
    ) {
        return vecng<4, T>(T(s) * v.x, T(s) * v.y, T(s) * v.z, T(s) * v.w);
    }

    template <index_t DIM, class T>
    inline std::ostream& operator<< (
        std::ostream& out, const GEO::vecng<DIM, T>& v
    ) {
        const char* sep = "";
        for(index_t i = 0; i < DIM; i++) {
            out << sep << v[i];
            sep = " ";
        }
        return out;
    }

    template <index_t DIM, class T>
    inline std::istream& operator>> (
        std::istream& in, GEO::vecng<DIM, T>& v
    ) {
        char c;
        while(isspace(in.peek())) {
            in.get(c);
        }
        if(in.peek() == '[' || in.peek() == '{') {
            in.get(c);
        }
        while(isspace(in.peek())) {
            in.get(c);
        }
        for(index_t i = 0; i < DIM; i++) {
            in >> v[i];
            while(isspace(in.peek())) {
                in.get(c);
            }
            if(in.peek() == ',') {
                in.get(c);
            }
            while(isspace(in.peek())) {
                in.get(c);
            }
        }
        if(in.peek() == ']' || in.peek() == '}') {
            in.get(c);
        }
        return in;
    }

    

    namespace Numeric {

        template<class T>
        inline void optimize_number_representation(
            vecng<2,T>& v
        ) {
            v.optimize();
        }

        template<class T>
        inline void optimize_number_representation(
            vecng<3,T>& v
        ) {
            v.optimize();
        }

    }

    

}

#endif

/******* extracted from ../basic/vechg.h *******/

#ifndef GEOGRAM_BASIC_VECHG
#define GEOGRAM_BASIC_VECHG



namespace GEO {


    

    template <class T> class vec2Hg {
    public:
        
        typedef T value_type;

        vec2Hg() = default;

        vec2Hg(const T& x_in, const T& y_in, const T& w_in) :
            x(x_in),
            y(y_in),
            w(w_in) {
        }

        vec2Hg(double x_in, double y_in, double w_in) :
            x(x_in),
            y(y_in),
            w(w_in) {
        }

        vec2Hg(T&& x_in, T&& y_in, T&& w_in) :
            x(x_in),
            y(y_in),
            w(w_in) {
        }

        vec2Hg(const vec2Hg& rhs) = default;

        vec2Hg(vec2Hg&& rhs) = default;

        template <class T2> explicit vec2Hg(const vecng<2,T2>& rhs) :
            x(rhs.x),
            y(rhs.y),
            w(1.0) {
        }

        template <class T2> explicit vec2Hg(const vec2Hg<T2>& rhs) :
            x(rhs.x),
            y(rhs.y),
            w(rhs.w) {
        }

        vec2Hg& operator=(const vec2Hg& rhs) = default;
        vec2Hg& operator=(vec2Hg&& rhs) = default;

        T* data() {
            return &x;
        }

        const T* data() const {
            return &x;
        }

        T& operator[](coord_index_t i) {
            geo_debug_assert(i < 2);
            return data()[i];
        }

        const T& operator[](coord_index_t i) const {
            geo_debug_assert(i < 2);
            return data()[i];
        }

        void optimize() {
            Numeric::optimize_number_representation(x);
            Numeric::optimize_number_representation(y);
            Numeric::optimize_number_representation(w);
        }

        T x;
        T y;
        T w;
    };

    

    template <class T> inline vec2Hg<T> operator-(
        const vec2Hg<T>& p1, const vec2Hg<T>& p2
    ) {
        if(p2.w == p1.w) {
            return vec2Hg<T>(
                p1.x-p2.x,
                p1.y-p2.y,
                p1.w
            );
        }
        return vec2Hg<T>(
            det2x2(p1.x,p1.w,p2.x,p2.w),
            det2x2(p1.y,p1.w,p2.y,p2.w),
            p1.w*p2.w
        );
    }

    

    template <class T> class vec2HgLexicoCompare {
    public:
        bool operator()(const vec2Hg<T>& v1, const vec2Hg<T>& v2) const {
            Sign s = Numeric::ratio_compare(v2.x, v2.w, v1.x, v1.w);
            if(s == POSITIVE) {
                return true;
            }
            if(s == NEGATIVE) {
                return false;
            }
            s = Numeric::ratio_compare(v2.y, v2.w, v1.y, v1.w);
            return (s == POSITIVE);
        }
    };

    

    template <class T> class vec3Hg {
    public:
        
        typedef T value_type;

        vec3Hg() = default;

        vec3Hg(const T& x_in, const T& y_in, const T& z_in, const T& w_in) :
            x(x_in),
            y(y_in),
            z(z_in),
            w(w_in) {
        }

        vec3Hg(T&& x_in, T&& y_in, T&& z_in, T&& w_in) :
            x(x_in),
            y(y_in),
            z(z_in),
            w(w_in) {
        }

        vec3Hg(double x_in, double y_in, double z_in, double w_in) :
            x(x_in),
            y(y_in),
            z(z_in),
            w(w_in) {
        }

        vec3Hg(const vec3Hg& rhs) = default;

        vec3Hg(vec3Hg&& rhs) = default;

        template <class T2> explicit vec3Hg(const vecng<3,T2>& rhs) :
            x(rhs.x),
            y(rhs.y),
            z(rhs.z),
            w(1.0) {
        }

        template <class T2> explicit vec3Hg(const vec3Hg<T2>& rhs) :
            x(rhs.x),
            y(rhs.y),
            z(rhs.z),
            w(rhs.w) {
        }

        vec3Hg& operator=(const vec3Hg& rhs) = default;
        vec3Hg& operator=(vec3Hg&& rhs) = default;

        T* data() {
            return &x;
        }

        const T* data() const {
            return &x;
        }

        T& operator[](coord_index_t i) {
            geo_debug_assert(i < 3);
            return data()[i];
        }

        const T& operator[](coord_index_t i) const {
            geo_debug_assert(i < 3);
            return data()[i];
        }

        void optimize() {
            Numeric::optimize_number_representation(x);
            Numeric::optimize_number_representation(y);
            Numeric::optimize_number_representation(z);
            Numeric::optimize_number_representation(w);
        }

        T x;
        T y;
        T z;
        T w;
    };

    

    template <class T> inline vec3Hg<T> operator-(
        const vec3Hg<T>& p1, const vec3Hg<T>& p2
    ) {
        if(p1.w == p2.w) {
            return vec3Hg<T>(
                p1.x - p2.x,
                p1.y - p2.y,
                p1.z - p2.z,
                p1.w
            );
        }
        return vec3Hg<T>(
            det2x2(p1.x,p1.w,p2.x,p2.w),
            det2x2(p1.y,p1.w,p2.y,p2.w),
            det2x2(p1.z,p1.w,p2.z,p2.w),
            p1.w * p2.w
        );
    }

    

    template <class T> class vec3HgLexicoCompare {
    public:
        bool operator()(const vec3Hg<T>& v1, const vec3Hg<T>& v2) const {
            Sign s = Numeric::ratio_compare(v2.x, v2.w, v1.x, v1.w);
            if(s == POSITIVE) {
                return true;
            }
            if(s == NEGATIVE) {
                return false;
            }

            s = Numeric::ratio_compare(v2.y, v2.w, v1.y, v1.w);
            if(s == POSITIVE) {
                return true;
            }
            if(s == NEGATIVE) {
                return false;
            }

            s = Numeric::ratio_compare(v2.z, v2.w, v1.z, v1.w);
            return (s == POSITIVE);
        }
    };

    

    template <class T> inline vec2Hg<T> mix(
        const rationalg<T>& t,
        const vecng<2,double>& p1, const vecng<2,double>& p2
    ) {
        const T& st_d = t.denom();
        const T& t_n  = t.num();
        T s_n = st_d - t_n;
        return vec2Hg<T>(
            s_n * T(p1.x) + t_n * T(p2.x),
            s_n * T(p1.y) + t_n * T(p2.y),
            st_d
        );
    }

    template <class T> inline vec3Hg<T> mix(
        const rationalg<T>& t,
        const vecng<3,double>& p1, const vecng<3,double>& p2
    ) {
        const T& st_d = t.denom();
        const T& t_n  = t.num();
        T s_n = st_d - t_n;
        return vec3Hg<T>(
            s_n * T(p1.x) + t_n * T(p2.x),
            s_n * T(p1.y) + t_n * T(p2.y),
            s_n * T(p1.z) + t_n * T(p2.z),
            st_d
        );
    }


    template <class T> inline vec2Hg<T> mix(
        const rationalg<T>& t, const vec2Hg<T>& p1, const vec2Hg<T>& p2
    ) {
        if(p1.w == p2.w) {
            T sn = t.denom() - t.num();
            T tn = t.num();
            return vec2Hg<T>(
                sn * p1.x + tn * p2.x,
                sn * p1.y + tn * p2.y,
                t.denom() * p1.w
            );
        } else {
            T sn = p2.w*(t.denom() - t.num());
            T tn = p1.w*t.num();
            return vec2Hg<T>(
                sn * p1.x + tn * p2.x,
                sn * p1.y + tn * p2.y,
                t.denom() * p1.w * p2.w
            );
        }
    }

    template <class T> inline vec3Hg<T> mix(
        const rationalg<T>& t, const vec3Hg<T>& p1, const vec3Hg<T>& p2
    ) {
        if(p1.w == p2.w) {
            T sn = t.denom() - t.num();
            T tn = t.num();
            return vec3Hg<T>(
                sn * p1.x + tn * p2.x,
                sn * p1.y + tn * p2.y,
                sn * p1.z + tn * p2.z,
                t.denom() * p1.w
            );
        } else {
            T sn = p2.w*(t.denom() - t.num());
            T tn = p1.w*t.num();
            return vec3Hg<T>(
                sn * p1.x + tn * p2.x,
                sn * p1.y + tn * p2.y,
                sn * p1.z + tn * p2.z,
                t.denom() * p1.w * p2.w
            );
        }
    }


    

    namespace Numeric {

        template<class T>
        inline void optimize_number_representation(vec2Hg<T>& v) {
            v.optimize();
        }

        template<class T>
        inline void optimize_number_representation(vec3Hg<T>& v) {
            v.optimize();
        }

    }

    
}


#endif

/******* extracted from ../basic/matrix.h *******/

#ifndef GEOGRAM_BASIC_MATRIX
#define GEOGRAM_BASIC_MATRIX

#include <initializer_list>


namespace GEO {

    


    template <index_t DIM, class FT>
    class Matrix {
    public:
        
        typedef Matrix<DIM, FT> matrix_type;

        
        typedef FT value_type;

        
        static constexpr index_t dim = DIM;

        inline Matrix() {
            load_identity();
        }

        explicit Matrix(const FT* vals) {
            for(index_t i = 0; i < DIM; i++) {
                for(index_t j = 0; j < DIM; j++) {
                    coeff_[i][j] = *vals;
                    ++vals;
                }
            }
        }

        Matrix(const std::initializer_list< std::initializer_list<FT> >& Mi) {
            index_t i = 0;
            for(auto& it: Mi) {
                index_t j = 0;
                for(auto& jt: it) {
                    geo_debug_assert(i < DIM);
                    geo_debug_assert(j < DIM);
                    coeff_[i][j] = jt;
                    ++j;
                }
                ++i;
            }
        }


        inline index_t dimension() const {
            return DIM;
        }

        inline void load_zero() {
            for(index_t i = 0; i < DIM; i++) {
                for(index_t j = 0; j < DIM; j++) {
                    coeff_[i][j] = FT(0);
                }
            }
        }

        inline void load_identity() {
            for(index_t i = 0; i < DIM; i++) {
                for(index_t j = 0; j < DIM; j++) {
                    coeff_[i][j] = (i == j) ? FT(1) : FT(0);
                }
            }
        }

        inline bool is_identity() const {
            for(index_t i = 0; i < DIM; i++) {
                for(index_t j = 0; j < DIM; j++) {
                    FT rhs = ((i == j) ? FT(1) : FT(0));
                    if(coeff_[i][j] != rhs) {
                        return false;
                    }
                }
            }
            return true;
        }

        inline FT& operator() (index_t i, index_t j) {
            geo_debug_assert(i < DIM);
            geo_debug_assert(j < DIM);
            return coeff_[i][j];
        }

        inline const FT& operator() (index_t i, index_t j) const {
            geo_debug_assert(i < DIM);
            geo_debug_assert(j < DIM);
            return coeff_[i][j];
        }

        inline matrix_type& operator+= (const matrix_type& m) {
            for(index_t i = 0; i < DIM; i++) {
                for(index_t j = 0; j < DIM; j++) {
                    coeff_[i][j] += m.coeff_[i][j];
                }
            }
            return *this;
        }

        inline matrix_type& operator-= (const matrix_type& m) {
            for(index_t i = 0; i < DIM; i++) {
                for(index_t j = 0; j < DIM; j++) {
                    coeff_[i][j] -= m.coeff_[i][j];
                }
            }
            return *this;
        }

        inline matrix_type& operator*= (FT val) {
            for(index_t i = 0; i < DIM; i++) {
                for(index_t j = 0; j < DIM; j++) {
                    coeff_[i][j] *= val;
                }
            }
            return *this;
        }

        inline matrix_type& operator/= (FT val) {
            for(index_t i = 0; i < DIM; i++) {
                for(index_t j = 0; j < DIM; j++) {
                    coeff_[i][j] /= val;
                }
            }
            return *this;
        }

        inline matrix_type operator+ (const matrix_type& m) const {
            matrix_type result = *this;
            result += m;
            return result;
        }

        inline matrix_type operator- (const matrix_type& m) const {
            matrix_type result = *this;
            result -= m;
            return result;
        }

        inline matrix_type operator* (FT val) const {
            matrix_type result = *this;
            result *= val;
            return result;
        }

        inline matrix_type operator/ (FT val) const {
            matrix_type result = *this;
            result /= val;
            return result;
        }

        matrix_type operator* (const matrix_type& m) const {
            matrix_type result;
            for(index_t i = 0; i < DIM; i++) {
                for(index_t j = 0; j < DIM; j++) {
                    result.coeff_[i][j] = FT(0);
                    for(index_t k = 0; k < DIM; k++) {
                        result.coeff_[i][j] += coeff_[i][k] * m.coeff_[k][j];
                    }
                }
            }
            return result;
        }

        matrix_type inverse() const {
            matrix_type result;
            bool invertible = compute_inverse(result);
            geo_assert(invertible);
            return result;
        }


        bool compute_inverse(matrix_type& result) const {
            FT val=FT(0.0), val2=FT(0.0);
            matrix_type tmp = (*this);

            result.load_identity();

            for(index_t i = 0; i != DIM; i++) {
                val = tmp(i, i);                     /* find pivot */
                index_t ind = i;
                for(index_t j = i + 1; j != DIM; j++) {
                    if(fabs(tmp(j, i)) > fabs(val)) {
                        ind = j;
                        val = tmp(j, i);
                    }
                }

                if(ind != i) {
                    for(index_t j = 0; j != DIM; j++) {
                        val2 = result(i, j);
                        result(i, j) = result(ind, j);
                        result(ind, j) = val2;           /* swap columns */
                        val2 = tmp(i, j);
                        tmp(i, j) = tmp(ind, j);
                        tmp(ind, j) = val2;
                    }
                }

                if(val == 0.0) {
                    return false;
                }

                for(index_t j = 0; j != DIM; j++) {
                    tmp(i, j) /= val;
                    result(i, j) /= val;
                }

                for(index_t j = 0; j != DIM; j++) {
                    if(j == i) {
                        continue;                       /* eliminate column */
                    }
                    val = tmp(j, i);
                    for(index_t k = 0; k != DIM; k++) {
                        tmp(j, k) -= tmp(i, k) * val;
                        result(j, k) -= result(i, k) * val;
                    }
                }
            }

            return true;
        }

        matrix_type transpose() const {
            matrix_type result;
            for(index_t i = 0; i < DIM; i++) {
                for(index_t j = 0; j < DIM; j++) {
                    result(i, j) = (* this)(j, i);
                }
            }
            return result;
        }

        

        inline const FT* data() const {
            return &(coeff_[0][0]);
        }

        

        inline FT* data() {
            return &(coeff_[0][0]);
        }

        void get_lower_triangle(FT* store) const {
            for(index_t i = 0; i < DIM; i++) {
                for(index_t j = 0; j <= i; j++) {
                    *store++ = coeff_[i][j];
                }
            }
        }

    private:
        FT coeff_[DIM][DIM];
    };

    

    template <index_t DIM, class FT>
    inline std::ostream& operator<< (
        std::ostream& output, const Matrix<DIM, FT>& m
    ) {
        const char* sep = "";
        for(index_t i = 0; i < DIM; i++) {
            for(index_t j = 0; j < DIM; j++) {
                output << sep << m(i, j);
                sep = " ";
            }
        }
        return output;
    }

    template <index_t DIM, class FT>
    inline std::istream& operator>> (
        std::istream& input, Matrix<DIM, FT>& m
    ) {
        for(index_t i = 0; i < DIM; i++) {
            for(index_t j = 0; j < DIM; j++) {
                input >> m(i, j);
            }
        }
        return input;
    }

    

    template <index_t DIM, class FT> inline
    void mult(const Matrix<DIM, FT>& M, const FT* x, FT* y) {
        for(index_t i = 0; i < DIM; i++) {
            y[i] = 0;
            for(index_t j = 0; j < DIM; j++) {
                y[i] += M(i, j) * x[j];
            }
        }
    }

    

    template <index_t DIM, class FT> inline
    vecng<DIM,FT> operator*(
        const Matrix<DIM, FT>& M, const vecng<DIM,FT>& x
    ) {
        vecng<DIM,FT> y;
        for(index_t i = 0; i < DIM; i++) {
            y[i] = 0;
            for(index_t j = 0; j < DIM; j++) {
                y[i] += M(i, j) * x[j];
            }
        }
        return y;
    }

    template <index_t DIM, class FT> inline
    vecng<DIM,FT> mult(
        const Matrix<DIM, FT>& M, const vecng<DIM,FT>& x
    ) {
        vecng<DIM,FT> y;
        for(index_t i = 0; i < DIM; i++) {
            y[i] = 0;
            for(index_t j = 0; j < DIM; j++) {
                y[i] += M(i, j) * x[j];
            }
        }
        return y;
    }

    

}

#endif

/******* extracted from ../basic/geometry.h *******/

#ifndef GEOGRAM_BASIC_GEOMETRY
#define GEOGRAM_BASIC_GEOMETRY



namespace GEO {

    

    typedef vecng<2, Numeric::float64> vec2;

    typedef vecng<3, Numeric::float64> vec3;

    typedef vecng<4, Numeric::float64> vec4;

    typedef vecng<2, Numeric::float32> vec2f;

    typedef vecng<3, Numeric::float32> vec3f;

    typedef vecng<4, Numeric::float32> vec4f;


    typedef vecng<2, Numeric::int32> vec2i;

    typedef vecng<3, Numeric::int32> vec3i;

    typedef vecng<4, Numeric::int32> vec4i;

    typedef vecng<2, Numeric::uint32> vec2u;

    typedef vecng<3, Numeric::uint32> vec3u;

    typedef vecng<4, Numeric::uint32> vec4u;

    typedef Matrix<2, Numeric::float64> mat2;

    typedef Matrix<3, Numeric::float64> mat3;

    typedef Matrix<4, Numeric::float64> mat4;

    

    inline double det(const mat2& M) {
        return det2x2(
            M(0,0), M(0,1),
            M(1,0), M(1,1)
        );
    }

    inline double det(const mat3& M) {
        return det3x3(
            M(0,0), M(0,1), M(0,2),
            M(1,0), M(1,1), M(1,2),
            M(2,0), M(2,1), M(2,2)
        );
    }

    inline double det(const mat4& M) {
        return det4x4(
            M(0,0), M(0,1), M(0,2), M(0,3),
            M(1,0), M(1,1), M(1,2), M(1,3),
            M(2,0), M(2,1), M(2,2), M(2,3),
            M(3,0), M(3,1), M(3,2), M(3,3)
        );
    }

    

    namespace Geom {

        inline vec3 barycenter(const vec3& p1, const vec3& p2) {
            return vec3(
                0.5 * (p1.x + p2.x),
                0.5 * (p1.y + p2.y),
                0.5 * (p1.z + p2.z)
            );
        }

        inline vec2 barycenter(const vec2& p1, const vec2& p2) {
            return vec2(
                0.5 * (p1.x + p2.x),
                0.5 * (p1.y + p2.y)
            );
        }

        inline vec3 barycenter(
            const vec3& p1, const vec3& p2, const vec3& p3
        ) {
            return vec3(
                (p1.x + p2.x + p3.x) / 3.0,
                (p1.y + p2.y + p3.y) / 3.0,
                (p1.z + p2.z + p3.z) / 3.0
            );
        }

        inline vec2 barycenter(
            const vec2& p1, const vec2& p2, const vec2& p3
        ) {
            return vec2(
                (p1.x + p2.x + p3.x) / 3.0,
                (p1.y + p2.y + p3.y) / 3.0
            );
        }

        inline double cos_angle(const vec3& a, const vec3& b) {
            double lab = ::sqrt(length2(a)*length2(b));
            double result = (lab > 1e-50) ? (dot(a, b) / lab) : 1.0;
            // Numerical precision problem may occur, and generate
            // normalized dot products that are outside the valid
            // range of acos.
            geo_clamp(result, -1.0, 1.0);
            return result;
        }

        inline double angle(const vec3& a, const vec3& b) {
            return ::acos(cos_angle(a, b));
        }

        inline double cos_angle(const vec2& a, const vec2& b) {
            double lab = ::sqrt(length2(a)*length2(b));
            double result = (lab > 1e-20) ? (dot(a, b) / lab) : 1.0;
            // Numerical precision problem may occur, and generate
            // normalized dot products that are outside the valid
            // range of acos.
            geo_clamp(result, -1.0, 1.0);
            return result;
        }

        inline double det(const vec2& a, const vec2& b) {
            return a.x * b.y - a.y * b.x;
        }

        inline double angle(const vec2& a, const vec2& b) {
            return det(a, b) > 0 ?
                ::acos(cos_angle(a, b)) :
                -::acos(cos_angle(a, b));
        }

        inline vec3 triangle_normal(
            const vec3& p1, const vec3& p2, const vec3& p3
        ) {
            return cross(p2 - p1, p3 - p1);
        }

        inline double triangle_area_3d(
            const double* p1, const double* p2, const double* p3
        ) {
            double Ux = p2[0] - p1[0];
            double Uy = p2[1] - p1[1];
            double Uz = p2[2] - p1[2];

            double Vx = p3[0] - p1[0];
            double Vy = p3[1] - p1[1];
            double Vz = p3[2] - p1[2];

            double Nx = Uy*Vz - Uz*Vy;
            double Ny = Uz*Vx - Ux*Vz;
            double Nz = Ux*Vy - Uy*Vx;
            return 0.5 * ::sqrt(Nx*Nx+Ny*Ny+Nz*Nz);
        }

        inline double triangle_area(
            const vec3& p1, const vec3& p2, const vec3& p3
        ) {
            return triangle_area_3d(p1.data(), p2.data(), p3.data());
        }

        inline double triangle_signed_area_2d(
            const double* p1, const double* p2, const double* p3
        ) {
            double a = p2[0]-p1[0];
            double b = p3[0]-p1[0];
            double c = p2[1]-p1[1];
            double d = p3[1]-p1[1];
            return 0.5*(a*d-b*c);
        }

        inline double triangle_signed_area(
            const vec2& p1, const vec2& p2, const vec2& p3
        ) {
            return 0.5 * det(p2 - p1, p3 - p1);
        }

        inline double triangle_area(
            const vec2& p1, const vec2& p2, const vec2& p3
        ) {
            return ::fabs(triangle_signed_area(p1, p2, p3));
        }

        inline double triangle_area_2d(
            const double* p1, const double* p2, const double* p3
        ) {
            return ::fabs(triangle_signed_area_2d(p1,p2,p3));
        }

        vec2 GEOGRAM_API triangle_circumcenter(
            const vec2& p1, const vec2& p2, const vec2& p3
        );

        inline bool has_nan(const vec3& v) {
            return
                Numeric::is_nan(v.x) ||
                Numeric::is_nan(v.y) ||
                Numeric::is_nan(v.z);
        }

        inline bool has_nan(const vec2& v) {
            return
                Numeric::is_nan(v.x) ||
                Numeric::is_nan(v.y);
        }

        vec3 GEOGRAM_API perpendicular(const vec3& V);

        inline double tetra_signed_volume(
            const vec3& p1, const vec3& p2,
            const vec3& p3, const vec3& p4
        ) {
            return dot(p2 - p1, cross(p3 - p1, p4 - p1)) / 6.0;
        }

        inline double tetra_signed_volume(
            const double* p1, const double* p2,
            const double* p3, const double* p4
        ) {
            return tetra_signed_volume(
                *reinterpret_cast<const vec3*>(p1),
                *reinterpret_cast<const vec3*>(p2),
                *reinterpret_cast<const vec3*>(p3),
                *reinterpret_cast<const vec3*>(p4)
            );
        }

        inline double tetra_volume(
            const vec3& p1, const vec3& p2,
            const vec3& p3, const vec3& p4
        ) {
            return ::fabs(tetra_signed_volume(p1, p2, p3, p4));
        }

        vec3 GEOGRAM_API tetra_circum_center(
            const vec3& p1, const vec3& p2,
            const vec3& p3, const vec3& p4
        );

        inline void triangle_centroid(
            const vec3& p, const vec3& q, const vec3& r,
            double a, double b, double c,
            vec3& Vg, double& V
        ) {
            double abc = a + b + c;
            double area = Geom::triangle_area(p, q, r);
            V = area / 3.0 * abc;
            double wp = a + abc;
            double wq = b + abc;
            double wr = c + abc;
            double s = area / 12.0;
            Vg.x = s * (wp * p.x + wq * q.x + wr * r.x);
            Vg.y = s * (wp * p.y + wq * q.y + wr * r.y);
            Vg.z = s * (wp * p.z + wq * q.z + wr * r.z);
        }

        inline double triangle_mass(
            const vec3& p, const vec3& q, const vec3& r,
            double a, double b, double c
        ) {
            return Geom::triangle_area(p, q, r) / 3.0 * (
                sqrt(::fabs(a)) + sqrt(::fabs(b)) + sqrt(::fabs(c))
            );
        }

        inline vec3 random_point_in_triangle(
            const vec3& p1,
            const vec3& p2,
            const vec3& p3
        ) {
            double s = Numeric::random_float64();
            double t = Numeric::random_float64();
            if(s + t > 1) {
                s = 1.0 - s;
                t = 1.0 - t;
            }
            double u = 1.0 - s - t;
            return vec3(
                u * p1.x + s * p2.x + t * p3.x,
                u * p1.y + s * p2.y + t * p3.y,
                u * p1.z + s * p2.z + t * p3.z
            );
        }
    }

    struct Plane {

        Plane(const vec3& p1, const vec3& p2, const vec3& p3) {
            vec3 n = cross(p2 - p1, p3 - p1);
            a = n.x;
            b = n.y;
            c = n.z;
            d = -(a * p1.x + b * p1.y + c * p1.z);
        }

        Plane(const vec3& p, const vec3& n) {
            a = n.x;
            b = n.y;
            c = n.z;
            d = -(a * p.x + b * p.y + c * p.z);
        }

        Plane(
            double a_in, double b_in, double c_in, double d_in
        ) :
            a(a_in),
            b(b_in),
            c(c_in),
            d(d_in) {
        }

        Plane() {
        }

        vec3 normal() const {
            return vec3(a, b, c);
        }

        double a, b, c, d;
    };

    

    class Box {
    public:
        double xyz_min[3];
        double xyz_max[3];

        bool contains(const vec3& b) const {
            for(coord_index_t c = 0; c < 3; ++c) {
                if(b[c] < xyz_min[c]) {
                    return false;
                }
                if(b[c] > xyz_max[c]) {
                    return false;
                }
            }
            return true;
        }
    };

    typedef Box Box3d;

    inline bool bboxes_overlap(const Box& B1, const Box& B2) {
        for(coord_index_t c = 0; c < 3; ++c) {
            if(B1.xyz_max[c] < B2.xyz_min[c]) {
                return false;
            }
            if(B1.xyz_min[c] > B2.xyz_max[c]) {
                return false;
            }
        }
        return true;
    }

    inline void bbox_union(Box& target, const Box& B1, const Box& B2) {
        for(coord_index_t c = 0; c < 3; ++c) {
            target.xyz_min[c] = std::min(B1.xyz_min[c], B2.xyz_min[c]);
            target.xyz_max[c] = std::max(B1.xyz_max[c], B2.xyz_max[c]);
        }
    }

    

    class Box2d {
    public:
        double xy_min[2];
        double xy_max[2];

        bool contains(const vec2& b) const {
            for(coord_index_t c = 0; c < 2; ++c) {
                if(b[c] < xy_min[c]) {
                    return false;
                }
                if(b[c] > xy_max[c]) {
                    return false;
                }
            }
            return true;
        }
    };


    inline bool bboxes_overlap(const Box2d& B1, const Box2d& B2) {
        for(coord_index_t c = 0; c < 2; ++c) {
            if(B1.xy_max[c] < B2.xy_min[c]) {
                return false;
            }
            if(B1.xy_min[c] > B2.xy_max[c]) {
                return false;
            }
        }
        return true;
    }

    inline void bbox_union(Box2d& target, const Box2d& B1, const Box2d& B2) {
        for(coord_index_t c = 0; c < 2; ++c) {
            target.xy_min[c] = std::min(B1.xy_min[c], B2.xy_min[c]);
            target.xy_max[c] = std::max(B1.xy_max[c], B2.xy_max[c]);
        }
    }

    

    template <class FT> vecng<3,FT> transform_vector(
        const vecng<3,FT>& v,
        const Matrix<4,FT>& m
    ){
        index_t i,j ;
        FT result[4] ;

        for(i=0; i<4; i++) {
            result[i] = 0 ;
        }
        for(i=0; i<4; i++) {
            for(j=0; j<3; j++) {
                result[i] += v[j] * m(j,i) ;
            }
        }

        return vecng<3,FT>(
            result[0], result[1], result[2]
        ) ;
    }

    template <class FT> vecng<3,FT> transform_point(
        const vecng<3,FT>& v,
        const Matrix<4,FT>& m
    ){
        index_t i,j ;
        FT result[4] ;

        for(i=0; i<4; i++) {
            result[i] = 0 ;
        }
        for(i=0; i<4; i++) {
            for(j=0; j<3; j++) {
                result[i] += v[j] * m(j,i) ;
            }
            result[i] += m(3,i);
        }

        return vecng<3,FT>(
            result[0] / result[3],
            result[1] / result[3],
            result[2] / result[3]
        ) ;
    }


    template <class FT> vecng<3,FT> transform_point(
        const Matrix<4,FT>& m,
        const vecng<3,FT>& v
    ){
        index_t i,j ;
        FT result[4] ;

        for(i=0; i<4; i++) {
            result[i] = 0 ;
        }
        for(i=0; i<4; i++) {
            for(j=0; j<3; j++) {
                result[i] += v[j] * m(i,j) ;
            }
            result[i] += m(i,3);
        }

        return vecng<3,FT>(
            result[0] / result[3],
            result[1] / result[3],
            result[2] / result[3]
        ) ;
    }

    template <class FT> vecng<4,FT> transform_vector(
        const vecng<4,FT>& v,
        const Matrix<4,FT>& m
    ) {
        index_t i,j ;
        FT res[4] = {FT(0), FT(0), FT(0), FT(0)};

        for(i=0; i<4; i++) {
            for(j=0; j<4; j++) {
                res[i] += v[j] * m(j,i) ;
            }
        }

        return vecng<4,FT>(res[0], res[1], res[2], res[3]) ;
    }

    

    inline mat4 create_translation_matrix(const vec3& T) {
        mat4 result;
        result.load_identity();
        result(3,0) = T.x;
        result(3,1) = T.y;
        result(3,2) = T.z;
        return result;
    }

    inline mat4 create_scaling_matrix(double s) {
        mat4 result;
        result.load_identity();
        result(0,0) = s;
        result(1,1) = s;
        result(2,2) = s;
        return result;
    }

    

    struct Ray {
        Ray(vec3 O, vec3 D) : origin(O), direction(D) {
        }
        Ray() {
        }
        vec3 origin;
        vec3 direction;
    };

    

}

#endif

/******* extracted from ../numerics/PCK.h *******/

#ifndef GEOGRAM_NUMERICS_PCK
#define GEOGRAM_NUMERICS_PCK

#include <functional>
#include <algorithm>
#include <atomic>


// Uncomment to get full reporting on predicate statistics
// (but has a non-negligible impact on performance)
// For instance, Early Universe Reconstruction with 2M points:
// with PCK_STATS: 6'36   without PCK_STATS: 3'38

//#define PCK_STATS

namespace GEO {

    namespace PCK {


#ifdef PCK_STATS
        class GEOGRAM_API PredicateStats {
        public:
        PredicateStats(const char* name);
        void log_invoke() {
            ++invoke_count_;
        }
        void log_exact() {
            ++exact_count_;
        }
        void log_SOS() {
            ++SOS_count_;
        }
        void show_stats();
        static void show_all_stats();
        private:
        static PredicateStats* first_;
        PredicateStats* next_;
        const char* name_;
        std::atomic<Numeric::int64> invoke_count_;
        std::atomic<Numeric::int64> exact_count_;
        std::atomic<Numeric::int64> SOS_count_;
        };
#else
        class PredicateStats {
        public:
            PredicateStats(const char* name) {
                geo_argused(name);
            }
            void log_invoke() {
            }
            void log_exact() {
            }
            void log_SOS() {
            }
            static void show_all_stats() {
                Logger::out("Stats") << "Compiled without PCK_STAT (no stats)"
                                     << std::endl;
            }
        };
#endif


#define SOS_result(x) [&]()->Sign { return Sign(x); }

        template <
            class POINT, class COMPARE,
            class FUNC1, class FUNC2, class FUNC3, class FUNC4
            > inline Sign SOS(
                COMPARE compare,
                const POINT& p1, FUNC1 sos_p1,
                const POINT& p2, FUNC2 sos_p2,
                const POINT& p3, FUNC3 sos_p3,
                const POINT& p4, FUNC4 sos_p4
            ) {
            static constexpr int N = 4;
            Sign result = ZERO;
            const POINT* p[N] = {&p1, &p2, &p3, &p4};
            std::sort(
                p, p+N,
                [compare](const POINT* A, const POINT* B)->bool{
                    return compare(*A,*B);
                }
            );
            for(int i=0; i<N; ++i) {
                if(p[i] == &p1) {
                    result = sos_p1();
                    if(result != ZERO) {
                        return result;
                    }
                }
                if(p[i] == &p2) {
                    result = sos_p2();
                    if(result != ZERO) {
                        return result;
                    }
                }
                if(p[i] == &p3) {
                    result = sos_p3();
                    if(result != ZERO) {
                        return result;
                    }
                }
                if(p[i] == &p4) {
                    result = sos_p4();
                    if(result != ZERO) {
                        return result;
                    }
                }
            }
            geo_assert_not_reached;
        }

    }
}

#endif

/******* extracted from ../numerics/predicates.h *******/

#ifndef GEOGRAM_NUMERICS_PREDICATES
#define GEOGRAM_NUMERICS_PREDICATES




namespace GEO {

    namespace PCK {

        enum SOSMode { SOS_ADDRESS, SOS_LEXICO };

        void GEOGRAM_API set_SOS_mode(SOSMode m);

        SOSMode GEOGRAM_API get_SOS_mode();

        Sign GEOGRAM_API side1_SOS(
            const double* p0, const double* p1,
            const double* q0,
            coord_index_t DIM
        );

        Sign GEOGRAM_API side2_SOS(
            const double* p0, const double* p1, const double* p2,
            const double* q0, const double* q1,
            coord_index_t DIM
        );

        Sign GEOGRAM_API side3_SOS(
            const double* p0, const double* p1,
            const double* p2, const double* p3,
            const double* q0, const double* q1, const double* q2,
            coord_index_t DIM
        );

        Sign GEOGRAM_API side3_3dlifted_SOS(
            const double* p0, const double* p1,
            const double* p2, const double* p3,
            double h0, double h1, double h2, double h3,
            const double* q0, const double* q1, const double* q2,
            bool SOS=true
        );

        Sign GEOGRAM_API side4_SOS(
            const double* p0,
            const double* p1, const double* p2,
            const double* p3, const double* p4,
            const double* q0, const double* q1,
            const double* q2, const double* q3,
            coord_index_t DIM
        );


        Sign GEOGRAM_API side4_3d(
            const double* p0,
            const double* p1, const double* p2,
            const double* p3, const double* p4
        );

        Sign GEOGRAM_API side4_3d_SOS(
            const double* p0, const double* p1,
            const double* p2, const double* p3, const double* p4
        );

        Sign GEOGRAM_API in_sphere_3d_SOS(
            const double* p0, const double* p1,
            const double* p2, const double* p3,
            const double* p4
        );


        Sign GEOGRAM_API in_circle_2d_SOS(
            const double* p0, const double* p1, const double* p2,
            const double* p3
        );


        Sign GEOGRAM_API in_circle_3d_SOS(
            const double* p0, const double* p1, const double* p2,
            const double* p3
        );


        Sign GEOGRAM_API in_circle_3dlifted_SOS(
            const double* p0, const double* p1, const double* p2,
            const double* p3,
            double h0, double h1, double h2, double h3,
            bool SOS=true
        );

        Sign GEOGRAM_API orient_2d(
            const double* p0, const double* p1, const double* p2
        );


#ifndef GEOGRAM_PSM
        inline Sign orient_2d(
            const vec2& p0, const vec2& p1, const vec2& p2
        ) {
            return orient_2d(p0.data(),p1.data(),p2.data());
        }
#endif

        Sign GEOGRAM_API orient_2dlifted_SOS(
            const double* p0, const double* p1,
            const double* p2, const double* p3,
            double h0, double h1, double h2, double h3
        );


        Sign GEOGRAM_API orient_3d(
            const double* p0, const double* p1,
            const double* p2, const double* p3
        );


#ifndef GEOGRAM_PSM
        inline Sign orient_3d(
            const vec3& p0, const vec3& p1,
            const vec3& p2, const vec3& p3
        ) {
            return orient_3d(p0.data(),p1.data(),p2.data(),p3.data());
        }
#endif

        Sign GEOGRAM_API orient_3dlifted(
            const double* p0, const double* p1,
            const double* p2, const double* p3, const double* p4,
            double h0, double h1, double h2, double h3, double h4
        );


        Sign GEOGRAM_API orient_3dlifted_SOS(
            const double* p0, const double* p1,
            const double* p2, const double* p3, const double* p4,
            double h0, double h1, double h2, double h3, double h4
        );


        Sign GEOGRAM_API det_3d(
            const double* p0, const double* p1, const double* p2
        );

#ifndef GEOGRAM_PSM
        inline Sign det_3d(
            const vec3& p0, const vec3& p1, const vec3& p2
        ) {
	    return det_3d(p0.data(), p1.data(), p2.data());
	}
#endif

        Sign GEOGRAM_API det_4d(
            const double* p0, const double* p1,
            const double* p2, const double* p3
        );

#ifndef GEOGRAM_PSM
        inline Sign det_4d(
            const vec4& p0, const vec4& p1,
            const vec4& p2, const vec4& p3
        ) {
	    return det_4d(p0.data(), p1.data(), p2.data(), p3.data());
	}
#endif

        Sign GEOGRAM_API det_compare_4d(
            const double* p0, const double* p1,
            const double* p2, const double* p3,
            const double* p4
        );

        bool GEOGRAM_API aligned_3d(
            const double* p0, const double* p1, const double* p2
        );

        Sign GEOGRAM_API dot_3d(
            const double* p0, const double* p1, const double* p2
        );

#ifndef GEOGRAM_PSM

        inline bool aligned_3d(
            const vec3& p0, const vec3& p1, const vec3& p2
        ) {
            return aligned_3d(p0.data(), p1.data(), p2.data());
        }

        inline Sign dot_3d(
            const vec3& p0, const vec3& p1, const vec3& p2
        ) {
            return dot_3d(p0.data(), p1.data(), p2.data());
        }
#endif

        Sign GEOGRAM_API dot_compare_3d(
            const double* v0, const double* v1, const double* v2
        );

        bool points_are_identical_2d(
            const double* p1,
            const double* p2
        );

        bool GEOGRAM_API points_are_identical_3d(
            const double* p1,
            const double* p2
        );

        bool GEOGRAM_API points_are_colinear_3d(
            const double* p1,
            const double* p2,
            const double* p3
        );

        inline Sign orient_3d_inexact(
            const double* p0, const double* p1,
            const double* p2, const double* p3
        ) {
            double a11 = p1[0] - p0[0] ;
            double a12 = p1[1] - p0[1] ;
            double a13 = p1[2] - p0[2] ;

            double a21 = p2[0] - p0[0] ;
            double a22 = p2[1] - p0[1] ;
            double a23 = p2[2] - p0[2] ;

            double a31 = p3[0] - p0[0] ;
            double a32 = p3[1] - p0[1] ;
            double a33 = p3[2] - p0[2] ;

            double Delta = det3x3(
                a11,a12,a13,
                a21,a22,a23,
                a31,a32,a33
            );

            return geo_sgn(Delta);
        }

        void GEOGRAM_API show_stats();

        void GEOGRAM_API initialize();

        void GEOGRAM_API terminate();
    }
}

#endif

/******* extracted from ../numerics/multi_precision.h *******/

#ifndef GEOGRAM_NUMERICS_MULTI_PRECISION
#define GEOGRAM_NUMERICS_MULTI_PRECISION

#include <iostream>
#include <sstream>
#include <new>
#include <math.h>


namespace GEO {

    extern double expansion_splitter_;
    extern double expansion_epsilon_;

    inline void two_sum(double a, double b, double& x, double& y) {
        x = a + b;
        double bvirt = x - a;
        double avirt = x - bvirt;
        double bround = b - bvirt;
        double around = a - avirt;
        y = around + bround;
    }

    inline void two_diff(double a, double b, double& x, double& y) {
        x = a - b;
        double bvirt = a - x;
        double avirt = x + bvirt;
        double bround = bvirt - b;
        double around = a - avirt;
        y = around + bround;
    }

    inline void split(double a, double& ahi, double& alo) {
        double c = expansion_splitter_ * a;
        double abig = c - a;
        ahi = c - abig;
        alo = a - ahi;
    }

    inline void two_product(double a, double b, double& x, double& y) {
#ifdef FP_FAST_FMA
        // If the target processor supports the FMA (Fused Multiply Add)
        // instruction, then the product of two doubles into a length-2
        // expansion can be implemented as follows. Thanks to Marc Glisse
        // for the information.
        // Note: under gcc, automatic generations of fma() for a*b+c needs
        // to be deactivated, using -ffp-contract=off, else it may break
        // other functions such as fast_expansion_sum_zeroelim().
        x = a*b;
        y = fma(a,b,-x);
#else
        x = a * b;
        double ahi, alo;
        split(a, ahi, alo);
        double bhi, blo;
        split(b, bhi, blo);
        double err1 = x - (ahi * bhi);
        double err2 = err1 - (alo * bhi);
        double err3 = err2 - (ahi * blo);
        y = (alo * blo) - err3;
#endif
    }

    inline void square(double a, double& x, double& y) {
#ifdef FP_FAST_FMA
        // If the target processor supports the FMA (Fused Multiply Add)
        // instruction, then the product of two doubles into a length-2
        // expansion can be implemented as follows. Thanks to Marc Glisse
        // for the information.
        // Note: under gcc, automatic generations of fma() for a*b+c needs
        // to be deactivated, using -ffp-contract=off, else it may break
        // other functions such as fast_expansion_sum_zeroelim().
        x = a*a;
        y = fma(a,a,-x);
#else
        x = a * a;
        double ahi, alo;
        split(a, ahi, alo);
        double err1 = x - (ahi * ahi);
        double err3 = err1 - ((ahi + ahi) * alo);
        y = (alo * alo) - err3;
#endif
    }

    

    class GEOGRAM_API expansion {
    public:
    index_t length() const {
        return length_;
    }

    index_t capacity() const {
        return capacity_;
    }

    void set_length(index_t new_length) {
        geo_debug_assert(new_length <= capacity());
        length_ = new_length;
    }

    const double& operator[] (index_t i) const {
        // Note: we allocate capacity+1 storage
        // systematically, since basic functions
        // may access one additional value (without
        // using it)
        geo_debug_assert(i <= capacity_);
        return x_[i];
    }

    double& operator[] (index_t i) {
        // Note: we allocate capacity+1 storage
        // systematically, since basic functions
        // may access one additional value (without
        // using it)
        geo_debug_assert(i <= capacity_);
        return x_[i];
    }

    double* data() {
        return x_;
    }

    const double* data() const {
        return x_;
    }

    static size_t bytes(index_t capa) {
        // --> 2*sizeof(double) because x_ is declared of size [2]
        // to avoid compiler's warning.
        // --> capa+1 to have an additional 'sentry' at the end
        // because fast_expansion_sum_zeroelim() may access
        // an entry past the end (without using it).
        return
            sizeof(expansion) - 2 * sizeof(double) +
            (capa + 1) * sizeof(double);
    }

    static size_t bytes_on_stack(index_t capa) {
#ifndef GEO_HAS_BIG_STACK
        // Note: standard predicates need at least 512, hence the min.
        // index_t(MAX_CAPACITY_ON_STACK) is necessary, else with
        // MAX_CAPACITY_ON_STACK alone the compiler tries to generate a
        // reference to NOT_IN_LIST resulting in a link error.
        // (weird, even with constexpr, I do not understand...)
        // Probably when the function excepts a *reference*
        geo_debug_assert(
            capa <= std::max(index_t(MAX_CAPACITY_ON_STACK),index_t(512))
        );
#endif
        return bytes(capa);
    }

    expansion(index_t capa) :
    length_(0),
    capacity_(capa) {
    }

#ifdef CPPCHECK
    // cppcheck does not understand that the result
    // of alloca() is passed to the placement syntax
    // of operator new.
    expansion& new_expansion_on_stack(index_t capa);
#else
#define new_expansion_on_stack(capa)                                    \
    (new (alloca(expansion::bytes_on_stack(capa)))expansion(capa))
#endif

    static expansion* new_expansion_on_heap(index_t capa);

    static void delete_expansion_on_heap(expansion* e);

    // ========================== Initialization from doubles

    expansion& assign(double a) {
        set_length(1);
        x_[0] = a;
        return *this;
    }

    expansion& assign(const expansion& rhs) {
        geo_debug_assert(capacity() >= rhs.length());
        set_length(rhs.length());
        for(index_t i=0; i<rhs.length(); ++i) {
            x_[i] = rhs.x_[i];
        }
        return *this;
    }

    expansion& assign_abs(const expansion& rhs) {
        assign(rhs);
        if(sign() == NEGATIVE) {
            negate();
        }
        return *this;
    }

    static index_t sum_capacity(double a, double b) {
        geo_argused(a);
        geo_argused(b);
        return 2;
    }

    expansion& assign_sum(double a, double b) {
        set_length(2);
        two_sum(a, b, x_[1], x_[0]);
        return *this;
    }

    static index_t diff_capacity(double a, double b) {
        geo_argused(a);
        geo_argused(b);
        return 2;
    }

    expansion& assign_diff(double a, double b) {
        set_length(2);
        two_diff(a, b, x_[1], x_[0]);
        return *this;
    }

    static index_t product_capacity(double a, double b) {
        geo_argused(a);
        geo_argused(b);
        return 2;
    }

    expansion& assign_product(double a, double b) {
        set_length(2);
        two_product(a, b, x_[1], x_[0]);
        return *this;
    }

    static index_t square_capacity(double a) {
        geo_argused(a);
        return 2;
    }

    expansion& assign_square(double a) {
        set_length(2);
        square(a, x_[1], x_[0]);
        return *this;
    }

    // ====== Initialization from expansion and double

    static index_t sum_capacity(const expansion& a, double b) {
        geo_argused(b);
        return a.length() + 1;
    }

    expansion& assign_sum(const expansion& a, double b);

    static index_t diff_capacity(const expansion& a, double b) {
        geo_argused(b);
        return a.length() + 1;
    }

    expansion& assign_diff(const expansion& a, double b);

    static index_t product_capacity(const expansion& a, double b) {
        geo_argused(b);
        // TODO: implement special case where the double argument
        // is a power of two.
        return a.length() * 2;
    }

    expansion& assign_product(const expansion& a, double b);

    // ========================== Initialization from expansions

    static index_t sum_capacity(const expansion& a, const expansion& b) {
        return a.length() + b.length();
    }

    expansion& assign_sum(const expansion& a, const expansion& b);

    static index_t sum_capacity(
        const expansion& a, const expansion& b, const expansion& c
    ) {
        return a.length() + b.length() + c.length();
    }

    expansion& assign_sum(
        const expansion& a, const expansion& b, const expansion& c
    );

    static index_t sum_capacity(
        const expansion& a, const expansion& b,
        const expansion& c, const expansion& d
    ) {
        return a.length() + b.length() + c.length() + d.length();
    }

    expansion& assign_sum(
        const expansion& a, const expansion& b,
        const expansion& c, const expansion& d
    );

    static index_t diff_capacity(const expansion& a, const expansion& b) {
        return a.length() + b.length();
    }

    expansion& assign_diff(const expansion& a, const expansion& b);

    static index_t product_capacity(
        const expansion& a, const expansion& b
    ) {
        return a.length() * b.length() * 2;
    }

    expansion& assign_product(const expansion& a, const expansion& b);

    static index_t product_capacity(
        const expansion& a, const expansion& b, const expansion& c
    ) {
        return a.length() * b.length() * c.length() * 4;
    }

    expansion& assign_product(
        const expansion& a, const expansion& b, const expansion& c
    );

    static index_t square_capacity(const expansion& a) {
        if(a.length() == 2) {
            return 6;
        }                                  // see two_square()
        return a.length() * a.length() * 2;
    }

    expansion& assign_square(const expansion& a);

    // ====== Determinants =============================

    static index_t det2x2_capacity(
        const expansion& a11, const expansion& a12,
        const expansion& a21, const expansion& a22
    ) {
        return
            product_capacity(a11, a22) +
            product_capacity(a21, a12);
    }

    expansion& assign_det2x2(
        const expansion& a11, const expansion& a12,
        const expansion& a21, const expansion& a22
    );

    static index_t det3x3_capacity(
        const expansion& a11, const expansion& a12, const expansion& a13,
        const expansion& a21, const expansion& a22, const expansion& a23,
        const expansion& a31, const expansion& a32, const expansion& a33
    ) {
        // Development w.r.t. first row
        index_t c11_capa = det2x2_capacity(a22, a23, a32, a33);
        index_t c12_capa = det2x2_capacity(a21, a23, a31, a33);
        index_t c13_capa = det2x2_capacity(a21, a22, a31, a32);
        return 2 * (
            a11.length() * c11_capa +
            a12.length() * c12_capa +
            a13.length() * c13_capa
        );
    }

    expansion& assign_det3x3(
        const expansion& a11, const expansion& a12, const expansion& a13,
        const expansion& a21, const expansion& a22, const expansion& a23,
        const expansion& a31, const expansion& a32, const expansion& a33
    );

    static index_t det_111_2x3_capacity(
        const expansion& a21, const expansion& a22, const expansion& a23,
        const expansion& a31, const expansion& a32, const expansion& a33
    ) {
        return
            det2x2_capacity(a22, a23, a32, a33) +
            det2x2_capacity(a23, a21, a33, a31) +
            det2x2_capacity(a21, a22, a31, a32);
    }

    expansion& assign_det_111_2x3(
        const expansion& a21, const expansion& a22, const expansion& a23,
        const expansion& a31, const expansion& a32, const expansion& a33
    );

    // ======= Geometry-specific initializations =======

    static index_t sq_dist_capacity(coord_index_t dim) {
        return index_t(dim) * 6;
    }

    expansion& assign_sq_dist(
        const double* p1, const double* p2, coord_index_t dim
    );

    static index_t dot_at_capacity(coord_index_t dim) {
        return index_t(dim) * 8;
    }

    expansion& assign_dot_at(
        const double* p1, const double* p2, const double* p0,
        coord_index_t dim
    );


    static index_t length2_capacity(
        const expansion& x, const expansion& y, const expansion& z
    ) {
        return square_capacity(x) + square_capacity(y) + square_capacity(z);
    }

    expansion& assign_length2(
        const expansion& x, const expansion& y, const expansion& z
    );

    // =============== some general purpose functions =========

    static void initialize();

    expansion& negate() {
        for(index_t i = 0; i < length_; ++i) {
            x_[i] = -x_[i];
        }
        return *this;
    }

    expansion& scale_fast(double s) {
        // TODO: debug assert is_power_of_two(s)
        for(index_t i = 0; i < length_; ++i) {
            x_[i] *= s;
        }
        return *this;
    }

    double estimate() const {
        double result = 0.0;
        for(index_t i = 0; i < length(); ++i) {
            result += x_[i];
        }
        return result;
    }

    Sign sign() const {
        if(length() == 0) {
            return ZERO;
        }
        return geo_sgn(x_[length() - 1]);
    }

    bool is_same_as(const expansion& rhs) const;

    bool is_same_as(double rhs) const;


    Sign compare(const expansion& rhs) const;

    Sign compare(double rhs) const;

    bool equals(const expansion& rhs) const {
        return (compare(rhs) == ZERO);
    }

    bool equals(double rhs) const {
        return (compare(rhs) == ZERO);
    }

    std::ostream& show(std::ostream& out) const {
        out << "expansion[" << length() << "] = [";
        for(index_t i=0; i<length(); ++i) {
            out << (*this)[i] << " ";
        }
        out << "]";
        return out;
    }

    std::string to_string() const {
        std::ostringstream out;
        show(out);
        return out.str();
    }

    void optimize();

    static void show_all_stats();

    protected:
    static index_t sub_product_capacity(
        index_t a_length, index_t b_length
    ) {
        return a_length * b_length * 2;
    }

    expansion& assign_sub_product(
        const double* a, index_t a_length, const expansion& b
    );

    expansion(const expansion& rhs) = delete;

    expansion& operator= (const expansion& rhs) = delete;

    private:

#ifdef GEO_OS_APPLE
    static constexpr index_t MAX_CAPACITY_ON_STACK = 256;
#else
    static constexpr index_t MAX_CAPACITY_ON_STACK = 1024;
#endif
    index_t length_;
    index_t capacity_;
    double x_[2];  // x_ is in fact of size [capacity_]

    friend class expansion_nt;
    };

    // =============== arithmetic operations ===========================

#define expansion_create(a)                     \
    new_expansion_on_stack(1)->assign(a)


#define expansion_abs(e)                                \
    new_expansion_on_stack(e.length())->assign_abs(e)

#define expansion_sum(a, b)                     \
    new_expansion_on_stack(                     \
        expansion::sum_capacity(a, b)           \
    )->assign_sum(a, b)

#define expansion_sum3(a, b, c)                 \
    new_expansion_on_stack(                     \
        expansion::sum_capacity(a, b, c)        \
    )->assign_sum(a, b, c)


#define expansion_sum4(a, b, c, d)              \
    new_expansion_on_stack(                     \
        expansion::sum_capacity(a, b, c, d)     \
    )->assign_sum(a, b, c, d)

#define expansion_diff(a, b)                    \
    new_expansion_on_stack(                     \
        expansion::diff_capacity(a, b)          \
    )->assign_diff(a, b)

#define expansion_product(a, b)                 \
    new_expansion_on_stack(                     \
        expansion::product_capacity(a, b)       \
    )->assign_product(a, b)

#define expansion_product3(a, b, c)             \
    new_expansion_on_stack(                     \
        expansion::product_capacity(a, b, c)    \
    )->assign_product(a, b, c)

#define expansion_square(a)                     \
    new_expansion_on_stack(                     \
        expansion::square_capacity(a)           \
    )->assign_square(a)

    // =============== determinants =====================================

#define expansion_det2x2(a11, a12, a21, a22)            \
    new_expansion_on_stack(                             \
        expansion::det2x2_capacity(a11, a12, a21, a22)  \
    )->assign_det2x2(a11, a12, a21, a22)

#define expansion_det3x3(a11, a12, a13, a21, a22, a23, a31, a32, a33)   \
    new_expansion_on_stack(                                             \
        expansion::det3x3_capacity(a11,a12,a13,a21,a22,a23,a31,a32,a33) \
    )->assign_det3x3(a11, a12, a13, a21, a22, a23, a31, a32, a33)

#define expansion_det_111_2x3(a21, a22, a23, a31, a32, a33)             \
    new_expansion_on_stack(                                             \
        expansion::det_111_2x3_capacity(a21, a22, a23, a31, a32, a33)   \
    )->assign_det_111_2x3(a21, a22, a23, a31, a32, a33)

    // =============== geometric functions ==============================

#define expansion_sq_dist(a, b, dim)            \
    new_expansion_on_stack(                     \
        expansion::sq_dist_capacity(dim)        \
    )->assign_sq_dist(a, b, dim)

#define expansion_dot_at(a, b, c, dim)          \
    new_expansion_on_stack(                     \
        expansion::dot_at_capacity(dim)         \
    )->assign_dot_at(a, b, c, dim)


#define expansion_length2(x,y,z)                \
    new_expansion_on_stack(                     \
        expansion::length2_capacity(x,y,z)      \
    )->assign_length2(x,y,z)

    

    Sign GEOGRAM_API sign_of_expansion_determinant(
        const expansion& a00,const expansion& a01,
        const expansion& a10,const expansion& a11
    );

    Sign GEOGRAM_API sign_of_expansion_determinant(
        const expansion& a00,const expansion& a01,const expansion& a02,
        const expansion& a10,const expansion& a11,const expansion& a12,
        const expansion& a20,const expansion& a21,const expansion& a22
    );

    Sign GEOGRAM_API sign_of_expansion_determinant(
        const expansion& a00,const expansion& a01,
        const expansion& a02,const expansion& a03,
        const expansion& a10,const expansion& a11,
        const expansion& a12,const expansion& a13,
        const expansion& a20,const expansion& a21,
        const expansion& a22,const expansion& a23,
        const expansion& a30,const expansion& a31,
        const expansion& a32,const expansion& a33
    );

    

    void GEOGRAM_API grow_expansion_zeroelim(
        const expansion& e, double b, expansion& h
    );

    void GEOGRAM_API scale_expansion_zeroelim(
        const expansion& e, double b, expansion& h
    );

    void GEOGRAM_API fast_expansion_sum_zeroelim(
        const expansion& e, const expansion& f, expansion& h
    );


    void GEOGRAM_API fast_expansion_diff_zeroelim(
        const expansion& e, const expansion& f, expansion& h
    );

    
}

#endif

/******* extracted from ../numerics/expansion_nt.h *******/

#ifndef GEOGRAM_NUMERICS_EXPANSION_NT
#define GEOGRAM_NUMERICS_EXPANSION_NT



namespace GEO {

    class expansion_nt;

    class GEOGRAM_API expansion_nt {
    public:

    enum Operation {
        SUM, DIFF, PRODUCT
    };

    expansion_nt() : rep_(nullptr) {
    }

    explicit expansion_nt(double x) {
        rep_ = expansion::new_expansion_on_heap(1);
        rep()[0] = x;
        rep().set_length(1);
    }

    explicit expansion_nt(const expansion& rhs) {
        rep_ = expansion::new_expansion_on_heap(rhs.length());
        rep().assign(rhs);
    }

    explicit expansion_nt(
        Operation op, const expansion& x, const expansion& y
    ) {
        switch(op) {
        case SUM:
            rep_ = expansion::new_expansion_on_heap(
                expansion::sum_capacity(x,y)
            );
            rep_->assign_sum(x,y);
            break;
        case DIFF:
            rep_ = expansion::new_expansion_on_heap(
                expansion::diff_capacity(x,y)
            );
            rep_->assign_diff(x,y);
            break;
        case PRODUCT:
            rep_ = expansion::new_expansion_on_heap(
                expansion::product_capacity(x,y)
            );
            rep_->assign_product(x,y);
            break;
        }
    }

    explicit expansion_nt(
        Operation op,
        const expansion& x, const expansion& y, const expansion& z
    ) {
        switch(op) {
        case SUM:
            rep_ = expansion::new_expansion_on_heap(
                expansion::sum_capacity(x,y,z)
            );
            rep_->assign_sum(x,y,z);
            break;
        case DIFF:
            geo_assert_not_reached;
            break;
        case PRODUCT:
            rep_ = expansion::new_expansion_on_heap(
                expansion::product_capacity(x,y,z)
            );
            rep_->assign_product(x,y,z);
            break;
        }
    }

    explicit expansion_nt(
        Operation op,
        const expansion& x, const expansion& y,
        const expansion& z, const expansion& t
    ) {
        switch(op) {
        case SUM:
            rep_ = expansion::new_expansion_on_heap(
                expansion::sum_capacity(x,y,z,t)
            );
            rep_->assign_sum(x,y,z,t);
            break;
        case DIFF:
            geo_assert_not_reached;
            break;
        case PRODUCT:
            // HERE: TODO CHECK SIZE
            const expansion& p1 = expansion_product(x,y);
            const expansion& p2 = expansion_product(z,t);
            rep_ = expansion::new_expansion_on_heap(
                expansion::product_capacity(p1,p2)
            );
            rep_->assign_sum(p1,p2);
            break;
        }
    }

    explicit expansion_nt(Operation op, double x, double y) {
        switch(op) {
        case SUM:
            rep_ = expansion::new_expansion_on_heap(
                expansion::sum_capacity(x,y)
            );
            rep_->assign_sum(x,y);
            break;
        case DIFF:
            rep_ = expansion::new_expansion_on_heap(
                expansion::diff_capacity(x,y)
            );
            rep_->assign_diff(x,y);
            break;
        case PRODUCT:
            rep_ = expansion::new_expansion_on_heap(
                expansion::product_capacity(x,y)
            );
            rep_->assign_product(x,y);
            break;
        }
    }

    expansion_nt(const expansion_nt& rhs) {
        copy(rhs);
    }

    expansion_nt(expansion_nt&& rhs) {
        rep_ = nullptr;
        std::swap(rep_, rhs.rep_);
    }

    expansion_nt& operator= (const expansion_nt& rhs) {
        if(&rhs != this) {
            cleanup();
            copy(rhs);
        }
        return *this;
    }

    expansion_nt& operator= (expansion_nt&& rhs) {
        if(&rhs != this) {
            cleanup();
            std::swap(rep_, rhs.rep_);
        }
        return *this;
    }

    ~expansion_nt() {
        cleanup();
    }

    void optimize() {
        rep().optimize();
    }

    void negate() {
        rep().negate();
    }

    

    expansion_nt& operator+= (const expansion_nt& rhs);

    expansion_nt& operator-= (const expansion_nt& rhs);

    expansion_nt& operator*= (const expansion_nt& rhs);

    expansion_nt& operator+= (double rhs);

    expansion_nt& operator-= (double rhs);

    expansion_nt& operator*= (double rhs);

    

    expansion_nt operator+ (const expansion_nt& rhs) const;

    expansion_nt operator- (const expansion_nt& rhs) const;

    expansion_nt operator* (const expansion_nt& rhs) const;

    expansion_nt operator+ (double rhs) const;

    expansion_nt operator- (double rhs) const;

    expansion_nt operator* (double rhs) const;

    

    expansion_nt operator- () const;

    

    Sign compare(const expansion_nt& rhs) const {
        return rep().compare(rhs.rep());
    }

    Sign compare(double rhs) const {
        return rep().compare(rhs);
    }

    bool operator> (const expansion_nt& rhs) const {
        return (int(compare(rhs))>0);
    }

    bool operator>= (const expansion_nt& rhs) const {
        return (int(compare(rhs))>=0);
    }

    bool operator< (const expansion_nt& rhs) const {
        return (int(compare(rhs))<0);
    }

    bool operator<= (const expansion_nt& rhs) const {
        return (int(compare(rhs))<=0);
    }

    bool operator> (double rhs) const {
        return (int(compare(rhs))>0);
    }

    bool operator>= (double rhs) const {
        return (int(compare(rhs))>=0);
    }

    bool operator< (double rhs) const {
        return (int(compare(rhs))<0);
    }

    bool operator<= (double rhs) const {
        return (int(compare(rhs))<=0);
    }

    

    double estimate() const {
        return rep().estimate();
    }

    Sign sign() const {
        return rep().sign();
    }

    index_t length() const {
        return rep().length();
    }

    double component(index_t i) const {
        geo_debug_assert(i < length());
        return rep()[i];
    }

    expansion_nt(expansion* rep) :
    rep_(rep) {
    }

    expansion& rep() {
        return *rep_;
    }

    const expansion& rep() const {
        return *rep_;
    }

    std::string to_string() const {
        return (rep_ == nullptr) ?
            std::string("null") :
            rep_->to_string()   ;
    }

    protected:

    void copy(const expansion_nt& rhs) {
        if(rhs.rep_ == nullptr) {
            rep_ = nullptr;
        } else {
            rep_ = expansion::new_expansion_on_heap(rhs.rep().capacity());
            rep_->set_length(rhs.rep().length());
            for(index_t i=0; i<rep_->length(); ++i) {
                (*rep_)[i] = rhs.rep()[i];
            }
        }
    }

    void cleanup() {
        if(rep_ != nullptr) {
            expansion::delete_expansion_on_heap(rep_);
            rep_ = nullptr;
        }
    }

    private:
    expansion* rep_;
    friend expansion_nt operator- (double a, const expansion_nt& b);

    friend expansion_nt expansion_nt_sq_dist(
        const double* a, const double* b, coord_index_t dim
    );

    friend expansion_nt expansion_nt_dot_at(
        const double* a, const double* b, const double* c,
        coord_index_t dim
    );
    // friend class rational_nt;
    };

    inline expansion_nt operator+ (double a, const expansion_nt& b) {
        return b + a;
    }

    inline expansion_nt operator- (double a, const expansion_nt& b) {
        expansion_nt result = b - a;
        result.rep().negate();
        return result;
    }

    inline expansion_nt operator* (double a, const expansion_nt& b) {
        return b * a;
    }

    inline bool operator== (const expansion_nt& a, const expansion_nt& b) {
        return a.rep().equals(b.rep());
    }

    inline bool operator== (const expansion_nt& a, double b) {
        return a.rep().equals(b);
    }

    inline bool operator== (double a, const expansion_nt& b) {
        return b.rep().equals(a);
    }

    inline bool operator!= (const expansion_nt& a, const expansion_nt& b) {
        return !a.rep().equals(b.rep());
    }

    inline bool operator!= (const expansion_nt& a, double b) {
        return !a.rep().equals(b);
    }

    inline bool operator!= (double a, const expansion_nt& b) {
        return !b.rep().equals(a);
    }

    inline expansion_nt expansion_nt_sq_dist(
        const double* a, const double* b, coord_index_t dim
    ) {
        expansion* result = expansion::new_expansion_on_heap(
            expansion::sq_dist_capacity(dim)
        );
        result->assign_sq_dist(a, b, dim);
        return expansion_nt(result);
    }

    inline expansion_nt expansion_nt_dot_at(
        const double* a, const double* b, const double* c, coord_index_t dim
    ) {
        expansion* result = expansion::new_expansion_on_heap(
            expansion::dot_at_capacity(dim)
        );
        result->assign_dot_at(a, b, c, dim);
        return expansion_nt(result);
    }

    

    template <> inline Sign geo_sgn(const expansion_nt& x) {
        return x.sign();
    }

    template <> inline Sign geo_cmp(
        const expansion_nt& x, const expansion_nt& y
    ) {
        return x.compare(y);
    }

    

    inline bool expansion_nt_is_zero(const expansion_nt& x) {
        return (x.sign() == GEO::ZERO);
    }

    inline bool expansion_nt_is_one(const expansion_nt& x) {
        return x.rep().equals(1.0);
    }


    inline Sign expansion_nt_compare(
        const expansion_nt& x, const expansion_nt& y
    ) {
        const expansion& diff = expansion_diff(x.rep(), y.rep());
        return diff.sign();
    }

    inline expansion_nt expansion_nt_square(const expansion_nt& x) {
        expansion_nt result(
            expansion::new_expansion_on_heap(
                expansion::square_capacity(x.rep()
                                          ))
        );
        result.rep().assign_square(x.rep());
        return result;
    }


    expansion_nt GEOGRAM_API expansion_nt_determinant(
        const expansion_nt& a00,const expansion_nt& a01,
        const expansion_nt& a10,const expansion_nt& a11
    );

    expansion_nt GEOGRAM_API expansion_nt_determinant(
        const expansion_nt& a00,const expansion_nt& a01,const expansion_nt& a02,
        const expansion_nt& a10,const expansion_nt& a11,const expansion_nt& a12,
        const expansion_nt& a20,const expansion_nt& a21,const expansion_nt& a22
    );

    expansion_nt GEOGRAM_API expansion_nt_determinant(
        const expansion_nt& a00,const expansion_nt& a01,
        const expansion_nt& a02,const expansion_nt& a03,
        const expansion_nt& a10,const expansion_nt& a11,
        const expansion_nt& a12,const expansion_nt& a13,
        const expansion_nt& a20,const expansion_nt& a21,
        const expansion_nt& a22,const expansion_nt& a23,
        const expansion_nt& a30,const expansion_nt& a31,
        const expansion_nt& a32,const expansion_nt& a33
    );

// Make things a bit faster if target OS has large stack size
#ifdef GEO_HAS_BIG_STACK


    template <> inline expansion_nt det2x2(
        const expansion_nt& a11, const expansion_nt& a12,
        const expansion_nt& a21, const expansion_nt& a22
    ) {
        return expansion_nt_determinant(
            a11,a12,
            a21,a22
        );
    }


    template <> inline expansion_nt det3x3(
        const expansion_nt& a11, const expansion_nt& a12,
        const expansion_nt& a13,
        const expansion_nt& a21, const expansion_nt& a22,
        const expansion_nt& a23,
        const expansion_nt& a31, const expansion_nt& a32,
        const expansion_nt& a33
    ) {
        return expansion_nt_determinant(
            a11,a12,a13,
            a21,a22,a23,
            a31,a32,a33
        );
    }


    template <> inline expansion_nt det4x4(
        const expansion_nt& a11, const expansion_nt& a12,
        const expansion_nt& a13, const expansion_nt& a14,
        const expansion_nt& a21, const expansion_nt& a22,
        const expansion_nt& a23, const expansion_nt& a24,
        const expansion_nt& a31, const expansion_nt& a32,
        const expansion_nt& a33, const expansion_nt& a34,
        const expansion_nt& a41, const expansion_nt& a42,
        const expansion_nt& a43, const expansion_nt& a44
    ) {
        return expansion_nt_determinant(
            a11,a12,a13,a14,
            a21,a22,a23,a24,
            a31,a32,a33,a34,
            a41,a42,a43,a44
        );
    }

#endif

    
}

inline std::ostream& operator<< (
    std::ostream& os, const GEO::expansion_nt& a
) {
    return os << a.estimate();
}

inline std::istream& operator>> ( std::istream& is, GEO::expansion_nt& a) {
    double d;
    is >> d;
    if (is) {
        a = GEO::expansion_nt(d);
    }
    return is;
}



namespace GEO {

    

    namespace Numeric {

        template<> inline void optimize_number_representation(expansion_nt& x) {
            x.optimize();
        }

        template<> Sign GEOGRAM_API ratio_compare(
            const expansion_nt& a_num, const expansion_nt& a_denom,
            const expansion_nt& b_num, const expansion_nt& b_denom
        );
    }

    

    typedef rationalg<expansion_nt> rational_nt;
}

#endif

/******* extracted from ../numerics/interval_nt.h *******/

#ifndef GEO_INTERVAL_NT
#define GEO_INTERVAL_NT

#include <iomanip>
#include <limits>
#include <cmath>

#ifdef __SSE__
#include <xmmintrin.h>
#else
#include <fenv.h>
#endif

// Uncomment to activate checks (keeps an arbitrary precision
// representation of the number and checks that the interval
// contains it).

// #define INTERVAL_CHECK

namespace GEO {

    class intervalBase {
    public:

        static void set_FPU_round_to_nearest() {
#ifdef __SSE__
            _MM_SET_ROUNDING_MODE(_MM_ROUND_NEAREST);
#else
            fesetround(FE_TONEAREST);
#endif
        }

        static void set_FPU_round_to_upper() {
#ifdef __SSE__
            _MM_SET_ROUNDING_MODE(_MM_ROUND_UP);
#else
            fesetround(FE_UPWARD);
#endif
        }

        enum Sign2 {
            SIGN2_ERROR = -1,
            SIGN2_ZERO  =  0,
            SIGN2_NP,
            SIGN2_PP,
            SIGN2_ZP,
            SIGN2_NN,
            SIGN2_NZ
        };

        static bool sign_is_determined(Sign2 s) {
            return
                s == SIGN2_ZERO ||
                s == SIGN2_NN   ||
                s == SIGN2_PP   ;
        }

        static bool sign_is_non_zero(Sign2 s) {
            return
                s == SIGN2_NN   ||
                s == SIGN2_PP   ;
        }

        static Sign convert_sign(Sign2 s) {
            geo_assert(sign_is_determined(s));
            if(s == SIGN2_NN) {
                return NEGATIVE;
            }
            if(s == SIGN2_PP) {
                return POSITIVE;
            }
            return ZERO;
        }

        intervalBase() {
            control_set(0);
        }

        intervalBase(double x) {
            control_set(x);
        }

        intervalBase(const intervalBase& rhs) = default;

        intervalBase& operator=(const intervalBase& rhs) = default;

    protected:
#ifdef INTERVAL_CHECK
        void control_set(const expansion_nt& x) {
            control_ = x;
        }
        void control_set(const intervalBase& x) {
            control_ = x.control_;
        }
        void control_set(double x) {
            control_ = expansion_nt(x);
        }
        void control_negate() {
            control_.rep().negate();
        }
        void control_add(const intervalBase& x) {
            control_ += x.control_;
        }
        void control_sub(const intervalBase& x) {
            control_ -= x.control_;
        }
        void control_mul(const intervalBase& x) {
            control_ *= x.control_;
        }
        void control_check(double inf, double sup) {
            typedef std::numeric_limits< double > dbl;
            if(inf > sup) {
                std::cerr.precision(dbl::max_digits10);
                std::cerr << "inf() > sup() !!" << std::endl;
                std::cerr << "inf()=" << inf << std::endl;
                std::cerr << "sup()=" << sup << std::endl;
                geo_assert_not_reached;
            }
            if(control_ < inf || control_ > sup) {
                std::cerr.precision(dbl::max_digits10);
                std::cerr << "[" << inf << "," << sup << "]"
                          << "   " << control_.estimate() << ":"
                          << control_.rep().length()
                          << std::endl;
                geo_assert_not_reached;
            }
        }
        expansion_nt control_; 
#else
        void control_set(double x) {
            geo_argused(x);
        }
        void control_set(const expansion_nt& x) {
            geo_argused(x);
        }
        void control_set(const intervalBase& x) {
            geo_argused(x);
        }
        void control_negate() {
        }
        void control_add(const intervalBase& x) {
            geo_argused(x);
        }
        void control_sub(const intervalBase& x) {
            geo_argused(x);
        }
        void control_mul(const intervalBase& x) {
            geo_argused(x);
        }
        void control_check(double inf, double sup) {
            geo_argused(inf);
            geo_argused(sup);
        }
#endif
    };




    class intervalRU : public intervalBase {
    public:

        struct Rounding {
            Rounding() {
                set_FPU_round_to_upper();
            }
            ~Rounding() {
                set_FPU_round_to_nearest();
            }
        };

        intervalRU() :
            intervalBase(),
            ln_(0.0),
            u_(0.0)
            {
                control_check();
            }

        intervalRU(double x) :
            intervalBase(x),
            ln_(-x),
            u_(x)
            {
                control_check();
            }

        intervalRU(double l, double u) : ln_(-l), u_(u) {
            // note: we cannot control check here.
        }

        intervalRU(const intervalRU& rhs) = default;

        intervalRU(const expansion_nt& rhs) {
            *this = rhs;
        }

        intervalRU& operator=(const intervalRU& rhs) = default;

        intervalRU& operator=(double rhs) {
            ln_ = -rhs;
            u_ = rhs;
            control_set(rhs);
            control_check();
            return *this;
        }

        intervalRU& operator=(const expansion_nt& rhs) {

            // Optimized expansion-to-interval conversion:
            //
            // Add components starting from the one of largest magnitude
            // Stop as soon as next component is smaller than ulp (and then
            // expand interval by ulp).

            index_t l = rhs.length();
            ln_ = -rhs.component(l-1);
            u_ = rhs.component(l-1);

            for(int comp_idx=int(l)-2; comp_idx>=0; --comp_idx) {
                double comp = rhs.component(index_t(comp_idx));
                u_ += comp;
                ln_ -= comp;
                if(comp > 0) {
                    double new_u = u_ + comp;
                    if(new_u == u_) {
                        u_ = std::nextafter(
                            u_, std::numeric_limits<double>::infinity()
                        );
                        break;
                    } else {
                        u_ = new_u;
                    }
                } else {
                    // If we stored l, we would write:
                    //  new_l  =  l  + comp
                    // But we store ln = -l, so we write:
                    // -new_ln = -ln + comp
                    // Which means:
                    //  new_ln =  ln - comp

                    double new_ln = ln_ - comp;
                    if(new_ln == ln_) {
                        ln_ = std::nextafter(
                            ln_, std::numeric_limits<double>::infinity()
                        );
                        break;
                    } else {
                        ln_ = new_ln;
                    }
                }
            }

            control_set(rhs);
            control_check();
            return *this;
        }

        double inf() const {
            return -ln_;
        }

        double sup() const {
            return u_;
        }

        double estimate() const {
            // 0.5*(lb+ub) ->
            return 0.5*(-ln_+u_);
        }

        bool is_nan() const {
            return !(ln_==ln_) || !(u_==u_);
        }

        Sign2 sign() const {
            // Branchless
            int lz = int(ln_ == 0);
            int ln = int(ln_ >  0); // inverted, it is ln_ !!!
            int lp = int(ln_ <  0); // inverted, it is ln_ !!!
            int uz = int(u_ ==  0);
            int un = int(u_ <   0);
            int up = int(u_ >   0);
            Sign2 result = Sign2(
                ln*up*SIGN2_NP+
                lp*up*SIGN2_PP+
                lz*up*SIGN2_ZP+
                ln*un*SIGN2_NN+
                ln*uz*SIGN2_NZ
            );
            result = Sign2(
                int(result) +
                int(result==SIGN2_ZERO && !(lz&&uz)) * SIGN2_ERROR
            );
            return result;
        }

        intervalRU& negate() {
            std::swap(ln_, u_);
            control_negate();
            control_check();
            return *this;
        }

        intervalRU& operator+=(const intervalRU &x) {
            // lb += x.lb -> -lbn += -x.lbn -> lbn += x.lbn
            ln_ += x.ln_;
            u_  += x.u_;
            control_add(x);
            control_check();
            return *this;
        }

        intervalRU& operator-=(const intervalRU &x) {
            // +=(x.negate()) ->
            ln_ += x.u_;
            u_  += x.ln_;
            control_sub(x);
            control_check();
            return *this;
        }


        intervalRU& operator*=(const intervalRU &b) {
            // get bounds of both operands
            double aln  = ln_;
            double au   = u_;
            double bln  = b.ln_;
            double bu   = b.u_;

            // negated bounds round to upper
            // (equivalent to bounds round to lower)
            double lln = (-aln)*bln;
            double lun = aln*bu;
            double uln = au*bln;
            double uun = (-au)*bu;

            // bounds round to upper
            double ll = aln*bln;
            double lu = (-aln)*bu;
            double ul = au*(-bln);
            double uu = au*bu;

            ln_ = std::max(std::max(lln,lun),std::max(uln,uun));
            u_  = std::max(std::max(ll,lu),std::max(ul,uu));

            control_mul(b);
            control_check();
            return *this;
        }

    protected:

#ifdef INTERVAL_CHECK
        void control_check() {
            // expansion_nt used in control_check() operates
            // in round to nearest mode !!
            set_FPU_round_to_nearest();
            intervalBase::control_check(inf(),sup());
            set_FPU_round_to_upper();
        }
#else
        void control_check() {
        }
#endif
        double ln_;
        double u_;
    };


    inline intervalRU operator+(const intervalRU& a, const intervalRU& b) {
        intervalRU result = a;
        return result += b;
    }

    inline intervalRU operator-(const intervalRU& a, const intervalRU& b) {
        intervalRU result = a;
        return result -= b;
    }

    inline intervalRU operator*(const intervalRU& a, const intervalRU& b) {
        intervalRU result = a;
        return result *= b;
    }

    

    class intervalRN : public intervalBase {
    public:

        // operates in default rounding mode
        // (so Rounding subclass does nothing)
        struct Rounding {
            Rounding() {
            }
            ~Rounding() {
            }
        };

        intervalRN() :
            intervalBase(),
            lb_(0.0),
            ub_(0.0)
            {
                control_check();
            }

        intervalRN(double x) :
            intervalBase(x),
            lb_(x),
            ub_(x)
            {
                control_check();
            }

        intervalRN(double l, double u) : lb_(l), ub_(u) {
            // note: we cannot control check here.
        }


        intervalRN(const intervalRN& rhs) = default;

        intervalRN(const expansion_nt& rhs) {
            *this = rhs;
        }

        intervalRN& operator=(const intervalRN& rhs) = default;

        intervalRN& operator=(double rhs) {
            lb_ = rhs;
            ub_ = rhs;
            control_set(rhs);
            control_check();
            return *this;
        }

        intervalRN& operator=(const expansion_nt& rhs) {

            // Optimized expansion-to-interval conversion:
            //
            // Add components starting from the one of largest magnitude
            // Stop as soon as next component is smaller than ulp (and then
            // expand interval by ulp).

            index_t l = rhs.length();
            lb_ = rhs.component(l-1);
            ub_ = rhs.component(l-1);

            for(int comp_idx=int(l)-2; comp_idx>=0; --comp_idx) {
                double comp = rhs.component(index_t(comp_idx));
                if(comp > 0) {
                    double nub = ub_ + comp;
                    if(nub == ub_) {
                        ub_ = std::nextafter(
                            ub_, std::numeric_limits<double>::infinity()
                        );
                        break;
                    } else {
                        ub_ = nub;
                        adjust();
                    }
                } else {
                    double nlb = lb_ + comp;
                    if(nlb == lb_) {
                        lb_ = std::nextafter(
                            lb_, -std::numeric_limits<double>::infinity()
                        );
                        break;
                    } else {
                        lb_ = nlb;
                        adjust();
                    }
                }
            }
            control_set(rhs);
            control_check();
            return *this;
        }

        double inf() const {
            return lb_;
        }

        double sup() const {
            return ub_;
        }

        double estimate() const {
            return 0.5*(lb_ + ub_);
        }

        bool is_nan() const {
            return !(lb_==lb_) || !(ub_==ub_);
        }

        Sign2 sign() const {
            if(is_nan()) {
                return SIGN2_ERROR;
            }
            // Branchless (not sure it is super though...)
            int lz = int(lb_ ==  0);
            int ln = int(lb_ <   0);
            int lp = int(lb_ >   0);
            int uz = int(ub_ ==  0);
            int un = int(ub_ <   0);
            int up = int(ub_ >   0);
            Sign2 result = Sign2(
                ln*up*SIGN2_NP+
                lp*up*SIGN2_PP+
                lz*up*SIGN2_ZP+
                ln*un*SIGN2_NN+
                ln*uz*SIGN2_NZ
            );
            result = Sign2(
                int(result) +
                int(result==SIGN2_ZERO && !(lz&&uz)) * SIGN2_ERROR
            );
            return result;
        }

        intervalRN& negate() {
            lb_ = -lb_;
            ub_ = -ub_;
            std::swap(lb_, ub_);
            control_negate();
            control_check();
            return *this;
        }

        intervalRN& operator+=(const intervalRN &x) {
            lb_ += x.lb_;
            ub_ += x.ub_;
            adjust();
            control_add(x);
            control_check();
            return *this;
        }

        intervalRN& operator-=(const intervalRN &x) {
            lb_ -= x.ub_;
            ub_ -= x.lb_;
            adjust();
            control_sub(x);
            control_check();
            return *this;
        }

        intervalRN& operator*=(const intervalRN &x) {
            if(!is_nan() && !x.is_nan()) {
                double ll = lb_*x.lb_;
                double lu = lb_*x.ub_;
                double ul = ub_*x.lb_;
                double uu = ub_*x.ub_;

                if(!(ll==ll)) ll = 0.0;
                if(!(lu==lu)) lu = 0.0;
                if(!(ul==ul)) ul = 0.0;
                if(!(uu==uu)) uu = 0.0;

                if(lu<ll) std::swap(lu, ll);
                if(ul<ll) std::swap(ul, ll);
                if(uu<ll) std::swap(uu, ll);

                if(lu>uu) uu = lu;
                if(ul>uu) uu = ul;

                lb_ = ll;
                ub_ = uu;

                adjust();
            } else {
                lb_ = std::numeric_limits<double>::quiet_NaN();
                ub_ = std::numeric_limits<double>::quiet_NaN();
            }
            control_mul(x);
            control_check();
            return *this;
        }

    protected:

        void adjust() {
            static constexpr double i = std::numeric_limits<double>::infinity();
            static constexpr double e = std::numeric_limits<double>::epsilon();
            // nextafter(1.0) - 1.0
            static constexpr double m = std::numeric_limits<double>::min();
            // smallest normalized
            static constexpr double l = 1.0-e;
            static constexpr double u = 1.0+e;
            static constexpr double em = e*m;

            if(lb_==lb_ && ub_==ub_ && (lb_!=ub_ || (lb_!=i && lb_!=-i))) {

                if(lb_>ub_) {
                    std::swap(lb_, ub_);
                }

                if(lb_>m) {
                    lb_ *= l;
                } else if(lb_<-m) {
                    lb_ *= u;
                } else {
                    lb_ -= em;
                }

                if(ub_>m) {
                    ub_ *= u;
                } else if(ub_<-m) {
                    ub_ *= l;
                } else {
                    ub_ += em;
                }
            } else {
                lb_ = std::numeric_limits<double>::quiet_NaN();
                ub_ = std::numeric_limits<double>::quiet_NaN();
            }
        }

#ifdef INTERVAL_CHECK
        void control_check() {
            intervalBase::control_check(inf(),sup());
        }
#else
        void control_check() {
        }
#endif

    private:
        double lb_; 
        double ub_; 
    };

    inline intervalRN operator+(const intervalRN& a, const intervalRN& b) {
        intervalRN result = a;
        return result += b;
    }

    inline intervalRN operator-(const intervalRN& a, const intervalRN& b) {
        intervalRN result = a;
        return result -= b;
    }

    inline intervalRN operator*(const intervalRN& a, const intervalRN& b) {
        intervalRN result = a;
        return result *= b;
    }

    typedef intervalRN interval_nt; // Seems that valgrind does not support RU
    //typedef intervalRU interval_nt;


    template <> inline vec2Hg<interval_nt> operator-(
        const vec2Hg<interval_nt>& p1, const vec2Hg<interval_nt>& p2
    ) {
        return vec2Hg<interval_nt>(
            det2x2(p1.x,p1.w,p2.x,p2.w),
            det2x2(p1.y,p1.w,p2.y,p2.w),
            p1.w*p2.w
        );
    }


    template <> inline vec3Hg<interval_nt> operator-(
        const vec3Hg<interval_nt>& p1, const vec3Hg<interval_nt>& p2
    ) {
        return vec3Hg<interval_nt>(
            det2x2(p1.x,p1.w,p2.x,p2.w),
            det2x2(p1.y,p1.w,p2.y,p2.w),
            det2x2(p1.z,p1.w,p2.z,p2.w),
            p1.w * p2.w
        );
    }

}

#endif

/******* extracted from ../numerics/exact_geometry.h *******/

#ifndef GEOGRAM_NUMERICS_EXACT_GEOMETRY
#define GEOGRAM_NUMERICS_EXACT_GEOMETRY



#ifdef GEOGRAM_WITH_GEOGRAMPLUS
#endif


// If Tessael's geogramplus is available, use exact_nt coordinates,
// else use expansion_nt coordinates.
// exact_nt coordinates makes the algorithm  10x to 20x faster
// and have no risk of underflow / overflow.
#ifdef GEOGRAM_WITH_GEOGRAMPLUS
#define GEOGRAM_USE_EXACT_NT
#endif

namespace GEO {

    typedef vecng<2,expansion_nt> vec2E;

    typedef vecng<3,expansion_nt> vec3E;

    typedef vecng<2,interval_nt> vec2I;

    typedef vecng<3,interval_nt> vec3I;

    typedef vec2Hg<expansion_nt> vec2HE;

    typedef vec3Hg<expansion_nt> vec3HE;

    typedef vec2Hg<interval_nt> vec2HI;

    typedef vec3Hg<interval_nt> vec3HI;

    

    template <class VEC3 = vec3>
    inline VEC3 make_vec3(const vec3& p1, const vec3& p2) {
        typedef typename VEC3::value_type value_type;
        return VEC3(
            value_type(p2.x) - value_type(p1.x),
            value_type(p2.y) - value_type(p1.y),
            value_type(p2.z) - value_type(p1.z)
        );
    }

    template <class VEC2>
    inline VEC2 make_vec2(
        const vec2& p1, const vec2& p2
    ) {
        typedef typename VEC2::value_type value_type;
        return VEC2(
            value_type(p2.x) - value_type(p1.x),
            value_type(p2.y) - value_type(p1.y)
        );
    }

    template <class VEC3>
    inline VEC3 triangle_normal(
        const vec3& p1, const vec3& p2, const vec3& p3
    ) {
        return cross(
            make_vec3<VEC3>(p1,p2),
            make_vec3<VEC3>(p1,p3)
        );
    }

    

    namespace PCK {

        Sign GEOGRAM_API orient_2d(
            const vec2HE& p0, const vec2HE& p1, const vec2HE& p2
        );

        Sign GEOGRAM_API orient_2d_projected(
            const vec3HE& p0, const vec3HE& p1, const vec3HE& p2,
            coord_index_t axis
        );

        Sign GEOGRAM_API orient_3d(
            const vec3HE& p0, const vec3HE& p1,
            const vec3HE& p2, const vec3HE& p3
        );

        Sign GEOGRAM_API dot_2d(
            const vec2HE& p0, const vec2HE& p1, const vec2HE& p2
        );

        Sign GEOGRAM_API incircle_2d_SOS_with_lengths(
            const vec2HE& p0, const vec2HE& p1,
            const vec2HE& p2, const vec2HE& p3,
            double l0, double l1, double l2, double l3
        );

        Sign GEOGRAM_API incircle_2d_SOS_with_lengths(
            const vec2HE& p0, const vec2HE& p1,
            const vec2HE& p2, const vec2HE& p3,
            double l0, double l1, double l2, double l3
        );

        inline Sign incircle_2d_SOS(
            const vec2HE& p0, const vec2HE& p1,
            const vec2HE& p2, const vec2HE& p3
        ) {
            double l0 = (geo_sqr(p0.x) + geo_sqr(p0.y)).estimate() /
                geo_sqr(p0.w).estimate();
            double l1 = (geo_sqr(p1.x) + geo_sqr(p1.y)).estimate() /
                geo_sqr(p1.w).estimate();
            double l2 = (geo_sqr(p2.x) + geo_sqr(p2.y)).estimate() /
                geo_sqr(p2.w).estimate();
            double l3 = (geo_sqr(p3.x) + geo_sqr(p3.y)).estimate() /
                geo_sqr(p3.w).estimate();
            return incircle_2d_SOS_with_lengths(p0,p1,p2,p3,l0,l1,l2,l3);
        }

        coord_index_t GEOGRAM_API triangle_normal_axis(
            const vec3& p1, const vec3& p2, const vec3& p3
        );

        bool GEOGRAM_API aligned_3d(
            const vec3HE& p0, const vec3HE& p1, const vec3HE& p2
        );

        bool GEOGRAM_API on_segment_3d(
            const vec3HE& p, const vec3HE& q1, const vec3HE& q2
        );

        vec3 GEOGRAM_API approximate(const vec3HE& p);

        vec2 GEOGRAM_API approximate(const vec2HE& p);

    }

    

    template <>
    inline vec2E make_vec2<vec2E>(const vec2& p1, const vec2& p2) {
        return vec2E(
            expansion_nt(expansion_nt::DIFF, p2.x, p1.x),
            expansion_nt(expansion_nt::DIFF, p2.y, p1.y)
        );
    }

    template <>
    inline vec3E make_vec3<vec3E>(const vec3& p1, const vec3& p2) {
        return vec3E(
            expansion_nt(expansion_nt::DIFF, p2.x, p1.x),
            expansion_nt(expansion_nt::DIFF, p2.y, p1.y),
            expansion_nt(expansion_nt::DIFF, p2.z, p1.z)
        );
    }

// Under Linux we got 10 Mb of stack (!) Then some operations can be
// made faster by using the low-level expansion API (that allocates
// intermediary multiprecision values on stack rather than in the heap).
// These optimized functions are written as template specializations
// (used automatically).

#ifdef GEO_HAS_BIG_STACK

    template<> expansion_nt GEOGRAM_API det(const vec2E& v1, const vec2E& v2);

    template<> expansion_nt GEOGRAM_API dot(const vec2E& v1, const vec2E& v2);

    template<> expansion_nt GEOGRAM_API dot(const vec3E& v1, const vec3E& v2);

    template<> vec2Hg<expansion_nt> GEOGRAM_API mix(
        const rationalg<expansion_nt>& t,
        const vecng<2,double>& p1, const vecng<2,double>& p2
    );

    template<> vec3Hg<expansion_nt> GEOGRAM_API mix(
        const rationalg<expansion_nt>& t,
        const vecng<3,double>& p1, const vecng<3,double>& p2
    );

    template <> GEOGRAM_API vec3E triangle_normal<vec3E>(
        const vec3& p1, const vec3& p2, const vec3& p3
    );

#endif

    

    namespace exact {
#ifdef GEOGRAM_USE_EXACT_NT
        typedef exact_nt scalar;     
#else
        typedef expansion_nt scalar; 
#endif
        typedef vecng<2,scalar> vec2; 
        typedef vecng<3,scalar> vec3; 

        typedef vec2Hg<scalar> vec2h;

        typedef vec3Hg<scalar> vec3h;

        typedef rationalg<scalar> rational;
    }
}

#endif

/******* extracted from ../basic/string.h *******/

#ifndef GEOGRAM_BASIC_STRING
#define GEOGRAM_BASIC_STRING


#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>

#include <vector>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>


namespace GEO {

    /*
     * \brief String manipulation utilities.
     */
    namespace String {

        void GEOGRAM_API split_string(
            const std::string& in,
            char separator,
            std::vector<std::string>& out,
            bool skip_empty_fields = true
        );

        void GEOGRAM_API split_string(
            const std::string& in,
            const std::string& separator,
            std::vector<std::string>& out,
            bool skip_empty_fields = true
        );

        bool GEOGRAM_API split_string(
            const std::string& in,
            char separator,
            std::string& left,
            std::string& right
        );

        std::string GEOGRAM_API join_strings(
            const std::vector<std::string>& in,
            char separator
        );

        std::string GEOGRAM_API join_strings(
            const std::vector<std::string>& in,
            const std::string& separator
        );

        std::string GEOGRAM_API to_lowercase(const std::string& s);

        std::string GEOGRAM_API to_uppercase(const std::string& s);

        inline std::string char_to_string(char c) {
            char s[2];
            s[0] = c;
            s[1] = '\0';
            return std::string(s);
        }

        std::string GEOGRAM_API quote(
            const std::string& s, char quotes = '\"'
        );

        bool GEOGRAM_API string_starts_with(
            const std::string& haystack, const std::string& needle
        );

        bool GEOGRAM_API string_ends_with(
            const std::string& haystack, const std::string& needle
        );

        std::string GEOGRAM_API format(const char* format, ...)
#ifndef GOMGEN
#ifdef GEO_COMPILER_GCC_FAMILY
        // Tells the compiler that format is a printf-like format
        // string, so that it can check that the arguments match
        // the format string and bark at you if it is not the case.
            __attribute__ ((__format__(printf, 1, 2)))
#endif
#endif
            ;

	std::string GEOGRAM_API format_time(double seconds, bool HMS_only=false);

        template <class T>
        inline std::string to_string(const T& value) {
            std::ostringstream out;
            // Makes sure that double-precision number are displayed
            // with a sufficient number of digits. This is important
            // to avoid losing precision when using ASCII files.
            out << std::setprecision(17);
            out << value;
            return out.str();
        }

        template <class T>
        inline std::string to_display_string(const T& value) {
            return to_string(value);
        }


        template <>
        inline std::string to_display_string(const double& value) {
            std::ostringstream out;
            out << value;
            return out.str();
        }

        template <>
        inline std::string to_display_string(const float& value) {
            std::ostringstream out;
            out << value;
            return out.str();
        }

        template <>
        inline std::string to_string(const bool& value) {
            return value ? "true" : "false";
        }

        class GEOGRAM_API ConversionError : public std::logic_error {
        public:
            ConversionError(const std::string& s, const std::string& type);

            const char* what() const GEO_NOEXCEPT override;
        };

        template <class T>
        inline bool from_string(const char* s, T& value) {
            std::istringstream in(s);
            return (in >> value) && (in.eof() || ((in >> std::ws) && in.eof()));
        }

        template <class T>
        inline bool from_string(const std::string& s, T& value) {
            return from_string(s.c_str(), value);
        }

        template <>
        inline bool from_string(const char* s, double& value) {
            errno = 0;
            char* end;
            value = strtod(s, &end);
            return end != s && *end == '\0' && errno == 0;
        }

        template <typename T>
        inline bool string_to_signed_integer(const char* s, T& value) {
            errno = 0;
            char* end;
#ifdef GEO_OS_WINDOWS
            Numeric::int64 v = _strtoi64(s, &end, 10);
#else
            Numeric::int64 v = strtoll(s, &end, 10);
#endif
            if(
                end != s && *end == '\0' && errno == 0 &&
                v >= std::numeric_limits<T>::min() &&
                v <= std::numeric_limits<T>::max()
            ) {
                value = static_cast<T>(v);
                return true;
            }

            return false;
        }

        template <>
        inline bool from_string(const char* s, Numeric::int8& value) {
            return string_to_signed_integer(s, value);
        }

        template <>
        inline bool from_string(const char* s, Numeric::int16& value) {
            return string_to_signed_integer(s, value);
        }

        template <>
        inline bool from_string(const char* s, Numeric::int32& value) {
            return string_to_signed_integer(s, value);
        }

        template <>
        inline bool from_string(const char* s, Numeric::int64& value) {
            errno = 0;
            char* end;
#ifdef GEO_OS_WINDOWS
            value = _strtoi64(s, &end, 10);
#else
            value = strtoll(s, &end, 10);
#endif
            return end != s && *end == '\0' && errno == 0;
        }

        template <typename T>
        inline bool string_to_unsigned_integer(const char* s, T& value) {
            errno = 0;
            char* end;
#ifdef GEO_OS_WINDOWS
            Numeric::uint64 v = _strtoui64(s, &end, 10);
#else
            Numeric::uint64 v = strtoull(s, &end, 10);
#endif
            if(
                end != s && *end == '\0' && errno == 0 &&
                v <= std::numeric_limits<T>::max()
            ) {
                value = static_cast<T>(v);
                return true;
            }

            return false;
        }

        template <>
        inline bool from_string(const char* s, Numeric::uint8& value) {
            return string_to_unsigned_integer(s, value);
        }

        template <>
        inline bool from_string(const char* s, Numeric::uint16& value) {
            return string_to_unsigned_integer(s, value);
        }

        template <>
        inline bool from_string(const char* s, Numeric::uint32& value) {
            return string_to_unsigned_integer(s, value);
        }

        template <>
        inline bool from_string(const char* s, Numeric::uint64& value) {
            errno = 0;
            char* end;
#ifdef GEO_OS_WINDOWS
            value = _strtoui64(s, &end, 10);
#else
            value = strtoull(s, &end, 10);
#endif
            return end != s && *end == '\0' && errno == 0;
        }

        template <>
        inline bool from_string(const char* s, bool& value) {
            if(strcmp(s, "true") == 0 ||
               strcmp(s, "True") == 0 ||
               strcmp(s, "1") == 0
              ) {
                value = true;
                return true;
            }
            if(strcmp(s, "false") == 0 ||
               strcmp(s, "False") == 0 ||
               strcmp(s, "0") == 0
              ) {
                value = false;
                return true;
            }
            return false;
        }

        inline int to_int(const std::string& s) {
            int value;
            if(!from_string(s, value)) {
                throw ConversionError(s, "integer");
            }
            return value;
        }

        inline unsigned int to_uint(const std::string& s) {
            unsigned int value;
            if(!from_string(s, value)) {
                throw ConversionError(s, "integer");
            }
            return value;
        }

        inline double to_double(const std::string& s) {
            double value;
            if(!from_string(s, value)) {
                throw ConversionError(s, "double");
            }
            return value;
        }

        inline bool to_bool(const std::string& s) {
            bool value;
            if(!from_string(s, value)) {
                throw ConversionError(s, "boolean");
            }
            return value;
        }

        std::string GEOGRAM_API wchar_to_UTF8(const wchar_t* in);
    }
}

#endif

/******* extracted from ../basic/line_stream.h *******/

#ifndef GEOGRAM_BASIC_LINE_STREAM
#define GEOGRAM_BASIC_LINE_STREAM

#include <cstring>
#include <stdio.h>


namespace GEO {

    class GEOGRAM_API LineInput {
    public:
    LineInput(const std::string& filename);

    ~LineInput();

    bool OK() const {
        return ok_;
    }

    bool eof() const {
        return feof(F_) ? true : false;
    }

    bool get_line();

    index_t nb_fields() const {
        return index_t(field_.size());
    }

    size_t line_number() const {
        return line_num_;
    }

    char* field(index_t i) {
        geo_assert(i < nb_fields());
        return field_[i];
    }

    const char* field(index_t i) const {
        geo_assert(i < nb_fields());
        return field_[i];
    }

    signed_index_t field_as_int(index_t i) const {
        signed_index_t result = 0;
        if(!String::from_string(field(i), result)) {
            conversion_error(i, "integer");
        }
        return result;
    }

    index_t field_as_uint(index_t i) const {
        index_t result = 0;
        if(!String::from_string(field(i), result)) {
            conversion_error(i, "unsigned integer");
        }
        return result;
    }

    double field_as_double(index_t i) const {
        double result = 0;
        if(!String::from_string(field(i), result)) {
            conversion_error(i, "floating point");
        }
        return result;
    }

    bool field_matches(index_t i, const char* s) const {
        return strcmp(field(i), s) == 0;
    }

    void get_fields(const char* separators = " \t\r\n");

    const char* current_line() const {
        return line_;
    }

    private:
    GEO_NORETURN_DECL void conversion_error(
        index_t index, const char* type
    ) const GEO_NORETURN ;

    static constexpr index_t MAX_LINE_LEN = 65535;

    FILE* F_;
    std::string file_name_;
    size_t line_num_;
    char line_[MAX_LINE_LEN];
    std::vector<char*> field_;
    bool ok_;
    };
}

#endif

/******* extracted from ../basic/stopwatch.h *******/

#ifndef GEOGRAM_BASIC_STOPWATCH
#define GEOGRAM_BASIC_STOPWATCH


#include <chrono>


namespace GEO {

    class GEOGRAM_API Stopwatch {
    public:
    Stopwatch(const std::string& task_name, bool verbose=true);


    Stopwatch();

    double elapsed_time() const;

    ~Stopwatch();


    void print_elapsed_time();

    static double now();

    static double process_elapsed_time() {
        return now() - process_start_time_;
    }

    static void initialize();
    static void show_stats();

    private:
    static double process_start_time_;
    static bool global_stats_;
    std::chrono::time_point<std::chrono::system_clock> start_;
    std::string task_name_;
    bool verbose_;
    };
}

#endif

/******* extracted from ../basic/command_line.h *******/

#ifndef GEOGRAM_BASIC_COMMAND_LINE
#define GEOGRAM_BASIC_COMMAND_LINE



namespace GEO {

    namespace CmdLine {

        void GEOGRAM_API initialize();

        void GEOGRAM_API terminate();


        void GEOGRAM_API set_config_file_name(
            const std::string& filename,
            bool auto_create_args = false
        );

        bool GEOGRAM_API config_file_loaded();

        std::string GEOGRAM_API get_config_file_name();

        void GEOGRAM_API load_config(
            const std::string& filename, const std::string& program_name = "*"
        );

	void GEOGRAM_API save_config(const std::string& filename);

        enum ArgType {
            
            ARG_UNDEFINED = 0,
            
            ARG_INT = 1,
            
            ARG_DOUBLE = 2,
            
            ARG_STRING = 4,
            
            ARG_BOOL = 8,
            
            ARG_PERCENT = 16
        };

        enum ArgFlags {
            
            ARG_FLAGS_DEFAULT = 0,
            
            ARG_ADVANCED = 1
        };

        void GEOGRAM_API declare_arg_group(
            const std::string& name,
            const std::string& description,
            ArgFlags flags = ARG_FLAGS_DEFAULT
        );

        void GEOGRAM_API declare_arg(
            const std::string& name,
            ArgType type,
            const std::string& default_value,
            const std::string& description,
            ArgFlags flags = ARG_FLAGS_DEFAULT
        );

        ArgType GEOGRAM_API get_arg_type(const std::string& name);


	std::string GEOGRAM_API get_arg_desc(const std::string& name);

        bool GEOGRAM_API arg_is_declared(const std::string& name);

        inline void declare_arg(
            const std::string& name,
            const std::string& default_value,
            const std::string& description,
            ArgFlags flags = ARG_FLAGS_DEFAULT
        ) {
            declare_arg(
                name, ARG_STRING, default_value,
                description, flags
            );
        }

        inline void declare_arg(
            const std::string& name,
            const char* default_value,
            const std::string& description,
            ArgFlags flags = ARG_FLAGS_DEFAULT
        ) {
            declare_arg(
                name, ARG_STRING, default_value,
                description, flags
            );
        }

        inline void declare_arg(
            const std::string& name,
            int default_value,
            const std::string& description,
            ArgFlags flags = ARG_FLAGS_DEFAULT
        ) {
            declare_arg(
                name, ARG_INT, String::to_string(default_value),
                description, flags
            );
        }

        inline void declare_arg(
            const std::string& name,
            double default_value,
            const std::string& description,
            ArgFlags flags = ARG_FLAGS_DEFAULT
        ) {
            declare_arg(
                name, ARG_DOUBLE, String::to_string(default_value),
                description, flags
            );
        }

        inline void declare_arg(
            const std::string& name,
            bool default_value,
            const std::string& description,
            ArgFlags flags = ARG_FLAGS_DEFAULT
        ) {
            declare_arg(
                name, ARG_BOOL, default_value ? "true" : "false",
                description, flags
            );
        }

        inline void declare_arg_percent(
            const std::string& name,
            double default_value,
            const std::string& description = "...",
            ArgFlags flags = ARG_FLAGS_DEFAULT
        ) {
            declare_arg(
                name, ARG_PERCENT, String::to_string(default_value) + "%",
                description, flags
            );
        }

        bool GEOGRAM_API parse(
            int argc, char** argv, std::vector<std::string>& unparsed_args,
            const std::string& additional_arg_specs = ""
        );

        bool GEOGRAM_API parse(
            int argc, char** argv
        );

        int GEOGRAM_API argc();


        typedef char** charptrptr; // Need to do that else the compiler thinks
        // that GEOGRAM_API qualifies the ptr instead
        // of the function.

        charptrptr GEOGRAM_API argv();

        void GEOGRAM_API show_usage(
            const std::string& additional_args = "",
            bool advanced = false
        );

        std::string GEOGRAM_API get_arg(const std::string& name);

        int GEOGRAM_API get_arg_int(const std::string& name);

        unsigned int GEOGRAM_API get_arg_uint(const std::string& name);

        double GEOGRAM_API get_arg_double(const std::string& name);

        double GEOGRAM_API get_arg_percent(
            const std::string& name, double reference
        );

        bool GEOGRAM_API get_arg_bool(const std::string& name);

        bool GEOGRAM_API set_arg(
            const std::string& name, const std::string& value
        );

        inline bool set_arg(const std::string& name, const char* value) {
            return set_arg(name, std::string(value));
        }

        void GEOGRAM_API set_arg(const std::string& name, Numeric::int32 value);

        /*
         * \brief Sets an argument value from an integer
         * \details This replaces the value of argument \p name by the given
         * integer \p value. If the declared type of the argument is not
         * compatible with an integer then the function aborts (compatible
         * argument types are: int, double or string). If the argument does
         * not exist, it is added as a new argument of undefined type.
         * \param[in] name the argument name
         * \param[in] value the new value as an integer
         */
        void GEOGRAM_API set_arg(
            const std::string& name, Numeric::uint32 value
        );

        /*
         * \brief Sets an argument value from an integer
         * \details This replaces the value of argument \p name by the given
         * integer \p value. If the declared type of the argument is not
         * compatible with an integer then the function aborts (compatible
         * argument types are: int, double or string). If the argument does
         * not exist, it is added as a new argument of undefined type.
         * \param[in] name the argument name
         * \param[in] value the new value as an integer
         */
        void GEOGRAM_API set_arg(const std::string& name, Numeric::int64 value);

        /*
         * \brief Sets an argument value from an integer
         * \details This replaces the value of argument \p name by the given
         * integer \p value. If the declared type of the argument is not
         * compatible with an integer then the function aborts (compatible
         * argument types are: int, double or string). If the argument does
         * not exist, it is added as a new argument of undefined type.
         * \param[in] name the argument name
         * \param[in] value the new value as an integer
         */
        void GEOGRAM_API set_arg(
            const std::string& name, Numeric::uint64 value
        );

        void GEOGRAM_API set_arg(const std::string& name, double value);

        void GEOGRAM_API set_arg(const std::string& name, bool value);

        void GEOGRAM_API set_arg_percent(const std::string& name, double value);

        

	void GEOGRAM_API get_arg_groups(std::vector<std::string>& groups);

	void GEOGRAM_API get_arg_names_in_group(
	    const std::string& group,
	    std::vector<std::string>& arg_names
	);

        

        void GEOGRAM_API get_args(std::vector<std::string>& args);

        index_t GEOGRAM_API ui_terminal_width();

        void GEOGRAM_API ui_separator(
            const std::string& title,
            const std::string& short_title = ""
        );

        void GEOGRAM_API ui_separator();

        void GEOGRAM_API ui_close_separator();

        void GEOGRAM_API ui_message(
            const std::string& message,
            index_t wrap_margin
        );

        void GEOGRAM_API ui_message(
            const std::string& message
        );

        void GEOGRAM_API ui_clear_line();

        void GEOGRAM_API ui_progress(
            const std::string& task_name, index_t val,
            index_t percent, bool clear = true
        );

        void GEOGRAM_API ui_progress_time(
            const std::string& task_name,
            double elapsed, bool clear = true
        );

        void GEOGRAM_API ui_progress_canceled(
            const std::string& task_name,
            double elapsed, index_t percent, bool clear = true
        );

        std::string GEOGRAM_API ui_feature(
            const std::string& feature, bool show = true
        );
    }
}


#ifdef GEO_OS_ANDROID
struct android_app;

namespace GEO {
    namespace CmdLine {
        void GEOGRAM_API set_android_app(android_app* app);

        android_app* GEOGRAM_API get_android_app();
    }
}

#endif


#endif

/******* extracted from ../basic/command_line_args.h *******/

#ifndef GEOGRAM_BASIC_COMMAND_LINE_ARGS
#define GEOGRAM_BASIC_COMMAND_LINE_ARGS



namespace GEO {

    namespace CmdLine {

        bool GEOGRAM_API import_arg_group(
            const std::string& name
        );

        bool GEOGRAM_API set_profile(
            const std::string& name
        );
    }
}

#endif

/******* extracted from ../voronoi/convex_cell.h *******/

#ifndef GEOGRAM_VORONOI_CONVEX_CELL
#define GEOGRAM_VORONOI_CONVEX_CELL

#ifndef STANDALONE_CONVEX_CELL
#  ifndef GEOGRAM_PSM
#  include <geogram/basic/attributes.h>
#  endif
#endif

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>




#ifndef STANDALONE_CONVEX_CELL
namespace GEO {
    class Mesh;
    class PeriodicDelaunay3d;
}
#endif


namespace VBW {

#ifdef STANDALONE_CONVEX_CELL
    using std::vector;
    typedef unsigned int index_t;
    typedef unsigned int global_index_t;
#   define vbw_assert(x) assert(x)
    struct vec2 {
        double x;
        double y;
    };
    struct vec3 {
        double x;
        double y;
        double z;
    };
    struct vec4 {
        double x;
        double y;
        double z;
        double w;
    };
#else
    using GEO::vector;
    typedef unsigned int index_t;        // Always 32 bits
    typedef GEO::index_t global_index_t; // Possibly 64 bits in GARGANTUA mode
#   define vbw_assert(x) geo_debug_assert(x)
    using GEO::vec2;
    using GEO::vec3;
    using GEO::vec4;
#endif




    inline vec2 make_vec2(
        double x, double y
    ) {
        vec2 result;
        result.x = x;
        result.y = y;
        return result;
    }


    inline vec3 make_vec3(
        double x, double y, double z
    ) {
        vec3 result;
        result.x = x;
        result.y = y;
        result.z = z;
        return result;
    }


    inline vec3 cross(vec3 v1, vec3 v2) {
        return make_vec3(
            v1.y*v2.z - v1.z*v2.y,
            v1.z*v2.x - v1.x*v2.z,
            v1.x*v2.y - v1.y*v2.x
        );
    }

    inline double dot(vec3 v1, vec3 v2) {
        return (
            v1.x*v2.x + v1.y*v2.y + v1.z*v2.z
        );
    }

    inline double squared_length(vec3 v) {
        return (v.x*v.x + v.y*v.y + v.z*v.z);
    }

    inline double squared_distance(vec3 v, vec3 w) {
        double dx = w.x-v.x;
        double dy = w.y-v.y;
        double dz = w.z-v.z;
        return (dx*dx+dy*dy+dz*dz);
    }

    inline double length(vec3 v) {
        return ::sqrt(squared_length(v));
    }

    inline vec3 normalize(vec3 v) {
        double s = 1.0/length(v);
        return make_vec3(
            s*v.x, s*v.y, s*v.z
        );
    }

    inline vec4 make_vec4(
        double x, double y, double z, double w
    ) {
        vec4 result;
        result.x = x;
        result.y = y;
        result.z = z;
        result.w = w;
        return result;
    }

    inline double dot(vec4 v1, vec4 v2) {
        return (
            v1.x*v2.x + v1.y*v2.y +
            v1.z*v2.z + v1.w*v2.w
        );
    }

    inline double squared_length(vec4 v) {
        return (
            v.x*v.x + v.y*v.y +
            v.z*v.z + v.w*v.w
        );
    }

    inline double length(vec4 v) {
        return ::sqrt(squared_length(v));
    }

    inline double squared_point_plane_distance(VBW::vec3 p, VBW::vec4 P) {
        double result = P.x*p.x + P.y*p.y + P.z*p.z + P.w;
        result = (result*result) / (P.x*P.x + P.y*P.y + P.z*P.z);
        return result;
    }

    enum {
        CONFLICT_MASK  = 32768, 
        MARKED_MASK    = 16384, 
        END_OF_LIST    = 16383, 
        VERTEX_AT_INFINITY = 0  
    };


    typedef unsigned char uchar;

    typedef unsigned short ushort;

    struct Triangle {
        ushort i;
        ushort j;
        ushort k;
        ushort operator[](unsigned int index) const {
            vbw_assert(index < 3);
            return (&i)[index];
        }
        ushort& operator[](unsigned int index) {
            vbw_assert(index < 3);
            return (&i)[index];
        }
    };

    inline Triangle make_triangle(
        ushort i, ushort j, ushort k
    ) {
        Triangle result;
        result.i = i;
        result.j = j;
        result.k = k;
        return result;
    }

    struct TriangleWithFlags : public Triangle {
        ushort flags;
    };

    inline TriangleWithFlags make_triangle_with_flags(
        ushort i, ushort j, ushort k, ushort f
    ) {
        TriangleWithFlags result;
        result.i = i;
        result.j = j;
        result.k = k;
        result.flags = f;
        return result;
    }




    inline double det2x2(
        double a11, double a12,
        double a21, double a22
    ) {
        return a11*a22 - a12*a21;
    }

    inline double det3x3(
        double a11, double a12, double a13,
        double a21, double a22, double a23,
        double a31, double a32, double a33
    ) {
        return
            a11*det2x2(a22,a23,a32,a33)
            -a21*det2x2(a12,a13,a32,a33)
            +a31*det2x2(a12,a13,a22,a23);
    }

    inline double det4x4(
        double a11, double a12, double a13, double a14,
        double a21, double a22, double a23, double a24,
        double a31, double a32, double a33, double a34,
        double a41, double a42, double a43, double a44
    ) {
        double m12 = a21*a12 - a11*a22;
        double m13 = a31*a12 - a11*a32;
        double m14 = a41*a12 - a11*a42;
        double m23 = a31*a22 - a21*a32;
        double m24 = a41*a22 - a21*a42;
        double m34 = a41*a32 - a31*a42;

        double m123 = m23*a13 - m13*a23 + m12*a33;
        double m124 = m24*a13 - m14*a23 + m12*a43;
        double m134 = m34*a13 - m14*a33 + m13*a43;
        double m234 = m34*a23 - m24*a33 + m23*a43;

        return (m234*a14 - m134*a24 + m124*a34 - m123*a44);
    }



    enum ConvexCellFlag {
        None        = 0, 
        WithVGlobal = 1, 
        WithTFlags  = 2  
    };

    typedef index_t ConvexCellFlags;

    class GEOGRAM_API ConvexCell {
    public:

    ConvexCell(ConvexCellFlags flags = None);

#ifndef STANDALONE_CONVEX_CELL
    void use_exact_predicates(bool x) {
        use_exact_predicates_ = x;
    }
#endif

    bool has_vglobal() const {
        return has_vglobal_;
    }

    bool has_tflags() const {
        return has_tflags_;
    }

    void create_vglobal() {
        if(!has_vglobal()) {
            has_vglobal_ = true;
            vglobal_.assign(max_v(), global_index_t(-1));
        }
    }

    void clear();

    void init_with_box(
        double xmin, double ymin, double zmin,
        double xmax, double ymax, double zmax
    );

    void init_with_tet(
        vec4 P0, vec4 P1, vec4 P2, vec4 P3
    );

    void init_with_tet(
        vec4 P0, vec4 P1, vec4 P2, vec4 P3,
        global_index_t P0_global_index,
        global_index_t P1_global_index,
        global_index_t P2_global_index,
        global_index_t P3_global_index
    );

    void save(const std::string& filename, double shrink=0.0) const;


    index_t save(
        std::ostream& out, global_index_t v_offset=1, double shrink=0.0,
        bool borders_only=false
    ) const;

#if !defined(STANDALONE_CONVEX_CELL) && !defined(GEOGRAM_PSM)
    void append_to_mesh(
        GEO::Mesh* mesh,
        double shrink=0.0, bool borders_only=false,
        GEO::Attribute<GEO::index_t>* facet_attr=nullptr
    ) const;

#endif

    void for_each_Voronoi_vertex(
        index_t v,
        std::function<void(index_t)> vertex
    );

    void clip_by_plane(vec4 P);

    void clip_by_plane(vec4 P, global_index_t j);


    void clip_by_plane(
        vec4 P, global_index_t P_global_index,
        std::function<bool(ushort,ushort)> triangle_conflict_predicate
    );

    void clip_by_plane_fast(vec4 P);

    void clip_by_plane_fast(vec4 P, global_index_t j);

    index_t nb_t() const {
        return nb_t_;
    }

    index_t nb_v() const {
        return nb_v_;
    }

    index_t create_vertex(vec4 P) {
        if(nb_v_ == max_v_) {
            grow_v();
        }
        plane_eqn_[nb_v_] = P;
        index_t result = nb_v_;
        ++nb_v_;
        return result;
    }

    index_t create_vertex(vec4 P, global_index_t v) {
        index_t result = create_vertex(P);
        vglobal_[nb_v()-1] = v;
        return result;
    }

    index_t create_triangle(index_t i, index_t j, index_t k) {
        vbw_assert(i < nb_v());
        vbw_assert(j < nb_v());
        vbw_assert(k < nb_v());
        return new_triangle(i,j,k);
    }

    void kill_vertex(index_t v);

    bool vertex_is_contributing(index_t v) const {
        if(!geometry_dirty_) {
            return v2t_[v] != END_OF_LIST;
        }
        index_t t = first_valid_;
        while(t != END_OF_LIST) {
            TriangleWithFlags T = get_triangle_and_flags(t);
            if(T.i == v || T.j == v || T.k == v) {
                return true;
            }
            t = index_t(T.flags);
        }
        return false;
    }

    index_t vertex_triangle(index_t v) const {
        geo_assert(!geometry_dirty_);
        return v2t_[v];
    }

    void compute_geometry();

    double facet_area(index_t v) const;

    double volume() const;

    vec3 barycenter() const;

    void compute_mg(double& m, vec3& mg) const ;


    double squared_radius(vec3 center) const;

    double squared_inner_radius(vec3 center) const;


    bool empty() const {
        return first_valid_ == END_OF_LIST;
    }

    global_index_t v_global_index(index_t lv) const {
        vbw_assert(has_vglobal_);
        vbw_assert(lv < nb_v());
        return vglobal_[lv];
    }

    void set_v_global_index(index_t lv, global_index_t v) {
        vbw_assert(has_vglobal_);
        vbw_assert(lv < nb_v());
        vglobal_[lv] = v;
    }

    bool has_v_global_index(global_index_t v) const;

    ushort first_triangle() const {
        return ushort(first_valid_);
    }

    ushort next_triangle(ushort t) const {
        return get_triangle_flags(t);
    }

    vec3 triangle_point(ushort t) const {
        if(geometry_dirty_) {
            vec4 result = compute_triangle_point(t);
            vbw_assert(result.w != 0.0);
            return make_vec3(
                result.x/result.w, result.y/result.w, result.z/result.w
            );
        }
        return triangle_point_[t];
    }

    global_index_t triangle_v_global_index(ushort t, index_t llv) const {
        Triangle T = get_triangle(t);
        ushort lv = ushort((llv==0)*T.i + (llv==1)*T.j + (llv==2)*T.k);
        return v_global_index(lv);
    }

    index_t triangle_v_local_index(ushort t, index_t llv) const {
        Triangle T = get_triangle(t);
        return index_t((llv==0)*T.i + (llv==1)*T.j + (llv==2)*T.k);
    }

    bool triangle_is_user_marked(ushort t) {
        vbw_assert(has_tflags_);
        vbw_assert(t < max_t_);
        return (tflags_[t] != 0);
    }

    void triangle_user_mark(ushort t) {
        vbw_assert(has_tflags_);
        vbw_assert(t < max_t_);
        tflags_[t] = 1;
    }

    void triangle_user_unmark(ushort t) {
        vbw_assert(has_tflags_);
        vbw_assert(t < max_t_);
        tflags_[t] = 0;
    }

    bool cell_has_conflict(const vec4& P) {
        for(
            ushort t = first_triangle();
            t!=END_OF_LIST; t=next_triangle(t)
        ) {
            TriangleWithFlags T = get_triangle_and_flags(t);
            if(triangle_is_in_conflict(T,P)) {
                return true;
            }
        }
        return false;
    }

    bool cell_is_totally_in_conflict(const vec4& P) {
        for(
            ushort t = first_triangle();
            t!=END_OF_LIST; t=next_triangle(t)
        ) {
            TriangleWithFlags T = get_triangle_and_flags(t);
            if(!triangle_is_in_conflict(T,P)) {
                return false;
            }
        }
        return true;
    }

    index_t triangle_adjacent(index_t t, index_t le) const {
        vbw_assert(t < max_t());
        vbw_assert(le < 3);
        return t_adj_[t][le];
    }


    void set_triangle_adjacent(index_t t1, index_t le, index_t t2) {
        vbw_assert(t1 < max_t());
        vbw_assert(le < 3);
        vbw_assert(t2 < max_t());
        t_adj_[t1][le] = VBW::ushort(t2);
    }



    index_t triangle_vertex(index_t t, index_t lv) const {
        vbw_assert(t < max_t());
        vbw_assert(lv < 3);
        return t_[t][lv];
    }


    index_t triangle_find_vertex(index_t t, index_t v) const {
        vbw_assert(t < max_t());
        Triangle T = get_triangle(t);
        index_t result = index_t((T.j == v) + 2*(T.k == v));
        vbw_assert(triangle_vertex(t,result) == v);
        return result;
    }

    index_t triangle_find_adjacent(index_t t1, index_t t2) const {
        vbw_assert(t1 < max_t());
        vbw_assert(t2 < max_t());
        Triangle T = t_adj_[t1];
        index_t result = index_t((T.j == t2) + 2*(T.k == t2));
        vbw_assert(triangle_adjacent(t1,result) == t2);
        return result;
    }

    bool triangle_is_infinite(index_t t) const {
        vbw_assert(t < max_t());
        Triangle T = get_triangle(t);
        return (
            T.i == VERTEX_AT_INFINITY ||
            T.j == VERTEX_AT_INFINITY ||
            T.k == VERTEX_AT_INFINITY
        );
    }

    vec4 vertex_plane(index_t v) const {
        vbw_assert(v < max_v());
        return plane_eqn_[v];
    }

    vec3 vertex_plane_normal(index_t v) const {
        vbw_assert(v != VERTEX_AT_INFINITY);
        vbw_assert(v < max_v());
        return make_vec3(
            plane_eqn_[v].x,
            plane_eqn_[v].y,
            plane_eqn_[v].z
        );
    }

    bool triangle_is_marked_as_conflict(index_t t) const {
        vbw_assert(t < max_t());
        return (get_triangle_flags(t) & ushort(CONFLICT_MASK)) != 0;
    }

    bool triangle_is_in_conflict(
        TriangleWithFlags T, const vec4& eqn
    ) const;

    index_t new_triangle(index_t i, index_t j, index_t k) {
        index_t result = first_free_;
        if(result == END_OF_LIST) {
            result = nb_t_;
            ++nb_t_;
            if(nb_t_ > max_t()) {
                grow_t();
            }
        } else {
            first_free_ = index_t(
                get_triangle_flags(first_free_) & ~ushort(CONFLICT_MASK)
            );
        }
        vbw_assert(result < max_t());
        t_[result] = make_triangle_with_flags(
            ushort(i), ushort(j), ushort(k), ushort(first_valid_)
        );
        first_valid_ = result;
        if(has_tflags_) {
            tflags_[result] = 0;
        }
        return result;
    }

    index_t new_triangle(
        index_t i, index_t j, index_t k,
        index_t adj0, index_t adj1, index_t adj2
    ) {
        index_t result = new_triangle(i, j, k);
        t_adj_[result] = make_triangle(
            ushort(adj0), ushort(adj1), ushort(adj2)
        );
        return result;
    }

    vec4 compute_triangle_point(index_t t) const;

    Triangle get_triangle(index_t t) const {
        vbw_assert(t < max_t());
        return t_[t];
    }

    ushort get_triangle_flags(index_t t) const {
        vbw_assert(t < max_t());
        return t_[t].flags;
    }

    void set_triangle_flags(index_t t, ushort flags) {
        vbw_assert(t < max_t());
        t_[t].flags = flags;
    }

    TriangleWithFlags get_triangle_and_flags(index_t t) const {
        vbw_assert(t < max_t());
        return t_[t];
    }

    bool triangle_is_marked_as_conflict(index_t t) {
        vbw_assert(t < max_t());
        ushort flg = get_triangle_flags(t);
        return ((flg & ushort(CONFLICT_MASK)) != 0);
    }

    index_t max_t() const {
        return max_t_;
    }

    index_t max_v() const {
        return max_v_;
    }

    void grow_t();

    void grow_v();


    void swap(ConvexCell& other) {
        std::swap(max_t_,other.max_t_);
        std::swap(max_v_,other.max_v_);
        std::swap(t_,other.t_);
        std::swap(t_adj_,other.t_adj_);
        std::swap(plane_eqn_,other.plane_eqn_);
        std::swap(nb_t_,other.nb_t_);
        std::swap(nb_v_,other.nb_v_);
        std::swap(first_free_,other.first_free_);
        std::swap(first_valid_,other.first_valid_);
        std::swap(geometry_dirty_,other.geometry_dirty_);
        std::swap(triangle_point_,other.triangle_point_);
        std::swap(v2t_,other.v2t_);
        std::swap(v2e_,other.v2e_);
        std::swap(vglobal_,other.vglobal_);
        std::swap(has_vglobal_,other.has_vglobal_);
        std::swap(tflags_,other.tflags_);
        std::swap(has_tflags_,other.has_tflags_);
#ifndef STANDALONE_CONVEX_CELL
        std::swap(use_exact_predicates_,other.use_exact_predicates_);
#endif
    }

    vec3& stored_triangle_point(ushort t) {
        return triangle_point_[t];
    }

    protected:

    void connect_triangles();


    void triangulate_conflict_zone(
        index_t lv, index_t conflict_head, index_t conflict_tail
    );

    void set_vertex_plane(index_t v, vec4 P) {
        vbw_assert(v < max_v());
        plane_eqn_[v] = P;
        geometry_dirty_ = true;
    }


    private:

    
    index_t max_t_;

    
    index_t max_v_;

    
    vector<TriangleWithFlags> t_;

    
    vector<Triangle> t_adj_;

    vector<vec4> plane_eqn_;

    
    index_t nb_t_;

    
    index_t nb_v_;

    
    index_t first_free_;

    
    index_t first_valid_;

    bool geometry_dirty_;

    vector<vec3> triangle_point_;

    vector<ushort> v2t_;

    vector<uchar> v2e_;

    vector<global_index_t> vglobal_;

    bool has_vglobal_;

    vector<uchar> tflags_;

    bool has_tflags_;

#ifndef STANDALONE_CONVEX_CELL
    bool use_exact_predicates_;
#endif

    friend class GEO::PeriodicDelaunay3d;
    };
}

namespace GEO {
    using VBW::ConvexCell;
}

#endif

/******* extracted from ../basic/algorithm.h *******/

#ifndef GEOGRAM_BASIC_ALGORITHM
#define GEOGRAM_BASIC_ALGORITHM


#if defined(GEO_OS_LINUX) && defined(GEO_OPENMP)
#if (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 4) && !defined(GEO_OS_ANDROID)
#include <parallel/algorithm>
#define GEO_USE_GCC_PARALLEL_STL
#endif
#elif defined(GEO_OS_WINDOWS)
#if (_MSC_VER >= 1700)
#include <ppl.h>
#define GEO_USE_MSVC_PARALLEL_STL
#endif
#endif

#include <algorithm>
#include <random>


namespace GEO {

    bool GEOGRAM_API uses_parallel_algorithm();

    template <typename ITERATOR>
    inline void sort(
        const ITERATOR& begin, const ITERATOR& end
    ) {
        if(uses_parallel_algorithm()) {
#if defined(GEO_USE_GCC_PARALLEL_STL)
            __gnu_parallel::sort(begin, end);
#elif defined(GEO_USE_MSVC_PARALLEL_STL)
            concurrency::parallel_sort(begin, end);
#else
            std::sort(begin, end);
#endif
        } else {
            std::sort(begin, end);
        }
    }

    template <typename ITERATOR, typename CMP>
    inline void sort(
        const ITERATOR& begin, const ITERATOR& end, const CMP& cmp
    ) {
        if(uses_parallel_algorithm()) {
#if defined(GEO_USE_GCC_PARALLEL_STL)
            __gnu_parallel::sort(begin, end, cmp);
#elif defined(GEO_USE_MSVC_PARALLEL_STL)
            concurrency::parallel_sort(begin, end, cmp);
#else
            std::sort(begin, end, cmp);
#endif
        } else {
            std::sort(begin, end, cmp);
        }
    }


    template <typename VECTOR> inline void sort_unique(VECTOR& v) {
        std::sort(v.begin(), v.end());
        // Note that std::unique leaves a 'queue' of duplicated elements
        // at the end of the vector, and returns an iterator that
        // indicates where to stop.
        v.erase(
            std::unique(v.begin(), v.end()), v.end()
        );
    }

    template <typename ITERATOR> inline void sort_3(ITERATOR items) {
        if (items[0]> items[1]) {
            std::swap(items[0], items[1]);
        }
        if (items[1]> items[2]) {
            std::swap(items[1], items[2]);
        }
        if (items[0]> items[1]) {
            std::swap(items[0], items[1]);
        }
    }

    template <typename ITERATOR> inline void sort_4(ITERATOR items) {
        if (items[1] < items[0]) {
            std::swap(items[0], items[1]);
        }
        if (items[3] < items[2]) {
            std::swap(items[2], items[3]);
        }
        if (items[2] < items[0]) {
            std::swap(items[0], items[2]);
            std::swap(items[1], items[3]);
        }
        if (items[2] < items[1]) {
            std::swap(items[1], items[2]);
        }
        if (items[3] < items[2]) {
            std::swap(items[2], items[3]);
        }
    }

    template <typename ITERATOR>
    inline void random_shuffle(
        const ITERATOR& begin, const ITERATOR& end
    ) {
	std::random_device rng;
	std::mt19937 urng(rng());
	std::shuffle(begin, end, urng);
    }

}

#endif

/******* extracted from ../mesh/index.h *******/

#ifndef GEOGRAM_MESH_INDEX
#define GEOGRAM_MESH_INDEX

#include <iostream>


namespace GEO {

    

    template <class IndexType>
    struct basic_bindex {

        IndexType indices[2];

        enum KeepOrderType {
            
            KEEP_ORDER
        };

        basic_bindex() {
        }

        basic_bindex(
            IndexType i,
            IndexType j
        ) {
            if(i < j) {
                indices[0] = i;
                indices[1] = j;
            } else {
                indices[0] = j;
                indices[1] = i;
            }
        }

        basic_bindex(
            IndexType i,
            IndexType j,
            KeepOrderType order
        ) {
            geo_argused(order);
            indices[0] = i;
            indices[1] = j;
        }

        bool operator< (const basic_bindex<IndexType>& rhs) const {
            if(indices[0] < rhs.indices[0]) {
                return true;
            }
            if(indices[0] > rhs.indices[0]) {
                return false;
            }
            if(indices[1] < rhs.indices[1]) {
                return true;
            }
            return false;
        }

        bool operator== (const basic_bindex<IndexType>& rhs) const {
            return
                (indices[0] == rhs.indices[0]) &&
                (indices[1] == rhs.indices[1]);
        }

        bool operator!= (const basic_bindex<IndexType>& rhs) const {
            return
                (indices[0] != rhs.indices[0]) ||
                (indices[1] != rhs.indices[1]);
        }

        basic_bindex(const basic_bindex<IndexType>& rhs) = default;

        basic_bindex<IndexType>& operator= (
            const basic_bindex<IndexType>& rhs
        ) = default;

        static basic_bindex inverse(const basic_bindex<IndexType>& b) {
            return basic_bindex(b.indices[1], b.indices[0], KEEP_ORDER);
        }
    };

    typedef basic_bindex<index_t> bindex;

    typedef basic_bindex<signed_index_t> signed_bindex;

    template <class IndexType>
    inline std::ostream& operator<< (
        std::ostream& out, const basic_bindex<IndexType>& B
    ) {
        return out << B.indices[0] << " " << B.indices[1];
    }

    

    template <class IndexType>
    struct basic_trindex {

        IndexType indices[3];

        enum KeepOrderType {
            
            KEEP_ORDER
        };

        basic_trindex() {
        }

        basic_trindex(
            IndexType i,
            IndexType j,
            IndexType k
        ) {
            indices[0] = i;
            indices[1] = j;
            indices[2] = k;
            GEO::sort_3(indices);
        }

        basic_trindex(
            IndexType i,
            IndexType j,
            IndexType k,
            KeepOrderType order
        ) {
            geo_argused(order);
            indices[0] = i;
            indices[1] = j;
            indices[2] = k;
        }

        bool operator< (const basic_trindex<IndexType>& rhs) const {
            for(index_t i = 0; i < 3; i++) {
                if(indices[i] < rhs.indices[i]) {
                    return true;
                }
                if(indices[i] > rhs.indices[i]) {
                    return false;
                }
            }
            return false;
        }

        bool operator== (const basic_trindex<IndexType>& rhs) const {
            return
                (indices[0] == rhs.indices[0]) &&
                (indices[1] == rhs.indices[1]) &&
                (indices[2] == rhs.indices[2]);
        }

        bool operator!= (const basic_trindex<IndexType>& rhs) const {
            return
                (indices[0] != rhs.indices[0]) ||
                (indices[1] != rhs.indices[1]) ||
                (indices[2] != rhs.indices[2]);
        }

        basic_trindex(const basic_trindex<IndexType>& rhs) = default;

        basic_trindex<IndexType>& operator= (
            const basic_trindex<IndexType>& rhs
        ) = default;

        static bool same_orientation(
            const basic_trindex<IndexType>& t,
            IndexType i, IndexType j, IndexType k
        ) {
            return
                (t.indices[0] == i && t.indices[1] == j && t.indices[2] == k) ||
                (t.indices[1] == i && t.indices[2] == j && t.indices[0] == k) ||
                (t.indices[2] == i && t.indices[0] == j && t.indices[1] == k);
        }

        static bool same_orientation(
            const basic_trindex<IndexType>& t1,
            const basic_trindex<IndexType>& t2
        ) {
            return same_orientation(
                t1, t2.indices[0], t2.indices[1], t2.indices[2]
            );
        }

        static basic_trindex inverse(const basic_trindex<IndexType>& t) {
            return basic_trindex(
                t.indices[2], t.indices[1], t.indices[0], KEEP_ORDER
            );
        }
    };

    typedef basic_trindex<index_t> trindex;

    typedef basic_trindex<signed_index_t> signed_trindex;

    template <class IndexType>
    inline std::ostream& operator<< (
        std::ostream& out, const basic_trindex<IndexType>& T
    ) {
        return out
            << T.indices[0] << " " << T.indices[1] << " " << T.indices[2];
    }

    

    template <class IndexType>
    struct basic_quadindex {
        IndexType indices[4];

        enum KeepOrderType {
            
            KEEP_ORDER
        };

        basic_quadindex() {
        }

        basic_quadindex(
            IndexType i,
            IndexType j,
            IndexType k,
            IndexType l
        ) {
            indices[0] = i;
            indices[1] = j;
            indices[2] = k;
            indices[3] = l;
            GEO::sort_4(indices);
        }

        basic_quadindex(
            IndexType i,
            IndexType j,
            IndexType k,
            IndexType l,
            KeepOrderType order
        ) {
            geo_argused(order);
            indices[0] = i;
            indices[1] = j;
            indices[2] = k;
            indices[3] = l;
        }

        bool operator< (const basic_quadindex<IndexType>& rhs) const {
            for(index_t i = 0; i < 4; i++) {
                if(indices[i] < rhs.indices[i]) {
                    return true;
                }
                if(indices[i] > rhs.indices[i]) {
                    return false;
                }
            }
            return false;
        }

        bool operator== (const basic_quadindex<IndexType>& rhs) const {
            return
                (indices[0] == rhs.indices[0]) &&
                (indices[1] == rhs.indices[1]) &&
                (indices[2] == rhs.indices[2]) &&
                (indices[3] == rhs.indices[3]);
        }

        bool operator!= (const basic_quadindex<IndexType>& rhs) const {
            return
                (indices[0] != rhs.indices[0]) ||
                (indices[1] != rhs.indices[1]) ||
                (indices[2] != rhs.indices[2]) ||
                (indices[3] != rhs.indices[3]);
        }

        basic_quadindex(const basic_quadindex<IndexType>& rhs) = default;

        basic_quadindex<IndexType>& operator= (
            const basic_quadindex<IndexType>& rhs
        ) = default;
    };

    typedef basic_quadindex<index_t> quadindex;

    typedef basic_quadindex<signed_index_t> signed_quadindex;

    template <class IndexType>
    inline std::ostream& operator<< (
        std::ostream& out, const basic_quadindex<IndexType>& Q
    ) {
        return out
            << Q.indices[0] << " " << Q.indices[1] << " "
            << Q.indices[2] << " " << Q.indices[3];
    }

    
}

#endif

/******* extracted from delaunay.h *******/

#ifndef GEOGRAM_DELAUNAY_DELAUNAY
#define GEOGRAM_DELAUNAY_DELAUNAY

#include <stdexcept>


namespace GEO {

    class Mesh;

    

    class GEOGRAM_API Delaunay : public Counted {
    public:
        struct InvalidDimension : std::logic_error {
            InvalidDimension(
                coord_index_t dimension,
                const char* name,
                const char* expected
            );

            const char* what() const GEO_NOEXCEPT override;
        };


        struct InvalidInput : std::logic_error {

            InvalidInput(int error_code_in);

            InvalidInput(const InvalidInput& rhs);

            ~InvalidInput() GEO_NOEXCEPT override;

            const char* what() const GEO_NOEXCEPT override;

            int error_code;

            vector<index_t> invalid_facets;
        };

        static Delaunay* create(
            coord_index_t dim, const std::string& name = "default"
        );


        static void initialize();

        coord_index_t dimension() const {
            return dimension_;
        }

        index_t cell_size() const {
            return cell_size_;
        }

        virtual void set_vertices(index_t nb_vertices, const double* vertices);

        void set_reorder(bool x) {
            do_reorder_ = x;
        }

        virtual void set_BRIO_levels(const vector<index_t>& levels);

        const double* vertices_ptr() const {
            return vertices_;
        }

        const double* vertex_ptr(index_t i) const {
            geo_debug_assert(i < nb_vertices());
            return vertices_ + vertex_stride_ * i;
        }

        index_t nb_vertices() const {
            return nb_vertices_;
        }

        virtual bool supports_constraints() const;

        virtual void set_constraints(const Mesh* mesh) {
            geo_assert(supports_constraints());
            constraints_ = mesh;
        }

        void set_refine(bool x) {
            refine_ = x;
        }

        bool get_refine() const {
            return refine_;
        }

        void set_quality(double qual) {
            quality_ = qual;
        }

        const Mesh* constraints() const {
            return constraints_;
        }

        index_t nb_cells() const {
            return nb_cells_;
        }

        index_t nb_finite_cells() const {
            geo_debug_assert(keeps_infinite());
            return nb_finite_cells_;
        }

        const index_t* cell_to_v() const {
            return cell_to_v_;
        }

        const index_t* cell_to_cell() const {
            return cell_to_cell_;
        }

        virtual index_t nearest_vertex(const double* p) const;

        index_t cell_vertex(index_t c, index_t lv) const {
            geo_debug_assert(c < nb_cells());
            geo_debug_assert(lv < cell_size());
            return cell_to_v_[c * cell_v_stride_ + lv];
        }

        index_t cell_adjacent(index_t c, index_t lf) const {
            geo_debug_assert(c < nb_cells());
            geo_debug_assert(lf < cell_size());
            return cell_to_cell_[c * cell_neigh_stride_ + lf];
        }

        bool cell_is_infinite(index_t c) const;

        bool cell_is_finite(index_t c) const {
            return !cell_is_infinite(c);
        }

        index_t index(index_t c, index_t v) const {
            geo_debug_assert(c < nb_cells());
            geo_debug_assert(v == NO_INDEX || v < nb_vertices());
            for(index_t iv = 0; iv < cell_size(); iv++) {
                if(cell_vertex(c, iv) == v) {
                    return iv;
                }
            }
            geo_assert_not_reached;
        }

        index_t adjacent_index(index_t c1, index_t c2) const {
            geo_debug_assert(c1 < nb_cells());
            geo_debug_assert(c2 < nb_cells());
            for(index_t f = 0; f < cell_size(); f++) {
                if(cell_adjacent(c1, f) == c2) {
                    return f;
                }
            }
            geo_assert_not_reached;
        }

        index_t vertex_cell(index_t v) const {
            geo_debug_assert(v < nb_vertices());
            geo_debug_assert(v < v_to_cell_.size());
            return v_to_cell_[v];
        }


        index_t next_around_vertex(index_t c, index_t lv) const {
            geo_debug_assert(c < nb_cells());
            geo_debug_assert(lv < cell_size());
            return cicl_[cell_size() * c + lv];
        }

        void get_neighbors(index_t v, vector<index_t>& neighbors) const {
            geo_debug_assert(v < nb_vertices());
            if(store_neighbors_) {
                neighbors_.get_array(v, neighbors);
            } else {
                get_neighbors_internal(v, neighbors);
            }
        }

        void save_histogram(std::ostream& out) const;

        bool stores_neighbors() const {
            return store_neighbors_;
        }

        void set_stores_neighbors(bool x) {
            store_neighbors_ = x;
            if(store_neighbors_) {
                set_stores_cicl(true);
            }
        }

        bool stores_cicl() const {
            return store_cicl_;
        }

        void set_stores_cicl(bool x) {
            store_cicl_ = x;
        }


        bool keeps_infinite() const {
            return keep_infinite_;
        }

        void set_keeps_infinite(bool x) {
            keep_infinite_ = x;
        }

        bool thread_safe() const {
            return neighbors_.thread_safe();
        }

        void set_thread_safe(bool x) {
            neighbors_.set_thread_safe(x);
        }

        void set_default_nb_neighbors(index_t x) {
            default_nb_neighbors_ = x;
        }

        index_t default_nb_neighbors() const {
            return default_nb_neighbors_;
        }

        void clear_neighbors() {
            neighbors_.clear();
        }

        void set_keep_regions(bool x) {
            keep_regions_ = x;
        }

        virtual index_t region(index_t t) const;


    protected:
        Delaunay(coord_index_t dimension);

        ~Delaunay() override;

        virtual void get_neighbors_internal(
            index_t v, vector<index_t>& neighbors
        ) const;

        virtual void set_arrays(
            index_t nb_cells,
            const index_t* cell_to_v, const index_t* cell_to_cell
        );

        virtual void update_v_to_cell();

        virtual void update_cicl();

        virtual void update_neighbors();

        void set_next_around_vertex(
            index_t c1, index_t lv, index_t c2
        ) {
            geo_debug_assert(c1 < nb_cells());
            geo_debug_assert(c2 < nb_cells());
            geo_debug_assert(lv < cell_size());
            cicl_[cell_size() * c1 + lv] = c2;
        }

    public:
        virtual void store_neighbors_CB(index_t i);

    protected:
        void set_dimension(coord_index_t dim) {
            dimension_ = dim;
            vertex_stride_ = dim;
            cell_size_ = index_t(dim) + 1;
            cell_v_stride_ = cell_size_;
            cell_neigh_stride_ = cell_size_;
        }

        coord_index_t dimension_;
        index_t vertex_stride_;
        index_t cell_size_;
        index_t cell_v_stride_;
        index_t cell_neigh_stride_;

        const double* vertices_;
        index_t nb_vertices_;
        index_t nb_cells_;
        const index_t* cell_to_v_;
        const index_t* cell_to_cell_;
        vector<index_t> v_to_cell_;
        vector<index_t> cicl_;
        bool is_locked_;
        PackedArrays neighbors_;
        bool store_neighbors_;
        index_t default_nb_neighbors_;

        bool do_reorder_;

        const Mesh* constraints_;

        bool refine_;
        double quality_;

        bool store_cicl_;

        bool keep_infinite_;

        index_t nb_finite_cells_;

        bool keep_regions_;
    };

    typedef SmartPointer<Delaunay> Delaunay_var;

    typedef Factory1<Delaunay, coord_index_t> DelaunayFactory;

#define geo_register_Delaunay_creator(type, name)               \
    geo_register_creator(GEO::DelaunayFactory, type, name)
}

#endif

/******* extracted from delaunay_2d.h *******/

#ifndef GEOGRAM_DELAUNAY_DELAUNAY_2D
#define GEOGRAM_DELAUNAY_DELAUNAY_2D


#include <stack>


namespace GEO {

    class GEOGRAM_API Delaunay2d : public Delaunay {
    public:
        Delaunay2d(coord_index_t dimension = 2);

        void set_vertices(index_t nb_vertices, const double* vertices) override;

        index_t nearest_vertex(const double* p) const override;

        bool has_empty_cells() const {
            return has_empty_cells_;
        }

        void abort_if_empty_cell(bool x) {
            abort_if_empty_cell_ = x;
        }

    protected:

        static constexpr index_t NO_TRIANGLE = NO_INDEX;

        bool create_first_triangle(index_t& iv0, index_t& iv1, index_t& iv2);

        index_t locate(
            const double* p, index_t hint = NO_TRIANGLE,
            bool thread_safe = false,
            Sign* orient = nullptr
        ) const;

        index_t locate_inexact(
	    const double* p, index_t hint, index_t max_iter
        ) const;

        index_t insert(index_t v, index_t hint = NO_TRIANGLE);

        void find_conflict_zone(
            index_t v,
            index_t t, const Sign* orient,
            index_t& t_bndry, index_t& e_bndry,
            index_t& first, index_t& last
        );

        void find_conflict_zone_iterative(
            const double* p, index_t t,
            index_t& t_bndry, index_t& e_bndry,
            index_t& first, index_t& last
        );

        index_t stellate_conflict_zone(
            index_t v,
            index_t t_bndry, index_t e_bndry
        );

        

        index_t max_t() const {
            return cell_to_v_store_.size() / 3;
        }


        static constexpr index_t NOT_IN_LIST  = ~index_t(0);

        static constexpr index_t NOT_IN_LIST_BIT =
	    index_t(1) << (sizeof(index_t)*8-1) ;

        static constexpr index_t END_OF_LIST = ~NOT_IN_LIST_BIT;

        bool triangle_is_in_list(index_t t) const {
            geo_debug_assert(t < max_t());
            return (cell_next_[t] & NOT_IN_LIST_BIT) == 0;
        }

        index_t triangle_next(index_t t) const {
            geo_debug_assert(t < max_t());
            geo_debug_assert(triangle_is_in_list(t));
            return cell_next_[t];
        }

        void add_triangle_to_list(index_t t, index_t& first, index_t& last) {
            geo_debug_assert(t < max_t());
            geo_debug_assert(!triangle_is_in_list(t));
            if(last == END_OF_LIST) {
                geo_debug_assert(first == END_OF_LIST);
                first = last = t;
                cell_next_[t] = END_OF_LIST;
            } else {
                cell_next_[t] = first;
                first = t;
            }
        }

        void remove_triangle_from_list(index_t t) {
            geo_debug_assert(t < max_t());
            geo_debug_assert(triangle_is_in_list(t));
            cell_next_[t] = NOT_IN_LIST;
        }

        static constexpr index_t VERTEX_AT_INFINITY = NO_INDEX;

        bool triangle_is_finite(index_t t) const {
            return
                (cell_to_v_store_[3 * t]     != NO_INDEX) &&
		(cell_to_v_store_[3 * t + 1] != NO_INDEX) &&
		(cell_to_v_store_[3 * t + 2] != NO_INDEX) ;
        }

        bool triangle_is_real(index_t t) const {
            return !triangle_is_free(t) && triangle_is_finite(t);
        }

        bool triangle_is_virtual(index_t t) const {
            return
                !triangle_is_free(t) && (
                    cell_to_v_store_[3 * t] == VERTEX_AT_INFINITY ||
                    cell_to_v_store_[3 * t + 1] == VERTEX_AT_INFINITY ||
                    cell_to_v_store_[3 * t + 2] == VERTEX_AT_INFINITY
                );
        }

        bool triangle_is_free(index_t t) const {
            return triangle_is_in_list(t);
        }

        index_t new_triangle() {
            index_t result;
            if(first_free_ == END_OF_LIST) {
                cell_to_v_store_.resize(
		    cell_to_v_store_.size() + 3, NO_INDEX
		);
                cell_to_cell_store_.resize(
		    cell_to_cell_store_.size() + 3, NO_INDEX
		);
                // index_t(NOT_IN_LIST) is necessary, else with
                // NOT_IN_LIST alone the compiler tries to generate a
                // reference to NOT_IN_LIST resulting in a link error.
                cell_next_.push_back(index_t(NOT_IN_LIST));
                result = max_t() - 1;
            } else {
                result = first_free_;
                first_free_ = triangle_next(first_free_);
                remove_triangle_from_list(result);
            }

            cell_to_cell_store_[3 * result] = NO_INDEX;
            cell_to_cell_store_[3 * result + 1] = NO_INDEX;
            cell_to_cell_store_[3 * result + 2] = NO_INDEX;

            return result;
        }

        index_t new_triangle(index_t v1, index_t v2, index_t v3) {
            index_t result = new_triangle();
            cell_to_v_store_[3 * result] = v1;
            cell_to_v_store_[3 * result + 1] = v2;
            cell_to_v_store_[3 * result + 2] = v3;
            return result;
        }

        void set_triangle_mark_stamp(index_t stamp) {
            cur_stamp_ = (stamp | NOT_IN_LIST_BIT);
        }

        bool triangle_is_marked(index_t t) const {
            return cell_next_[t] == cur_stamp_;
        }

        void mark_triangle(index_t t) {
            cell_next_[t] = cur_stamp_;
        }

        

        static index_t triangle_edge_vertex(index_t e, index_t v) {
            geo_debug_assert(e < 3);
            geo_debug_assert(v < 2);
            return index_t(triangle_edge_vertex_[e][v]);
        }

        index_t triangle_vertex(index_t t, index_t lv) const {
            geo_debug_assert(t < max_t());
            geo_debug_assert(lv < 3);
            return cell_to_v_store_[3 * t + lv];
        }

        index_t find_triangle_vertex(index_t t, index_t v) const {
            geo_debug_assert(t < max_t());
            //   Find local index of v in triangle t vertices.
            const index_t* T = &(cell_to_v_store_[3 * t]);
            return find_3(T,v);
        }


        index_t finite_triangle_vertex(index_t t, index_t lv) const {
            geo_debug_assert(t < max_t());
            geo_debug_assert(lv < 3);
            geo_debug_assert(cell_to_v_store_[3 * t + lv] != NO_INDEX);
            return cell_to_v_store_[3 * t + lv];
        }

        void set_triangle_vertex(index_t t, index_t lv, index_t v) {
            geo_debug_assert(t < max_t());
            geo_debug_assert(lv < 3);
            cell_to_v_store_[3 * t + lv] = v;
        }

        index_t triangle_adjacent(index_t t, index_t le) const {
            geo_debug_assert(t < max_t());
            geo_debug_assert(le < 3);
            index_t result = cell_to_cell_store_[3 * t + le];
            return result;
        }

        void set_triangle_adjacent(index_t t1, index_t le1, index_t t2) {
            geo_debug_assert(t1 < max_t());
            geo_debug_assert(t2 < max_t());
            geo_debug_assert(le1 < 3);
            geo_debug_assert(t1 != t2);
            cell_to_cell_store_[3 * t1 + le1] = t2;
        }

        index_t find_triangle_adjacent(index_t t1, index_t t2) const {
            geo_debug_assert(t1 < max_t());
            geo_debug_assert(t2 < max_t());
            geo_debug_assert(t1 != t2);

            // Find local index of t2 in triangle t1 adajcent tets.
            const index_t* T = &(cell_to_cell_store_[3 * t1]);
            index_t result = find_3(T,t2);

            // Sanity check: make sure that t1 is adjacent to t2
            // only once!
            geo_debug_assert(triangle_adjacent(t1,(result+1)%3) != t2);
            geo_debug_assert(triangle_adjacent(t1,(result+2)%3) != t2);
            return result;
        }

        void set_triangle(
            index_t t,
            index_t v0, index_t v1, index_t v2,
            index_t a0, index_t a1, index_t a2
        ) {
            geo_debug_assert(t < max_t());
            cell_to_v_store_[3 * t] = v0;
            cell_to_v_store_[3 * t + 1] = v1;
            cell_to_v_store_[3 * t + 2] = v2;
            cell_to_cell_store_[3 * t] = a0;
            cell_to_cell_store_[3 * t + 1] = a1;
            cell_to_cell_store_[3 * t + 2] = a2;
        }

        

        bool triangle_is_conflict(index_t t, const double* p) const {

            // Lookup triangle vertices
            const double* pv[3];
            for(index_t i=0; i<3; ++i) {
                index_t v = triangle_vertex(t,i);
                pv[i] = (v == NO_INDEX) ? nullptr : vertex_ptr(v);
            }

            // Check for virtual triangles (then in_circle()
            // is replaced with orient2d())
            for(index_t le = 0; le < 3; ++le) {

                if(pv[le] == nullptr) {

                    // Facet of a virtual triangle opposite to
                    // infinite vertex corresponds to
                    // the triangle on the convex hull of the points.
                    // Orientation is obtained by replacing vertex lf
                    // with p.
                    pv[le] = p;
                    Sign sign = PCK::orient_2d(pv[0],pv[1],pv[2]);

                    if(sign > 0) {
                        return true;
                    }

                    if(sign < 0) {
                        return false;
                    }

                    // If sign is zero, we check the real triangle
                    // adjacent to the facet on the convex hull.
                    geo_debug_assert(triangle_adjacent(t, le) != NO_INDEX);
                    index_t t2 = triangle_adjacent(t, le);
                    geo_debug_assert(!triangle_is_virtual(t2));

                    //  If t2 is already chained in the conflict list,
                    // then it is conflict
                    if(triangle_is_in_list(t2)) {
                        return true;
                    }

                    //  If t2 is marked, then it is not in conflict.
                    if(triangle_is_marked(t2)) {
                        return false;
                    }

                    return triangle_is_conflict(t2, p);
                }
            }

            //   If the triangle is a finite one, it is in conflict
            // if its circumscribed sphere contains the point (this is
            // the standard case).

            if(weighted_) {
                double h0 = heights_[finite_triangle_vertex(t, 0)];
                double h1 = heights_[finite_triangle_vertex(t, 1)];
                double h2 = heights_[finite_triangle_vertex(t, 2)];
                index_t pindex = index_t(
                    (p - vertex_ptr(0)) / int(vertex_stride_)
                );
                double h = heights_[pindex];
                return (PCK::orient_2dlifted_SOS(
                            pv[0],pv[1],pv[2],p,h0,h1,h2,h
                        ) > 0) ;
            }

            return (PCK::in_circle_2d_SOS(pv[0], pv[1], pv[2], p) > 0);
        }

    protected:

        static inline index_t find_3(const index_t* T, index_t v) {
            // The following expression is 10% faster than using
            // if() statements. This uses the C++ norm, that
            // ensures that the 'true' boolean value converted to
            // an int is always 1. With most compilers, this avoids
            // generating branching instructions.
            // Thank to Laurent Alonso for this idea.
            index_t result = index_t( (T[1] == v) | ((T[2] == v) * 2) );
            // Sanity check, important if it was T[0], not explicitly
            // tested (detects input that does not meet the precondition).
            geo_debug_assert(T[result] == v);
            return result;
        }

        ~Delaunay2d() override;

        void show_triangle(index_t t) const;

        void show_triangle_adjacent(index_t t, index_t le) const;

        void show_list(index_t first, const std::string& list_name) const;

        void check_combinatorics(bool verbose = false) const;

        void check_geometry(bool verbose = false) const;

    private:
        vector<index_t> cell_to_v_store_;
        vector<index_t> cell_to_cell_store_;
        vector<index_t> cell_next_;
        vector<index_t> reorder_;
        index_t cur_stamp_; // used for marking
        index_t first_free_;
        bool weighted_;
        vector<double> heights_; // only used in weighted mode

        bool debug_mode_;

        bool verbose_debug_mode_;

        bool benchmark_mode_;

        static char triangle_edge_vertex_[3][2];

        std::stack<index_t> S_;

        bool has_empty_cells_;

        bool abort_if_empty_cell_;
    };

    

    class GEOGRAM_API RegularWeightedDelaunay2d : public Delaunay2d {
    public:
        RegularWeightedDelaunay2d(coord_index_t dimension = 3);

    protected:
        ~RegularWeightedDelaunay2d() override;
    };
}

#endif

/******* extracted from periodic.h *******/

#ifndef GEOGRAM_DELAUNAY_PERIODIC
#define GEOGRAM_DELAUNAY_PERIODIC



namespace GEO {

    class GEOGRAM_API Periodic {
    public:

    index_t nb_vertices_non_periodic() const {
	return nb_vertices_non_periodic_;
    }

    index_t periodic_vertex_instance(index_t pv) const {
        geo_debug_assert(pv < nb_vertices_non_periodic_ * 27);
        return pv / nb_vertices_non_periodic_;
    }

    index_t periodic_vertex_real(index_t pv) const {
        geo_debug_assert(pv < nb_vertices_non_periodic_ * 27);
        return pv % nb_vertices_non_periodic_;
    }

    index_t make_periodic_vertex(index_t real, index_t instance) const {
        geo_debug_assert(real < nb_vertices_non_periodic_);
        geo_debug_assert(instance < 27);
        return real + nb_vertices_non_periodic_*instance;
    }

    static index_t T_to_instance(int Tx, int Ty, int Tz) {
        geo_debug_assert(Tx >= -1 && Tx <= 1);
        geo_debug_assert(Ty >= -1 && Ty <= 1);
        geo_debug_assert(Tz >= -1 && Tz <= 1);
        int i = (Tz+1) + 3*(Ty+1) + 9*(Tx+1);
        geo_debug_assert(i >= 0 && i < 27);
        return index_t(reorder_instances[i]);
    }

    void periodic_vertex_get_T(index_t pv, int& Tx, int& Ty, int& Tz) const {
        geo_debug_assert(pv < nb_vertices_non_periodic_ * 27);
        index_t instance = periodic_vertex_instance(pv);
        Tx = translation[instance][0];
        Ty = translation[instance][1];
        Tz = translation[instance][2];
    }

    void periodic_vertex_set_T(index_t& pv, int Tx, int Ty, int Tz) const {
        geo_debug_assert(pv < nb_vertices_non_periodic_ * 27);
        geo_debug_assert(Tx >= -1 && Tx <= 1);
        geo_debug_assert(Ty >= -1 && Ty <= 1);
        geo_debug_assert(Tz >= -1 && Tz <= 1);
        pv = make_periodic_vertex(
            periodic_vertex_real(pv), T_to_instance(Tx, Ty, Tz)
        );
    }

    std::string periodic_vertex_to_string(index_t v) const {
        return
            String::to_string(periodic_vertex_real(v)) + ":" +
            String::to_string(periodic_vertex_instance(v)) ;
    }

    std::string binary_to_string(Numeric::uint32 m) const {
        std::string s(32,' ');
        for(index_t i=0; i<32; ++i) {
            s[i] = ((m & (1u << (31u-i))) != 0) ? '1' : '0';
        }
        return s;
    }

    static int translation[27][3];

    static int reorder_instances[27];

    static bool instance_is_positive[27];

    index_t nb_vertices_non_periodic_;
    };

}

#endif

/******* extracted from delaunay_sync.h *******/

#ifndef DELAUNAY_SYNC_H
#define DELAUNAY_SYNC_H

#include <atomic>

// In GARGANTUA mode (64-bit indices), we also enable
// more than 127 concurrent threads (16-bits cell status,
// that contain owner thread id).
#ifdef GARGANTUA
#define GEO_CONNECTION_MACHINE
#endif


namespace GEO {

    class CellStatusArray {
    public:
#ifdef GEO_CONNECTION_MACHINE
	// For machines that can run more than 127 concurrent threads
        typedef uint16_t thread_index_t;
        typedef uint16_t cell_status_t;
        static constexpr cell_status_t FREE_CELL     = 32767;
        static constexpr cell_status_t THREAD_MASK   = 32767;
        static constexpr cell_status_t CONFLICT_MASK = 32768;
#else
        typedef uint8_t thread_index_t;
        typedef uint8_t cell_status_t;
        static constexpr cell_status_t FREE_CELL     = 127;
        static constexpr cell_status_t THREAD_MASK   = 127;
        static constexpr cell_status_t CONFLICT_MASK = 128;
#endif

	static constexpr index_t MAX_THREADS = index_t(THREAD_MASK)-1;

        CellStatusArray() : cell_status_(nullptr), size_(0), capacity_(0) {
        }

        CellStatusArray(index_t size_in) :
            cell_status_(nullptr), size_(0), capacity_(0) {
            resize(size_in,size_in);
        }

        ~CellStatusArray() {
            clear();
        }

        CellStatusArray(const CellStatusArray& rhs) = delete;

        CellStatusArray& operator=(const CellStatusArray& rhs) = delete;

        cell_status_t acquire_cell(index_t cell, cell_status_t status) {
            geo_debug_assert(cell < size_);
            cell_status_t expected = FREE_CELL;
            // strong: acquire_cell is not used in a spinlock-like
            // spinning loop (so we do not want to have "false negatives")
            cell_status_[cell].compare_exchange_strong(
                expected,status,
                std::memory_order_acquire,std::memory_order_acquire
            ); // this one could probably be relaxed ----^
            // if compare_exchange was not sucessful, expected contains
            // the current stored value.
            return (expected & THREAD_MASK);
        }

        void release_cell(index_t cell) {
            geo_debug_assert(cell < size_);
            cell_status_[cell].store(FREE_CELL, std::memory_order_release);
        }

        cell_status_t cell_thread(index_t cell) const {
            geo_debug_assert(cell < size_);
            return (
                cell_status_[cell].load(std::memory_order_relaxed) &
                THREAD_MASK
            );
        }

        bool cell_is_marked_as_conflict(index_t cell) const {
            geo_debug_assert(cell < size_);
            return(
                (
                    cell_status_[cell].load(std::memory_order_relaxed) &
                    CONFLICT_MASK
                ) != 0
            );
        }

        void mark_cell_as_conflict(index_t cell) {
	    // memory_order_relaxed because this function is always called from
            // a thread that previously acquired the cell.
	    cell_status_[cell].fetch_or(
		CONFLICT_MASK, std::memory_order_relaxed
	    );
        }

        void set_cell_status(index_t cell, cell_status_t status) {
            geo_debug_assert(cell < size_);
            cell_status_[cell].store(status, std::memory_order_relaxed);
        }

        void resize(index_t size_in, index_t capacity_in) {
            geo_debug_assert(capacity_in >= size_in);
            geo_debug_assert(!Process::is_running_threads());
            if(capacity_in > capacity_) {
                capacity_ = capacity_in;
                std::atomic<cell_status_t>* old_cell_status = cell_status_;
                cell_status_ = new std::atomic<cell_status_t>[capacity_];
                for(index_t i=0; i<capacity_; ++i) {
                    cell_status_t val = (i < size_) ?
                        old_cell_status[i].load(std::memory_order_relaxed) :
                        FREE_CELL;
                    std::atomic_init(&cell_status_[i],val);
                }
                delete[] old_cell_status;
            }
            size_ = size_in;
#ifdef __cpp_lib_atomic_is_always_lock_free
            static_assert(std::atomic<cell_status_t>::is_always_lock_free);
#else
            geo_debug_assert(size_ == 0 || cell_status_[0].is_lock_free());
#endif
        }

        void resize(index_t size_in) {
            resize(size_in, size_in);
        }

        void reserve(index_t new_capacity) {
            if(new_capacity > capacity_) {
                resize(size_, new_capacity);
            }
        }

        void grow() {
            if(size_+1 >= capacity_) {
                resize(size_+1, std::max(capacity_*2,size_+1));
            } else {
                resize(size_+1, capacity_);
            }
        }

        index_t size() const {
            return size_;
        }

        void clear() {
            geo_debug_assert(!Process::is_running_threads());
#ifdef GEO_DEBUG
            for(index_t i=0; i<size_; ++i) {
                geo_debug_assert(cell_thread(i) == FREE_CELL);
            }
#endif
            delete[] cell_status_;
	    cell_status_ = nullptr;
            size_ = 0;
            capacity_ = 0;
        }

    private:
        std::atomic<cell_status_t>* cell_status_;
        index_t size_;
        index_t capacity_;
    };
}

#endif

/******* extracted from periodic_delaunay_3d.h *******/

#ifndef PERIODIC_DELAUNAY_TRIANGULATION_3D
#define PERIODIC_DELAUNAY_TRIANGULATION_3D

#include <stack>


namespace GEO {

    class PeriodicDelaunay3dThread;


    class GEOGRAM_API PeriodicDelaunay3d : public Delaunay, public Periodic {
    public:

        struct IncidentTetrahedra {
            std::stack<index_t> S;
            vector<index_t> incident_tets_set;

            void clear_incident_tets() {
                incident_tets_set.resize(0);
            }

            void add_incident_tet(index_t t) {
                incident_tets_set.push_back(t);
            }

            bool has_incident_tet(index_t t) const {
                for(index_t i=0; i<incident_tets_set.size(); ++i) {
                    if(incident_tets_set[i] == t) {
                        return true;
                    }
                }
                return false;
            }

            vector<index_t>::const_iterator begin() const {
                return incident_tets_set.begin();
            }

            vector<index_t>::const_iterator end() const {
                return incident_tets_set.end();
            }
        };

        PeriodicDelaunay3d(bool periodic, double period=1.0);

        PeriodicDelaunay3d(const vec3& period);

        void set_vertices(
            index_t nb_vertices, const double* vertices
        ) override;

        void set_weights(const double* weights);

        void compute();

        void use_exact_predicates_for_convex_cell(bool x) {
            convex_cell_exact_predicates_ = x;
        }

        vec3 vertex(index_t v) const {
            if(!periodic_) {
                geo_debug_assert(v < nb_vertices());
                return vec3(vertices_ + 3*v);
            }
            index_t instance = v/nb_vertices_non_periodic_;
            v = v%nb_vertices_non_periodic_;
            vec3 result(vertices_ + 3*v);
            result.x += double(translation[instance][0]) * period_.x;
            result.y += double(translation[instance][1]) * period_.y;
            result.z += double(translation[instance][2]) * period_.z;
            return result;
        }

        double weight(index_t v) const {
            if(weights_ == nullptr) {
                return 0.0;
            }
            return periodic_ ? weights_[periodic_vertex_real(v)] : weights_[v] ;
        }

        index_t nearest_vertex(const double* p) const override;

        void set_BRIO_levels(const vector<index_t>& levels) override;

        void get_incident_tets(index_t v, IncidentTetrahedra& W) const;

        void copy_Laguerre_cell_from_Delaunay(
            GEO::index_t i,
            ConvexCell& C,
            IncidentTetrahedra& W
        ) const;

        void copy_Laguerre_cell_from_Delaunay(
            GEO::index_t i,
            ConvexCell& C
        ) const {
            IncidentTetrahedra W;
            copy_Laguerre_cell_from_Delaunay(i,C,W);
        }

        bool has_empty_cells() const {
            return has_empty_cells_;
        }

        void save_cells(const std::string& basename, bool clipped);

    protected:

        GEO::index_t copy_Laguerre_cell_facet_from_Delaunay(
            GEO::index_t i,
            const GEO::vec3& Pi,
            double wi,
            double Pi_len2,
            GEO::index_t t,
            ConvexCell& C,
            IncidentTetrahedra& W
        ) const;


        index_t compress(bool shrink=true);

        void update_v_to_cell() override;

        void update_cicl() override;

        void handle_periodic_boundaries();


	void handle_periodic_boundaries_phase_I();

	bool Laguerre_vertex_is_in_conflict_with_plane(index_t t, vec4 P) const;

	void handle_periodic_boundaries_phase_II();

	void insert_vertices(const char* phase, index_t b, index_t e);

	void insert_vertices_with_BRIO(
	    const char* phase, const vector<index_t>& levels
	);

        void check_volume();

        PeriodicDelaunay3dThread* thread(index_t t) {
            geo_debug_assert(t < threads_.size());
            return reinterpret_cast<PeriodicDelaunay3dThread*>(
                threads_[t].get()
            );
        }

        index_t nb_threads() const {
            return index_t(threads_.size());
        }

	void check_max_t();

    private:
        friend class PeriodicDelaunay3dThread;

        bool periodic_;
        vec3 period_;

        const double* weights_;
        vector<index_t> cell_to_v_store_;
        vector<index_t> cell_to_cell_store_;
        vector<index_t> cell_next_;

        CellStatusArray cell_status_;

        ThreadGroup threads_;
        vector<index_t> reorder_;
        vector<index_t> levels_;

        bool debug_mode_;

        bool verbose_debug_mode_;

        bool benchmark_mode_;

        bool detailed_benchmark_mode_;

        vector<Numeric::uint32> vertex_instances_;

        bool update_periodic_v_to_cell_;
        vector<index_t> periodic_v_to_cell_rowptr_;
        vector<index_t> periodic_v_to_cell_data_;

        bool has_empty_cells_;

        index_t nb_reallocations_;

        bool convex_cell_exact_predicates_;

	struct Stats {

	    Stats();

	    void reset();

	    std::string to_string() {
		return raw_ ? to_string_raw() : to_string_pretty();
	    }

	    std::string to_string_raw() const;
	    std::string to_string_pretty() const;

	    bool raw_;

	    double  total_t_;

	    double  phase_0_t_;

	    double  phase_I_t_;
	    double  phase_I_classify_t_;
	    index_t phase_I_nb_inside_;
	    index_t phase_I_nb_cross_;
	    index_t phase_I_nb_outside_;
	    double  phase_I_insert_t_;
	    index_t phase_I_insert_nb_;

	    double  phase_II_t_;
	    double  phase_II_classify_t_;
	    double  phase_II_insert_t_;
	    index_t phase_II_insert_nb_;
	} stats_;

	friend class LaguerreDiagramOmegaSimple3d;
    };


}

#endif

/******* extracted from CDT_2d.h *******/

#ifndef GEOGRAM_DELAUNAY_CDT_2D
#define GEOGRAM_DELAUNAY_CDT_2D

#include <functional>


namespace GEO {

    struct CDT2d_ConstraintWalker;

    class GEOGRAM_API CDTBase2d {
    public:
    CDTBase2d();

    virtual ~CDTBase2d();

    virtual void clear();

    void insert_constraint(index_t i, index_t j);

    void remove_external_triangles(bool remove_internal_holes=false);

    void set_delaunay(bool delaunay) {
        delaunay_ = delaunay;
    }

    index_t nT() const {
        return T_.size()/3;
    }

    index_t nv() const {
        return nv_;
    }

    index_t ncnstr() const {
        return ncnstr_;
    }

    index_t Tv(index_t t, index_t lv) const {
        geo_debug_assert(t<nT());
        geo_debug_assert(lv<3);
        return T_[3*t+lv];
    }

    index_t Tv_find(index_t t, index_t v) const {
        geo_debug_assert(t<nT());
        geo_debug_assert(v<nv());
        return find_3(T_.data()+3*t, v);
    }

    index_t Tadj(index_t t, index_t le) const {
        geo_debug_assert(t<nT());
        geo_debug_assert(le<3);
        return Tadj_[3*t+le];
    }

    index_t Tadj_find(index_t t1, index_t t2) const {
        geo_debug_assert(t1<nT());
        geo_debug_assert(t2<nT());
        return find_3(Tadj_.data()+3*t1, t2);
    }

    index_t vT(index_t v) const {
        geo_debug_assert(v < nv());
        return v2T_[v];
    }


    index_t Tedge_cnstr_first(index_t t, index_t le) const {
        geo_debug_assert(t < nT());
        geo_debug_assert(le < 3);
        return Tecnstr_first_[3*t+le];
    }

    index_t edge_cnstr_next(index_t ecit) const {
        return ecnstr_next_[ecit];
    }

    index_t edge_cnstr(index_t ecit) const {
        return ecnstr_val_[ecit];
    }

    index_t Tedge_cnstr_nb(index_t t, index_t le) const {
        index_t result = 0;
        for(
            index_t ecit = Tedge_cnstr_first(t,le);
            ecit != NO_INDEX;
            ecit = edge_cnstr_next(ecit)
        ) {
            ++result;
        }
        return result;
    }


    virtual void save(const std::string& filename) const = 0;

    bool Tedge_is_Delaunay(index_t t, index_t le) const;

    protected:
    virtual void begin_insert_transaction();
    virtual void commit_insert_transaction();
    virtual void rollback_insert_transaction();

    index_t insert(index_t v, index_t hint = NO_INDEX);

    void create_enclosing_triangle(index_t v1, index_t v2, index_t v3);

    void create_enclosing_quad(
        index_t v1, index_t v2, index_t v3, index_t v4
    );

    void Tset_flag(index_t t, index_t flag) {
        geo_debug_assert(t < nT());
        geo_debug_assert(flag < 8);
        Tflags_[t] |= Numeric::uint8(1u << flag);
    }

    void Treset_flag(index_t t, index_t flag) {
        geo_debug_assert(t < nT());
        geo_debug_assert(flag < 8);
        Tflags_[t] &= Numeric::uint8(~(1u << flag));
    }

    bool Tflag_is_set(index_t t, index_t flag) {
        geo_debug_assert(t < nT());
        geo_debug_assert(flag < 8);
        return ((Tflags_[t] & (1u << flag)) != 0);
    }

    enum {
        DLIST_S_ID=0,
        DLIST_Q_ID=1,
        DLIST_N_ID=2,
        DLIST_NB=3
    };

    enum {
        T_MARKED_FLAG  = DLIST_NB,
        T_VISITED_FLAG = DLIST_NB+1
    };

    bool Tis_in_list(index_t t) const {
        return (
            (Tflags_[t] &
             Numeric::uint8((1 << DLIST_NB)-1)
            ) != 0
        );
    }

    struct DList {
        DList(CDTBase2d& cdt, index_t list_id) :
            cdt_(cdt), list_id_(list_id),
            back_(NO_INDEX), front_(NO_INDEX) {
            geo_debug_assert(list_id < DLIST_NB);
        }

        DList(CDTBase2d& cdt) :
            cdt_(cdt), list_id_(NO_INDEX),
            back_(NO_INDEX), front_(NO_INDEX) {
        }

        void initialize(index_t list_id) {
            geo_debug_assert(!initialized());
            geo_debug_assert(list_id < DLIST_NB);
            list_id_ = list_id;
        }

        bool initialized() const {
            return (list_id_ != NO_INDEX);
        }

        ~DList() {
            if(initialized()) {
                clear();
            }
        }

        bool empty() const {
            geo_debug_assert(initialized());
            geo_debug_assert(
                (back_==NO_INDEX)==(front_==NO_INDEX)
            );
            return (back_==NO_INDEX);
        }

        bool contains(index_t t) const {
            geo_debug_assert(initialized());
            return cdt_.Tflag_is_set(t, list_id_);
        }

        index_t front() const {
            geo_debug_assert(initialized());
            return front_;
        }

        index_t back() const {
            geo_debug_assert(initialized());
            return back_;
        }

        index_t next(index_t t) const {
            geo_debug_assert(initialized());
            geo_debug_assert(contains(t));
            return cdt_.Tnext_[t];
        }

        index_t prev(index_t t) const {
            geo_debug_assert(initialized());
            geo_debug_assert(contains(t));
            return cdt_.Tprev_[t];
        }

        void clear() {
            for(index_t t=front_; t!=NO_INDEX; t = cdt_.Tnext_[t]) {
                cdt_.Treset_flag(t,list_id_);
            }
            back_ = NO_INDEX;
            front_ = NO_INDEX;
        }

        index_t size() const {
            geo_debug_assert(initialized());
            index_t result = 0;
            for(index_t t=front(); t!=NO_INDEX; t = next(t)) {
                ++result;
            }
            return result;
        }

        void push_back(index_t t) {
            geo_debug_assert(initialized());
            geo_debug_assert(!cdt_.Tis_in_list(t));
            cdt_.Tset_flag(t,list_id_);
            if(empty()) {
                back_ = t;
                front_ = t;
                cdt_.Tnext_[t] = NO_INDEX;
                cdt_.Tprev_[t] = NO_INDEX;
            } else {
                cdt_.Tnext_[t] = NO_INDEX;
                cdt_.Tnext_[back_] = t;
                cdt_.Tprev_[t] = back_;
                back_ = t;
            }
        }

        index_t pop_back() {
            geo_debug_assert(initialized());
            geo_debug_assert(!empty());
            index_t t = back_;
            back_ = cdt_.Tprev_[back_];
            if(back_ == NO_INDEX) {
                geo_debug_assert(front_ == t);
                front_ = NO_INDEX;
            } else {
                cdt_.Tnext_[back_] = NO_INDEX;
            }
            geo_debug_assert(contains(t));
            cdt_.Treset_flag(t,list_id_);
            return t;
        }

        void push_front(index_t t) {
            geo_debug_assert(initialized());
            geo_debug_assert(!cdt_.Tis_in_list(t));
            cdt_.Tset_flag(t,list_id_);
            if(empty()) {
                back_ = t;
                front_ = t;
                cdt_.Tnext_[t] = NO_INDEX;
                cdt_.Tprev_[t] = NO_INDEX;
            } else {
                cdt_.Tprev_[t] = NO_INDEX;
                cdt_.Tprev_[front_] = t;
                cdt_.Tnext_[t] = front_;
                front_ = t;
            }
        }

        index_t pop_front() {
            geo_debug_assert(initialized());
            geo_debug_assert(!empty());
            index_t t = front_;
            front_ = cdt_.Tnext_[front_];
            if(front_ == NO_INDEX) {
                geo_debug_assert(back_ == t);
                back_ = NO_INDEX;
            } else {
                cdt_.Tprev_[front_] = NO_INDEX;
            }
            geo_debug_assert(contains(t));
            cdt_.Treset_flag(t,list_id_);
            return t;
        }

        void remove(index_t t) {
            geo_debug_assert(initialized());
            if(t == front_) {
                pop_front();
            } else if(t == back_) {
                pop_back();
            } else {
                geo_debug_assert(contains(t));
                index_t t_prev = cdt_.Tprev_[t];
                index_t t_next = cdt_.Tnext_[t];
                cdt_.Tprev_[t_next] = t_prev;
                cdt_.Tnext_[t_prev] = t_next;
                cdt_.Treset_flag(t,list_id_);
            }
        }

        void show(std::ostream& out = std::cerr) const {
            switch(list_id_) {
            case DLIST_S_ID:
                out << "S";
                break;
            case DLIST_Q_ID:
                out << "Q";
                break;
            case DLIST_N_ID:
                out << "N";
                break;
            case NO_INDEX:
                out << "<uninitialized list>";
                break;
            default:
                out << "<unknown list id:" << list_id_ << ">";
                break;
            }
            out << "=";
            for(index_t t=front(); t!=NO_INDEX; t = next(t)) {
                out << t << ";";
            }
            out << std::endl;
        }

    private:
        CDTBase2d& cdt_;
        index_t list_id_;
        index_t back_;
        index_t front_;
    };

    void insert_vertex_in_edge(index_t v, index_t t, index_t le, DList& S);

    void insert_vertex_in_edge(index_t v, index_t t, index_t le) {
        DList S(*this);
        insert_vertex_in_edge(v,t,le,S);
    }

    void insert_vertex_in_triangle(index_t v, index_t t, DList& S);

    index_t find_intersected_edges(index_t i, index_t j, DList& Q);

    void walk_constraint_v(CDT2d_ConstraintWalker& W);

    void walk_constraint_t(CDT2d_ConstraintWalker& W, DList& Q);

    void constrain_edges(index_t i, index_t j, DList& Q, DList& N);

    void Delaunayize_vertex_neighbors(index_t from_v);

    void Delaunayize_vertex_neighbors(index_t v, DList& S);

    void Delaunayize_new_edges(DList& N);


    void Tset(
        index_t t,
        index_t v1,   index_t v2,   index_t v3,
        index_t adj1, index_t adj2, index_t adj3,
        index_t e1cnstr = NO_INDEX,
        index_t e2cnstr = NO_INDEX,
        index_t e3cnstr = NO_INDEX
    ) {
        geo_debug_assert(t < nT());
        geo_debug_assert(v1 < nv());
        geo_debug_assert(v2 < nv());
        geo_debug_assert(v3 < nv());
        geo_debug_assert(adj1 < nT() || adj1 == NO_INDEX);
        geo_debug_assert(adj2 < nT() || adj2 == NO_INDEX);
        geo_debug_assert(adj3 < nT() || adj3 == NO_INDEX);
        geo_debug_assert(v1 != v2);
        geo_debug_assert(v2 != v3);
        geo_debug_assert(v3 != v1);
        geo_debug_assert(adj1 != adj2 || adj1 == NO_INDEX);
        geo_debug_assert(adj2 != adj3 || adj2 == NO_INDEX);
        geo_debug_assert(adj3 != adj1 || adj3 == NO_INDEX);
        geo_debug_assert(orient2d(v1,v2,v3) != ZERO);
        T_[3*t  ]    = v1;
        T_[3*t+1]    = v2;
        T_[3*t+2]    = v3;
        Tadj_[3*t  ] = adj1;
        Tadj_[3*t+1] = adj2;
        Tadj_[3*t+2] = adj3;
        Tecnstr_first_[3*t]   = e1cnstr;
        Tecnstr_first_[3*t+1] = e2cnstr;
        Tecnstr_first_[3*t+2] = e3cnstr;
        v2T_[v1] = t;
        v2T_[v2] = t;
        v2T_[v3] = t;
    }

    void Trot(index_t t, index_t lv) {
        geo_debug_assert(t < nT());
        geo_debug_assert(lv < 3);
        if(lv != 0) {
            index_t i = 3*t+lv;
            index_t j = 3*t+((lv+1)%3);
            index_t k = 3*t+((lv+2)%3);
            Tset(
                t,
                T_[i], T_[j], T_[k],
                Tadj_[i], Tadj_[j], Tadj_[k],
                Tecnstr_first_[i], Tecnstr_first_[j], Tecnstr_first_[k]
            );
        }
    }

    void swap_edge(index_t t1, bool swap_t1_t2=false);

    void Tadj_set(index_t t, index_t le, index_t adj) {
        geo_debug_assert(t < nT());
        geo_debug_assert(adj < nT());
        geo_debug_assert(le < 3);
        Tadj_[3*t+le] = adj;
    }

    index_t Topp(index_t t, index_t e=0) const {
        index_t t2 = Tadj(t,e);
        if(t2 == NO_INDEX) {
            return NO_INDEX;
        }
        index_t e2 = Tadj_find(t2,t);
        return Tv(t2,e2);
    }

    void Tadj_back_connect(
        index_t t1, index_t le1, index_t prev_t2_adj_e2
    ) {
        geo_debug_assert(t1 < nT());
        geo_debug_assert(le1 < 3);
        index_t t2 = Tadj(t1,le1);
        if(t2 == NO_INDEX) {
            return;
        }
        index_t le2 = Tadj_find(t2,prev_t2_adj_e2);
        Tadj_set(t2,le2,t1);
        Tset_edge_cnstr_first(t1,le1,Tedge_cnstr_first(t2,le2));
    }

    index_t Tnew() {
        index_t t = nT();
        index_t nc = (t+1)*3; // new number of corners
        T_.resize(nc, NO_INDEX);
        Tadj_.resize(nc, NO_INDEX);
        Tecnstr_first_.resize(nc, NO_INDEX);
        Tflags_.resize(t+1,0);
        Tnext_.resize(t+1,NO_INDEX);
        Tprev_.resize(t+1,NO_INDEX);
        return t;
    }

    void Tset_edge_cnstr_first(
        index_t t, index_t le, index_t ecit
    ) {
        geo_debug_assert(t < nT());
        geo_debug_assert(le < 3);
        Tecnstr_first_[3*t+le] = ecit;
    }

    void Tadd_edge_cnstr(
        index_t t, index_t le, index_t cnstr_id
    ) {
        geo_debug_assert(t < nT());
        geo_debug_assert(le < 3);
        // Check whether the edge is already constrained with the
        // same constraint.
        // TODO (if possible): understand how this can happen and
        // remove this bloc of code that is not super elegant
        // (it seems to be when we arrive at j and coming from a vertex
        // traversed by the edge, both conditions make the constraint
        // added to the traversed edge).
        for(
            index_t ecit = Tedge_cnstr_first(t,le);
            ecit != NO_INDEX;
            ecit = edge_cnstr_next(ecit)
        ) {
            if(edge_cnstr(ecit) == cnstr_id) {
                return;
            }
        }
        ecnstr_val_.push_back(cnstr_id);
        ecnstr_next_.push_back(Tedge_cnstr_first(t,le));
        Tset_edge_cnstr_first(t,le, ecnstr_val_.size()-1);
    }

    void Tadd_edge_cnstr_with_neighbor(
        index_t t, index_t le, index_t cnstr_id
    ) {
        geo_debug_assert(t < nT());
        geo_debug_assert(le < 3);
#ifdef GEO_DEBUG
        index_t t_e_cnstr_first = Tedge_cnstr_first(t,le);
#endif
        Tadd_edge_cnstr(t, le, cnstr_id);
        index_t t2 = Tadj(t,le);
        if(t2 != NO_INDEX) {
            index_t le2 = Tadj_find(t2,t);
            // Sanity check: make sure the two edges always share the
            // same constraint list.
            geo_debug_assert(Tedge_cnstr_first(t2,le2) == t_e_cnstr_first);
            Tset_edge_cnstr_first(t2,le2,Tedge_cnstr_first(t,le));
        }
    }

    bool Tedge_is_constrained(index_t t, index_t le) const {
        return (Tedge_cnstr_first(t,le) != NO_INDEX);
    }

    void for_each_T_around_v(
        index_t v, std::function<bool(index_t t, index_t lv)> doit
    ) {
        index_t t = vT(v);
        index_t lv = NO_INDEX;
        do {
            lv = Tv_find(t,v);
            if(doit(t,lv)) {
                return;
            }
            t = Tadj(t, (lv+1)%3);
        } while(t != vT(v) && t != NO_INDEX);

        // We are done, this was an interior vertex
        if(t != NO_INDEX) {
            return;
        }

        // It was a vertex on the border, so we need
        // to traverse the triangle fan in the other
        // direction until we reach the border again
        t = vT(v);
        lv = Tv_find(t,v);
        t = Tadj(t, (lv+2)%3);
        while(t != NO_INDEX) {
            lv = Tv_find(t,v);
            if(doit(t,lv)) {
                return;
            }
            t = Tadj(t, (lv+2)%3);
        }
    }


    index_t locate(
        index_t v, index_t hint = NO_INDEX, Sign* orient = nullptr
    ) const;

    bool is_convex_quad(index_t t) const;

    virtual Sign orient2d(index_t i,index_t j,index_t k) const=0;

    virtual Sign incircle(index_t i,index_t j,index_t k,index_t l) const=0;

    virtual index_t create_intersection(
        index_t E1, index_t i, index_t j,
        index_t E2, index_t k, index_t l
    ) = 0;

    static inline index_t find_3(const index_t* T, index_t v) {
        // The following expression is 10% faster than using
        // if() statements. This uses the C++ norm, that
        // ensures that the 'true' boolean value converted to
        // an int is always 1. With most compilers, this avoids
        // generating branching instructions.
        // Thank to Laurent Alonso for this idea.
        index_t result = index_t( (T[1] == v) | ((T[2] == v) * 2) );
        // Sanity check, important if it was T[0], not explicitly
        // tested (detects input that does not meet the precondition).
        geo_debug_assert(T[result] == v);
        return result;
    }

    

    void remove_marked_triangles();

    

    void Tcheck(index_t t) const {
        if(t == NO_INDEX) {
            return;
        }
        for(index_t e=0; e<3; ++e) {
            geo_assert(Tv(t,e) != Tv(t,(e+1)%3));
            if(Tadj(t,e) == NO_INDEX) {
                continue;
            }
            geo_assert(Tadj(t,e) != Tadj(t,(e+1)%3));
            index_t t2 = Tadj(t,e);
            index_t e2 = Tadj_find(t2,t);
            geo_assert(Tadj(t2,e2) == t);
        }
    }

    void debug_Tcheck(index_t t) const {
#ifdef GEO_DEBUG
        Tcheck(t);
#else
        geo_argused(t);
#endif
    }

    void check_combinatorics() const {
        for(index_t t=0; t<nT(); ++t) {
            Tcheck(t);
        }
    }

    void debug_check_combinatorics() const {
#ifdef GEO_DEBUG
        check_combinatorics();
#endif
    }

    virtual void check_geometry() const;

    void debug_check_geometry() const {
#ifdef GEO_DEBUG
        check_geometry();
#endif
    }


    public:
    void check_consistency() const {
        check_combinatorics();
        check_geometry();
    }

    protected:
    void debug_check_consistency() const {
        debug_check_combinatorics();
        debug_check_geometry();
    }

    bool segment_segment_intersect(
        index_t u1, index_t u2, index_t v1, index_t v2
    ) const {
        if(orient2d(u1,u2,v1)*orient2d(u1,u2,v2) > 0) {
            return false;
        }
        return (orient2d(v1,v2,u1)*orient2d(v1,v2,u2) < 0);
    }

    bool segment_edge_intersect(
        index_t v1, index_t v2, index_t t, index_t le
    ) const {
        index_t u1 = Tv(t,(le + 1)%3);
        index_t u2 = Tv(t,(le + 2)%3);
        return segment_segment_intersect(u1,u2,v1,v2);
    }

    void check_edge_intersections(
        index_t v1, index_t v2, const DList& Q
    );

    typedef std::pair<index_t, index_t> Edge;

    index_t eT(Edge E) {
        index_t v1 = E.first;
        index_t v2 = E.second;
        index_t result = NO_INDEX;
        for_each_T_around_v(
            v1, [&](index_t t, index_t lv)->bool {
                if(Tv(t, (lv+1)%3) == v2) {
                    if(Tv(t, (lv+2)%3) != v1) {
                        Trot(t, (lv+2)%3);
                    }
                    result = t;
                    return true;
                } else if(Tv(t, (lv+1)%3) == v1) {
                    if(Tv(t, (lv+2)%3) != v2) {
                        Trot(t, (lv+2)%3);
                    }
                    result = t;
                    return true;
                }
                return false;
            }
        );
        geo_debug_assert(result != NO_INDEX);
        geo_debug_assert(
            (Tv(result,1) == v1 && Tv(result,2) == v2) ||
            (Tv(result,1) == v2 && Tv(result,2) == v1)
        );
        return result;
    }

    index_t locate_naive(
        index_t v, index_t hint = NO_INDEX, Sign* orient = nullptr
    ) const;

    void constrain_edges_naive(
        index_t i, index_t j, DList& Q, vector<Edge>& N
    );

    void Delaunayize_new_edges_naive(vector<Edge>& N);

    protected:
    index_t nv_;
    index_t ncnstr_;
    vector<index_t> T_;        
    vector<index_t> Tadj_;     
    vector<index_t> v2T_;      
    vector<uint8_t> Tflags_;   
    vector<index_t> Tecnstr_first_;  
    vector<index_t> ecnstr_val_;     
    vector<index_t> ecnstr_next_;    
    vector<index_t> Tnext_;    
    vector<index_t> Tprev_;    
    bool delaunay_;            
    Sign orient_012_;          
    bool exact_incircle_;      
    bool exact_intersections_; 
    };

    

    class GEOGRAM_API CDT2d: public CDTBase2d {
    public:

        CDT2d();

        ~CDT2d() override;

        void clear() override;

        void create_enclosing_triangle(
            const vec2& p1, const vec2& p2, const vec2& p3
        );

        void create_enclosing_quad(
            const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p4
        );


        void create_enclosing_rectangle(
            double x1, double y1, double x2, double y2
        ) {
            create_enclosing_quad(
                vec2(x1,y1),
                vec2(x2,y1),
                vec2(x2,y2),
                vec2(x1,y2)
            );
        }

        index_t insert(const vec2& p, index_t hint = NO_INDEX) {
            debug_check_consistency();
            point_.push_back(p);
            index_t v = CDTBase2d::insert(point_.size()-1, hint);
            // If inserted point already existed in
            // triangulation, then nv() did not increase
            if(point_.size() > nv()) {
                point_.pop_back();
            }
            debug_check_consistency();
            return v;
        }

        void insert(
            index_t nb_points, const double* points,
            index_t* indices = nullptr,
            bool remove_unreferenced_vertices = false
        );

        void save(const std::string& filename) const override;

        const vec2 point(index_t v) const {
            geo_debug_assert(v < nv());
            return point_[v];
        }

    protected:
        Sign orient2d(index_t i, index_t j, index_t k) const override;

        Sign incircle(index_t i,index_t j,index_t k,index_t l) const override;

        index_t create_intersection(
            index_t E1, index_t i, index_t j,
            index_t E2, index_t k, index_t l
        ) override;

    protected:
        vector<vec2> point_;
    };

    

    class GEOGRAM_API ExactCDT2d : public CDTBase2d {
    public:
        typedef exact::vec2h ExactPoint;

        ExactCDT2d();

        ~ExactCDT2d() override;

        void clear() override;

        index_t insert(
            const ExactPoint& p, index_t id=0, index_t hint = NO_INDEX
        );

        void insert_constraint(index_t v1, index_t v2, index_t operand_bits=0) {
            constraints_.push_back(bindex(v1,v2,bindex::KEEP_ORDER));
            cnstr_operand_bits_.push_back(operand_bits);
            CDTBase2d::insert_constraint(v1,v2);
        }

        void create_enclosing_triangle(
            const ExactPoint& p1, const ExactPoint& p2, const ExactPoint& p3
        );

        void create_enclosing_quad(
            const ExactPoint& p1, const ExactPoint& p2,
            const ExactPoint& p3, const ExactPoint& p4
        );

        void create_enclosing_rectangle(
            double x1, double y1, double x2, double y2
        ) {
            create_enclosing_quad(
                ExactPoint(vec2(x1,y1)),
                ExactPoint(vec2(x2,y1)),
                ExactPoint(vec2(x2,y2)),
                ExactPoint(vec2(x1,y2))
            );
        }

        const ExactPoint& point(index_t v) const {
            geo_debug_assert(v < nv());
            return point_[v];
        }

        index_t vertex_id(index_t v) const {
            geo_debug_assert(v < nv());
            return id_[v];
        }

        void set_vertex_id(index_t v, index_t id) {
            geo_debug_assert(v < nv());
            id_[v] = id;
        }

        void classify_triangles(
            const std::string& boolean_expression, bool mark_only=false
        );

        void save(const std::string& filename) const override;

    protected:

	void classify_triangles_union_cnstr_operand_bits_is_operand_id(
	    bool mark_only=false
	);

        void add_point(const ExactPoint& p, index_t id = NO_INDEX);
        void begin_insert_transaction() override;
        void commit_insert_transaction() override;
        void rollback_insert_transaction() override;

        Sign orient2d(index_t i, index_t j, index_t k) const override;

        Sign incircle(index_t i,index_t j,index_t k,index_t l) const override;

        index_t create_intersection(
            index_t E1, index_t i, index_t j,
            index_t E2, index_t k, index_t l
        ) override;

    protected:
        vector<ExactPoint> point_;
#ifndef GEOGRAM_USE_EXACT_NT
        vector<double> length_;
#endif
        vector<index_t> id_;
        vector<index_t> cnstr_operand_bits_;
        vector<index_t> facet_inclusion_bits_;
        mutable std::map<trindex, Sign> pred_cache_;
        bool use_pred_cache_insert_buffer_;
        mutable std::vector<std::pair<trindex, Sign>> pred_cache_insert_buffer_;
        vector<bindex> constraints_;
    };

    

}

#endif

/******* extracted from ../points/nn_search.h *******/

#ifndef GEOGRAM_POINTS_NN_SEARCH
#define GEOGRAM_POINTS_NN_SEARCH



namespace GEO {

    class GEOGRAM_API NearestNeighborSearch : public Counted {
    public:
        static NearestNeighborSearch* create(
            coord_index_t dimension, const std::string& name = "default"
        );

        virtual void set_points(index_t nb_points, const double* points);

        virtual bool stride_supported() const;

        virtual void set_points(
            index_t nb_points, const double* points, index_t stride
        );

        virtual void get_nearest_neighbors(
            index_t nb_neighbors,
            const double* query_point,
            index_t* neighbors,
            double* neighbors_sq_dist
        ) const = 0;


        struct KeepInitialValues {
        };

        virtual void get_nearest_neighbors(
            index_t nb_neighbors,
            const double* query_point,
            index_t* neighbors,
            double* neighbors_sq_dist,
            KeepInitialValues dummy
        ) const;

        virtual void get_nearest_neighbors(
            index_t nb_neighbors,
            index_t query_point,
            index_t* neighbors,
            double* neighbors_sq_dist
        ) const;

        index_t get_nearest_neighbor(const double* query_point) const {
            index_t result;
            double sq_dist;
            get_nearest_neighbors(1, query_point, &result, &sq_dist);
	    geo_assert(result < nb_points());
            return result;
        }

        coord_index_t dimension() const {
            return dimension_;
        }

        index_t nb_points() const {
            return nb_points_;
        }

        const double* point_ptr(index_t i) const {
            geo_debug_assert(i < nb_points());
            return points_ + i * stride_;
        }

        bool exact() const {
            return exact_;
        }

        virtual void set_exact(bool x);

    protected:
        NearestNeighborSearch(coord_index_t dimension);

        ~NearestNeighborSearch() override;

    protected:
        coord_index_t dimension_;
        index_t nb_points_;
        index_t stride_;
        const double* points_;
        bool exact_;
    };

    typedef SmartPointer<NearestNeighborSearch> NearestNeighborSearch_var;

    typedef Factory1<NearestNeighborSearch, coord_index_t>
    NearestNeighborSearchFactory;

#define geo_register_NearestNeighborSearch_creator(type, name)          \
    geo_register_creator(GEO::NearestNeighborSearchFactory, type, name)
}

#endif

/******* extracted from ../points/kd_tree.h *******/

#ifndef GEOGRAM_POINTS_KD_TREE
#define GEOGRAM_POINTS_KD_TREE

#include <algorithm>


namespace GEO {

    class GEOGRAM_API KdTree : public NearestNeighborSearch {
    public:
        KdTree(coord_index_t dim);

        
        void set_points(index_t nb_points, const double* points) override;

        
        bool stride_supported() const override;

        
        void set_points(
            index_t nb_points, const double* points, index_t stride
        ) override;

        
        void get_nearest_neighbors(
            index_t nb_neighbors,
            const double* query_point,
            index_t* neighbors,
            double* neighbors_sq_dist
        ) const override;

        
        void get_nearest_neighbors(
            index_t nb_neighbors,
            const double* query_point,
            index_t* neighbors,
            double* neighbors_sq_dist,
            KeepInitialValues
        ) const override;

        
        void get_nearest_neighbors(
            index_t nb_neighbors,
            index_t query_point,
            index_t* neighbors,
            double* neighbors_sq_dist
        ) const override;

        

        struct NearestNeighbors {

            NearestNeighbors(
                index_t nb_neighbors_in,
                index_t* user_neighbors_in,
                double* user_neighbors_sq_dist_in,
                index_t* work_neighbors_in,
                double* work_neighbors_sq_dist_in
            ) :
                nb_neighbors(0),
                nb_neighbors_max(nb_neighbors_in),
                neighbors(work_neighbors_in),
                neighbors_sq_dist(work_neighbors_sq_dist_in),
                user_neighbors(user_neighbors_in),
                user_neighbors_sq_dist(user_neighbors_sq_dist_in),
                nb_visited(0)
                {
                    // Yes, '<=' because we got space for n+1 neigbors
                    // in the work arrays.
                    for(index_t i = 0; i <= nb_neighbors; ++i) {
                        neighbors[i] = NO_INDEX;
                        neighbors_sq_dist[i] = Numeric::max_float64();
                    }
                }

            double furthest_neighbor_sq_dist() const {
                return
                    nb_neighbors == nb_neighbors_max ?
                    neighbors_sq_dist[nb_neighbors - 1] :
                    Numeric::max_float64()
                    ;
            }

            void insert(
                index_t neighbor, double sq_dist
            ) {
                geo_debug_assert(
                    sq_dist <= furthest_neighbor_sq_dist()
                );

                int i;
                for(i=int(nb_neighbors); i>0; --i) {
                    if(neighbors_sq_dist[i - 1] < sq_dist) {
                        break;
                    }
                    neighbors[i] = neighbors[i - 1];
                    neighbors_sq_dist[i] = neighbors_sq_dist[i - 1];
                }

                neighbors[i] = neighbor;
                neighbors_sq_dist[i] = sq_dist;

                if(nb_neighbors < nb_neighbors_max) {
                    ++nb_neighbors;
                }
            }

            void copy_from_user() {
                for(index_t i=0; i<nb_neighbors_max; ++i) {
                    neighbors[i] = user_neighbors[i];
                    neighbors_sq_dist[i] = user_neighbors_sq_dist[i];
                }
                neighbors[nb_neighbors_max] = NO_INDEX;
                neighbors_sq_dist[nb_neighbors_max] = Numeric::max_float64();
                nb_neighbors = nb_neighbors_max;
            }

            void copy_to_user() {
                for(index_t i=0; i<nb_neighbors_max; ++i) {
                    user_neighbors[i] = neighbors[i];
                    user_neighbors_sq_dist[i] = neighbors_sq_dist[i];
                }
            }

            
            index_t nb_neighbors;

            
            index_t nb_neighbors_max;

            index_t* neighbors;

            double* neighbors_sq_dist;

            index_t* user_neighbors;

            double* user_neighbors_sq_dist;

            size_t nb_visited;
        };

        virtual void get_nearest_neighbors_recursive(
            index_t node_index, index_t b, index_t e,
            double* bbox_min, double* bbox_max,
            double bbox_dist, const double* query_point,
            NearestNeighbors& neighbors
        ) const;

        void init_bbox_and_bbox_dist_for_traversal(
            double* bbox_min, double* bbox_max,
            double& box_dist, const double* query_point
        ) const;

        index_t root() const {
            return root_;
        }

    protected:
        static constexpr index_t MAX_LEAF_SIZE = 16;

        virtual index_t build_tree() = 0 ;

        virtual void get_node(
            index_t n, index_t b, index_t e,
            index_t& left_child, index_t& right_child,
            coord_index_t&  splitting_coord,
            index_t& m,
            double& splitting_val
        ) const = 0;



        virtual void get_nearest_neighbors_leaf(
            index_t node_index, index_t b, index_t e,
            const double* query_point,
            NearestNeighbors& neighbors
        ) const;

        void get_minmax(
            index_t b, index_t e, coord_index_t coord,
            double& minval, double& maxval
        ) const {
            minval = Numeric::max_float64();
            maxval = Numeric::min_float64();
            for(index_t i = b; i < e; ++i) {
                double val = point_ptr(point_index_[i])[coord];
                minval = std::min(minval, val);
                maxval = std::max(maxval, val);
            }
        }

        double spread(index_t b, index_t e, coord_index_t coord) const {
            double minval,maxval;
            get_minmax(b,e,coord,minval,maxval);
            return maxval - minval;
        }

        ~KdTree() override;

    protected:
        vector<index_t> point_index_;
        vector<double> bbox_min_;
        vector<double> bbox_max_;
        index_t root_;
    };

    

    class GEOGRAM_API BalancedKdTree : public KdTree {
    public:
        BalancedKdTree(coord_index_t dim);

    protected:
        ~BalancedKdTree() override;

        static index_t max_node_index(
            index_t node_id, index_t b, index_t e
        ) {
            if(e - b <= MAX_LEAF_SIZE) {
                return node_id;
            }
            index_t m = b + (e - b) / 2;
            return std::max(
                max_node_index(2 * node_id, b, m),
                max_node_index(2 * node_id + 1, m, e)
            );
        }

        coord_index_t best_splitting_coord(index_t b, index_t e);

        void create_kd_tree_recursive(
            index_t node_index, index_t b, index_t e
        ) {
            if(e - b <= MAX_LEAF_SIZE) {
                return;
            }
            index_t m = split_kd_node(node_index, b, e);
            create_kd_tree_recursive(2 * node_index, b, m);
            create_kd_tree_recursive(2 * node_index + 1, m, e);
        }

        index_t split_kd_node(
            index_t node_index, index_t b, index_t e
        );

        
        index_t build_tree() override;

        
        void get_node(
            index_t n, index_t b, index_t e,
            index_t& left_child, index_t& right_child,
            coord_index_t&  splitting_coord,
            index_t& m,
            double& splitting_val
        ) const override;

    protected:

        vector<coord_index_t> splitting_coord_;

        vector<double> splitting_val_;

        index_t m0_, m1_, m2_, m3_, m4_, m5_, m6_, m7_, m8_;
    };

    

    class GEOGRAM_API AdaptiveKdTree : public KdTree {
    public:
        AdaptiveKdTree(coord_index_t dim);

    protected:
        
        index_t build_tree() override;

        
        void get_node(
            index_t n, index_t b, index_t e,
            index_t& left_child, index_t& right_child,
            coord_index_t&  splitting_coord,
            index_t& m,
            double& splitting_val
        ) const override;

        virtual index_t create_kd_tree_recursive(
            index_t b, index_t e,
            double* bbox_min, double* bbox_max
        );

        virtual void split_kd_node(
            index_t b, index_t e,
            double* bbox_min, double* bbox_max,
            index_t& m, coord_index_t& cut_dim, double& cut_val
        );

        virtual void plane_split(
            index_t b, index_t e, coord_index_t coord, double val,
            index_t& br1, index_t& br2
        );

        double point_coord(int index, coord_index_t coord) {
            geo_debug_assert(index >= 0);
            geo_debug_assert(index_t(index) < nb_points());
            geo_debug_assert(coord < dimension());
            index_t direct_index = point_index_[index_t(index)];
            geo_debug_assert(direct_index < nb_points());
            return (points_ + direct_index * stride_)[coord];
        }


        index_t nb_nodes() const {
            return splitting_coord_.size();
        }

        virtual index_t new_node();

    protected:
        vector<coord_index_t> splitting_coord_;

        vector<double> splitting_val_;

        vector<index_t> node_m_;

        vector<index_t> node_right_child_;
    };

    
}

#endif
