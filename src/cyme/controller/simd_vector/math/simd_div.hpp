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

#ifndef CYME_SIMD_DIV_HPP
#define CYME_SIMD_DIV_HPP

namespace numeric{
    /**
     \brief reccursive implementation of the Newton-Raphson algo
     */
    template<class T, memory::simd O, std::size_t n>
    struct helper_div{
        static inline vec_simd<T,O> div(vec_simd<T,O> const& rhs){
#ifdef __FMA__
            return helper_div<T,O,n-1>::div(rhs)*negatemulsub(rhs,helper_div<T,O,n-1>::div(rhs),vec_simd<T,O>(2.0)); 
#else
            return helper_div<T,O,n-1>::div(rhs)*(vec_simd<T,O>(2.0)-rhs*helper_div<T,O,n-1>::div(rhs));
#endif
        }
    };

    /**
     \brief reccursive init with 1/r approximation
     */
    template<class T, memory::simd O>
    struct helper_div<T,O,0>{
        static inline vec_simd<T,O> div(vec_simd<T,O> const& rhs){
            return rec<T,O>(rhs);
        }
    };

    /**
     \brief free function based on Newton-Raphson algo <3, ^_^'
     */
    template<class T,memory::simd O>
    inline vec_simd<T,O> div (const vec_simd<T,O>& lhs, const vec_simd<T,O>& rhs){ // lhs/rhs
        vec_simd<T,O> nrv = lhs*helper_div<T,O,div_recursion<T,O>::value>::div(rhs); 
        return nrv;
    }

    /**
     \brief free function / operator between two vectors this function uses the return value optimization
     */
    template<class T,memory::simd O>
    inline vec_simd<T,O> operator/ (const vec_simd<T,O>& lhs, const vec_simd<T,O>& rhs){
    //       vec_simd<T,O> nrv(lhs);
    //       nrv /= rhs;
    //       return nrv;
             vec_simd<T,O> nrv = div(lhs,rhs);
             return nrv;
    }
} //end namespace
#endif
