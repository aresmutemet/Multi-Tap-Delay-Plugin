#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/aresmute/Desktop/Multitapper/build
  make -f /Users/aresmute/Desktop/Multitapper/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/aresmute/Desktop/Multitapper/build
  make -f /Users/aresmute/Desktop/Multitapper/build/CMakeScripts/ReRunCMake.make
fi

