#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initialize();
}

MainWindow::~MainWindow()
{
    QSettings settings("Intel", "Terralogic");
    settings.setValue("Author", ui->author_line->text());
    delete this->testCaseID_line;
    delete this->testCaseID_cb;
    settings.value("Author");
    delete ui;
}

bool MainWindow::initialize() {

    pyW = new Wrapper();
    pyW->createToken();

    QSettings settings("Intel", "Terralogic");
    if (settings.value("Author") != "") {
        QString author = settings.value("Author").toString();
        ui->author_line->setText(author);
    }

    QStringList formType = {"Added New", "Updated", "Deleted"};
    ui->type_cb->addItems(formType);

    QStringList sheets = pyW->getSheets();
    ui->testSuite_cb->addItems(sheets);

    QDateTime date = QDateTime::currentDateTime();
    ui->dateEdit->setDateTime(date);

    this->testCaseID_line = new QLineEdit();
    QString newTestCaseID = this->createTestCaseID();
    this->testCaseID_line->setText(newTestCaseID);
    this->testCaseID_cb = new QComboBox();
    ui->stackedWidget->addWidget(testCaseID_line);
    ui->stackedWidget->addWidget(testCaseID_cb);
    ui->stackedWidget->setCurrentWidget(testCaseID_line);
    int swHeight = ui->stackedWidget->fontMetrics().height();
    ui->stackedWidget->setFixedHeight(swHeight + 10);

    //get font metric height
    int fmhTestDes = ui->testDes_le->fontMetrics().height();
    ui->testDes_le->setFixedHeight(fmhTestDes*2 + 10);
    int fmhExpectResult = ui->er_le->fontMetrics().height();
    ui->er_le->setFixedHeight(fmhExpectResult*3 + 10);
    int fmhNote = ui->note_le->fontMetrics().height();
    ui->note_le->setFixedHeight(fmhNote*3 + 10);

    QStringList validTCs = {"Yes", "No"};
    ui->valid_cb->addItems(validTCs);

    QStringList autoAvailability = {"Not yet", "Can", "Can not", "Done", "Delete"};
    ui->autoAvai_cb->addItems(autoAvailability);

    QObject::connect(ui->pushButton, &QPushButton::pressed, this, &MainWindow::close);
    QObject::connect(ui->pushButton_2, &QPushButton::pressed, this, &MainWindow::Finished);
    QObject::connect(ui->type_cb, &QComboBox::currentTextChanged, this, &MainWindow::changeType);
    QObject::connect(ui->testSuite_cb, &QComboBox::currentTextChanged, this, &MainWindow::changeTestSuite);
    // ui->type_cb->currentTextChanged("New");
    return true;
}

void MainWindow::changeType() {
    qDebug() << "Changed" << endl;
    if (ui->type_cb->currentText() == "Added New") {
        this->change2New();
        return;
    }
    else
    if ( ui->type_cb->currentText() == "Updated") {
        this->change2Update();
        return;
    }
    this->change2Delete();
    return;
}

void MainWindow::change2New() {
    qDebug() << "New" << endl;

    ui->stackedWidget->setCurrentWidget(this->testCaseID_line);

    //2. Create test case ID
    QString currTestSuite = ui->testSuite_cb->currentText();
    QLineEdit* le = static_cast<QLineEdit*>(ui->stackedWidget->currentWidget());
    qDebug() << "?????" << endl;
    le->setText(this->createTestCaseID());
    //check if testcaseID already exist ??

    //3. Change button
    ui->func_le->setReadOnly(false);
    ui->testDes_le->setReadOnly(false);
    ui->steps_le->setReadOnly(false);
    ui->er_le->setReadOnly(false);
    ui->ri_le->setReadOnly(false);
    ui->note_le->setReadOnly(false);
    ui->valid_cb->setDisabled(false);
    ui->autoAvai_cb->setDisabled(false);
    ui->func_le->setText("");
    ui->testDes_le->setText("");
    ui->steps_le->setText("");
    ui->er_le->setText("");
    ui->ri_le->setText("");
    ui->note_le->setText("");
    ui->valid_cb->setCurrentText("Yes");
    ui->autoAvai_cb->setCurrentText("Not yet");
    ui->pushButton_2->setText("Add");
}

