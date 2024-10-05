#include "../includes/main_window.h"

PolynomialsPrak::PolynomialsPrak(QWidget* parent) : QMainWindow(parent) {
    window->setWindowTitle("21");
    window->resize(900, 600);


    Make();
    Styling();
    AddWidgets();
    window->show();
}

void PolynomialsPrak::AddWidgets() {
    window->setLayout(main_layout);

    main_layout->addLayout(base_table_layout);
    main_layout->addLayout(enter_layout);


    base_table_layout->addWidget(base_table);


    enter_layout->addLayout(polynomial_operations_layout);
    enter_layout->addLayout(base_operations_layout);
    enter_layout->addLayout(push_to_base_layout);
    enter_layout->addLayout(two_polynomial_operations_main_layout);
    enter_layout->addLayout(integer_solutions_main_layout);
    enter_layout->addLayout(derivative_main_layout);
    enter_layout->addLayout(get_value_main_layout);


    polynomial_operations_layout->addWidget(get_value_button);
    polynomial_operations_layout->addWidget(compare_button);
    polynomial_operations_layout->addWidget(plus_button);
    polynomial_operations_layout->addWidget(multiplicater_button);
    polynomial_operations_layout->addWidget(derivative_button);
    polynomial_operations_layout->addWidget(divison_button);
    polynomial_operations_layout->addWidget(get_int_solutions_button);


    base_operations_layout->addWidget(add_polynomial_button);
    base_operations_layout->addWidget(load_from_file_button);
    base_operations_layout->addWidget(save_to_file_button);


    push_to_base_layout->addWidget(push_to_base_line);
    push_to_base_layout->addWidget(save_to_base_button);


    two_polynomial_operations_main_layout->addLayout(two_polynomial_operations_first_layout);
    two_polynomial_operations_first_layout->addWidget(plus_or_minus_button);
    two_polynomial_operations_first_layout->addWidget(divise_or_remain_button);
    two_polynomial_operations_first_layout->addWidget(operation_label);
    two_polynomial_operations_first_layout->addWidget(first_polynomial_label);

    two_polynomial_operations_main_layout->addLayout(two_polynomial_operations_second_layout);
    two_polynomial_operations_second_layout->addWidget(result_button);
    two_polynomial_operations_second_layout->addWidget(second_polynomial_label);

    two_polynomial_operations_main_layout->addLayout(two_polynomial_operations_ans_layout);
    two_polynomial_operations_ans_layout->addWidget(ans_label);
    two_polynomial_operations_ans_layout->addWidget(push_to_base_button);
    two_polynomial_operations_ans_layout->addWidget(push_to_base_label);


    integer_solutions_main_layout->addLayout(integer_solutions_enter_layout);
    integer_solutions_enter_layout->addWidget(integer_solutions_label);
    integer_solutions_enter_layout->addWidget(integer_solutions_polynomial_label);
    integer_solutions_main_layout->addLayout(integer_solutions_ans_layout);
    integer_solutions_ans_layout->addWidget(integer_result_button);
    integer_solutions_ans_layout->addWidget(ans_integer_label);



    derivative_main_layout->addLayout(derivative_polynomial_layout);
    derivative_polynomial_layout->addWidget(derivative_operation_label);
    derivative_polynomial_layout->addWidget(derivative_polynomial_label);

    derivative_main_layout->addLayout(derivative_operations_layout);
    derivative_operations_layout->addWidget(derivative_result_button);
    derivative_operations_layout->addWidget(derivative_varriable_line);
    derivative_operations_layout->addWidget(derivative_num_line);
    derivative_operations_layout->addWidget(derivative_save_to_base_label);
    derivative_operations_layout->addWidget(derivative_save_to_base_button);

    derivative_main_layout->addLayout(derivative_ans_layout);
    derivative_ans_layout->addWidget(derivative_ans_label);


    get_value_main_layout->addLayout(get_value_polynomial_layout);
    get_value_polynomial_layout->addWidget(get_value_result_button);
    get_value_polynomial_layout->addWidget(get_value_operation_label);
    get_value_polynomial_layout->addWidget(get_value_polynomial_label);

    get_value_main_layout->addLayout(get_value_grid_and_spacer_layout);
    get_value_grid_and_spacer_layout->addLayout(get_value_value_layout);
    get_value_grid_and_spacer_layout->addSpacerItem(get_value_spacer);
    for (int i = 0; i < 26; ++i) {
        char tmp_char = 'a';
        tmp_char += i;
        get_value_value_layout->addWidget(
            get_value_parametrs[tmp_char].first, i / 3, i % 3 * 3);
        get_value_value_layout->addWidget(
            get_value_parametrs[tmp_char].second, i / 3, i % 3 * 3 + 1);
    }

    get_value_main_layout->addWidget(get_value_ans_label);


    enter_layout->addSpacerItem(spacer_down);
}

