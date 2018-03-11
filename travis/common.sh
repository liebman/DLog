#!/bin/bash

function build_boards()
{
    local exit_code=0;
    echo
    echo "-------------- esp8266 -----------------"
    echo
    arduino --board esp8266:esp8266:generic:CpuFrequency=80,CrystalFreq=26,FlashFreq=40,FlashMode=qio,FlashSize=4M1M,led=2,LwIPVariant=v2mss536,Debug=Serial,DebugLevel=CORE --save-prefs
    build_examples
    if [ $? -ne 0 ]; then
        exit_code=1
    fi
    echo
    echo "-------------- esp32 -----------------"
    echo
    arduino --board espressif:esp32:ESP32_DEV:FlashMode=qio,FlashFreq=80,FlashSize=4M,DebugLevel=info --save-prefs
    if [ $? -ne 0 ]; then
        exit_code=1
    fi
    build_examples
    return $exit_code
}

function build_examples()
{
  # track the exit code for this platform
  local exit_code=0
  # loop through results and add them to the array
  examples=($(find $PWD/examples/ -name "*.pde" -o -name "*.ino"))

  # get the last example in the array
  local last="${examples[@]:(-1)}"

  # loop through example sketches
  for example in "${examples[@]}"; do

    # store the full path to the example's sketch directory
    local example_dir=$(dirname $example)

    # store the filename for the example without the path
    local example_file=$(basename $example)

    echo "$example_file: "
    local sketch="$example_dir/$example_file"
    echo "$sketch"
    #arduino -v --verbose-build --verify $sketch

    # verify the example, and save stdout & stderr to a variable
    # we have to avoid reading the exit code of local:
    # "when declaring a local variable in a function, the local acts as a command in its own right"
    local build_stdout
    build_stdout=$(arduino -v --verbose-build --verify $sketch 2>&1)

    # echo output if the build failed
    if [ $? -ne 0 ]; then
      # heavy X
      echo -e "\xe2\x9c\x96"
      echo -e "----------------------------- DEBUG OUTPUT -----------------------------\n"
      echo "$build_stdout"
      echo -e "\n------------------------------------------------------------------------\n"

      # mark as fail
      exit_code=1

    else
      # heavy checkmark
      echo -e "\xe2\x9c\x93"
    fi
  done

  return $exit_code
}