void MainWindow::change2Update() {
    qDebug() << "Update" << endl;
    this->updateOrDelete();
    ui->func_le->setReadOnly(false);
    ui->testDes_le->setReadOnly(false);
    ui->steps_le->setReadOnly(false);
    ui->er_le->setReadOnly(false);
    ui->ri_le->setReadOnly(false);
    ui->note_le->setReadOnly(false);
    ui->valid_cb->setDisabled(false);
    ui->autoAvai_cb->setDisabled(false);
    ui->pushButton_2->setText("Update");
}

void MainWindow::change2Delete() {
    qDebug() << "Delete" << endl;
    this->updateOrDelete();
    ui->func_le->setReadOnly(true);
    ui->testDes_le->setReadOnly(true);
    ui->steps_le->setReadOnly(true);
    ui->er_le->setReadOnly(true);
    ui->ri_le->setReadOnly(true);
    ui->note_le->setReadOnly(true);
    ui->valid_cb->setDisabled(true);
    ui->autoAvai_cb->setDisabled(true);
    ui->pushButton_2->setText("Delete");
}

void MainWindow::updateOrDelete() {
    qDebug() << "update or delete" <<endl;
    ui->stackedWidget->setCurrentWidget(this->testCaseID_cb);
    QObject::connect(ui->testSuite_cb, &QComboBox::currentTextChanged, this, &MainWindow::changeTestSuite);
    QObject::connect(this->testCaseID_cb, &QComboBox::currentTextChanged, this, &MainWindow::changeTestCaseID);
    QComboBox* cb = static_cast<QComboBox*>(ui->stackedWidget->currentWidget());
    cb->clear();
    QStringList testCaseIDs = pyW->getTestCaseIDs(ui->testSuite_cb->currentText());
    cb->addItems(testCaseIDs);
}

void MainWindow::changeTestSuite() {
    qDebug() << "changeTestSuite" << endl;
    if (ui->type_cb->currentText() == "Added New") {
        static_cast<QLineEdit*>(ui->stackedWidget->currentWidget())->setText(this->createTestCaseID());
    }
    else {
        //Update or Delete
        QComboBox* cb = static_cast<QComboBox*>(ui->stackedWidget->currentWidget());
        cb->clear();
        QStringList testCaseIDs = pyW->getTestCaseIDs(ui->testSuite_cb->currentText());
        // qDebug() << testCaseIDs << endl;
        cb->addItems(testCaseIDs);
    }
}

void MainWindow::changeTestCaseID() {
    qDebug() << "changeTestCaseID" << endl;
    QString testSuite = ui->testSuite_cb->currentText();
    QString testCaseID = static_cast<QComboBox*>(ui->stackedWidget->currentWidget())->currentText();
    if (testCaseID == "") {
        return;
    }
    // qDebug() << testSuite << " " << testCaseID << endl;
    QString data = pyW->getData(testSuite, testCaseID);
    // qDebug() << data << endl;
    data = data.left(data.length()-3);
    QStringList dataList = data.mid(2, data.length()-2).split("', '");
    // qDebug() << dataList << endl;
    ui->func_le->setText(dataList[1]);
    // qDebug() << ui->testDes_le->acceptRichText();

    ui->testDes_le->setAcceptRichText(true);
    ui->testDes_le->setText("");
    for (auto line : dataList[2].split("\\n")) {
        ui->testDes_le->append(line);
    }
    ui->steps_le->setText("");
    ui->steps_le->setAcceptRichText(true);
    for (auto line : dataList[3].split("\\n")) {
        ui->steps_le->append(line);
    }
    ui->er_le->setText("");
    ui->er_le->setAcceptRichText(true);
    for (auto line : dataList[4].split("\\n")) {
        ui->er_le->append(line);
    }
    ui->valid_cb->setCurrentText(dataList[5]);
    ui->autoAvai_cb->setCurrentText(dataList[6]);
    ui->ri_le->setText("");
    if (dataList.length() >=8)
        ui->ri_le->setText(dataList[7]);
    ui->note_le->setText("");
    if (dataList.length() ==9) {
        for (auto line : dataList[8].split("\\n")) {
            ui->note_le->append(line);
        }
    }
}

