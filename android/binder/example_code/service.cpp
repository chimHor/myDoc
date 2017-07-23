#include <sys/types.h>
#include <unistd.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <ServiceTestA.h>

using namespace android;

int main(int argc,char *argv[]){
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
    sm->addService(String16(SERVICETESTA),new ServiceTestA());
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
