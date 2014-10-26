#include <sys/types.h>
#include <unistd.h>
#include <cutils/log.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <serviceTestA.h>
#include <serviceTestB.h>


using namespace android;


int main(int argc,char *argv[]){
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
    ALOGI("ServiceManager: %p", sm.get());
    serviceTestA::instantiate(); // 这是重点。。。。
    sm->addService(String16("ServiceTestB"),new ServiceTestB());
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
