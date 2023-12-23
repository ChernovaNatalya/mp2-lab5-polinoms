#include <gtest.h>
#include "TPolinom.h"

TEST(Polinom, Created_polinom_is_empty) {
	TPolinom polinom;
	EXPECT_EQ(true, polinom.IsEmpty());
}

TEST(Polinom, Created_polinom_with_one_monom_is_not_empty) {
	TPolinom polinom;
	polinom.AddMonom(TMonom(1, 1, 1, 1));
	EXPECT_EQ(false, polinom.IsEmpty());
}

TEST(Polinom, Coefficients_add_up_if_degrees_are_equal) {
	TPolinom polinom;
	polinom.AddMonom(TMonom(1, 1, 1, 1));
	polinom.AddMonom(TMonom(1, 1, 1, 1));
	EXPECT_EQ(2, polinom.GetCurrentItem().GetCoef());
}

TEST(Polinom, Coefficients_dont_add_up_if_degrees_are_different) {
	TPolinom polinom;
	polinom.AddMonom(TMonom(1, 1, 1, 1));
	polinom.AddMonom(TMonom(1, 2, 3, 4));
	EXPECT_EQ(1, polinom.GetCurrentItem().GetCoef());
}

TEST(Polinom, Monom_delete_if_coefficient_equal_zero) {
	TPolinom polinom;
	polinom.AddMonom(TMonom(1, 1, 1, 1));
	polinom.AddMonom(TMonom(-1, 1, 1, 1));
	EXPECT_EQ(1, polinom.IsEmpty());
}

TEST(Polinom, Can_not_get_monom_from_empty_polinom) {
	TPolinom polinom;
	ASSERT_ANY_THROW(polinom.GetCurrentItem());
}

TEST(Polinom, Copied_polinom_is_equal_copiable) {
	TPolinom polinom;
	polinom.AddMonom(TMonom(1, 2, 3, 4));
	TPolinom polinom2(polinom);
	bool ans = (polinom2 == polinom);
	EXPECT_EQ(ans, true);
}

TEST(Polinom, Assigned_polinom_is_equal_assignable) {
	TPolinom polinom;
	polinom.AddMonom(TMonom(1, 2, 3, 4));
	TPolinom polinom2 = polinom;
	bool ans = (polinom2 == polinom);
	EXPECT_EQ(ans, true);
}

TEST(Polinom, Correct_adding_operator) {
	TPolinom polinom;
	TMonom m2(1, 5, 3, 4);
	TMonom m1(1, 2, 3, 4);
	polinom.AddMonom(m2);
	polinom.AddMonom(m1);
	polinom.Reset();
	bool ans = (m1.GetCoef() == polinom.GetCurrentItem().GetCoef());
	ans = ans && (m1.GetIndex() == polinom.GetCurrentItem().GetIndex());
	polinom.GoNext();

	ans = ans && (m2.GetCoef() == polinom.GetCurrentItem().GetCoef());
	ans = ans && (m2.GetIndex() == polinom.GetCurrentItem().GetIndex());
	EXPECT_EQ(true, ans);
}

TEST(Polinom, Correct_constant_multiply) {
	TPolinom polinom;
	polinom.AddMonom(TMonom(3, 1, 2, 3));
	polinom.AddMonom(TMonom(2, 1, 4, 3));
	TPolinom polinom2 = polinom * 3;
	TPolinom polinom3;
	polinom3.AddMonom(TMonom(9, 1, 2, 3));
	polinom3.AddMonom(TMonom(6, 1, 4, 3));
	bool ans = (polinom2 == polinom3);
	EXPECT_EQ(true, ans);
}

TEST(Polinom, Correct_monom_multiply) {
	TPolinom polinom;
	polinom.AddMonom(TMonom(3, 1, 2, 3));
	polinom.AddMonom(TMonom(2, 1, 4, 3));
	polinom.AddMonom(TMonom(1, 1, 6, 3));
	polinom.MultMonom(TMonom(3, 1, 2, 3));
	bool ans = (polinom.GetCurrentItem() == TMonom(3, 1, 2, 3));
	EXPECT_EQ(true, ans);
}

TEST(Polinom, Correct_polinom_enter) {
	TPolinom p5("4X^9YZ - 5XZ");
	p5.Reset();
	TMonom m = p5.GetCurrentItem();
	p5.GoNext();
	TMonom m2 = p5.GetCurrentItem();
	bool ans = ((m2.coef == 4) && (m2.index == 911));
	ans = ans && ((m.coef == -5) && (m.index == 101));
	EXPECT_EQ(true, ans);
}

