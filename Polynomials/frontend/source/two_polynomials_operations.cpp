#include "../includes/main_window.h"

void PolynomialsPrak::StylingTwoPolynomialOperations() {
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
    first_polynomial_label->setStyleSheet(LabelStyler);
    operation_label->setStyleSheet(LabelStyler);
    plus_or_minus_button->setStyleSheet(PushButtonStyler);
    divise_or_remain_button->setStyleSheet(PushButtonStyler);
    result_button->setStyleSheet(PushButtonStyler);
    second_polynomial_label->setStyleSheet(LabelStyler);
    ans_label->setStyleSheet(LabelStyler);
    push_to_base_button->setStyleSheet(PushButtonStyler);
    push_to_base_label->setStyleSheet(LabelStyler);
}

void PolynomialsPrak::MakeTwoPolynomialOperations() {
    operation_label->setFixedSize(50, 50);
    operation_label->setAlignment(Qt::AlignCenter);

    result_button->setFixedSize(50, 50);
    first_polynomial_label->setFixedSize(470, 50);
    second_polynomial_label->setFixedSize(470, 50);

    ans_label->setFixedSize(450, 50);
    ans_label->setText("Your answer will be here");

    plus_or_minus_button->setFixedSize(50, 50);
    divise_or_remain_button->setFixedSize(50, 50);

    push_to_base_button->setFixedSize(70, 50);
    push_to_base_label->setFixedSize(70, 50);
    push_to_base_label->setAlignment(Qt::AlignCenter);


    QObject::connect(result_button, &QPushButton::clicked, [&]() {
        try {
            if (compare_polynomial_pressed) {
                if (chosen_item_mode == 2) {
                    if (Polynomial(first_polynomial_label->text().toStdString()) ==
                        Polynomial(second_polynomial_label->text().toStdString())) {
                        ans_label->setText("same");
                    } else {
                        ans_label->setText("differnet");
                    }
                }
            } else if (plus_polynomial_pressed) {
                if (chosen_item_mode == 2) {
                    if (plus_or_minus_polynomials) {
                        ans_label->setText(QString::fromStdString(
                            (Polynomial(first_polynomial_label->text().toStdString()) +
                                Polynomial(second_polynomial_label->text().toStdString())).to_string()));
                        push_to_base_label->setVisible(false);
                        push_to_base_button->setVisible(true);
                    } else {
                        ans_label->setText(QString::fromStdString(
                            (Polynomial(first_polynomial_label->text().toStdString()) -
                                Polynomial(second_polynomial_label->text().toStdString())).to_string()));
                        push_to_base_label->setVisible(false);
                        push_to_base_button->setVisible(true);
                    }
                }
            } else if (multiplie_polynomial_pressed) {
                if (chosen_item_mode == 2) {
                    ans_label->setText(QString::fromStdString(
                        (Polynomial(first_polynomial_label->text().toStdString()) *
                            Polynomial(second_polynomial_label->text().toStdString())).to_string()));
                    push_to_base_label->setVisible(false);
                    push_to_base_button->setVisible(true);
                }
            } else if (divise_polynomial_pressed) {
                if (chosen_item_mode == 2) {
                    if (divise_or_remain_polynomials) {
                        ans_label->setText(QString::fromStdString(
                            (Polynomial(first_polynomial_label->text().toStdString()) /
                                Polynomial(second_polynomial_label->text().toStdString())).to_string()));
                        push_to_base_label->setVisible(false);
                        push_to_base_button->setVisible(true);
                    } else {
                        Polynomial polynomial1(first_polynomial_label->text().toStdString());
                        Polynomial polynomial2(second_polynomial_label->text().toStdString());
                        ans_label->setText(QString::fromStdString((polynomial1 % polynomial2).to_string()));
                        push_to_base_label->setVisible(false);
                        push_to_base_button->setVisible(true);
                    }
                }
            }
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


    QObject::connect(push_to_base_button, &QPushButton::clicked, [&]() {
        try {
            std::string str = ans_label->text().toStdString();
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
}
