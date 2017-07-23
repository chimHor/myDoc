#include <ServiceTestA.h>
#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>


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
