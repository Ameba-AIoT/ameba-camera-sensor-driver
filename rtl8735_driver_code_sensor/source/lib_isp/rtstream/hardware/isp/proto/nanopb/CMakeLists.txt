file(GLOB src *.c)
set_property(GLOBAL APPEND PROPERTY ispsrc ${src})

install(FILES pb.h DESTINATION include)

