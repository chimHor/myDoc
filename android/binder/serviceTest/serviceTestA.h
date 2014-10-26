#ifndef __SERVICE_TEST_A__
#define __SERVICE_TEST_A__


#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <utils/threads.h>


namespace android{
    //继承BBinder类，从而提供IBinder 接口
    class serviceTestA:public BBinder
    {
        public:
              serviceTestA();
              virtual ~serviceTestA();
              static int instantiate(); //建立唯一类实例
              virtual status_t onTransact(uint32_t, const Parcel&, Parcel*, uint32_t);


              private:
              // protected by mLock 多线程安全
                             mutable Mutex mLock;
    };
}


#endif /* __SERVICE_TEST_A__ */
