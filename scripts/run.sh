#!/bin/bash

#-----------------------------------------------------------
# 
# start Halo Light Application
#
#-----------------------------------------------------------

echo '-> Halo Light Script'

dir=$(dirname $0)
cd $dir

echo '-> Starting Fade Candy Server'

cd ../fcserver
./fcserver-osx ServerConfig.json &


echo '-> Starting Halo Light Application'

cd ../bin/HaloLight.app/Contents/MacOS/
./HaloLight

