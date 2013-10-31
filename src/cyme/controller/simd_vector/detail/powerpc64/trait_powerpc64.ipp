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

#ifndef CYME_TRAIT_POWERPC64_IPP
#define CYME_TRAIT_POWERPC64_IPP

namespace numeric{
    /** \cond I do not need this part in the doc
        \brief Specialization trait for float with QPX
    */
    template <>
    struct simd_trait<float,memory::qpx> : trait<float>{
        typedef vector4double register_type;
    };

    /**
        \brief Specialization trait for double with QPX
    */
    template <>
    struct simd_trait<double,memory::qpx> : trait<double>{
        typedef vector4double register_type;
    };
    /* \endcond I do not need this part in the doc*/

    /**
     \brief Specialization trait for float  Newton-Raphson division
     */
    template<>
    struct div_recursion<float, memory::qpx>{
        static const std::size_t value = 2; // cardinal([0-2])=3
    };

    /**
     \brief Specialization trait for double  Newton-Raphson division
     */
    template<>
    struct div_recursion<double, memory::qpx>{
        static const std::size_t value = 3; // card([0-3])=4
    };
}
#endif
