pebble_swiss_german
===================

A Pebble Watchface in Swiss German

* to build the watchface install the pebble sdk in https://developer.getpebble.com
* create a new watchface https://developer.getpebble.com/1/01_GetStarted/01_Step_4
  ../tools/create_pebble_project.py ../sdk/ swiss_german
* add the source directory to the newly created swiss_german diretory
* ./waf configure
* ./waf build
* install the created swiss_german.pbw https://developer.getpebble.com/1/01_GetStarted/01_Step_1