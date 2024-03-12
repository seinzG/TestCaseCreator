#include "wrapper.h"

Wrapper::Wrapper() {}

QString Wrapper::callScript(QString script, QString args) {
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    QString exe = "python3 "+script+" "+args;
    process.start(exe);
    process.waitForFinished(-1);
    QString output(process.readAllStandardOutput());
    // qDebug() << output << endl;
    return output;
}

QString Wrapper::createToken() {
    return callScript("createToken.py", "");
}

// QString Wrapper::getOwners() {
//     return callScript("getOwners.py", "");
// }

QStringList Wrapper::getSheets() {
    QString sResult = callScript("getSheets.py", "");
    sResult.remove('\r');
    QStringList slResult = sResult.left(sResult.length()-1).split("\n");
    slResult.removeFirst();
    slResult.removeFirst();
    return slResult;
}

QString Wrapper::createTestCaseID(QString testSuite) {
    QString sResult = callScript("getTestCaseID.py", testSuite);
    QString last = this->parseResult(sResult).last();
    //TODO: Update last number
    return last;
}

QStringList Wrapper::getTestCaseIDs(QString testSuite) {
    QString sResult = callScript("getTestCaseID.py", testSuite);
    sResult.remove('\'');
    sResult = sResult.mid(1,(sResult.length() - 2));
    sResult = sResult.left(sResult.length()-1);
    // qDebug() << sResult << endl;
    return sResult.split("] [");
}

QStringList Wrapper::parseResult(QString result) {
    // qDebug() << result << endl;
    result.remove('\'');
    result = result.left(result.length() - 2);
    return result.split("] [");
}

QString Wrapper::Add(QString args) {
    QString result = callScript("add.py", args);
    return result;
}

QString Wrapper::Update(QString args) {
    QString result = callScript("update.py", args);
    return result;
}

QString Wrapper::Delete(QString args) {
    QString result = callScript("delete.py", args);
    return result;
}

QString Wrapper::updateHistory(QString args) {
    QString result = callScript("updateHistory.py", args);
    return result;
}

QString Wrapper::getData(QString testSuite, QString testCaseID) {
    QString args = testSuite + " " + testCaseID;
    return callScript("read.py", args);
}


