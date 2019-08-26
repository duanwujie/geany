

INCLUDE_DIRECTORIES(../../ctags/main)


ADD_DEFINITIONS(-DGEANY_PRIVATE)
ADD_DEFINITIONS(-DGEANY_EXPORT_SYMBOL=__attribute__\(\(visibility\(\"default\"\)\)\))
ADD_DEFINITIONS(-DGEANY_API_SYMBOL=GEANY_EXPORT_SYMBOL)
ADD_DEFINITIONS(-DCTAGS_LIB=1)


set(TM_SRCS tm_parser.h
    tm_parser.c
    tm_source_file.h
    tm_source_file.c
    tm_tag.h
    tm_tag.c
    tm_workspace.h
    tm_workspace.c)


add_library(tagmanager STATIC ${TM_SRCS})

target_link_libraries(tagmanager ctags)
