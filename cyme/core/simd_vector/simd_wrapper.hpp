/*
 * CYME, License
 * 
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne 
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef CYME_O_WRAPPER_H
#define CYME_O_WRAPPER_H

namespace numeric{

    /**
    \brief free function (wrapper) for loading basic type (double,into) into register
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_load1(const typename simd_trait<T,O,N>::value_type a);

    /**
    \brief free function (wrapper) for loading data from memory (pointer) into register
    \warning The data must be  aligned else segfault
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_load(typename simd_trait<T,O,N>::const_pointer a);

    /**
    \brief free function (wrapper) for storing the data in the memory (pointer)
    \warning The data must be  aligned else segfault
    */
    template<class T, memory::simd O, int N>
    forceinline void _mm_store(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::pointer a);

    /**
    \brief free function (wrapper) for multiplying two registers
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_mul(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1);

    /**
    \brief free function (wrapper) for divising two registers
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_div(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1);

    /**
    \brief free function (wrapper) for adding two registers
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_add(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1);

    /**
    \brief free function (wrapper) for substracting two registers
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_sub(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1); //xmm0 - xmm1

    /**
    \brief free function (wrapper) for calculating the exp of a vector
    \warning this function is only works if the wrapper Helper_exp is setup to Vendor_exp
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_exp(typename simd_trait<T,O,N>::register_type xmm0); // Vendor (IBM/Intel) only 

    /**
    \brief free function (wrapper) for calculating the log of a vector
    \warning this function is only works if the wrapper Helper_log is setup to Vendor_log
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_log(typename simd_trait<T,O,N>::register_type xmm0); // Vendor (IBM/Intel) only 

    /**
     \brief free function (wrapper) for calculating a light version of the inverse
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_rec(typename simd_trait<T,O,N>::register_type xmm0);

    /**
     \brief free function (wrapper) for calculating the negate number
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_neg(typename simd_trait<T,O,N>::register_type xmm0);

    /**
     \brief free function (wrapper) to floor
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<int,O,N>::register_type _mm_floor(typename simd_trait<T,O,N>::register_type xmm0);

    /**
     \brief free function cast in to float for the exp
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_cast(typename simd_trait<int,O,N>::register_type xmm0);

    /**
     \brief free function return the FLOAT vector 2^k
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_twok(typename simd_trait<int,O,N>::register_type xmm0);

#ifdef __FMA__ // This macro is a compiler one
    /**
    \brief free function (wrapper) for the FMA between three registers
    */
    template<class T, memory::simd O, int N> // a*b+c
    forceinline typename simd_trait<T,O,N>::register_type _mm_fma(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1, typename simd_trait<T,O,N>::register_type xmm2);

    /**
    \brief free function (wrapper) for the FMS between three registers
    */
    template<class T, memory::simd O, int N> // a*b-c
    forceinline typename simd_trait<T,O,N>::register_type _mm_fms(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1, typename simd_trait<T,O,N>::register_type xmm2);

    /**
     \brief free function (wrapper) for the negative FMA part between three registers
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_nfma(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1, typename simd_trait<T,O,N>::register_type xmm2);

    /**
     \brief free function (wrapper) for the negative FMS part between three registers
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_nfms(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1, typename simd_trait<T,O,N>::register_type xmm2);

#endif
} //end namespace 

#ifdef __SSE__
    #include "cyme/core/simd_vector/detail/x86/simd_wrapper_sse.ipp"
#endif

#ifdef __AVX__
    #include "cyme/core/simd_vector/detail/x86/simd_wrapper_avx.ipp"
#endif

#ifdef _ARCH_QP
    #include "cyme/core/simd_vector/detail/powerpc64/simd_wrapper_qpx.ipp"
#endif

#ifdef __MIC__
    #include "cyme/core/simd_vector/detail/mic/simd_wrapper_mic.ipp"
#endif

#endif
