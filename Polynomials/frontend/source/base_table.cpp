#include "../includes/main_window.h"

void PolynomialsPrak::StylingBaseTable() {
    base_table->setStyleSheet(
        "QTableWidget{ "
        "  border: 0px;"
        "  font-size: 24px;"
        "  background-color: #f0e1ec;"
        "  border-width: 6px;"
        "  border-color: #997099;"
        "  border-style: solid;"
        "  border-radius: 6px;"
        "}"
        "QHeaderView {"
        "  background-color: #f0e1ec;"
        "}"
        "QHeaderView::section {"
        "  color: #31466B;"
        "  background-color: #CDB1C8;"
        "}"
        "QLineEdit { "
        "  border: 6px;"
        "  border-color: #ffccff;"
        "  font-size: 24px;"
        "  background-color: #ffccff;"
        "}"
        "QScrollBar { "
        "  background-color: #f0e1ec;"
        "}"
    );
}

void PolynomialsPrak::MakeBaseTable() {
    //base_table->verticalHeader()->setVisible(false);
    base_table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    base_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    base_table->verticalHeader()->setMinimumSectionSize(50);
    base_table->verticalHeader()->setDefaultSectionSize(50);
    base_table->horizontalHeader()->setVisible(false);
    base_table->setRowCount(0);
    base_table->setColumnCount(1);
    base_table->setMinimumWidth(100);
    base_table->setMinimumHeight(70);
    base_table->setSelectionMode(QAbstractItemView::NoSelection);
    for (int i = 0; i < base_table->rowCount(); ++i) {
        QTableWidgetItem* item = new QTableWidgetItem();
        //item->setBackground(Qt::red);
        //item->setTextAlignment(Qt::AlignCenter);
        item->setSelected(false);
        base_table->setItem(0, i, item);
    }
    QObject::connect(base_table, &QTableWidget::itemChanged, [&](QTableWidgetItem* item) {
        if (item_has_already_been_changed) {
            return;
        }
        try {
            Polynomial polynomial(item->text().toStdString());
            size_t row = item->row();
            base_[row] = polynomial;
            item_has_already_been_changed = true;
            UpdateBaseTable();
            item_has_already_been_changed = false;
        }
        catch (const std::exception& e) {
            MsgBox->setWindowTitle("Damn!");
            std::string exception;
            exception += "Exception: ";
            exception += e.what();
            MsgBox->setText(QString::fromStdString(exception));
            MsgBox->exec();
            base_.erase(item->row());
            item_has_already_been_changed = true;
            UpdateBaseTable();
            item_has_already_been_changed = false;
        }
        });

    QObject::connect(base_table, &QTableWidget::itemDoubleClicked, [&](QTableWidgetItem* item) {
        QBrush first_color = QBrush(QColor(199, 119, 122));
        QBrush second_color = QBrush(QColor(177, 217, 242));
        QBrush main_color = QBrush(QColor(240, 225, 236));
        if (compare_polynomial_pressed || plus_polynomial_pressed
            || multiplie_polynomial_pressed || divise_polynomial_pressed) {
            if (chosen_item_mode == 0) {
                chosen_item_mode = 1;
                item->setBackground(first_color);
                first_polynomial_label->setText(item->text());
                if (plus_polynomial_pressed || divise_polynomial_pressed
                    || multiplie_polynomial_pressed) {
                    push_to_base_label->setVisible(true);
                    push_to_base_button->setVisible(false);
                }
                ans_label->setText("Your answer will be here");
            } else if (chosen_item_mode == 1) {
                if (item->background() == first_color) {
                    item->setBackground(QBrush(QColor(240, 225, 236)));
                    first_polynomial_label->setText("");
                    chosen_item_mode = 0;
                } else {
                    chosen_item_mode = 2;
                    second_polynomial_label->setText(item->text());
                    item->setBackground(second_color);
                }
                if (plus_polynomial_pressed || divise_polynomial_pressed
                    || multiplie_polynomial_pressed) {
                    push_to_base_label->setVisible(true);
                    push_to_base_button->setVisible(false);
                }
                ans_label->setText("Your answer will be here");
            } else if (chosen_item_mode == 2) {
                if (item->background() == second_color) {
                    item->setBackground(main_color);
                    chosen_item_mode = 1;
                    second_polynomial_label->setText("");
                    if (plus_polynomial_pressed || divise_polynomial_pressed
                        || multiplie_polynomial_pressed) {
                        push_to_base_label->setVisible(true);
                        push_to_base_button->setVisible(false);
                    }
                    ans_label->setText("Your answer will be here");
                } else if (item->background() == first_color) {
                    item->setBackground(main_color);
                    for (int i = 0; i < base_table->rowCount(); ++i) {
                        if (base_table->item(i, 0)->background() == second_color) {
                            base_table->item(i, 0)->setBackground(first_color);
                            break;
                        }
                    }
                    first_polynomial_label->setText(second_polynomial_label->text());
                    second_polynomial_label->setText("");
                    chosen_item_mode = 1;
                    if (plus_polynomial_pressed || divise_polynomial_pressed
                        || multiplie_polynomial_pressed) {
                        push_to_base_label->setVisible(true);
                        push_to_base_button->setVisible(false);
                    }
                    ans_label->setText("Your answer will be here");
                }
            }
        } else if (get_int_solutions_of_polynomial_pressed) {
            if (chosen_item_integer == 0) {
                chosen_item_integer = 1;
                item->setBackground(first_color);
                integer_solutions_polynomial_label->setText(item->text());
                ans_integer_label->setText("Your answer will be here");
            } else if (chosen_item_integer == 1) {
                if (item->background() == first_color) {
                    chosen_item_integer = 0;
                    item->setBackground(main_color);
                    ans_integer_label->setText("Your answer will be here");
                    integer_solutions_polynomial_label->setText("");
                }
            }
        } else if (derivative_polynomial_pressed) {
            if (chosen_item_derivative == 0) {
                chosen_item_derivative = 1;
                item->setBackground(first_color);
                derivative_polynomial_label->setText(item->text());
                derivative_ans_label->setText("Your answer will be here");
            } else if (chosen_item_derivative == 1) {
                if (item->background() == first_color) {
                    chosen_item_derivative = 0;
                    item->setBackground(main_color);
                    derivative_ans_label->setText("Your answer will be here");
                    derivative_polynomial_label->setText("");
                    derivative_varriable_line->setText("");
                    derivative_num_line->setText("");
                }
            }
        } else if (get_value_of_polynomial_pressed) {
            if (chosen_item_get_value == 0) {
                chosen_item_get_value = 1;
                item->setBackground(first_color);
                get_value_polynomial_label->setText(item->text());
                get_value_ans_label->setText("Your answer will be here");
                std::vector<char> vector_of_var = Polynomial(item->text().toStdString()).get_all_variables();
                for (int i = 0; i < vector_of_var.size(); ++i) {
                    get_value_value_layout->addWidget(
                        get_value_parametrs[vector_of_var[i]].first, i / 3, i % 3 * 3);
                    get_value_parametrs[vector_of_var[i]].first->setVisible(true);
                    get_value_parametrs[vector_of_var[i]].second->setVisible(true);
                    get_value_value_layout->addWidget(
                        get_value_parametrs[vector_of_var[i]].second, i / 3, i % 3 * 3 + 1);
                }
            } else if (chosen_item_get_value == 1) {
                if (item->background() == first_color) {
                    chosen_item_get_value = 0;
                    item->setBackground(main_color);
                    get_value_ans_label->setText("Your answer will be here");
                    get_value_polynomial_label->setText("");
                    for (int i = 0; i < 26; ++i) {
                        char tmp_char = 'a';
                        tmp_char += i;
                        get_value_parametrs[tmp_char].first->setVisible(false);
                        get_value_parametrs[tmp_char].second->setVisible(false);
                        get_value_parametrs[tmp_char].second->clear();
                    }
                }
            }
        }
        });
}
