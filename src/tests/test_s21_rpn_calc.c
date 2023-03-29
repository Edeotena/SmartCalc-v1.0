#include "tests/s21_tests.h"

START_TEST(rpn_calc_1) {
  queue *res;
  char *str = "5 + 6";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calculate(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, 11, EPS);

  free_queue(&res);
}
END_TEST

START_TEST(rpn_calc_2) {
  queue *res;
  char *str = "5 * 10 / 4";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calculate(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, 12.5, EPS);

  free_queue(&res);
}
END_TEST

START_TEST(rpn_calc_3) {
  queue *res;
  char *str = "sin(asin(1))";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calculate(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, 1, EPS);

  free_queue(&res);
}
END_TEST

START_TEST(rpn_calc_4) {
  queue *res;
  char *str = "sin(asin(sin(asin(sin(asin(sin(asin(1))))))))";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calculate(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, 1, EPS);

  free_queue(&res);
}
END_TEST

START_TEST(rpn_calc_5) {
  queue *res;
  char *str = "log(10 ^ 7)      ";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calculate(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, 7, EPS);

  free_queue(&res);
}
END_TEST

START_TEST(wr_rpn_calc_1) {
  queue *res;
  char *str = "3 + 5 5";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  calculate(rpn, 0, &code);
  ck_assert_int_eq(code, FAILURE);

  free_queue(&res);
}
END_TEST

Suite *rpn_calc_suite() {
  Suite *suite = suite_create("prn_calc_suite");
  TCase *tcase = tcase_create("prn_calc_suite");

  tcase_add_test(tcase, rpn_calc_1);
  tcase_add_test(tcase, rpn_calc_2);
  tcase_add_test(tcase, rpn_calc_3);
  tcase_add_test(tcase, rpn_calc_4);
  tcase_add_test(tcase, rpn_calc_5);
  tcase_add_test(tcase, wr_rpn_calc_1);

  suite_add_tcase(suite, tcase);
  return suite;
}