/**
 * pnm_tests.c
 * 
 * Ce fichier contient les tests unitaires de pnm.h
 * 
 * @author: Dumoulin Peissone S193957
 * @date: 21/03/21
 * @projet: INFO0030 Projet 2
 */

#include <stdio.h>
#include <stdlib.h>
#include "pnm.h"
#include "seatest.h"

static void test_load_pnm(){
   PNM *image;
   load_pnm(&image, "monalisa.pgm");

   assert_string_contains("P2", get_magicNumber(image));
   assert_int_equal(250, (int)get_columns(image));
   assert_int_equal(360, (int)get_rows(image));
   assert_int_equal(255, (int)get_maxValuePixel(image));
}

static void test_write_pnm(){
   PNM *image, *image2;
   load_pnm(&image, "monalisa.pgm");
   write_pnm(image, "monalisa_copie.pgm");
   load_pnm(&image2, "monalisa_copie.pgm");

   assert_string_contains("P2", get_magicNumber(image));
   assert_int_equal(250, (int)get_columns(image));
   assert_int_equal(360, (int)get_rows(image));
   assert_int_equal(255, (int)get_maxValuePixel(image));

   for(unsigned short i = 0; i < get_rows(image); i++){
      for(unsigned short j = 0; j < get_columns(image); j++){
         assert_int_equal((int)get_matrix(image2)[i][j], (int)get_matrix(image)[i][j]);
      }
   }
}

static void test_fixture(){
   test_fixture_start();

   run_test(test_load_pnm);
   run_test(test_write_pnm);

   test_fixture_end();
}//fin test_fixture()

static void all_tests(){
   test_fixture();
}//fin all_tests()

int main(){
   return run_tests(all_tests);
}//fin main()