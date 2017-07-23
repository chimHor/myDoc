LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
    LOCAL_SRC_FILES:= ServiceTestA.cpp
    LOCAL_SHARED_LIBRARIES:= libutils libbinder
    LOCAL_MODULE:= libServiceTestA
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
    LOCAL_SRC_FILES:= service.cpp
    LOCAL_SHARED_LIBRARIES:= libutils libServiceTestA libbinder
    LOCAL_MODULE:= serviceTestMain
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
    LOCAL_SRC_FILES:= client.cpp
    LOCAL_SHARED_LIBRARIES:= libutils libbinder libServiceTestA
    LOCAL_MODULE:= serviceTest
include $(BUILD_EXECUTABLE)