void PolynomialsPrak::Styling() {
    window->setStyleSheet(
        "QWidget {"
        "  background-color: #F0C49F;"
        "}"
    );
    MsgBox->setStyleSheet(
        "QMessageBox QLabel {"
        "  background-color: #48A54C;"
        "  color: black;"
        "}"
        "QMessageBox {"
        "  background-color: #F0C49F;"
        "}"
        "QMessageBox QPushButton {"
        "  font-size: 16px;"
        "  background-color: #F5E2D8;"
        "  border-width: 4px;"
        "  border-color: #CE8468;"
        "  border-style: solid;"
        "  border-radius: 4px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "  background-color: #E4CAB1;"
        "  border-color: #AD5A5A;"
        "}"
        "QMessageBox QPushButton:pressed {"
        "  background-color: #D8B79C;"
        "  border-color: #7D5050;"
        "}"
        "QMessageBox QLabel {"
        "  font-size: 16px;"
        "  background-color: #F5E2D8;"
        "  border-width: 4px;"
        "  border-color: #CE8468;"
        "  border-style: solid;"
        "  border-radius: 4px;"
        "}"
    );
    StylingBaseTable();
    StylingPolynomialOperations();
    StylingBaseOperations();
    StylingPushToBase();
    StylingTwoPolynomialOperations();
    StylingOtherOperations();
}

void PolynomialsPrak::Make() {
    MakeBaseTable();
    MakePolynomialOperations();
    MakeBaseOperations();
    MakePushToBase();
    MakeTwoPolynomialOperations();
    MakeOtherOperations();
    SetTmpElementsVisibleFalse();
}

void PolynomialsPrak::SetTmpElementsVisibleFalse() {
    push_to_base_line->clear();
    push_to_base_line->setVisible(false);
    save_to_base_button->setVisible(false);


    plus_or_minus_button->setVisible(false);
    divise_or_remain_button->setVisible(false);
    operation_label->clear();
    operation_label->setVisible(false);
    first_polynomial_label->clear();
    first_polynomial_label->setVisible(false);
    second_polynomial_label->clear();
    second_polynomial_label->setVisible(false);
    ans_label->setText("Your answer will be here");
    divise_or_remain_button->setText("÷(%)");
    plus_or_minus_button->setText("+(-)");
    ans_label->setVisible(false);
    push_to_base_button->setVisible(false);
    result_button->setVisible(false);
    push_to_base_label->setVisible(false);


    integer_solutions_label->setVisible(false);
    integer_solutions_polynomial_label->clear();
    integer_solutions_polynomial_label->setVisible(false);
    integer_result_button->setVisible(false);
    ans_integer_label->setText("Your answer will be here");
    ans_integer_label->setVisible(false);


    derivative_operation_label->setVisible(false);
    derivative_polynomial_label->setVisible(false);
    derivative_polynomial_label->clear();
    derivative_result_button->setVisible(false);
    derivative_varriable_line->clear();
    derivative_varriable_line->setVisible(false);
    derivative_num_line->clear();
    derivative_num_line->setVisible(false);
    derivative_save_to_base_label->setVisible(false);
    derivative_save_to_base_button->setVisible(false);
    derivative_ans_label->setText("Your answer will be here");
    derivative_ans_label->setVisible(false);


    get_value_result_button->setVisible(false);
    get_value_operation_label->setVisible(false);
    get_value_polynomial_label->setVisible(false);
    get_value_polynomial_label->clear();
    for (int i = 0; i < 26; ++i) {
        char tmp_char = 'a';
        tmp_char += i;
        get_value_parametrs[tmp_char].first->setVisible(false);
        get_value_parametrs[tmp_char].second->setVisible(false);
        get_value_parametrs[tmp_char].second->clear();
    }
    get_value_ans_label->setVisible(false);
    get_value_ans_label->setText("Your answer will be here");


    enter_polynomial_pressed = false;

    plus_or_minus_polynomials = true;
    divise_or_remain_polynomials = true;

    get_value_of_polynomial_pressed = false;
    compare_polynomial_pressed = false;
    plus_polynomial_pressed = false;
    multiplie_polynomial_pressed = false;
    divise_polynomial_pressed = false;
    derivative_polynomial_pressed = false;
    get_int_solutions_of_polynomial_pressed = false;

    chosen_item_mode = 0;
    chosen_item_integer = 0;
    chosen_item_derivative = 0;
    chosen_item_get_value = 0;

    for (int i = 0; i < base_table->rowCount(); ++i) {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setBackground(QBrush(QColor(240, 225, 236)));
        //item->setTextAlignment(Qt::AlignCenter);
        Polynomial polynomial = base_[i];
        item->setText(QString::fromStdString(polynomial.to_string()));
        item->setSelected(false);
        base_table->setItem(i, 0, item);
    }
}

void PolynomialsPrak::UpdateBaseTable() {
    base_table->setRowCount(base_.size());
    for (int i = 0; i < base_.size(); ++i) {
        QTableWidgetItem* item = base_table->item(i, 0);
        if (item == nullptr) {
            item = new QTableWidgetItem();
        }
        //item->setBackground(Qt::red);
        //item->setTextAlignment(Qt::AlignCenter);
        Polynomial polynomial = base_[i];
        item->setText(QString::fromStdString(polynomial.to_string()));
        item->setSelected(false);
        base_table->setItem(i, 0, item);
    }
}

void PolynomialsPrak::clear() {
    /*delete window;
    delete main_layout;


    delete base_table_layout;
    delete base_table;


    delete enter_layout;

    delete polynomial_operations_layout;
    delete get_value_button;
    delete compare_button;
    delete plus_button;
    delete multiplicater_button;
    delete derivative_button;
    delete divison_button;
    delete get_int_solutions_button;


    delete base_operations_layout;
    delete add_polynomial_button;
    delete load_from_file_button;
    delete save_to_file_button;

    delete spacer_down;

    delete MsgBox;*/
}

PolynomialsPrak::~PolynomialsPrak() {
    //clear();
}
