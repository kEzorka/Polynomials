#include "../includes/main_window.h"

void PolynomialsPrak::StylingBaseOperations() {
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
    add_polynomial_button->setStyleSheet(styler);
    load_from_file_button->setStyleSheet(styler);
    save_to_file_button->setStyleSheet(styler);
}


void PolynomialsPrak::MakeBaseOperations() {
    add_polynomial_button->setFixedSize(170, 50);
    load_from_file_button->setFixedSize(170, 50);
    save_to_file_button->setFixedSize(170, 50);

    QObject::connect(add_polynomial_button, &QPushButton::clicked, [&]() {
        if (!enter_polynomial_pressed) {
            SetTmpElementsVisibleFalse();
            push_to_base_line->setVisible(true);
            save_to_base_button->setVisible(true);
            enter_polynomial_pressed = true;
        } else {
            SetTmpElementsVisibleFalse();
        }
        });

    QObject::connect(save_to_file_button, &QPushButton::clicked, [&]() {
        QString file_name = QFileDialog::getSaveFileName(this,
        "Save file", QString(), "Text files (*.txt)");
    if (!file_name.isEmpty()) {
        try {
            base_.SaveToFile(file_name.toStdString());
        }
        catch (const std::exception& e) {
            MsgBox->setWindowTitle("Damn!");
            std::string exception;
            exception += "Exception: ";
            exception += e.what();
            MsgBox->setText(QString::fromStdString(exception));
            MsgBox->exec();
            base_.clear();
            UpdateBaseTable();
        }
        MsgBox->setWindowTitle("Hooray!");
        MsgBox->setText("Saved successfully!");
        MsgBox->exec();
    }
        });

    QObject::connect(load_from_file_button, &QPushButton::clicked, [&]() {
        QString file_name = QFileDialog::getOpenFileName(this, "Upload a file",
        "../../../Polynomials/frontend", "Text files (*.txt)");
    if (!file_name.isEmpty()) {
        bool check = base_.LoadFromFile(file_name.toStdString());
        SetTmpElementsVisibleFalse();
        UpdateBaseTable();
        if (check) {
            MsgBox->setWindowTitle("Hooray!");
            MsgBox->setText("Uploaded successfully!");
            MsgBox->exec();
        } else {
            MsgBox->setWindowTitle("Damn!");
            std::string exception;
            exception += "Exception: can't download all polynomials";
            MsgBox->setText(QString::fromStdString(exception));
            MsgBox->exec();
        }
    }
        });
}
