#!/bin/bash

#-----------------------------------------------------------
# 
# start Halo Light Application
#
#-----------------------------------------------------------

echo '-> Halo Light Script'

echo '-> Starting Fade Candy Server'

cd ../fcserver
./fcserver-osx ServerConfig.json 

echo '-> waiting...'

sleep 10

echo '-> Starting Halo Light Application'

cd ../bin
open HaloLight.app

