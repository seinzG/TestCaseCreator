#ifndef WRAPPER_H
#define WRAPPER_H
#include <QString>
#include <QProcess>
#include <QDebug>

class Wrapper
{
public:
    Wrapper();
    QString callScript(QString script, QString args);
    QString createToken();
    // QString getOwners();
    QStringList getSheets();
    QString createTestCaseID(QString testSuite);
    QStringList getTestCaseIDs(QString testSuite);
    QStringList parseResult(QString result);
    QString Add(QString args);
    QString Update(QString args);
    QString Delete(QString args);
    QString updateHistory(QString args);
    QString getData(QString testSuite, QString testCaseID);
};

#endif // WRAPPER_H
