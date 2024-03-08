#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/aresmute/Desktop/Multitapper/build/bin
  /Users/aresmute/Desktop/Multitapper/build/bin/Debug/moduleinfotool -create -version 1.0.0.0 -path /Users/aresmute/Desktop/Multitapper/build/VST3/Debug/Multitapper.vst3 -output /Users/aresmute/Desktop/Multitapper/build/VST3/Debug/Multitapper.vst3/Contents/moduleinfo.json
  cd /Users/aresmute/Desktop/Multitapper/build/bin
  codesign -f -s - -v /Users/aresmute/Desktop/Multitapper/build/VST3/Debug/Multitapper.vst3/Contents/moduleinfo.json
  cd /Users/aresmute/Desktop/Multitapper/build/bin
  /Users/aresmute/Desktop/Multitapper/build/bin/Debug/validator /Users/aresmute/Desktop/Multitapper/build/VST3/Debug/Multitapper.vst3 
  cd /Users/aresmute/Desktop/Multitapper/build
  /Applications/CMake.app/Contents/bin/cmake -E make_directory /Users/aresmute/Library/Audio/Plug-Ins/VST3
  ln -svfF /Users/aresmute/Desktop/Multitapper/build/VST3/Debug/Multitapper.vst3 /Users/aresmute/Library/Audio/Plug-Ins/VST3
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/aresmute/Desktop/Multitapper/build/bin
  /Users/aresmute/Desktop/Multitapper/build/bin/Release/moduleinfotool -create -version 1.0.0.0 -path /Users/aresmute/Desktop/Multitapper/build/VST3/Release/Multitapper.vst3 -output /Users/aresmute/Desktop/Multitapper/build/VST3/Release/Multitapper.vst3/Contents/moduleinfo.json
  cd /Users/aresmute/Desktop/Multitapper/build/bin
  codesign -f -s - -v /Users/aresmute/Desktop/Multitapper/build/VST3/Release/Multitapper.vst3/Contents/moduleinfo.json
  cd /Users/aresmute/Desktop/Multitapper/build/bin
  /Users/aresmute/Desktop/Multitapper/build/bin/Release/validator  /Users/aresmute/Desktop/Multitapper/build/VST3/Release/Multitapper.vst3
  cd /Users/aresmute/Desktop/Multitapper/build
  /Applications/CMake.app/Contents/bin/cmake -E make_directory /Users/aresmute/Library/Audio/Plug-Ins/VST3
  ln -svfF /Users/aresmute/Desktop/Multitapper/build/VST3/Release/Multitapper.vst3 /Users/aresmute/Library/Audio/Plug-Ins/VST3
fi

