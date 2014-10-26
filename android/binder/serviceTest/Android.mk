LOCAL_PATH:= $(call my-dir)
 
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= serviceTestA.cpp
LOCAL_SHARED_LIBRARIES:= libutils  libbinder liblog 
LOCAL_C_INCLUDES := $(TOP)/frameworks/base/include
LOCAL_MODULE:= libServiceTestA
LOCAL_PRELINK_MODULE:= false
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= serviceTestB.cpp
LOCAL_SHARED_LIBRARIES:= libutils  libbinder liblog 
LOCAL_C_INCLUDES := $(TOP)/frameworks/base/include
LOCAL_MODULE:= libServiceTestB
LOCAL_PRELINK_MODULE:= false
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= main.cpp
LOCAL_SHARED_LIBRARIES:= libutils libServiceTestA libServiceTestB liblog libbinder
LOCAL_MODULE:= serviceTestMain
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= testService.cpp
LOCAL_SHARED_LIBRARIES:= libutils libbinder libServiceTestB liblog
LOCAL_MODULE:= serviceTest
include $(BUILD_EXECUTABLE)
