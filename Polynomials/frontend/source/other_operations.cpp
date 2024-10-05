#include "../includes/main_window.h"

void PolynomialsPrak::StylingOtherOperations() {
    QString PushButtonStyler =
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
    QString LabelStyler =
        "QLabel {"
        "  border: 0px;"
        "  font-size: 16px;"
        "  background-color: #F5E2D8;"
        "  border-width: 4px;"
        "  border-color: #CE8468;"
        "  border-style: solid;"
        "  border-radius: 7px;"
        "}";
    QString LineStyler =
        "QLineEdit {"
        "  border: 0px;"
        "  font-size: 16px;"
        "  background-color: #F5E2D8;"
        "  border-width: 4px;"
        "  border-color: #CE8468;"
        "  border-style: solid;"
        "  border-radius: 7px;"
        "}";
    integer_result_button->setStyleSheet(PushButtonStyler);
    integer_solutions_polynomial_label->setStyleSheet(LabelStyler);
    ans_integer_label->setStyleSheet(LabelStyler);
    integer_solutions_label->setStyleSheet(LabelStyler);


    derivative_operation_label->setStyleSheet(LabelStyler);
    derivative_polynomial_label->setStyleSheet(LabelStyler);
    derivative_result_button->setStyleSheet(PushButtonStyler);
    derivative_varriable_line->setStyleSheet(LineStyler);
    derivative_num_line->setStyleSheet(LineStyler);
    derivative_save_to_base_label->setStyleSheet(LabelStyler);
    derivative_save_to_base_button->setStyleSheet(PushButtonStyler);
    derivative_ans_label->setStyleSheet(LabelStyler);


    get_value_result_button->setStyleSheet(PushButtonStyler);
    get_value_operation_label->setStyleSheet(LabelStyler);
    get_value_polynomial_label->setStyleSheet(LabelStyler);
    for (int i = 0; i < 26; ++i) {
        char tmp_char = 'a';
        tmp_char += i;
        get_value_parametrs[tmp_char].first->setStyleSheet(LabelStyler);
        get_value_parametrs[tmp_char].second->setStyleSheet(LineStyler);
    }
    get_value_ans_label->setStyleSheet(LabelStyler);
}

