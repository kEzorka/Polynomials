#pragma once

#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include "qt_headers.h"
#include "../../backend/includes/fraction.h"
#include "../../backend/includes/my_base.h"
//#include "ui_PolynomialsPrak.h"


class PolynomialsPrak : public QMainWindow {
    Q_OBJECT

public:
    PolynomialsPrak(QWidget* parent = nullptr);
    ~PolynomialsPrak();

    void AddWidgets();
    void Styling();
    void StylingBaseTable();
    void StylingPolynomialOperations();
    void StylingBaseOperations();
    void StylingPushToBase();
    void StylingTwoPolynomialOperations();
    void StylingOtherOperations();

    void Make();
    void MakeBaseTable();
    void MakePolynomialOperations();
    void MakeBaseOperations();
    void MakePushToBase();
    void MakeTwoPolynomialOperations();
    void MakeOtherOperations();

    void SetTmpElementsVisibleFalse();
    void UpdateBaseTable();

private:
    void clear();

    bool item_has_already_been_changed = false;

    Base<Polynomial> base_;
    //Ui::PolynomialsPrakClass ui;

    QWidget* window = new QWidget();
    QHBoxLayout* main_layout = new QHBoxLayout();


    QVBoxLayout* base_table_layout = new QVBoxLayout();
    QTableWidget* base_table = new QTableWidget();


    QVBoxLayout* enter_layout = new QVBoxLayout();

    bool get_value_of_polynomial_pressed = false;
    bool compare_polynomial_pressed = false;
    bool plus_polynomial_pressed = false;
    bool multiplie_polynomial_pressed = false;
    bool derivative_polynomial_pressed = false;
    bool divise_polynomial_pressed = false;
    bool get_int_solutions_of_polynomial_pressed = false;
    QHBoxLayout* polynomial_operations_layout = new QHBoxLayout();
    QPushButton* get_value_button = new QPushButton("P(data)");
    QPushButton* compare_button = new QPushButton("==");
    bool plus_or_minus_polynomials = true;
    QPushButton* plus_button = new QPushButton("+(-)");
    QPushButton* multiplicater_button = new QPushButton("*");
    bool divise_or_remain_polynomials = true;
    QPushButton* divison_button = new QPushButton("÷(%)");
    QPushButton* derivative_button = new QPushButton("d(n, varriable)");
    QPushButton* get_int_solutions_button = new QPushButton("Integer\nSolutions");


    QHBoxLayout* base_operations_layout = new QHBoxLayout();
    QPushButton* add_polynomial_button = new QPushButton("Enter polynomial");
    QPushButton* load_from_file_button = new QPushButton("Load from file");
    QPushButton* save_to_file_button = new QPushButton("Save to file");


    bool enter_polynomial_pressed = false;
    QHBoxLayout* push_to_base_layout = new QHBoxLayout();
    QLineEdit* push_to_base_line = new QLineEdit();
    QPushButton* save_to_base_button = new QPushButton("Save\nto base");


    int chosen_item_mode = 0;
    QVBoxLayout* two_polynomial_operations_main_layout = new QVBoxLayout();
    QHBoxLayout* two_polynomial_operations_first_layout = new QHBoxLayout();
    QLabel* first_polynomial_label = new QLabel();
    QLabel* operation_label = new QLabel();
    QPushButton* plus_or_minus_button = new QPushButton("+(-)");
    QPushButton* divise_or_remain_button = new QPushButton("÷(%)");
    QHBoxLayout* two_polynomial_operations_second_layout = new QHBoxLayout();
    QPushButton* result_button = new QPushButton("=");
    QLabel* second_polynomial_label = new QLabel();
    QHBoxLayout* two_polynomial_operations_ans_layout = new QHBoxLayout();
    QLabel* ans_label = new QLabel();
    QPushButton* push_to_base_button = new QPushButton("Save\nto base");
    QLabel* push_to_base_label = new QLabel("Save\nto base");


    int chosen_item_integer = 0;
    QVBoxLayout* integer_solutions_main_layout = new QVBoxLayout();
    QHBoxLayout* integer_solutions_enter_layout = new QHBoxLayout();
    QLabel* integer_solutions_label = new QLabel("Integer\nSolutions");
    QLabel* integer_solutions_polynomial_label = new QLabel();
    QHBoxLayout* integer_solutions_ans_layout = new QHBoxLayout();
    QPushButton* integer_result_button = new QPushButton("=");
    QLabel* ans_integer_label = new QLabel("Your answer will be here");


    int chosen_item_derivative = 0;
    QVBoxLayout* derivative_main_layout = new QVBoxLayout();
    QHBoxLayout* derivative_polynomial_layout = new QHBoxLayout();
    QLabel* derivative_operation_label = new QLabel("d(n, varriable)");
    QLabel* derivative_polynomial_label = new QLabel();
    QHBoxLayout* derivative_operations_layout = new QHBoxLayout();
    QPushButton* derivative_result_button = new QPushButton("=");
    QLineEdit* derivative_varriable_line = new QLineEdit();
    QLineEdit* derivative_num_line = new QLineEdit();
    QLabel* derivative_save_to_base_label = new QLabel("Save\nto base");
    QPushButton* derivative_save_to_base_button = new QPushButton("Save\nto base");
    QHBoxLayout* derivative_ans_layout = new QHBoxLayout();
    QLabel* derivative_ans_label = new QLabel("Your answer will be here");


    int chosen_item_get_value = 0;
    QVBoxLayout* get_value_main_layout = new QVBoxLayout();
    QHBoxLayout* get_value_polynomial_layout = new QHBoxLayout();
    QPushButton* get_value_result_button = new QPushButton("=");
    QLabel* get_value_operation_label = new QLabel("P(data)");
    QLabel* get_value_polynomial_label = new QLabel();
    QHBoxLayout* get_value_grid_and_spacer_layout = new QHBoxLayout();
    QGridLayout* get_value_value_layout = new QGridLayout();
    std::map<char, std::pair<QLabel*, QLineEdit*>> get_value_parametrs;
    QLabel* get_value_ans_label = new QLabel("Your answer will be here");
    QSpacerItem* get_value_spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);


    QSpacerItem* spacer_down = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);

    QMessageBox* MsgBox = new QMessageBox();
};
