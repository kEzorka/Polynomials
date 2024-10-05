#include "../includes/main_window.h"

void PolynomialsPrak::StylingPushToBase() {
    push_to_base_line->setStyleSheet(
        "QLineEdit {"
        "  border: 0px;"
        "  font-size: 16px;"
        "  background-color: #F5E2D8;"
        "  border-width: 4px;"
        "  border-color: #CE8468;"
        "  border-style: solid;"
        "  border-radius: 7px;"
        "}"
    );
    save_to_base_button->setStyleSheet(
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
        "}"
    );
}

void PolynomialsPrak::MakePushToBase() {
    push_to_base_line->setFixedSize(450, 50);
    push_to_base_line->setPlaceholderText("Your polynomial");

    save_to_base_button->setFixedSize(70, 50);

    QObject::connect(save_to_base_button, &QPushButton::clicked, [&]() {
        try {
            std::string str = push_to_base_line->text().toStdString();
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
