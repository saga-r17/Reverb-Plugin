cmake_minimum_required(VERSION 3.10)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

set (BaseTargetName FreeReverb)
project(${BaseTargetName} LANGUAGES CXX VERSION 0.1.0)

include_directories("C:/Program Files/Faust/include")
link_directories("C:/Program Files/Faust/lib")

# Fetch JUCE library
include(FetchContent)

FetchContent_Declare(
        juce
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 7.0.0
)
FetchContent_MakeAvailable(juce)

include_directories(${JUCE_INCLUDE_DIRS})

juce_add_plugin("${BaseTargetName}"
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME "Sagar Bhandari"
        IS_SYNTH FALSE    
        NEEDS_MIDI_INPUT FALSE
        NEEDS_MIDI_OUTPUT FALSE
        AU_MAIN_TYPE kAudioUnitType_MIDIProcessor
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD FALSE
        PLUGIN_MANUFACTURER_CODE Juce3.
        PLUGIN_CODE MFxt
        FORMATS VST3
        PRODUCT_NAME ${BaseTargetName})

juce_generate_juce_header(${BaseTargetName})

file(GLOB_RECURSE SOURCE_FILES "Source/*.cpp")

target_sources(${BaseTargetName} PRIVATE ${SOURCE_FILES})

add_subdirectory(Assets)

target_compile_definitions(${BaseTargetName}
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${BaseTargetName} PUBLIC
        Binary
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_data_structures
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce_recommended_config_flags
        juce_recommended_lto_flags
        juce_recommended_warning_flags
        faust)
