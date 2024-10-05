#include "../includes/main_window.h"

void PolynomialsPrak::StylingPolynomialOperations() {
    QString styler =
        "QPushButton {"
        "  border: 0px;"
        "  font-size: 16px;"
        "  background-color: #F5E2D8;"
        "  border-width: 4px;"
        "  border-color: #CE8468;"
        "  border-style: solid;"
        "  border-radius: 7px;"
        "}"
        "QPushButton:hover { "
        "  background-color: #E4CAB1;"
        "  border-color: #AD5A5A;"
        "}"
        "QPushButton:pressed { "
        "  background-color: #D8B79C;"
        "  border-color: #7D5050;"
        "}";
    get_value_button->setStyleSheet(styler);
    compare_button->setStyleSheet(styler);
    plus_button->setStyleSheet(styler);
    multiplicater_button->setStyleSheet(styler);
    divison_button->setStyleSheet(styler);
    derivative_button->setStyleSheet(styler);
    get_int_solutions_button->setStyleSheet(styler);
}

void PolynomialsPrak::MakePolynomialOperations() {
    get_value_button->setFixedSize(70, 50);
    compare_button->setFixedSize(50, 50);
    plus_button->setFixedSize(50, 50);
    multiplicater_button->setFixedSize(50, 50);
    divison_button->setFixedSize(50, 50);
    derivative_button->setFixedSize(110, 50);
    get_int_solutions_button->setFixedSize(110, 50);



    QObject::connect(get_value_button, &QPushButton::clicked, [&]() {
        if (!get_value_of_polynomial_pressed) {
            SetTmpElementsVisibleFalse();
            get_value_result_button->setVisible(true);
            get_value_operation_label->setVisible(true);
            get_value_polynomial_label->setVisible(true);
            get_value_ans_label->setVisible(true);
            get_value_of_polynomial_pressed = true;
        } else {
            SetTmpElementsVisibleFalse();
        }
        });

    QObject::connect(compare_button, &QPushButton::clicked, [&]() {
        ans_label->setFixedSize(526, 50);
        if (!compare_polynomial_pressed) {
            SetTmpElementsVisibleFalse();
            operation_label->setVisible(true);
            first_polynomial_label->setVisible(true);
            result_button->setVisible(true);
            second_polynomial_label->setVisible(true);
            ans_label->setVisible(true);
            operation_label->setText("==");
            compare_polynomial_pressed = true;
        } else {
            SetTmpElementsVisibleFalse();
        }
        compare_polynomial_pressed = compare_polynomial_pressed;
        });

    QObject::connect(plus_button, &QPushButton::clicked, [&]() {
        ans_label->setFixedSize(450, 50);
        if (!plus_polynomial_pressed) {
            SetTmpElementsVisibleFalse();
            plus_or_minus_button->setVisible(true);
            first_polynomial_label->setVisible(true);
            result_button->setVisible(true);
            second_polynomial_label->setVisible(true);
            ans_label->setVisible(true);
            push_to_base_label->setVisible(true);
            plus_polynomial_pressed = true;
        } else {
            SetTmpElementsVisibleFalse();
        }
        });

    QObject::connect(multiplicater_button, &QPushButton::clicked, [&]() {
        ans_label->setFixedSize(450, 50);
        if (!multiplie_polynomial_pressed) {
            SetTmpElementsVisibleFalse();
            operation_label->setVisible(true);
            first_polynomial_label->setVisible(true);
            result_button->setVisible(true);
            second_polynomial_label->setVisible(true);
            ans_label->setVisible(true);
            push_to_base_label->setVisible(true);
            operation_label->setText("*");
            multiplie_polynomial_pressed = true;
        } else {
            SetTmpElementsVisibleFalse();
        }
        });

    QObject::connect(derivative_button, &QPushButton::clicked, [&]() {
        ans_label->setFixedSize(450, 50);
        if (!derivative_polynomial_pressed) {
            SetTmpElementsVisibleFalse();
            derivative_operation_label->setVisible(true);
            derivative_polynomial_label->setVisible(true);
            derivative_result_button->setVisible(true);
            derivative_varriable_line->setVisible(true);
            derivative_num_line->setVisible(true);
            derivative_save_to_base_label->setVisible(true);
            derivative_ans_label->setVisible(true);
            derivative_polynomial_pressed = true;
        } else {
            SetTmpElementsVisibleFalse();
        }
        });

    QObject::connect(divison_button, &QPushButton::clicked, [&]() {
        ans_label->setFixedSize(450, 50);
        if (!divise_polynomial_pressed) {
            SetTmpElementsVisibleFalse();
            divise_or_remain_button->setVisible(true);
            first_polynomial_label->setVisible(true);
            result_button->setVisible(true);
            second_polynomial_label->setVisible(true);
            ans_label->setVisible(true);
            push_to_base_label->setVisible(true);
            divise_polynomial_pressed = true;
        } else {
            SetTmpElementsVisibleFalse();
        }
        });

    QObject::connect(get_int_solutions_button, &QPushButton::clicked, [&]() {
        ans_integer_label->setFixedSize(470, 50);
        if (!get_int_solutions_of_polynomial_pressed) {
            SetTmpElementsVisibleFalse();
            integer_solutions_label->setVisible(true);
            integer_solutions_polynomial_label->setVisible(true);
            integer_result_button->setVisible(true);
            ans_integer_label->setVisible(true);
            get_int_solutions_of_polynomial_pressed = true;
        } else {
            SetTmpElementsVisibleFalse();
        }
        });

    QObject::connect(plus_or_minus_button, &QPushButton::clicked, [&]() {
        if (!plus_or_minus_polynomials) {
            plus_or_minus_button->setText("+(-)");
            plus_or_minus_polynomials = true;
        } else {
            plus_or_minus_button->setText("-(+)");
            plus_or_minus_polynomials = false;
        }
        });

    QObject::connect(divise_or_remain_button, &QPushButton::clicked, [&]() {
        if (!divise_or_remain_polynomials) {
            divise_or_remain_button->setText("÷(%)");
            divise_or_remain_polynomials = true;
        } else {
            divise_or_remain_button->setText("%(÷)");
            divise_or_remain_polynomials = false;
        }
        });
}

