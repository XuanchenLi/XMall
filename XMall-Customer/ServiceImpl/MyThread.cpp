#include "Service/MyThread.h"

void MyThread::run()
{
    emit initAddress();
    emit initCategoryMenu();
    emit initProduction();
    emit initUserBaseInfo();
}


