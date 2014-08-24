#include <serviceTestB.h>
#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android{


class BpServiceTestB : public BpInterface<IServiceTestB>
{
public:
    BpServiceTestB(const sp<IBinder>& impl)
        : BpInterface<IServiceTestB>(impl)
    {
        ALOGE("BpServiceTestB construct");
    }

    void actionOne(int input)
    {
        ALOGE("BpServiceTestB actionOne");
        Parcel data, reply;
        data.writeInterfaceToken(IServiceTestB::getInterfaceDescriptor());
        data.writeInt32(input);
        remote()->transact(10, data, &reply);
        return ;
    }
    int actionTwo(int input)
    {
        ALOGE("BpServiceTestB actionTwo");
        Parcel data, reply;
        data.writeInterfaceToken(IServiceTestB::getInterfaceDescriptor());
        data.writeInt32(input);
        remote()->transact(11, data, &reply);
        return reply.readInt32();
    }

};

IMPLEMENT_META_INTERFACE(ServiceTestB, "ServiceTestB");

status_t BnServiceTestB::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    //printf("ServiceManager received: "); data.print();
    ALOGE("BnServiceTestB onTransact");
    switch(code) {
        case 10: {
            CHECK_INTERFACE(IServiceTestB, data, reply);
            int input = data.readInt32();
            actionOne(input);
            return NO_ERROR;
        } break;
        case 11: {
            CHECK_INTERFACE(IServiceTestB, data, reply);
            int input = data.readInt32();
            int output = actionTwo(input);
            reply->writeInt32(output);
            return NO_ERROR;
        } break;
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

void ServiceTestB::actionOne(int input)
{
    ALOGE("ServiceTestB actionOne %d",input);
}

int ServiceTestB::actionTwo(int input)
{
    ALOGE("ServiceTestB actionTwo %d",input);
    int result=input+1;
    return result;
}


}
