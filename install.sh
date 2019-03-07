#!/bin/bash
##
# Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
#
# The software in this package is published under the terms of the Commercial
# Free Software license V.1, a copy of which has been included with this
# distribution in the LICENSE.md file.
#

cd $(dirname ${BASH_SOURCE[0]})
export OPENMME_DIR=$PWD
echo "------------------------------------------------------------------------------"
echo " OPENMME_DIR exported as $OPENMME_DIR"
echo "------------------------------------------------------------------------------"

OSDIST=`lsb_release -is`
OSVER=`lsb_release -rs`

#
# Sets QUIT variable so script will finish.
#
quit()
{
  QUIT=$1
}

# Shortcut for quit.
q()
{
  quit
}

################################################################################

step_1()
{
    TITLE="Environment setup."
    CONFIG_NUM=1
    TEXT[1]="Check OS and network connection"
    FUNC[1]="setup_env"
    CPLT[1]=$SETUP_ENV_COMPLETE
}

setup_env()
{
  # a. Check for OS and version dependencies
  case "$OSDIST" in
    Ubuntu)
      case "$OSVER" in
        18.04|16.04) echo "$OSDIST version $OSVER is supported." ;;
        *) echo "$OSDIST version $OSVER is unsupported." ; exit;;
      esac
      ;;
    *) echo "ERROR: Unsupported operating system distribution: $OSDIST"; exit;;
  esac
  
  echo
  echo "Checking network connectivity..."
  # b. Check for internet connections
  wget -T 3 -t 3 --spider http://www.google.com 2>/dev/null
  if [ "$?" != 0 ]; then
    while true; do
      read -p "No Internet connection. Are you behind a proxy (y/n)? " yn
      case $yn in
        [Yy]* ) $SETUP_PROXY ; return;;
        [Nn]* ) echo "Please check your internet connection..." ; exit;;
        * ) "Please answer yes or no.";;
      esac
    done
  fi

  SETUP_ENV_COMPLETE="- COMPLETE"
}

################################################################################

step_2()
{
  TITLE="Download and Install"
  CONFIG_NUM=1
  TEXT[1]="Agree to download"
  FUNC[1]="get_agreement_download"
  CPLT[1]=$GET_AGREEMENT_DOWNLOAD_COMPLETE

  case $OSDIST in
    Ubuntu)
      case "$OSVER" in
        18.04)
          TEXT[4]="Download packages"
          FUNC[4]="install_libs"
          CPLT[4]=$INSTALL_LIBS_COMPLETE
          ;;
        16.04)
          TEXT[2]="Download packages"
          FUNC[2]="install_libs"
          CPLT[2]=$INSTALL_LIBS_COMPLETE
          ;;
        *) echo "$OSDIST version $OSVER is unsupported." ; exit;;
      esac
      ;;
    *) echo "ERROR: Unsupported operating system distribution: $OSDIST"; exit;;
  esac
}

get_agreement_download()
{
  echo
  echo "List of packages needed for OPENMME build and installation:"
  echo "-------------------------------------------------------"
  
  case $OSDIST in
    Ubuntu)
      case $OSVER in
        18.04)
          echo "gcc g++ make cmake libuv-dev libssl-dev autotools-dev libtool-bin"
          echo "m4 automake libmemcached-dev memcached cmake-curses-gui gcc bison"
          echo "flex libsctp-dev libgnutls-dev libgcrypt-dev libidn11-dev nettle-dev"
          ;;
        16.04)
          echo "gcc g++ make cmake libuv-dev libssl-dev autotools-dev libtool-bin"
          echo "m4 automake libmemcached-dev memcached cmake-curses-gui gcc bison"
          echo "flex libsctp-dev libgnutls-dev libgcrypt-dev libidn11-dev nettle-dev"
          ;;
        *) echo "$OSDIST version $OSVER is unsupported." ; exit;;
      esac
      ;;
    *) echo "ERROR: Unsupported operating system distribution: $OSDIST"; exit;;
  esac
  
  while true; do
    echo
    read -p "We need to download and install the above mentioned packages. Press (y/n) to continue? " yn
    case $yn in
      [Yy]* )
        touch .agree
        break;;
      [Nn]* ) exit;;
      * ) "Please answer yes or no.";;
    esac
  done

  GET_AGREEMENT_DOWNLOAD_COMPLETE="- COMPLETE"
}

install_libs()
{
  sudo apt update && sudo apt-get install -y g++ make cmake libuv-dev libssl-dev \
    autotools-dev libtool-bin m4 automake libmemcached-dev memcached \
    cmake-curses-gui gcc bison flex libsctp-dev libgnutls-dev libgcrypt-dev \
    libidn11-dev nettle-dev 
}

build_freeDiameter()
{
  pushd modules/freediameter
  rm -rf build
  mkdir -p build
  cd build
  cmake -DDISABLE_SCTP:BOOL=ON .. && make -j && make install
  popd
}

build_openmme(){
  make; make install
}

step_3()
{
  TITLE="Build and Install Project and Submodules"
  CONFIG_NUM=1
  TEXT[1]="Build and install freeDiameter"
  FUNC[1]="init_submodules"
  CPLT[1]=$INIT_SUBMODULES_COMPLETE
  TEXT[2]="Build OpenMME"
  FUNC[2]="build_openmme"
  CPLT[2]=$BUILD_OPENMME_COMPLETE
}

init_submodules()
{
  git submodule init
  git submodule update

  build_freeDiameter
  sudo ldconfig
    
  INIT_SUBMODULES_COMPLETE="- COMPLETE"
}


SETUP_PROXY="setup_http_proxy"
STEPS[1]="step_1"
STEPS[2]="step_2"
STEPS[3]="step_3"

QUIT=0

# clear the .argee file
rm -rf .agree

clear

while [ "$QUIT" == "0" ]; do
  OPTION_NUM=1
  for s in $(seq ${#STEPS[@]}) ; do
    ${STEPS[s]}

    echo "----------------------------------------------------------"
    echo " Step $s: ${TITLE}"
    echo "----------------------------------------------------------"
  
    for i in $(seq ${#TEXT[@]}) ; do
      echo "[$OPTION_NUM] ${TEXT[i]} ${CPLT[i]}"
      OPTIONS[$OPTION_NUM]=${FUNC[i]}
      let "OPTION_NUM+=1"
    done

    # Clear TEXT and FUNC arrays before next step
    unset TEXT
    unset FUNC
    unset CPLT

    echo ""
  done
  
  echo "[$OPTION_NUM] Exit Script"
  OPTIONS[$OPTION_NUM]="quit"
  echo ""
  echo -n "Option: "
  read our_entry
  
  ${OPTIONS[our_entry]} ${our_entry}
  
  if [ "$QUIT" == "0" ] ; then
    echo
    echo -n "Press enter to continue ..."; read
    clear
    continue
    exit
  fi
  echo "Installation complete. Please refer to README.md for more information"
done
