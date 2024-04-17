#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QInputDialog"
#include "polynomial.h"
#include "dataBase.h"
#include "QComboBox"
#include "QMessageBox"
#include "QFileDialog"
#include "QFile"
#include "QProgressDialog"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(1);
    // ui->tableWidget->setDisabled(1);
    // ui->tableWidget->setRowCount(1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

auto base = new dataBase();

void MainWindow::on_pushButton_clicked()
{
    // QProgressDialog progress;
    // progress.setWindowModality(Qt::WindowModal);
    // progress.exec();

    // for (int i = 0; i < 100; i++) {
    //     progress.setValue(i);
    //     progress.show();

    // }
    // progress.setValue(100);


    QMessageBox msgBox;
    QString a = QInputDialog::getText(this, "", "Entire your polinomial", QLineEdit::Normal);
    if (a.isEmpty()) {
        msgBox.setText("Nothing was entered");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        int ret = msgBox.exec();
        return;
    }
    string b = a.toStdString();
    if (b[0] == '+') {
        b = b.substr(1, b.size() - 1);
    }

    int err = polynomial_check(b);



    if (err) {
        if (err == 7) {
            msgBox.setText("Expected variable found integer (ты вообще тепленький)");
        } else if (err == 1) {
            msgBox.setText("Expected variable found ???");
        } else if (err == 2) {
            msgBox.setText("Expected integer found ^");
        } else if (err == 3) {
            msgBox.setText("Expected integer found ???");
        } else if (err == 4 || err == 5) {
            msgBox.setText("Expected monomial found not monomial");
        } else if (err == 10) {
            msgBox.setText("Empty string");
        } else if (err == 11) {
            msgBox.setText("Unexpected symbol");
        }
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        int ret = msgBox.exec();
        return;
    }
    auto p = new polynomial(b);
    string null = "0";
    if (p->is_empty()) p->insert(new monomial(null));
     // base->insert(*p, 0);
    // msgBox.setText(*p;

    const int currentRow = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    QString tmp = QString::fromStdString(p->to_string());

    ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(tmp));
    // ui->tableWidget->
}




void MainWindow::on_pushButton_2_clicked()
{
    int n = QInputDialog::getInt(this, "", "Indicate the number", QLineEdit::Normal);
    ui->tableWidget->removeRow(n - 1);
}




void MainWindow::on_pushButton_3_clicked()
{
    const int currentRow = ui->tableWidget->rowCount();
    bool ok = false, ok2 = false;
    int fi = QInputDialog::getInt(this, "", "Indicate the number of first polinomial", ok);
    int se = QInputDialog::getInt(this, "", "Indicate the number of second polinomial", ok2);

    if (&fi == nullptr || &se == nullptr) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    if (fi > currentRow || se > currentRow || fi < 1 || se < 1) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    // std::msgBox.setText(fi << " " << se;
    QTableWidgetItem *a = ui->tableWidget->item(fi - 1, 0);
    QTableWidgetItem *b = ui->tableWidget->item(se - 1, 0);
    // if (a == nullptr) {
    //     std::msgBox.setText("blya";
    // }
    string s1 = a->text().toStdString();
    string s2 = b->text().toStdString();
    if (s1[0] == '+') {
        s1 = s1.substr(1, s1.size() - 1);
    }
    if (s2[0] == '+') {
        s2 = s2.substr(1, s2.size() - 1);
    }

    auto first = new polynomial(s1);
    auto second = new polynomial(s2);
    // msgBox.setText(*first << *second;
    auto third = *first + *second;

    string null = "0";
    if (third.is_empty()) {
        third.insert(new monomial(null));
    }

    // msgBox.setText(third;
    string res = "Result:" + third.to_string();
    // msgBox.setText(res;
    QString ans = QString::fromStdString(res);
    QMessageBox msgBox;
    msgBox.setText(ans);
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.setIcon(QMessageBox::Question);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Save:


        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString::fromStdString(third.to_string())));
        // Save was clicked
        break;
    }

}


