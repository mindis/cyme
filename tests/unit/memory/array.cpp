/*
 * Cyme - array.cpp, Copyright (c), 2014,
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
 * timothee.ewart@epfl.ch,
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 */

#include <tests/unit/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define N T::n
#define M T::m
#define ORDER T::order
#define MAX 1000

template <class S, size_t m>
struct synapse {
    typedef S value_type;
    static const size_t value_size = m;
};

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_default_constructor, T, floating_point_block_types) {
    cyme::array<synapse<TYPE, M>, N, ORDER> block_a;
    TYPE test[M * N];
    memset((void *)test, 0, M * N * sizeof(TYPE));
    size_t b = memcmp((void *)test, (void *)&block_a(0, 0), M * N * sizeof(TYPE));
    BOOST_CHECK_EQUAL(b, 0);
}
BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_value_constructor, T, floating_point_block_types) {
    TYPE random = GetRandom<TYPE>();
    cyme::array<synapse<TYPE, M>, N, ORDER> block_a(random);
    TYPE test[M * N];
    for (std::size_t i = 0; i < M * N; ++i)
        test[i] = random;
    size_t b = memcmp((void *)test, (void *)&block_a(0, 0), M * N * sizeof(TYPE));
    BOOST_CHECK_EQUAL(b, 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_operator_bracket, T, floating_point_block_types) {
    cyme::array<synapse<TYPE, M>, N, ORDER> block_a;
    cyme::array<synapse<TYPE, M>, N, ORDER> block_b;

    init(block_a, block_b);

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_copy_constructor, T, floating_point_block_types) {
    cyme::array<synapse<TYPE, M>, N, ORDER> block_a;
    cyme::array<synapse<TYPE, M>, N, ORDER> block_b;

    init(block_a, block_b);

    cyme::array<synapse<TYPE, M>, N, ORDER> block_a_cpy(block_a);
    cyme::array<synapse<TYPE, M>, N, ORDER> block_b_cpy(block_b);

    check(block_a, block_b);
    check(block_a_cpy, block_b_cpy);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_equal, T, floating_point_block_types) {
    cyme::array<synapse<TYPE, M>, N, cyme::AoS> block_a;
    cyme::array<synapse<TYPE, M>, N, cyme::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoS>::iterator it_AoS_w = block_a.begin();
    typename cyme::array<synapse<TYPE, M>, N, cyme::AoS>::const_iterator it_AoS_r = block_a.begin();
    for (; it_AoS_r != block_a.end(); ++it_AoS_r, ++it_AoS_w)
        (*it_AoS_w)[0] = (*it_AoS_r)[1];

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::iterator it_AoSoA_w = block_b.begin();
    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::const_iterator it_AoSoA_r = block_b.begin();
    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_negate, T, floating_point_block_types) {
    cyme::array<synapse<TYPE, M>, N, cyme::AoS> block_a;
    cyme::array<synapse<TYPE, M>, N, cyme::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoS>::iterator it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = -(*it_AoS)[1];

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::iterator it_AoSoA_w = block_b.begin();
    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::const_iterator it_AoSoA_r = block_b.begin();

    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] = -(*it_AoSoA_r)[1];

    check(block_a, block_b);
    it_AoS = block_a.begin();
    it_AoSoA_w = block_b.begin();
    it_AoSoA_r = block_b.begin();

    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = -(-(*it_AoS)[1]);

    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] = -(-(*it_AoSoA_r)[1]);

    check(block_a, block_b);
    it_AoS = block_a.begin();
    it_AoSoA_w = block_b.begin();
    it_AoSoA_r = block_b.begin();

    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = -(-(*it_AoS)[1] - -(*it_AoS)[2]);

    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] = -(-(*it_AoSoA_r)[1] - -(*it_AoSoA_r)[2]);

    check(block_a, block_b);
    it_AoS = block_a.begin();
    it_AoSoA_w = block_b.begin();
    it_AoSoA_r = block_b.begin();

    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = -(-(*it_AoS)[1] - - - - - -(*it_AoS)[2]);

    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] = -(-(*it_AoSoA_r)[1] - - - - - -(*it_AoSoA_r)[2]);

    check(block_a, block_b);
}
BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_equal_assign, T, floating_point_block_types) {
    cyme::array<synapse<TYPE, 4>, N, cyme::AoS> block_a;
    cyme::array<synapse<TYPE, 4>, N, cyme::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE, 4>, N, cyme::AoS>::iterator it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS) {
        (*it_AoS)[0] = (*it_AoS)[0];
        (*it_AoS)[0] = (*it_AoS)[1];
        (*it_AoS)[0] = (*it_AoS)[2];
        (*it_AoS)[0] = (*it_AoS)[3];

        (*it_AoS)[1] = (*it_AoS)[0];
        (*it_AoS)[1] = (*it_AoS)[1];
        (*it_AoS)[1] = (*it_AoS)[2];
        (*it_AoS)[1] = (*it_AoS)[3];

        (*it_AoS)[2] = (*it_AoS)[0];
        (*it_AoS)[2] = (*it_AoS)[1];
        (*it_AoS)[2] = (*it_AoS)[2];
        (*it_AoS)[2] = (*it_AoS)[3];

        (*it_AoS)[3] = (*it_AoS)[0];
        (*it_AoS)[3] = (*it_AoS)[1];
        (*it_AoS)[3] = (*it_AoS)[2];
        (*it_AoS)[3] = (*it_AoS)[3];
    }

    typename cyme::array<synapse<TYPE, 4>, N, cyme::AoSoA>::const_iterator it_AoSoA_r = block_b.begin();
    typename cyme::array<synapse<TYPE, 4>, N, cyme::AoSoA>::iterator it_AoSoA_w = block_b.begin();

    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w) {
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[0];
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1];
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[2];
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[3];

        (*it_AoSoA_w)[1] = (*it_AoSoA_r)[0];
        (*it_AoSoA_w)[1] = (*it_AoSoA_r)[1];
        (*it_AoSoA_w)[1] = (*it_AoSoA_r)[2];
        (*it_AoSoA_w)[1] = (*it_AoSoA_r)[3];

        (*it_AoSoA_w)[2] = (*it_AoSoA_r)[0];
        (*it_AoSoA_w)[2] = (*it_AoSoA_r)[1];
        (*it_AoSoA_w)[2] = (*it_AoSoA_r)[2];
        (*it_AoSoA_w)[2] = (*it_AoSoA_r)[3];

        (*it_AoSoA_w)[3] = (*it_AoSoA_r)[0];
        (*it_AoSoA_w)[3] = (*it_AoSoA_r)[1];
        (*it_AoSoA_w)[3] = (*it_AoSoA_r)[2];
        (*it_AoSoA_w)[3] = (*it_AoSoA_r)[3];
    }

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_plusequal, T, floating_point_block_types) {
    cyme::array<synapse<TYPE, M>, N, cyme::AoS> block_a;
    cyme::array<synapse<TYPE, M>, N, cyme::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoS>::iterator it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] += (*it_AoS)[1];

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::const_iterator it_AoSoA_r = block_b.begin();
    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::iterator it_AoSoA_w = block_b.begin();

    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] += (*it_AoSoA_r)[1];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] += (*it_AoS)[1];

    it_AoSoA_r = block_b.begin();
    it_AoSoA_w = block_b.begin();
    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] += (*it_AoSoA_r)[1];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_minusequal, T, floating_point_block_types) {
    cyme::array<synapse<TYPE, M>, N, cyme::AoS> block_a;
    cyme::array<synapse<TYPE, M>, N, cyme::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoS>::iterator it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] -= (*it_AoS)[1];

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::const_iterator it_AoSoA_r = block_b.begin();
    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::iterator it_AoSoA_w = block_b.begin();

    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] -= (*it_AoSoA_r)[1];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] -= (*it_AoS)[1];

    it_AoSoA_r = block_b.begin();
    it_AoSoA_w = block_b.begin();
    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] -= (*it_AoSoA_r)[1];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_minus_basic_type, T, floating_point_block_types) {
    cyme::array<synapse<TYPE, M>, N, cyme::AoS> block_a;
    cyme::array<synapse<TYPE, M>, N, cyme::AoSoA> block_b;

    init(block_a, block_b);

    TYPE one(1);

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoS>::iterator it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1] - one;

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::const_iterator it_AoSoA_r = block_b.begin();
    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::iterator it_AoSoA_w = block_b.begin();
    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1] - one;

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = one - (*it_AoS)[1];

    it_AoSoA_r = block_b.begin();
    it_AoSoA_w = block_b.begin();
    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] = one - (*it_AoSoA_r)[1];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = -one - (*it_AoS)[1];

    it_AoSoA_r = block_b.begin();
    it_AoSoA_w = block_b.begin();
    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] = -one - (*it_AoSoA_r)[1];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = -(*it_AoS)[1] - one;

    it_AoSoA_r = block_b.begin();
    it_AoSoA_w = block_b.begin();
    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] = -(*it_AoSoA_r)[1] - one;

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_multiplyequal, T, floating_point_block_types) {
    cyme::array<synapse<TYPE, M>, N, cyme::AoS> block_a;
    cyme::array<synapse<TYPE, M>, N, cyme::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoS>::iterator it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] *= (*it_AoS)[1];

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::const_iterator it_AoSoA_r = block_b.begin();
    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::iterator it_AoSoA_w = block_b.begin();
    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] *= (*it_AoSoA_r)[1];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] *= (*it_AoS)[1];

    it_AoSoA_r = block_b.begin();
    it_AoSoA_w = block_b.begin();
    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] *= (*it_AoSoA_r)[1];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_divideequal, T, floating_point_block_types) {
    cyme::array<synapse<TYPE, M>, N, cyme::AoS> block_a;
    cyme::array<synapse<TYPE, M>, N, cyme::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoS>::iterator it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] /= (*it_AoS)[1];

    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::const_iterator it_AoSoA_r = block_b.begin();
    typename cyme::array<synapse<TYPE, M>, N, cyme::AoSoA>::iterator it_AoSoA_w = block_b.begin();
    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] /= (*it_AoSoA_r)[1];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for (; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] /= (*it_AoS)[1];

    it_AoSoA_r = block_b.begin();
    it_AoSoA_w = block_b.begin();
    for (; it_AoSoA_r != block_b.end(); ++it_AoSoA_r, ++it_AoSoA_w)
        (*it_AoSoA_w)[0] /= (*it_AoSoA_r)[1];

    check(block_a, block_b);
}

#undef TYPE
#undef N
#undef MAX
#undef SIZE
