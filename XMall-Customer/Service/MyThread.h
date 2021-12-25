#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(){};
    ~MyThread(){};


protected:

    void run();

signals:
    void initUserBaseInfo();
    void initAddress();
    void initCategoryMenu();
    void initProduction();
    void initSlide();

private:


};

#endif // MYTHREAD_H