void MainWindow::on_pushButton_4_clicked()
{
    const int currentRow = ui->tableWidget->rowCount();
    bool ok, ok2;
    int fi = QInputDialog::getInt(this, "", "Indicate the number of first polinomial", ok);

    // auto dialog = new QInputDialog(this, "", "Indicate the number of first polinomial");


    int se = QInputDialog::getInt(this, "", "Indicate the number of second polinomial", ok2);

    if (&fi == nullptr || &se == nullptr) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    if (fi > currentRow || se > currentRow || fi < 1 || se < 1) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    // std::msgBox.setText(fi << " " << se;
    QTableWidgetItem *a = ui->tableWidget->item(fi - 1, 0);
    QTableWidgetItem *b = ui->tableWidget->item(se - 1, 0);
    // if (a == nullptr) {
    //     std::msgBox.setText("blya";
    // }
    string s1 = a->text().toStdString();
    string s2 = b->text().toStdString();
    if (s1[0] == '+') {
        s1 = s1.substr(1, s1.size() - 1);
    }
    if (s2[0] == '+') {
        s2 = s2.substr(1, s2.size() - 1);
    }

    auto first = new polynomial(s1);
    auto second = new polynomial(s2);
    // msgBox.setText(*first << *second;
    auto third = *first * *second;
    // msgBox.setText(third;
    string res = "Result:" + third.to_string();
    // msgBox.setText(res;
    QString ans = QString::fromStdString(res);
    QMessageBox msgBox;
    msgBox.setText(ans);
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.setIcon(QMessageBox::Question);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Save:
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString::fromStdString(third.to_string())));
        // Save was clicked
        break;
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    bool ok = false, ok2 = false;
    int currentRow = ui->tableWidget->rowCount();
    int fi = QInputDialog::getInt(this, "", "Indicate the number of first polinomial", ok);
    int se = QInputDialog::getInt(this, "", "Indicate the number of second polinomial", ok2);
    if (&fi == nullptr || &se == nullptr) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    if (fi > currentRow || se > currentRow || fi < 1 || se < 1) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    // std::msgBox.setText(fi << " " << se;
    QTableWidgetItem *a = ui->tableWidget->item(fi - 1, 0);
    QTableWidgetItem *b = ui->tableWidget->item(se - 1, 0);
    // if (a == nullptr) {
    //     std::msgBox.setText("blya";
    // }
    string s1 = a->text().toStdString();
    string s2 = b->text().toStdString();
    if (s1[0] == '+') {
        s1 = s1.substr(1, s1.size() - 1);
    }
    if (s2[0] == '+') {
        s2 = s2.substr(1, s2.size() - 1);
    }

    auto first = new polynomial(s1);
    auto second = new polynomial(s2);
    bool flag = false;
    for (auto el : first->variable()) {
        if (el && !flag) {
            flag = true;
        } else if (el && flag) {
            QMessageBox msgBox;
            msgBox.setInformativeText("Too many variables");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
            return;
        }
    }
    bool flag2 = false;
    for (auto el : second->variable()) {
        if (el && !flag2) {
            flag2 = true;
        } else if (el && flag2) {
            QMessageBox msgBox;
            msgBox.setInformativeText("Too many variables");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
            return;
        }
    }
    try {
        auto third = (*first / *second).first;
        auto fourth = (*first / *second).second;
    } catch (int) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Delish na noll");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    auto third = (*first / *second).first;
    auto fourth = (*first / *second).second;
    fourth.normalize();
    string null = "0";
    if (fourth.is_empty()) {
        fourth.insert(new monomial(null));
    }

    string res = "Integer:" + third.to_string();    // msgBox.setText(res;
    QString ans = QString::fromStdString(res);
    QMessageBox msgBox;

    string res2 = "Remainder:" + fourth.to_string();
    QString ans2 = QString::fromStdString(res2);
    QMessageBox msgBox2;

    msgBox.setText(ans);
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.setIcon(QMessageBox::Question);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Save:
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString::fromStdString(third.to_string())));
        currentRow++;
        // Save was clicked
        break;
    }

    msgBox2.setText(ans2);
    msgBox2.setInformativeText("Do you want to save your changes?");
    msgBox2.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox2.setIcon(QMessageBox::Question);
    msgBox2.setDefaultButton(QMessageBox::Save);
    int ret2 = msgBox2.exec();
    switch (ret2) {
    case QMessageBox::Save:
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString::fromStdString(fourth.to_string())));
        // Save was clicked
        break;
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    const int currentRow = ui->tableWidget->rowCount();
    bool ok = false, ok2 = false;
    int fi = QInputDialog::getInt(this, "", "Indicate the number of first polinomial", ok);

    if (&fi == nullptr) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    if (fi > currentRow || fi < 1) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    QTableWidgetItem *a = ui->tableWidget->item(fi - 1, 0);

    string s1 = a->text().toStdString();

    if (s1[0] == '+') {
        s1 = s1.substr(1, s1.size() - 1);
    }


    auto first = new polynomial(s1);
    bool flag = false;
    for (auto el : first->variable()) {
        if (el && !flag) {
            flag = true;
        } else if (el && flag) {
            QMessageBox msgBox;
            msgBox.setInformativeText("Too many variables");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
            return;
        }
    }


    bool no = false;
    for (int i = 0; i < 26; ++i) {
        if (first->variabless()[i]) no = true;
    }
    if (!no) {
        QMessageBox msgBox;
        msgBox.setText("No any variable");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        return;
    }

    vector <long long> r = first->roots();



    string res = "Roots: ";
    for (auto & el : r) {
        res += std::to_string(el);
        res += "; ";
    }



    QString ans = QString::fromStdString(res);
    QMessageBox msgBox;
    msgBox.setText(ans);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();

}


