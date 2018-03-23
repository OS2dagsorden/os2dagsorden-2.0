#!/bin/sh
# The purpose of this file is initialization process which will help developers
# with setup of local/remote environment.

DIR=$(pwd)
git clone --recursive git@github.com:bellcom/os2dagsorden-2.0.git
mkdir os2dagsorden-2.0/private
mkdir os2dagsorden-2.0/tmp