QString MainWindow::createTestCaseID() {
    QString latestID = pyW->getTestCaseIDs(ui->testSuite_cb->currentText()).last();
    QStringList a = latestID.split("_");
    return a[0] + "_" + QString::number(a[1].toInt() + 1);
}

void MainWindow::Finished() {
    {
        QString Author = ui->author_line->text();
        QString Type = ui->type_cb->currentText();
        QString Date = ui->dateEdit->text();
        QString TestSuite = ui->testSuite_cb->currentText();
        QString TestCaseID;
        QString Functionality = ui->func_le->text();
        QString TestDescription = ui->testDes_le->toPlainText();
        QString Steps = ui->steps_le->toPlainText();
        QString ER = ui->er_le->toPlainText();
        QString RI = ui->ri_le->text();
        QString Note = ui->note_le->toPlainText();
        QString ValidTCs = ui->valid_cb->currentText();
        QString Automation = ui->autoAvai_cb->currentText();

        QString result;

        if (ui->pushButton_2->text() == "Add") {
            TestCaseID = static_cast<QLineEdit*>(ui->stackedWidget->currentWidget())->text();
            QString add_args =
                                "\"4"+TestSuite+"\" "+
                                "\"5"+TestCaseID+"\" "+
                                "\"6"+Functionality+"\" "+
                                "\"7"+TestDescription+"\" "+
                                "\"8"+Steps+"\" "+
                                "\"9"+ER+"\" "+
                                "\"A"+ValidTCs+"\" "+
                                "\"B" +Automation+"\" "+
                                /*"1"+Author+" "+\*/
                                /*"2:"+Type+" "+\*/
                                /*"3"+Date+" "+\*/
                                "\"C"+RI+"\" "+
                                "\"D"+Note+"\"";

            result = pyW->Add(add_args);
        }
        if (ui->pushButton_2->text() == "Update") {
            TestCaseID = static_cast<QComboBox*>(ui->stackedWidget->currentWidget())->currentText();
            QString update_args =
                                "\"4"+TestSuite+"\" "+
                                "\"5"+TestCaseID+"\" "+
                                "\"6"+Functionality+"\" "+
                                "\"7"+TestDescription+"\" "+
                                "\"8"+Steps+"\" "+
                                "\"9"+ER+"\" "+
                                "\"A"+ValidTCs+"\" "+
                                "\"B" +Automation+"\" "+
                                /*"1"+Author+" "+\*/
                                /*"2:"+Type+" "+\*/
                                /*"3"+Date+" "+\*/
                                "\"C"+RI+"\" "+
                                "\"D"+Note+"\"";
            result = pyW->Update(update_args);
        }

        if (ui->pushButton_2->text() == "Delete") {
            TestCaseID = static_cast<QComboBox*>(ui->stackedWidget->currentWidget())->currentText();
            QString delete_args =
                                "\"4"+TestSuite+"\" "+
                                "\"5"+TestCaseID+"\" "+
                                "\"6"+Functionality+"\" "+
                                "\"7"+TestDescription+"\" "+
                                "\"8"+Steps+"\" "+
                                "\"9"+ER+"\" "+
                                "\"A"+ValidTCs+"\" "+
                                "\"B" +Automation+"\" "+
                                /*"1"+Author+" "+\*/
                                /*"2:"+Type+" "+\*/
                                /*"3"+Date+" "+\*/
                                "\"C"+RI+"\" "+
                                "\"D"+Note+"\"";
            result = pyW->Delete(delete_args);
        }
        if (result.trimmed() == "Success") {
            QString hist_args =
                "\"1"+TestSuite+"\" "+
                "\"2"+Functionality+"\" "+
                "\"3"+RI+"\" "+
                "\"4"+TestCaseID+"\" "+
                "\"5"+Type+"\" "+
                "\"6"+Date+"\" "+
                "\"7"+Author;
            result = pyW->updateHistory(hist_args);
        }
        QMessageBox msgBox;
        msgBox.setText(result.trimmed());
        msgBox.exec();
    }
}
