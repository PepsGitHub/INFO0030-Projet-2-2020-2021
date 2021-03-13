#include "lfsr.h"
#include "seatest.h"

static void test_create_lfsr(){
   LFSR *register11tap8 = create_lfsr(11, "01101000010", 8);

   assert_int_equal(11, (int)get_N(register11tap8));
   assert_string_equal("01101000010", get_seed(register11tap8));
   assert_int_equal(8, (int)get_tap(register11tap8));

   destroy_lfsr(register11tap8, 1);
}//fin test_create_lfsr

static void test_operation(){
   LFSR *l1 = initialisation("01101000010", 8);
   LFSR *l2 = initialisation("11010000101", 8);
   LFSR *l3 = initialisation("10100001011", 8);
   LFSR *l4 = initialisation("01000010110", 8);
   LFSR *l5 = initialisation("10000101100", 8);
   LFSR *l6 = initialisation("00001011001", 8);
   LFSR *l7 = initialisation("00010110010", 8);
   LFSR *l8 = initialisation("00101100100", 8);
   LFSR *l9 = initialisation("01011001001", 8);
   LFSR *l10 = initialisation("10110010010", 8);

   assert_true(operation(l1));
   assert_true(operation(l2));
   assert_false(operation(l3));
   assert_false(operation(l4));
   assert_true(operation(l5));
   assert_false(operation(l6));
   assert_false(operation(l7));
   assert_true(operation(l8));
   assert_false(operation(l9));
   assert_false(operation(l10));

   destroy_lfsr(l1, 1);
   destroy_lfsr(l2, 1);
   destroy_lfsr(l3, 1);
   destroy_lfsr(l4, 1);
   destroy_lfsr(l5, 1);
   destroy_lfsr(l6, 1);
   destroy_lfsr(l7, 1);
   destroy_lfsr(l8, 1);
   destroy_lfsr(l9, 1);
   destroy_lfsr(l10, 1);
}//fin test_operation()

static void test_generation(){
   LFSR *l1 = initialisation("01101000010", 8);
   LFSR *l2 = initialisation("00001011001", 8);
   LFSR *l3 = initialisation("01100100100", 8);
   LFSR *l4 = initialisation("10010011110", 8);
   LFSR *l5 = initialisation("01111011011", 8);
   LFSR *l6 = initialisation("01101110010", 8);
   LFSR *l7 = initialisation("11001011010", 8);
   LFSR *l8 = initialisation("01101011100", 8);
   LFSR *l9 = initialisation("01110011000", 8);
   LFSR *l10 = initialisation("01100010111", 8);
   LFSR *l11 = initialisation("01101000010100010000", 16);

   assert_int_equal(25, generation(l1, 5));
   assert_int_equal(4, generation(l2, 5));
   assert_int_equal(30, generation(l3, 5));
   assert_int_equal(27, generation(l4, 5));
   assert_int_equal(18, generation(l5, 5));
   assert_int_equal(26, generation(l6, 5));
   assert_int_equal(28, generation(l7, 5));
   assert_int_equal(24, generation(l8, 5));
   assert_int_equal(23, generation(l9, 5));
   assert_int_equal(29, generation(l10, 5));

   destroy_lfsr(l1, 1);
   destroy_lfsr(l2, 1);
   destroy_lfsr(l3, 1);
   destroy_lfsr(l4, 1);
   destroy_lfsr(l5, 1);
   destroy_lfsr(l6, 1);
   destroy_lfsr(l7, 1);
   destroy_lfsr(l8, 1);
   destroy_lfsr(l9, 1);
   destroy_lfsr(l10, 1);
   destroy_lfsr(l11, 1);
}//fin test_generation()

static void test_string(){
   LFSR *l1 = initialisation("01101000010", 8);
   LFSR *l2 = initialisation("11010000101", 8);
   LFSR *l3 = initialisation("10100001011", 8);
   LFSR *l4 = initialisation("01000010110", 8);
   LFSR *l5 = initialisation("10000101100", 8);
   LFSR *l6 = initialisation("00001011001", 8);
   LFSR *l7 = initialisation("00010110010", 8);
   LFSR *l8 = initialisation("00101100100", 8);
   LFSR *l9 = initialisation("01011001001", 8);
   LFSR *l10 = initialisation("10110010010", 8);
   LFSR *l11 = initialisation("01100100100", 8);

   LFSR *l12 = initialisation("01101000010", 8);
   LFSR *l13 = initialisation("00001011001", 8);
   LFSR *l14 = initialisation("01100100100", 8);
   LFSR *l15 = initialisation("10010011110", 8);
   LFSR *l16 = initialisation("01111011011", 8);
   LFSR *l17 = initialisation("01101110010", 8);
   LFSR *l18 = initialisation("11001011010", 8);
   LFSR *l19 = initialisation("01101011100", 8);
   LFSR *l20 = initialisation("01110011000", 8);
   LFSR *l21 = initialisation("01100010111", 8);
   LFSR *l22 = initialisation("01011111101", 8);

   operation(l1);
   operation(l2);
   operation(l3);
   operation(l4);
   operation(l5);
   operation(l6);
   operation(l7);
   operation(l8);
   operation(l9);
   operation(l10);

   generation(l12, 5);
   generation(l13, 5);
   generation(l14, 5);
   generation(l15, 5);
   generation(l16, 5);
   generation(l17, 5);
   generation(l18, 5);
   generation(l19, 5);
   generation(l20, 5);
   generation(l21, 5);

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

   destroy_lfsr(l1, 1);
   destroy_lfsr(l2, 1);
   destroy_lfsr(l3, 1);
   destroy_lfsr(l4, 1);
   destroy_lfsr(l5, 1);
   destroy_lfsr(l6, 1);
   destroy_lfsr(l7, 1);
   destroy_lfsr(l8, 1);
   destroy_lfsr(l9, 1);
   destroy_lfsr(l10, 1);
   destroy_lfsr(l11, 1);

   destroy_lfsr(l12, 1);
   destroy_lfsr(l13, 1);
   destroy_lfsr(l14, 1);
   destroy_lfsr(l15, 1);
   destroy_lfsr(l16, 1);
   destroy_lfsr(l17, 1);
   destroy_lfsr(l18, 1);
   destroy_lfsr(l19, 1);
   destroy_lfsr(l20, 1);
   destroy_lfsr(l21, 1);
   destroy_lfsr(l22, 1);
}//fin test_string

static void test_fixture(){
   test_fixture_start();

   run_test(test_create_lfsr);
   run_test(test_operation);
   run_test(test_generation);
   run_test(test_string);

   test_fixture_end();
}//fin test_fixture()

static void all_tests(){
   test_fixture();
}//fin all_tests()

int main(){
   return run_tests(all_tests);
}//fin main()