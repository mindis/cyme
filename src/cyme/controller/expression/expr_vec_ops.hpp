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

#ifndef CYME_EXPR_VEC_OPS_HPP
#define CYME_EXPR_VEC_OPS_HPP

namespace numeric{
/** \cond I do not need this part in the doc */

    /* this is the key of parser, describe every possibilities */
    //addition of two vectors v+w
    template<class T, memory::simd O, class R1, class R2>
    vec<T,O, vec_add<T,O,R1,R2> >
    inline operator +(vec<T,O,R1> const& a, vec<T,O,R2> const& b){
        return vec<T,O, vec_add<T,O,R1,R2> >(vec_add<T,O,R1,R2>(a.rep(),b.rep()));
    }

    //subtraction of two vectors v-w
    template<class T, memory::simd O, class R1, class R2>
    vec<T,O, vec_sub<T,O,R1,R2> >
    inline operator -(vec<T,O,R1> const& a, vec<T,O,R2> const& b){
        return vec<T,O, vec_sub<T,O,R1,R2> >(vec_sub<T,O,R1,R2>(a.rep(),b.rep()));
    }

    //division of two vectors v/w
    template<class T, memory::simd O, class R1, class R2>
    vec<T,O, vec_div<T,O,R1,R2> >
    inline operator /(vec<T,O,R1> const& a, vec<T,O,R2> const& b){
        return vec<T,O,vec_div<T,O,R1,R2> >(vec_div<T,O,R1,R2>(a.rep(),b.rep()));
    }

    //multiplication of two vectors v*w
    template<class T, memory::simd O, class R1, class R2>
    vec<T,O, vec_mul<T,O,R1,R2> >
    inline operator *(vec<T,O,R1> const& a, vec<T,O,R2> const& b){
        return vec<T,O,vec_mul<T,O,R1,R2> >(vec_mul<T,O,R1,R2>(a.rep(),b.rep()));
    }

    /* OK I give the type because the compiler makes me partial specialization*/
    /* C - TIM TO DO, PLEASE FIND A SOLUTION DUPLICATION IS EVIL */

    //addition of scalar/vector, lambda+v for double, partial specialization are impossible on a single function
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_add<T,O,vec_scalar<T,O>,R2> >
    operator +(double const& s, vec<T,O,R2> const& b){
        return vec<T,O,vec_add<T,O,vec_scalar<T,O>, R2> >(vec_add<T,O,vec_scalar<T,O>,R2>(vec_scalar<T,O>(s),b.rep()));
    }

    //addition of scalar/vector, lambda+v for int
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_add<T,O,vec_scalar<T,O>,R2> >
    operator +(int const& s, vec<T,O,R2> const& b){
        return operator+(static_cast<T>(s),b);// CHECK IF NO COPY
    }
    
    //v + lambda(double)
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_add<T,O,vec_scalar<T,O>,R2> >
    operator +(vec<T,O,R2> const& b, double const& s){
        return operator+(s,b);// CHECK IF NO COPY
    }

    //v + lambda(int)
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_add<T,O,vec_scalar<T,O>,R2> >
    operator +(vec<T,O,R2> const& b, int const& s){
        return operator+(static_cast<T>(s),b);
    }

    //subtraction of scalar/vector, lambda-v for double, partial specialization are impossible on a single function
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_sub<T,O,vec_scalar<T,O>,R2> >
    operator -(double const& s, vec<T,O,R2> const& b){
        return vec<T,O,vec_sub<T,O,vec_scalar<T,O>, R2> >(vec_sub<T,O,vec_scalar<T,O>,R2>(vec_scalar<T,O>(s),b.rep()));
    }

    //subtraction of scalar/vector, lambda-v for int
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_sub<T,O,vec_scalar<T,O>,R2> >
    operator -(int const& s, vec<T,O,R2> const& b){
        return operator-(static_cast<T>(s),b);// CHECK IF NO COPY
    }

    //v - lambda(double)
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_sub<T,O,vec_scalar<T,O>,R2> >
    operator -(vec<T,O,R2> const& b, double const& s){
        return operator-(s,b);// CHECK IF NO COPY
    }

    //v - lambda(int)
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_sub<T,O,vec_scalar<T,O>,R2> >
    operator -(vec<T,O,R2> const& b, int const& s){
        return operator-(static_cast<T>(s),b);
    }

    //multiplication of scalar/vector, lambda*v for double, partial specialization are impossible on a single function
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_mul<T,O,vec_scalar<T,O>,R2> >
    operator *(double const& s, vec<T,O,R2> const& b){
        return vec<T,O,vec_mul<T,O,vec_scalar<T,O>, R2> >(vec_mul<T,O,vec_scalar<T,O>,R2>(vec_scalar<T,O>(s),b.rep()));
    }

    //multiplication of scalar/vector, lambda*v for int
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_mul<T,O,vec_scalar<T,O>,R2> >
    operator *(int const& s, vec<T,O,R2> const& b){
        return operator*(static_cast<T>(s),b); 
    }
    
    //v * lambda(double)
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_mul<T,O,vec_scalar<T,O>,R2> >
    operator *(vec<T,O,R2> const& b, double const& s){
        return operator*(s,b);    }

    //v * lambda(int)
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_mul<T,O,vec_scalar<T,O>,R2> >
    operator *(vec<T,O,R2> const& b, int const& s){
        return operator*(static_cast<T>(s),b);
    }
    
    //division of scalar/vector, lambda*v for double, partial specialization are impossible on a single function
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_div<T,O,vec_scalar<T,O>,R2> >
    operator /(double const& s, vec<T,O,R2> const& b){
        return vec<T,O,vec_div<T,O,vec_scalar<T,O>, R2> >(vec_div<T,O,vec_scalar<T,O>,R2>(vec_scalar<T,O>(s),b.rep()));
    }

    //division of scalar/vector, lambda*v for int
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_div<T,O,vec_scalar<T,O>,R2> >
    operator /(int const& s, vec<T,O,R2> const& b){
        return operator/(static_cast<T>(s),b); 
    }
    
    //v * lambda(double)
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_div<T,O,vec_scalar<T,O>,R2> >
    operator /(vec<T,O,R2> const& b, double const& s){
        return operator*(s,b);
    }

    //v * lambda(int)
    template<class T, memory::simd O, class R2>
    inline vec<T,O, vec_div<T,O,vec_scalar<T,O>,R2> >
    operator /(vec<T,O,R2> const& b, int const& s){
        return operator*(static_cast<T>(s),b);
    }
/** \endcond I do not need this part in the doc */
}

#endif
