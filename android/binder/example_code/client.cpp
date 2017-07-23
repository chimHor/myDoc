 #include <cutils/log.h>
 #include <cutils/properties.h>
 #include <binder/IServiceManager.h>
 #include <binder/IPCThreadState.h>
 #include "ServiceTestA.h"

using namespace android;
int main(int argc,char *argv[]){
    sp<IBinder> binder;
    sp<IServiceTestA> service;

    sp<IServiceManager> sm = defaultServiceManager();
    while(1){
        binder = sm->getService(String16(SERVICETESTA));
        if (binder == 0) {
            usleep(1000000);
            continue;
        }
        else{
            break;
        }
    }

    service = interface_cast<IServiceTestA>( binder);
    int ret = service->funA(10);
    printf("ServiceTestA funA ret: %d\n",ret);
    return 0;
}
