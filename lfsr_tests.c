/**
 * lfsr_tests.c
 * 
 * Ce fichier contient les tests unitaires de lfsr.h
 * 
 * @author: Dumoulin Peissone S193957
 * @date: 21/03/21
 * @projet: INFO0030 Projet 2
 */

#include <stdio.h>
#include <stdlib.h>
#include "pnm.h"
#include "lfsr.h"
#include "seatest.h"

static void test_create_lfsr(){
   LFSR *register11tap8 = create_lfsr(11, "01101000010", 8);

   assert_int_equal(11, (int)get_N(register11tap8));
   assert_string_equal("01101000010", get_seed(register11tap8));
   assert_int_equal(8, (int)get_tap(register11tap8));

   destroy_lfsr(register11tap8);
}//fin test_create_lfsr

static void test_operate(){
   LFSR *l1 = initialize("01101000010", 8);
   LFSR *l2 = initialize("11010000101", 8);
   LFSR *l3 = initialize("10100001011", 8);
   LFSR *l4 = initialize("01000010110", 8);
   LFSR *l5 = initialize("10000101100", 8);
   LFSR *l6 = initialize("00001011001", 8);
   LFSR *l7 = initialize("00010110010", 8);
   LFSR *l8 = initialize("00101100100", 8);
   LFSR *l9 = initialize("01011001001", 8);
   LFSR *l10 = initialize("10110010010", 8);

   assert_true(operate(l1));
   assert_true(operate(l2));
   assert_false(operate(l3));
   assert_false(operate(l4));
   assert_true(operate(l5));
   assert_false(operate(l6));
   assert_false(operate(l7));
   assert_true(operate(l8));
   assert_false(operate(l9));
   assert_false(operate(l10));

   destroy_lfsr(l1);
   destroy_lfsr(l2);
   destroy_lfsr(l3);
   destroy_lfsr(l4);
   destroy_lfsr(l5);
   destroy_lfsr(l6);
   destroy_lfsr(l7);
   destroy_lfsr(l8);
   destroy_lfsr(l9);
   destroy_lfsr(l10);
}//fin test_operate()

static void test_generate(){
   LFSR *l1 = initialize("01101000010", 8);
   LFSR *l2 = initialize("00001011001", 8);
   LFSR *l3 = initialize("01100100100", 8);
   LFSR *l4 = initialize("10010011110", 8);
   LFSR *l5 = initialize("01111011011", 8);
   LFSR *l6 = initialize("01101110010", 8);
   LFSR *l7 = initialize("11001011010", 8);
   LFSR *l8 = initialize("01101011100", 8);
   LFSR *l9 = initialize("01110011000", 8);
   LFSR *l10 = initialize("01100010111", 8);

   assert_int_equal(25, generate(l1, 5));
   assert_int_equal(4, generate(l2, 5));
   assert_int_equal(30, generate(l3, 5));
   assert_int_equal(27, generate(l4, 5));
   assert_int_equal(18, generate(l5, 5));
   assert_int_equal(26, generate(l6, 5));
   assert_int_equal(28, generate(l7, 5));
   assert_int_equal(24, generate(l8, 5));
   assert_int_equal(23, generate(l9, 5));
   assert_int_equal(29, generate(l10, 5));

   destroy_lfsr(l1);
   destroy_lfsr(l2);
   destroy_lfsr(l3);
   destroy_lfsr(l4);
   destroy_lfsr(l5);
   destroy_lfsr(l6);
   destroy_lfsr(l7);
   destroy_lfsr(l8);
   destroy_lfsr(l9);
   destroy_lfsr(l10);
}//fin test_generate()

