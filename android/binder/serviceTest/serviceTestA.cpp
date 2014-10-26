#include <cutils/log.h>
#include <cutils/properties.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <serviceTestA.h>


namespace android {


    enum{
        CALCULATE_MUL_NUM = 0,
        CALCULATE_DIV_NUM ,
    };

    int serviceTestA::instantiate() {
        ALOGI("serviceTestA instantiate");


        int r = defaultServiceManager()->addService(String16("service.TestA"),new serviceTestA());
        ALOGI("serviceTestA r = %d", r);
        return r;
    }


    serviceTestA::serviceTestA() {
        ALOGI("serviceTestA created");
    }


    serviceTestA::~serviceTestA(){
        ALOGI("serviceTestA destroyed");
    }


    status_t serviceTestA::onTransact(uint32_t code, const Parcel&data, Parcel*reply, uint32_t flags){
        ALOGI("serviceTestA::onTransact code = %d",code);
        Mutex::Autolock _l(mLock);
        switch(code){
            case CALCULATE_MUL_NUM:{
                int a = data.readInt32();
                int b = data.readInt32();
                int sum = a * b ;
                ALOGI("sum mul value = %d",sum);
                reply->writeInt32(sum);
                return NO_ERROR;
            }break;
            case CALCULATE_DIV_NUM:{
                int a = data.readInt32();
                int b = data.readInt32();
                int sum = a / b ;
                ALOGI("sum div value = %d",sum);
                reply->writeInt32(sum);
                return NO_ERROR;
            }break;
            default:
            return BBinder::onTransact(code, data, reply, flags);
        }
        return 0;
    }
}
