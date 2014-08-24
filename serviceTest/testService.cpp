#include <cutils/log.h>
#include <cutils/properties.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include "serviceTestA.h"
#include "serviceTestB.h"

using namespace android;


enum{
    CALCULATE_ADD_NUM = 0,
    CALCULATE_SUB_NUM ,
};


enum{
    CALCULATE_MUL_NUM = 0,
    CALCULATE_DIV_NUM ,
};

int main(int argc,char *argv[]){
    sp<IBinder> TestAbinder;
    sp<IBinder> TestBbinder;
    sp<IServiceTestB> tb;
    Parcel data, reply;
    int sum=0;


    ALOGI("testService main is call...");


    sp<IServiceManager> sm = defaultServiceManager();

    while(1){
        TestAbinder = sm->getService(String16("service.TestA"));
        ALOGE("TestA::getAddService %p/n",sm.get());
        if (TestAbinder == 0) {
            ALOGE("TestAService not published, waiting...");
            usleep(1000000);
            continue;
        }
        else{
            ALOGI("TestA::getAddService success...");
            break;
        }
    }

    while(1){
        TestBbinder = sm->getService(String16("ServiceTestB"));
        ALOGE("TestA::getAddService %p/n",sm.get());
        if (TestBbinder == 0) {
            ALOGE("TestAService not published, waiting...");
            usleep(1000000);
            continue;
        }
        else{
            ALOGI("TestA::getAddService success...");
            break;
        }
    }

    tb = interface_cast<IServiceTestB>( TestBbinder);
    

    tb->actionOne(10);
    ALOGI("test action2 %d",tb->actionTwo(10));

    //测试两个service中的函数
    data.writeInt32(1000);
    data.writeInt32(200);
    ALOGI("BpAddService::create remote()->transact()/n");
    TestAbinder->transact(CALCULATE_MUL_NUM,data,&reply);
    sum = reply.readInt32();
    ALOGI("CALCULATE_ADD_NUM value = %d",sum);

    data.writeInt32(1000);
    data.writeInt32(200);
    ALOGI("BpAddService::create remote()->transact()/n");
    TestAbinder->transact(CALCULATE_DIV_NUM,data,&reply);
    sum = reply.readInt32();
    ALOGI("CALCULATE_SUB_NUM value = %d",sum);

    return 0;
}
