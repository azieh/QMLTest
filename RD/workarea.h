#ifndef WORKAREA_H
#define WORKAREA_H

#include "plchandler.h"
#include "sqlhandler.h"

#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QMutex>



class WorkArea : public QObject
{
    Q_OBJECT
public:
    explicit WorkArea(SqlHandler* sqlHandler, QObject *parent = 0);
    ~WorkArea();

    void doSetup        (QThread* cThread);
    void setPlcParameters(const QString &typeOfPlc, const char* ip, const int rackOrLocalTsap, const int slotOrRemoteTsap);
    void setDbNumber    (const int &dbNumber);
    void setName        (const char* arg1);
    RepoDestDbStruct*    dbStruct;
    SqlApuDataStruct*    sqlApuDataStruct;
    SqlPcsDataStruct*    sqlPcsDataStruct;

private:
    QThread*        _thread;
    PlcHandler* _plcHandler;
    SqlHandler* _sqlHandler;


    QString         _name;
    QElapsedTimer   _loopTimer;
    QElapsedTimer   _faultTimer;
    QDateTime       _datetime;
    QDate           _date;
    QTime           _time;
    bool            _faultIsDetected;
    bool            _makeWritingPlc;
    bool            _makeWritingSql;
    bool            _prepareDataForPartsInLastMinute;
    int             _repeatThreadTime;

    QString shiftCheck();
    QString pcsRecIdGenerator();
    void repeatThread();
    void checkDbStruct              (RepoDestDbStruct* dbStruct);
    void checkDbForFault            (RepoDestDbStruct* dbStruct);
    void checkDbForPartOk           (RepoDestDbStruct* dbStruct);
    void checkDbForPartsInLastMinute(RepoDestDbStruct* dbStruct);
    void checkLoopTime();
    void sqlHInsertDataPartsInLastMinute();
    void sqlHInsertDataLastFaultInfo();

signals:
    void messageText        (const QString &);
    void messageOk          (int );
    void messageKo          (int );
    void connectionStatus   (bool);
    void loopTime           (const QString &);


private slots:
    void messageTextChanged     (const QString &arg1);
    void labelStatus_Changed    (bool arg1);
    void lineEditOk_Changed     (int arg1);
    void lineEditNok_Changed    (int arg1);

public slots:
    void mainOperation();
};

#endif // WORKAREA_H
