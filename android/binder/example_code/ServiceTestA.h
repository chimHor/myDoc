#ifndef __SERVICE_TEST_A__
#define __SERVICE_TEST_A__


#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

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

#endif