void PolynomialsPrak::MakeOtherOperations() {
    integer_solutions_label->setFixedSize(110, 50);
    integer_solutions_label->setAlignment(Qt::AlignCenter);
    integer_solutions_polynomial_label->setFixedSize(410, 50);
    integer_result_button->setFixedSize(50, 50);
    ans_integer_label->setFixedSize(470, 50);

    QObject::connect(integer_result_button, &QPushButton::clicked, [&]() {
        try {
            if (chosen_item_integer == 1) {
                std::vector<int64_t> solutions =
                    Polynomial(integer_solutions_polynomial_label->text().toStdString()).IntegerSolutions();
                std::string solutions_str = "{ ";
                for (size_t i = 0; i < solutions.size(); ++i) {
                    solutions_str += std::to_string(solutions[i]);
                    if (i + 1 < solutions.size()) {
                        solutions_str += "; ";
                    }
                }
                solutions_str += " }";
                ans_integer_label->setText(QString::fromStdString(solutions_str));
            }
        }
        catch (const std::exception& e) {
            MsgBox->setWindowTitle("Damn!");
            std::string exception;
            exception += "Exception: ";
            exception += e.what();
            MsgBox->setText(QString::fromStdString(exception));
            MsgBox->exec();
            item_has_already_been_changed = true;
            UpdateBaseTable();
            item_has_already_been_changed = false;
        }
        });




    derivative_operation_label->setFixedSize(110, 50);
    derivative_operation_label->setAlignment(Qt::AlignCenter);
    derivative_polynomial_label->setFixedSize(410, 50);
    derivative_result_button->setFixedSize(50, 50);
    derivative_varriable_line->setFixedSize(194, 50);
    derivative_varriable_line->setPlaceholderText("Your varriable");
    derivative_num_line->setFixedSize(194, 50);
    derivative_num_line->setPlaceholderText("Count to derivate");
    derivative_save_to_base_label->setFixedSize(70, 50);
    derivative_save_to_base_button->setFixedSize(70, 50);
    derivative_ans_label->setFixedSize(526, 50);


    QObject::connect(derivative_result_button, &QPushButton::clicked, [&]() {
        try {
            std::string str_varriable = derivative_varriable_line->text().toStdString();
            if (str_varriable.size() > 1) {
                derivative_varriable_line->setText("");
                throw std::runtime_error("Varrible contains only one symbol");
            } else if (str_varriable.size() == 1) {
                if (str_varriable[0] > 'z' || str_varriable[0] < 'a') {
                    derivative_varriable_line->setText("");
                    throw std::runtime_error("You can use only letters");
                }
            } else if (str_varriable.size() == 0) {
                throw std::runtime_error("Enter varriable");
            }
            std::string str_num = derivative_num_line->text().toStdString();
            int count_to_derivate = 0;
            if (str_num.size() == 0) {
                count_to_derivate = 1;
                derivative_num_line->setText("1");
            } else {
                for (int i = 0; i < str_num.size(); ++i) {
                    if (str_num[i] < '0' || str_num[i] > '9') {
                        count_to_derivate = 0;
                        throw std::runtime_error("Your count gotta contain only number");
                    } else {
                        count_to_derivate *= 10;
                        count_to_derivate += str_num[i] - '0';
                    }
                }
            }

            if (chosen_item_derivative == 0) {
                throw std::runtime_error("Enter polynomial");
            }

            derivative_ans_label->setText(QString::fromStdString(
                Polynomial(derivative_polynomial_label->text().toStdString())
                .derivative(count_to_derivate, str_varriable[0]).to_string()));
            derivative_save_to_base_label->setVisible(false);
            derivative_save_to_base_button->setVisible(true);
        }
        catch (const std::exception& e) {
            MsgBox->setWindowTitle("Damn!");
            std::string exception;
            exception += "Exception: ";
            exception += e.what();
            MsgBox->setText(QString::fromStdString(exception));
            MsgBox->exec();
            item_has_already_been_changed = true;
            UpdateBaseTable();
            item_has_already_been_changed = false;
        }
        });


    QObject::connect(derivative_save_to_base_button, &QPushButton::clicked, [&]() {
        try {
            std::string str = derivative_ans_label->text().toStdString();
            Polynomial polynomial(str);
            base_.push_back(polynomial);
            UpdateBaseTable();
            push_to_base_line->clear();
        }
        catch (const std::exception& e) {
            MsgBox->setWindowTitle("Damn!");
            std::string exception;
            exception += "Exception: ";
            exception += e.what();
            exception += "\n---------------------------\nAre you a 3 year old girl?";
            MsgBox->setText(QString::fromStdString(exception));
            MsgBox->exec();
            push_to_base_line->clear();
        }
        });



    get_value_result_button->setFixedSize(50, 50);
    get_value_operation_label->setFixedSize(70, 50);
    get_value_polynomial_label->setFixedSize(390, 50);
    for (int i = 0; i < 26; ++i) {
        char tmp_char = 'a';
        tmp_char += i;
        get_value_parametrs[tmp_char] = std::make_pair(new QLabel(), new QLineEdit());
        get_value_parametrs[tmp_char].first->setText(QString(tmp_char));
        get_value_parametrs[tmp_char].first->setAlignment(Qt::AlignCenter);
        get_value_parametrs[tmp_char].first->setMaximumHeight(50);
        get_value_parametrs[tmp_char].first->setFixedWidth(50);
        get_value_parametrs[tmp_char].second->setMaximumHeight(50);
        get_value_parametrs[tmp_char].second->setFixedWidth(115);
        get_value_parametrs[tmp_char].second->setPlaceholderText("value");
    }
    get_value_ans_label->setFixedSize(526, 50);


    QObject::connect(get_value_result_button, &QPushButton::clicked, [&]() {
        try {
            if (get_value_polynomial_label->text().isEmpty()) {
                throw std::logic_error("Enter your polynomial");
            }
            std::vector<char> vector_of_var =
                Polynomial(get_value_polynomial_label->text().toStdString()).get_all_variables();
            std::vector<std::pair<char, int>> for_result;
            for (int i = 0; i < vector_of_var.size(); ++i) {
                if (get_value_parametrs[vector_of_var[i]].second->text().isEmpty()) {
                    throw std::runtime_error("You gotta enter all values for your variables");
                }
                std::string string = get_value_parametrs[vector_of_var[i]].second->text().toStdString();
                int result_int = 0;
                bool sign = false;
                bool minus = false;
                for (int j = 0; j < string.size(); ++j) {
                    if (string[j] == '-' || string[j] == '+') {
                        if (!sign) {
                            sign = true;
                            if (string[i] == '-') {
                                minus = true;
                            }
                        } else {
                            throw std::logic_error("Your value gotta contain only one sign");
                        }
                        continue;
                    }
                    if (string[j] > '9' || string[j] < '0') {
                        get_value_parametrs[vector_of_var[i]].second->clear();
                        throw std::logic_error("Your value gotta contain only numbers");
                    }
                    result_int *= 10;
                    result_int += string[j] - '0';
                }
                if (minus) {
                    result_int = -result_int;
                }
                for_result.push_back(std::make_pair(vector_of_var[i], result_int));
            }
            Fraction result_to_ans =
                Polynomial(get_value_polynomial_label->text().toStdString()).result(for_result);
            get_value_ans_label->setText(QString::fromStdString(result_to_ans.to_string()));
        }
        catch (const std::exception& e) {
            MsgBox->setWindowTitle("Damn!");
            std::string exception;
            exception += "Exception: ";
            exception += e.what();
            exception += "\n---------------------------\nAre you a 3 year old girl?";
            MsgBox->setText(QString::fromStdString(exception));
            MsgBox->exec();
            push_to_base_line->clear();
        }
        });
}
