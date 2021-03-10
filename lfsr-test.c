#include "lfsr.h"
#include "seatest.h"

static void test_create_lfsr(){
   LFSR *register11tap8 = create_lfsr(11, "01101000010", 8);

   assert_int_equal(11, (int)get_N(register11tap8));
   assert_string_equal("01101000010", get_seed(register11tap8));
   assert_int_equal(8, (int)get_tap(register11tap8));

   destroy_lfsr(register11tap8, 1);
}//fin test_create_lfsr

/*
static void test_initialisation(){

}

static void test_operation(){

}

static void test_generation(){

}

static void test_string(){

}

*/
static void test_fixture(){
   test_fixture_start();

   run_test(test_create_lfsr);

   test_fixture_end();
}//fin test_fixture()

static void all_tests(){
   test_fixture();
}//fin all_tests()

int main(){
   LFSR *lfsr = initialisation("01101000010", 8);
   for(int i=0; i<10; i++){
      int r = generation(lfsr, 5);
      //affichage du registre résultat (avec la représentation en chaîne de
      //caractères du LFSR -- module string ()) et du bit retourné
      printf ("%s %d\n", string(lfsr), r);
   }//fin for - i

   //libération de la mémoire
   destroy_lfsr(lfsr, 1);
   
   return run_tests(all_tests);
}//fin main()