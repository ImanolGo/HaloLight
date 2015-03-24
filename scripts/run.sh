#!/bin/bash

#-----------------------------------------------------------
# 
# start Halo Light Application
#
#-----------------------------------------------------------

echo '-> Halo Light Script'

echo '-> Starting Fade Candy Server'

cd ../fcserver
./fcserver-osx ServerConfig.json &


echo '-> Starting Halo Light Application'

cd ../bin
open HaloLight.app &

