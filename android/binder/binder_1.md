#Binder笔记_Binder服务例子

##Binder简单介绍

Binder是Android里面一种基本IPC方式，Android的Binder来源是OpenBinder。

下面一句话是来源于OpenBinder官网的描述：
OpenBinder is a system-level component architecture, designed to provide a richer high-level abstraction on top of traditional modern operating system services.

Binder相对其他IPC，个人觉得，Binder的最大特点不是内存只复制一次效率高，而是提供一种方便的系统内进程间的RPC，提高上层软件开发和后续系统演进的效率。

Binder简单抽象通信模型如下：

![](pic/AbstractBinderCommunication.png)

相比其他IPC还有以下特点：
1. 内存数据只拷贝一次
2. 安全，包括UID/PID识别，selinux支持等
3. 服务端死亡通知


##Binder简单应用例子

由于java层上应用binder实际上时通过java类和jni作了一次封装后最后调用libbinder接口实现通信，所以例子直接在native层已C++实现。


###ServiceTestA服务的实现
基本类关系结构如下：

![](pic/ServiceTestA_class.png)

紫色部分为libbinder的内容，黄色部分类为Binder例子的内容
具体如下：
1. IServiceTestA继承IInterface,定义服务的业务接口
2. BnServiceTestA为服务端类，继承BnInterface和IServiceTestA,实现了服务端业务接口与通信层的libbinder的适配
3. BpServiceTestA为客户端代理类，继承BpInterface和IServiceTestA，实现客户端业务接口与通信层的libbinder的适配
4. ServiceTestA实现真正业务逻辑

黄色部分的代码实现包括ServiceTestA.h和ServiceTestA.cpp，以下是具体代码

ServiceTestA.h
```cpp
//定义服务名字，service进程注册服务，client进程查询服务用到
#define SERVICETESTA "ServiceTestA"
namespace android{
class IServiceTestA : public IInterface
{
    public:
        DECLARE_META_INTERFACE(ServiceTestA);
        //定义业务接口funA
        virtual int funA(int input) = 0;
};

class BnServiceTestA : public BnInterface<IServiceTestA>
{
    public:
    	//在onTransact里面实现业务层与通信层适配
        virtual status_t onTransact( uint32_t code,
                const Parcel& data, Parcel* reply, uint32_t flags = 0);
};

class ServiceTestA : public BnServiceTestA
{
    public:
        //真正实现业务接口业务逻辑
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
           //打包调用参数
		   data.writeInterfaceToken(IServiceTestA::getInterfaceDescriptor());
            data.writeInt32(input);
            remote()->transact(FUNA, data, &reply);
			//取回结果
            return reply.readInt32();
        }
};

IMPLEMENT_META_INTERFACE(ServiceTestA, SERVICETESTA);

status_t BnServiceTestA::onTransact(
        uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case FUNA: {
                     CHECK_INTERFACE(IServiceTestA, data, reply);
                     int input = data.readInt32();
					 //调用实际业务接口实现
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

补充说明：
1. ServiceTestA.h声明了IServiceTestA，BnServiceTestA，ServiceTestA，却没有声明BpServiceTestA，主要原因是因为从客户端使用角度只需要IServiceTestA不需要BpServiceTestA
2. DECLARE_META_INTERFACE和IMPLEMENT_META_INTERFACE两个宏在IInterface.h里面定义，主要功能是定义descriptor成员变量和asInterface，getInterfaceDescriptor两个成员函数
3. 定义枚举常量FUNA的值为IBinder::FIRST_CALL_TRANSACTION，是业务层适配到通信层的要去，每个业务接口都需要对应一个不同的常量

总体上，完成一个业务层服务，需要定义业务接口，实现业务逻辑，和实现业务层到通信层的适配，这些都通过继承实现libbinder的提供的类完成


###ServiceTestA服务的使用

实现一个ServiceTestA服务端的代码service.cpp
```cpp
using namespace android;

int main(int argc,char *argv[]){
    sp<ProcessState> proc(ProcessState::self());
	//获取ServiceManager代理
    sp<IServiceManager> sm = defaultServiceManager();
    //注册ServiceTestA服务
	sm->addService(String16(SERVICETESTA),new ServiceTestA());
	//开启线程池，等待客户端调用
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
```

实现客户段代码client.cpp
client.cpp
```cpp
using namespace android;
int main(int argc,char *argv[]){
    sp<IBinder> binder;
    sp<IServiceTestA> service;
	//获取ServiceManager
    sp<IServiceManager> sm = defaultServiceManager();
    while(1){
	    //向查询ServiceManager查询ServiceTestA服务
        binder = sm->getService(String16(SERVICETESTA));
        if (binder == 0) {
            usleep(1000000);
            continue;
        }
        else{
			//找到服务，退出循环
            break;
        }
    }
	//把从ServiceManager获取到的IBinder转化为IServiceTestA对象
    service = interface_cast<IServiceTestA>( binder);
	//调用funA并打印结果
    int ret = service->funA(10);
    printf("ServiceTestA funA ret: %d\n",ret);
    return 0;
}
```

基于Binder通信的服务，需要一个字符串命名。服务端启动的时候要要向ServiceManager注册自己的名字，客户端要调用服务的业务接口先要按照服务名字向ServiceManager查询服务，返回IBinder对象后转化为对应的IServiceTestA对象（实际是BpServiceTest对象，但对于客户端代码，不需要知道）

![](pic/ServiceTestA_seq.png)
