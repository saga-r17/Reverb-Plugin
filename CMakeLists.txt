cmake_minimum_required(VERSION 3.10)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

set (BaseTargetName juceFaust)

project(${BaseTargetName} LANGUAGES CXX VERSION 0.1.0)

include_directories("Faust/include")

# Fetch JUCE library
include(FetchContent)

FetchContent_Declare(
        juce
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 7.0.0
)
FetchContent_MakeAvailable(juce)

FetchContent_Declare(
  faust
  GIT_REPOSITORY https://github.com/grame-cncm/faust.git
)

FetchContent_GetProperties(faust)
if(NOT faust_POPULATED)
  FetchContent_Populate(faust)
endif()


include_directories(${FAUST_SOURCE_DIR} ${JUCE_INCLUDE_DIRS})

juce_add_plugin("${BaseTargetName}"
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME "Sagar Bhandari"
        IS_SYNTH TRUE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT FALSE
        AU_MAIN_TYPE kAudioUnitType_MIDIProcessor
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD TRUE
        PLUGIN_MANUFACTURER_CODE Juce
        PLUGIN_CODE MFxt
        FORMATS Standalone
        PRODUCT_NAME ${BaseTargetName})

juce_generate_juce_header(${BaseTargetName})

file(GLOB_RECURSE SOURCE_FILES "Source/*.cpp")

target_sources(${BaseTargetName} PRIVATE ${SOURCE_FILES})

target_compile_definitions(${BaseTargetName}
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${BaseTargetName} PUBLIC juce::juce_audio_utils)