void MainWindow::on_pushButton_7_clicked()
{
    const int currentRow = ui->tableWidget->rowCount();
    bool ok = false, ok2 = false;
    int fi = QInputDialog::getInt(this, "", "Indicate the number of first polinomial", ok);
    if (&fi == nullptr) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    if (fi > currentRow || fi < 1) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
         msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    QTableWidgetItem *a = ui->tableWidget->item(fi - 1, 0);

    string s1 = a->text().toStdString();

    if (s1[0] == '+') {
        s1 = s1.substr(1, s1.size() - 1);
    }

    if (s1 == "0") {
        string res = "Value:";

        res += s1;




        QString ans = QString::fromStdString(res);
        QMessageBox msgBox;
        msgBox.setText(ans);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        return;
    }


    auto first = new polynomial(s1);
    vector <int> val(26, 0);

    for (int i = 0; i < 26; ++i) {
        if (first->variable()[i]) {
            string print = "Input variable value:";
            print += (i + 'a');
            QString last = QString::fromStdString(print);
            int fi = QInputDialog::getInt(this, "", last);
            val[i] = fi;
        }
    }



    string res = "Value:";

    res += std::to_string(first->value(val));




    QString ans = QString::fromStdString(res);
    QMessageBox msgBox;
    msgBox.setText(ans);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}


