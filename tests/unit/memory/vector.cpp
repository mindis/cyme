/*
 * Cyme - vector.cpp, Copyright (c), 2014,
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
#define ORDER T::order

template <class T, size_t M>
struct synapse {
    typedef T value_type;
    static const size_t value_size = M;
};

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_init_default_constructor, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE, N>, ORDER> a;
    BOOST_CHECK_EQUAL(a(0, 0), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_init_default_size_constructor, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE, N>, ORDER> a(10);
    TYPE test[N * 10];

    for (std::size_t i = 0; i < N * 10; ++i)
        test[i] = 0;

    size_t b = memcmp((void *)test, (void *)&a(0, 0), N * 10 * sizeof(TYPE));
    BOOST_CHECK_EQUAL(b, 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_init_value_size_constructor, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE, N>, ORDER> a(10, 3);
    TYPE test[N * 10];

    for (std::size_t i = 0; i < N * 10; ++i)
        test[i] = 3;

    size_t b = memcmp((void *)test, (void *)&a(0, 0), N * 10 * sizeof(TYPE));
    BOOST_CHECK_EQUAL(b, 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_init_operator_bracket, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE, N>, cyme::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE, N>, cyme::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_copy_constructor, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE, N>, cyme::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE, N>, cyme::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    cyme::vector<synapse<TYPE, N>, cyme::AoS> vector_a_cpy(vector_a);
    cyme::vector<synapse<TYPE, N>, cyme::AoSoA> vector_b_cpy(vector_b);

    check(vector_a, vector_b);
    check(vector_a_cpy, vector_b_cpy);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_resize_operator_bracket, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE, N>, cyme::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE, N>, cyme::AoSoA> vector_b(1024);

    init(vector_a, vector_b);
    check(vector_a, vector_b);

    vector_a.resize(999);
    vector_b.resize(999);

    check(vector_a, vector_b);

    vector_a.resize(777);
    vector_b.resize(777);

    check(vector_a, vector_b);

    vector_a.resize(7);
    vector_b.resize(7);

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_equal, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE, N>, cyme::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE, N>, cyme::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE, N>, cyme::AoS>::iterator it_AoS = vector_a.begin();
    for (; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1];

    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::iterator it_AoSoA_w = vector_b.begin();
    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::const_iterator it_AoSoA_r = vector_b.begin();
    for (; it_AoSoA_r != vector_b.end(); ++it_AoSoA_w, ++it_AoSoA_r)
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1];

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_equal_multiple, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE, N>, cyme::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE, N>, cyme::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE, N>, cyme::AoS>::iterator it_AoS = vector_a.begin();
    for (; it_AoS != vector_a.end(); ++it_AoS) {
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

    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::iterator it_AoSoA_w = vector_b.begin();
    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::const_iterator it_AoSoA_r = vector_b.begin();
    for (; it_AoSoA_r != vector_b.end(); ++it_AoSoA_w, ++it_AoSoA_r) {
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

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_scalar_fma, T, floating_point_torture_list) {
    cyme::vector<synapse<TYPE, N>, cyme::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE, N>, cyme::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE, N>, cyme::AoS>::iterator it_AoS = vector_a.begin();
    for (; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] = 3.3 * (*it_AoS)[0] + 2.2;

    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::iterator it_AoSoA_w = vector_b.begin();
    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::const_iterator it_AoSoA_r = vector_b.begin();
    for (; it_AoSoA_r != vector_b.end(); ++it_AoSoA_w, ++it_AoSoA_r)
        (*it_AoSoA_w)[0] = 3.3 * (*it_AoSoA_r)[0] + 2.2;

    check(vector_a, vector_b);

    it_AoS = vector_a.begin();
    for (; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1] * 2.5 + 6.9;

    it_AoSoA_w = vector_b.begin();
    it_AoSoA_r = vector_b.begin();
    for (; it_AoSoA_r != vector_b.end(); ++it_AoSoA_w, ++it_AoSoA_r)
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1] * 2.5 + 6.9;

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_plusequal, T, floating_point_torture_list) {
    cyme::vector<synapse<TYPE, N>, cyme::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE, N>, cyme::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE, N>, cyme::AoS>::iterator it_AoS = vector_a.begin();
    for (; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] += (*it_AoS)[1];

    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::iterator it_AoSoA_w = vector_b.begin();
    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::const_iterator it_AoSoA_r = vector_b.begin();
    for (; it_AoSoA_r != vector_b.end(); ++it_AoSoA_w, ++it_AoSoA_r)
        (*it_AoSoA_w)[0] += (*it_AoSoA_r)[1];

    check(vector_a, vector_b);

    it_AoS = vector_a.begin();
    for (; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] += (*it_AoS)[1];

    it_AoSoA_w = vector_b.begin();
    it_AoSoA_r = vector_b.begin();
    for (; it_AoSoA_r != vector_b.end(); ++it_AoSoA_w, ++it_AoSoA_r)
        (*it_AoSoA_w)[0] += (*it_AoSoA_r)[1];

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_minusequal, T, floating_point_torture_list) {
    cyme::vector<synapse<TYPE, N>, cyme::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE, N>, cyme::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE, N>, cyme::AoS>::iterator it_AoS = vector_a.begin();
    for (; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] -= (*it_AoS)[1];

    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::iterator it_AoSoA_w = vector_b.begin();
    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::const_iterator it_AoSoA_r = vector_b.begin();
    for (; it_AoSoA_r != vector_b.end(); ++it_AoSoA_w, ++it_AoSoA_r)
        (*it_AoSoA_w)[0] -= (*it_AoSoA_r)[1];

    check(vector_a, vector_b);

    it_AoS = vector_a.begin();
    for (; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] -= (*it_AoS)[1];

    it_AoSoA_w = vector_b.begin();
    it_AoSoA_r = vector_b.begin();
    for (; it_AoSoA_r != vector_b.end(); ++it_AoSoA_w, ++it_AoSoA_r)
        (*it_AoSoA_w)[0] -= (*it_AoSoA_r)[1];

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_multiplyequal, T, floating_point_torture_list) {
    cyme::vector<synapse<TYPE, N>, cyme::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE, N>, cyme::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE, N>, cyme::AoS>::iterator it_AoS = vector_a.begin();
    for (; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] *= (*it_AoS)[1];

    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::iterator it_AoSoA_w = vector_b.begin();
    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::const_iterator it_AoSoA_r = vector_b.begin();
    for (; it_AoSoA_r != vector_b.end(); ++it_AoSoA_w, ++it_AoSoA_r)
        (*it_AoSoA_w)[0] *= (*it_AoSoA_r)[1];

    check(vector_a, vector_b);

    it_AoS = vector_a.begin();
    for (; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] *= (*it_AoS)[1];

    it_AoSoA_w = vector_b.begin();
    it_AoSoA_r = vector_b.begin();
    for (; it_AoSoA_r != vector_b.end(); ++it_AoSoA_w, ++it_AoSoA_r)
        (*it_AoSoA_w)[0] *= (*it_AoSoA_r)[1];

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_divideequal, T, floating_point_torture_list) {
    cyme::vector<synapse<TYPE, N>, cyme::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE, N>, cyme::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE, N>, cyme::AoS>::iterator it_AoS = vector_a.begin();
    for (; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] /= (*it_AoS)[1];

    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::iterator it_AoSoA_w = vector_b.begin();
    typename cyme::vector<synapse<TYPE, N>, cyme::AoSoA>::const_iterator it_AoSoA_r = vector_b.begin();
    for (; it_AoSoA_r != vector_b.end(); ++it_AoSoA_w, ++it_AoSoA_r)
        (*it_AoSoA_w)[0] /= (*it_AoSoA_r)[1];

    check(vector_a, vector_b);

    it_AoS = vector_a.begin();
    for (; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] /= (*it_AoS)[1];

    it_AoSoA_w = vector_b.begin();
    it_AoSoA_r = vector_b.begin();
    for (; it_AoSoA_r != vector_b.end(); ++it_AoSoA_w, ++it_AoSoA_r)
        (*it_AoSoA_w)[0] /= (*it_AoSoA_r)[1];

    check(vector_a, vector_b);
}

#undef TYPE
#undef N
#undef ORDER
