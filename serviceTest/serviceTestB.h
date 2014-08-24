#ifndef __SERVICE_TEST_B__
#define __SERVICE_TEST_B__

#include <cutils/log.h>
#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
namespace android{

class IServiceTestB : public IInterface
{
public:
    DECLARE_META_INTERFACE(ServiceTestB);
    virtual void actionOne(int input) = 0;
    virtual int actionTwo(int input) = 0;
};

class BnServiceTestB : public BnInterface<IServiceTestB>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
     //void actionOne(int intput){}
     //int actionTwo(int intput){return 0;}
};

class ServiceTestB : public BnServiceTestB
{
public:
    void actionOne(int intput);
    int actionTwo(int intput);

};

}

#endif
