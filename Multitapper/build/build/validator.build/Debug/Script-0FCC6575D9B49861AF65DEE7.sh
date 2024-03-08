#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/aresmute/Desktop/Multitapper/build/vst3sdk/public.sdk/samples/vst-hosting/validator
  /Users/aresmute/Desktop/Multitapper/build/bin/Debug/validator -selftest
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/aresmute/Desktop/Multitapper/build/vst3sdk/public.sdk/samples/vst-hosting/validator
  /Users/aresmute/Desktop/Multitapper/build/bin/Release/validator -selftest
fi