void MainWindow::on_pushButton_8_clicked()
{
    const int currentRow = ui->tableWidget->rowCount();
    bool ok = false, ok2 = false;
    int fi = QInputDialog::getInt(this, "", "Indicate the number of first polinomial", ok);
    int se = QInputDialog::getInt(this, "", "Indicate the ordinal number", ok2);




    QString th = QInputDialog::getText(this, "", "Indicate the variable");
    if (&fi == nullptr || &se == nullptr) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    if (fi > currentRow || fi < 1 || se < 0) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    if (th.size() > 1 || th.size() == 0) {
        QMessageBox msgBox;
        msgBox.setInformativeText("String must contains 1 char");
        msgBox.setStandardButtons(QMessageBox::Ok);
         msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }





    QTableWidgetItem *a = ui->tableWidget->item(fi - 1, 0);

    string res = "Result:";

    string s1 = a->text().toStdString();

    if (s1[0] == '+') {
        s1 = s1.substr(1, s1.size() - 1);
    }


    auto first = new polynomial(s1);

    char need = th.toStdString()[0];



    auto second = first->derivative(se, need);

    res += second.to_string();

    QString ans = QString::fromStdString(res);
    QMessageBox msgBox;
    msgBox.setText(ans);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();

}


void MainWindow::on_pushButton_9_clicked()
{
    bool ok = false, ok2 = false;
    int currentRow = ui->tableWidget->rowCount();
    int fi = QInputDialog::getInt(this, "", "Indicate the number of first polinomial", ok);
    int se = QInputDialog::getInt(this, "", "Indicate the number of second polinomial", ok2);
    if (&fi == nullptr || &se == nullptr) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    if (fi > currentRow || se > currentRow || fi < 1 || se < 1) {
        QMessageBox msgBox;
        msgBox.setInformativeText("Index out of range");
        msgBox.setStandardButtons(QMessageBox::Ok);
         msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    // std::msgBox.setText(fi << " " << se;
    QTableWidgetItem *a = ui->tableWidget->item(fi - 1, 0);
    QTableWidgetItem *b = ui->tableWidget->item(se - 1, 0);

    string s1 = a->text().toStdString();
    string s2 = b->text().toStdString();


    QMessageBox msgBox;



    if (s1 == s2) {
        msgBox.setText("Polynomials equal");
    } else {
        msgBox.setText("Polynomials not equal");
    }
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}



void MainWindow::on_pushButton_10_clicked()
{
    int currentRow = ui->tableWidget->rowCount();

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "/Users/ker1l/Polynomial files/text.txt",
                                                    tr("Text files (*.txt)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setInformativeText("File dont exist");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < currentRow; ++i) {
        QTableWidgetItem *a = ui->tableWidget->item(i, 0);

        QString s1 = a->text();

        out << s1 << "\n";
    }

    file.close();
}


void MainWindow::on_pushButton_11_clicked()
{
    int currentRow = ui->tableWidget->rowCount();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Load from file"),
                                                    "/Users/ker1l/Polynomial files/text.txt",
                                                    tr("Text files (*.txt)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setInformativeText("File dont exist");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    vector <string> data;

    QTextStream in(&file);
    // You could use readAll() here, too.
    while (!in.atEnd()) {
        QString line = in.readLine();
        data.push_back(line.toStdString());
    }

    file.close();

    QMessageBox msgBox;



    for (int i = 0; i < data.size(); ++i) {
        string b = data[i];
        if (b[0] == '+') {
            b = b.substr(1, b.size() - 1);
        }
        int err = polynomial_check(b);

        if (err) {
            if (err == 7) {
                msgBox.setText("Expected variable found integer (ты вообще тепленький)");
            } else if (err == 1) {
                msgBox.setText("Expected variable found ???");
            } else if (err == 2) {
                msgBox.setText("Expected integer found ^");
            } else if (err == 3) {
                msgBox.setText("Expected integer found ???");
            } else if (err == 4 || err == 5) {
                msgBox.setText("Expected monomial found not monomial");
            } else if (err == 10) {
                msgBox.setText("Empty string");
            } else if (err == 11) {
                msgBox.setText("Unexpected symbol");
            }
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.setIcon(QMessageBox::Critical);
            int ret = msgBox.exec();
            continue;
        }
        auto p = new polynomial(b);

        const int currentRow = ui->tableWidget->rowCount();

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        QString tmp = QString::fromStdString(p->to_string());

        ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(tmp));
    }

}