static void test_string(){
   LFSR *l1 = initialize("01101000010", 8);
   LFSR *l2 = initialize("11010000101", 8);
   LFSR *l3 = initialize("10100001011", 8);
   LFSR *l4 = initialize("01000010110", 8);
   LFSR *l5 = initialize("10000101100", 8);
   LFSR *l6 = initialize("00001011001", 8);
   LFSR *l7 = initialize("00010110010", 8);
   LFSR *l8 = initialize("00101100100", 8);
   LFSR *l9 = initialize("01011001001", 8);
   LFSR *l10 = initialize("10110010010", 8);
   LFSR *l11 = initialize("01100100100", 8);

   LFSR *l12 = initialize("01101000010", 8);
   LFSR *l13 = initialize("00001011001", 8);
   LFSR *l14 = initialize("01100100100", 8);
   LFSR *l15 = initialize("10010011110", 8);
   LFSR *l16 = initialize("01111011011", 8);
   LFSR *l17 = initialize("01101110010", 8);
   LFSR *l18 = initialize("11001011010", 8);
   LFSR *l19 = initialize("01101011100", 8);
   LFSR *l20 = initialize("01110011000", 8);
   LFSR *l21 = initialize("01100010111", 8);
   LFSR *l22 = initialize("01011111101", 8);

   LFSR *l23 = initialize("01101000010100010000", 16);
   LFSR *l24 = initialize("10010001011111000001", 16);

   operate(l1);
   operate(l2);
   operate(l3);
   operate(l4);
   operate(l5);
   operate(l6);
   operate(l7);
   operate(l8);
   operate(l9);
   operate(l10);

   generate(l12, 5);
   generate(l13, 5);
   generate(l14, 5);
   generate(l15, 5);
   generate(l16, 5);
   generate(l17, 5);
   generate(l18, 5);
   generate(l19, 5);
   generate(l20, 5);
   generate(l21, 5);
   
   generate(l23, 32);

   assert_string_equal(get_seed(l1), string(l1));
   assert_string_equal(get_seed(l2), string(l2));
   assert_string_equal(get_seed(l3), string(l3));
   assert_string_equal(get_seed(l4), string(l4));
   assert_string_equal(get_seed(l5), string(l5));
   assert_string_equal(get_seed(l6), string(l6));
   assert_string_equal(get_seed(l7), string(l7));
   assert_string_equal(get_seed(l8), string(l8));
   assert_string_equal(get_seed(l9), string(l9));
   assert_string_equal(get_seed(l10), string(l10));
   assert_string_equal(get_seed(l11), string(l11));

   assert_string_equal(get_seed(l12), string(l12));
   assert_string_equal(get_seed(l13), string(l13));
   assert_string_equal(get_seed(l14), string(l14));
   assert_string_equal(get_seed(l15), string(l15));
   assert_string_equal(get_seed(l16), string(l16));
   assert_string_equal(get_seed(l17), string(l17));
   assert_string_equal(get_seed(l18), string(l18));
   assert_string_equal(get_seed(l19), string(l19));
   assert_string_equal(get_seed(l20), string(l20));
   assert_string_equal(get_seed(l21), string(l21));
   assert_string_equal(get_seed(l22), string(l22));

   assert_string_equal(get_seed(l23), string(l23));
   assert_string_equal(get_seed(l24), string(l24));

   destroy_lfsr(l1);
   destroy_lfsr(l2);
   destroy_lfsr(l3);
   destroy_lfsr(l4);
   destroy_lfsr(l5);
   destroy_lfsr(l6);
   destroy_lfsr(l7);
   destroy_lfsr(l8);
   destroy_lfsr(l9);
   destroy_lfsr(l10);
   destroy_lfsr(l11);

   destroy_lfsr(l12);
   destroy_lfsr(l13);
   destroy_lfsr(l14);
   destroy_lfsr(l15);
   destroy_lfsr(l16);
   destroy_lfsr(l17);
   destroy_lfsr(l18);
   destroy_lfsr(l19);
   destroy_lfsr(l20);
   destroy_lfsr(l21);
   destroy_lfsr(l22);
   destroy_lfsr(l23);
   destroy_lfsr(l24);
}//fin test_string

static void test_fixture(){
   test_fixture_start();

   run_test(test_create_lfsr);
   run_test(test_operate);
   run_test(test_generate);
   run_test(test_string);

   test_fixture_end();
}//fin test_fixture()

static void all_tests(){
   test_fixture();
}//fin all_tests()

int main(){
   return run_tests(all_tests);
}//fin main()