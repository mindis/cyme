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

#ifndef CYME_SIMD_VEC_HPP
#define CYME_SIMD_VEC_HPP

#include "controller/simd_vector/trait.hpp"
#include "controller/simd_vector/simd_wrapper.hpp"

namespace numeric{

    /**
      \brief Vector computation class. The SIMD register (hardware) is encapsulated. It is generic, it can be SEE, AVX or QPX.
      the type is given by the trait class (simd_trait)
    */
    template<class T,memory::simd O>
    struct vec_simd{
        typedef typename simd_trait<T,O>::value_type value_type;
        typedef typename simd_trait<T,O>::pointer pointer;
        typedef typename simd_trait<T,O>::const_pointer const_pointer;
        typedef typename simd_trait<T,O>::register_type register_type;

        /**
         \brief construtor desired value else 0, note copy constructor generated automaticaly. Only used for constant.
         */
        inline explicit vec_simd(const value_type a = value_type()){
            xmm = _mm_load1<value_type,O>(xmm,a);
        }

        /**
         \brief construtor from a pointer
         */
        inline vec_simd(const_pointer a){
            xmm = _mm_load<value_type,O>(xmm,a);
        }

        /**
         \brief bracket operator called by the parser (expr_vec)
         */
        inline vec_simd& operator()(){
            return *this;
        }

        /**
         \brief bracket operator called by the parser (expr_vec)
         */
        inline const vec_simd& operator()() const{
            return *this;
        }

        /**
         \brief operator *= between two vectors
         */
        inline vec_simd& operator *=(const vec_simd& rhs){
            xmm = _mm_mul<value_type,O>(xmm,rhs.xmm);
            return *this;
        }

        /**
         \brief operator /= between two vectors
         */
        inline vec_simd& operator /=(const vec_simd& rhs){
            xmm = _mm_div<value_type,O>(xmm,rhs.xmm);
            return *this;
        }
        
        /**
        \brief operator += between two vectors
        */
        inline vec_simd& operator +=(const vec_simd& rhs){
            xmm = _mm_add<value_type,O>(xmm,rhs.xmm);
            return *this;
        }

        /**
         \brief operator -= between two vectors
         */
        inline vec_simd& operator -=(const vec_simd& rhs){
            xmm = _mm_sub<value_type,O>(xmm,rhs.xmm);
            return *this;
        }

        /**
         \brief Save the value into the register into the memory
         */
        inline void store(pointer a) const{
            _mm_store<value_type,O>(xmm,a);
        } 

#ifdef __FMA__
        /**
         \brief FMA operator
         */
        inline void ma(const vec_simd& lhs, const vec_simd& rhs){
            xmm = _mm_fma<value_type,O>(xmm,lhs.xmm,rhs.xmm);
        }

        /**
         \brief FMS operator
         */
        inline void ms(const vec_simd& lhs, const vec_simd& rhs){
            xmm = _mm_fms<value_type,O>(xmm,lhs.xmm,rhs.xmm);
        }

        /**
         \brief FMS operator, 2nd case of the operator -
         */
        inline void nma(const vec_simd& lhs, const vec_simd& rhs){
            xmm = _mm_nfma<value_type,O>(xmm,lhs.xmm,rhs.xmm);
        }
#endif

         /**
         \brief hardware Register
         */
        register_type xmm;
    };

    /**
    \brief free function for call the vendor exponential, this function uses the return value optimization
    */
    template<class T,memory::simd O>
    inline vec_simd<T,O> exp_v(const vec_simd<T,O>& rhs){
        vec_simd<T,O> nrv(0.0);
        nrv.xmm = _mm_exp<T,O>(rhs.xmm);
        return nrv;
    }

    /**
    \brief free function * operator between two vectors, this function uses the return value optimization
    */
    template<class T,memory::simd O>
    inline vec_simd<T,O> operator* (const vec_simd<T,O>& lhs, const vec_simd<T,O>& rhs){
        vec_simd<T,O> nrv(lhs);   // named return value optimization
        nrv *= rhs;
        return nrv;
    }

    /**
    \brief free function / operator between two vectors and a int, used only for my exp, this function uses the return value optimization
    */
    template<class T,memory::simd O>
    inline vec_simd<T,O> operator/ (const vec_simd<T,O>& lhs, const vec_simd<T,O>& rhs){
        vec_simd<T,O> nrv(lhs);
        nrv /= rhs;
        return nrv;
    }
    
    /**
    \brief free function + operator between two vectorsm, this function uses the return value optimization
    */
    template<class T,memory::simd O>
    inline vec_simd<T,O> operator+ (const vec_simd<T,O>& lhs, const vec_simd<T,O>& rhs){
        vec_simd<T,O> nrv(lhs);
        nrv += rhs;
        return nrv;
    }
    /**
    \brief free function - operator between two vectorsm, this function uses the return value optimization
    */
    template<class T,memory::simd O>
    inline vec_simd<T,O> operator- (const vec_simd<T,O>& lhs, const vec_simd<T,O>& rhs){
        vec_simd<T,O> nrv(lhs);
        nrv -= rhs;
        return nrv;
    }

#ifdef __FMA__
    /**
    \brief free function FMA between 3 vectors, a*b+c or c + a*B, + is commutative so no pb
    */
    template<class T,memory::simd O>
    inline vec_simd<T,O> muladd(const vec_simd<T,O>& lhs, const vec_simd<T,O>& mhs, const vec_simd<T,O>& rhs){
        vec_simd<T,O> nrv(lhs);
        nrv.ma(mhs,rhs);
        return nrv;
    }

    /**
    \brief free function FMS between 3 vectors, only a*b - c, - is not commutative
    */
    template<class T,memory::simd O>
    inline vec_simd<T,O> mulsub(const vec_simd<T,O>& lhs, const vec_simd<T,O>& mhs, const vec_simd<T,O>& rhs){
        vec_simd<T,O> nrv(lhs);
        nrv.ms(mhs,rhs);
        return nrv;
    }

    /**
     \brief free function FMS c - a*b as - is not commutative
     */
    template<class T,memory::simd O>
    inline vec_simd<T,O> negatemuladd(const vec_simd<T,O>& lhs, const vec_simd<T,O>& mhs, const vec_simd<T,O>& rhs){
        vec_simd<T,O> nrv(lhs);
        nrv.nma(mhs,rhs);
        return nrv;
    }
#endif

} //end namespace

#endif

