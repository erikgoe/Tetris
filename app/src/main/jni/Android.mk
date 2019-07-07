LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := tetris

LOCAL_SRC_FILES := main.cpp
LOCAL_SRC_FILES += Board.cpp
LOCAL_SRC_FILES += Figure.cpp
LOCAL_SRC_FILES += Game.cpp
LOCAL_SRC_FILES += Tone.cpp
LOCAL_SRC_FILES += Melodies.cpp
LOCAL_SRC_FILES += Text.cpp

LOCAL_SHARED_LIBRARIES := sfml-system-d
LOCAL_SHARED_LIBRARIES += sfml-window-d
LOCAL_SHARED_LIBRARIES += sfml-graphics-d
LOCAL_SHARED_LIBRARIES += sfml-audio-d
LOCAL_SHARED_LIBRARIES += sfml-network-d
LOCAL_SHARED_LIBRARIES += sfml-activity-d
LOCAL_SHARED_LIBRARIES += openal
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main-d

include $(BUILD_SHARED_LIBRARY)

$(call import-module,third_party/sfml)
