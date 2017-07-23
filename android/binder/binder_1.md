Binder笔记_使用例子

##Binder简单介绍

Binder是Android里面一种基本IPC方式，Android的Binder来源是OpenBinder。

下面一句话是来源于OpenBinder官网的描述：
OpenBinder is a system-level component architecture, designed to provide a richer high-level abstraction on top of traditional modern operating system services.

Binder相对其他IPC，个人觉得，Binder的最大特点不是内存只复制一次效率高，而是提供一种方便的系统内进程间的RPC，提高上层软件开发和后续系统演进的效率。

Binder简单抽象通信模型如下：



相比其他IPC还有以下特点：
1. 内存数据只拷贝一次
2. 安全，包括UID/PID识别，selinux支持等
3. 服务端死亡通知




##Binder简单应用例子

由于java层上应用binder实际上时通过java类和jni作了一次封装后最后调用libbinder接口实现通信，所以例子直接在native层已C++实现。

ServiceTestA.h
```cpp
#define SERVICE_A "ServiceA" //定义服务名字，service进程注册服务，client进程查询服务用到
namespace android{
class IServiceTestA : public IInterface
{
    public:
        DECLARE_META_INTERFACE(ServiceTestA);
        virtual int funA(int input) = 0;
};

class BnServiceTestA : public BnInterface<IServiceTestA>
{
    public:
        virtual status_t    onTransact( uint32_t code,
                const Parcel& data, Parcel* reply, uint32_t flags = 0);
};

class ServiceTestA : public BnServiceTestA
{
    public:
        int funA(int intput);
};
}
```

ServiceTestA.cpp
```cpp
namespace android{
enum {
    FUNA = IBinder::FIRST_CALL_TRANSACTION,
};
class BpServiceTestA : public BpInterface<IServiceTestA>
{
    public:
        BpServiceTestA(const sp<IBinder>& impl)
            : BpInterface<IServiceTestA>(impl)
        {
        }

        int funA(int input)
        {
            Parcel data, reply;
            data.writeInterfaceToken(IServiceTestA::getInterfaceDescriptor());
            data.writeInt32(input);
            remote()->transact(FUNA, data, &reply);
            return reply.readInt32();
        }
};

IMPLEMENT_META_INTERFACE(ServiceTestA, SERVICE_A);

status_t BnServiceTestA::onTransact(
        uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case FUNA: {
                     CHECK_INTERFACE(IServiceTestA, data, reply);
                     int input = data.readInt32();
                     int output = funA(input);
                     reply->writeInt32(output);
                     return NO_ERROR;
                 } break;
        default:
                 return BBinder::onTransact(code, data, reply, flags);
    }
}

int ServiceTestA::funA(int input)
{
    int result=input+1;
    return result;
}
}

```

service.cpp
```cpp
using namespace android;

int main(int argc,char *argv[]){
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
    sm->addService(String16(SERVICE_A),new ServiceTestA());
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
```


client.cpp
```cpp
using namespace android;
int main(int argc,char *argv[]){
    sp<IBinder> binder;
    sp<IServiceTestA> service;
    Parcel data, reply;

    sp<IServiceManager> sm = defaultServiceManager();
    while(1){
        binder = sm->getService(String16(SERVICE_A));
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
```

