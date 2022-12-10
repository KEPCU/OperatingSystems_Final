# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ProducerConsumer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ProducerConsumer_autogen.dir\\ParseCache.txt"
  "ProducerConsumer_autogen"
  )
endif()
