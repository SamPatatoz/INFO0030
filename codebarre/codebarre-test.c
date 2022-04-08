/**
 * codebarre-test.c
 * 
 * This file has the tests for all the setters 
 * 
 * @author: EL MASRI Sam s190377
 * @date: 03/04/2022
 * @projet: INFO0030 Projet 2
 */


#include "pnm.h"
#include "codebarre.h"
#include "codebarreCorrection.h"
#include "seatest.h"
#include <stdlib.h>


//-----------------------------------------------------------------------------

static void test_set_registration_number() {
    CODE *barCode = NULL;
    create_bar_code(&barCode);

    set_registration_number(barCode, 15);
    assert_int_equal(15, get_registration_number(barCode));

    free(barCode);
}

static void test_set_magic_number() {
    PNM *image = NULL;
    create_pnm(&image);

    set_magic_number(image, 1);
    assert_int_equal(1, get_magic_number(image));

    free(image);
}

static void test_set_nbr_columns() {
    PNM *image = NULL;
    create_pnm(&image);

    set_nbr_columns(image, 1);
    assert_int_equal(1, get_nbr_columns(image));

    free(image);
}

static void test_set_nbr_rows() {
    PNM *image = NULL;
    create_pnm(&image);

    set_nbr_rows(image, 1);
    assert_int_equal(1, get_nbr_rows(image));

    free(image);
}

static void test_set_max_value() {
    PNM *image = NULL;
    create_pnm(&image);

    set_max_value(image, 254);
    assert_int_equal(254, get_max_value(image));

    free(image);
}
//no more functions to check ???????



//-----------------------------------------------------------------------------

static void test_fixture() {
    test_fixture_start();

    run_test(test_set_registration_number);
    run_test(test_set_magic_number);
    run_test(test_set_nbr_columns);
    run_test(test_set_nbr_rows);
    run_test(test_set_max_value);

    test_fixture_end();

}

static void all_tests() {
    test_fixture();
}

int main () {
    return run_tests(all_tests);
}
