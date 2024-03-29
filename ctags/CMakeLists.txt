
set(CMAKE_C_STANDARD 99)

INCLUDE_DIRECTORIES(main)
INCLUDE_DIRECTORIES(parsers)

ADD_DEFINITIONS(-DUSE_STDBOOL_H=1)
ADD_DEFINITIONS(-DCTAGS_LIB=1)
ADD_DEFINITIONS(-DHAVE_ERRNO_H=1)
ADD_DEFINITIONS(-DHAVE_LIMITS_H=1)
ADD_DEFINITIONS(-DHAVE_SYS_STAT_H=1)
ADD_DEFINITIONS(-DHAVE_FCNTL_H=1)



set(PARSERS_SOURCE parsers/abaqus.c 
    parsers/abc.c
    parsers/asciidoc.c
    parsers/asm.c
    parsers/basic.c
    parsers/c.c
    parsers/cobol.c
    parsers/iniconf.c
    parsers/css.c
    parsers/diff.c
    parsers/docbook.c
    parsers/erlang.c
    parsers/flex.c
    parsers/fortran.c
    parsers/go.c
    parsers/haskell.c
    parsers/haxe.c
    parsers/html.c
    parsers/jscript.c
    parsers/json.c
    parsers/lua.c
    parsers/make.c
    parsers/markdown.c
    parsers/matlab.c
    parsers/nsis.c
    parsers/objc.c
    parsers/pascal.c
    parsers/perl.c
    parsers/php.c
    parsers/powershell.c
    parsers/python.c
    parsers/r.c
    parsers/rst.c
    parsers/ruby.c
    parsers/rust.c
    parsers/sh.c
    parsers/sql.c
    parsers/tcl.c
    parsers/tex.c
    parsers/txt2tags.c
    parsers/verilog.c
    parsers/vhdl.c)

set(TAGS_SOURCES main/args.c 
    main/args.h 
    main/ctags.h 
    main/ctags-api.c 
    main/ctags-api.h 
    main/debug.h 
    main/debug.c 
    main/dependency.h 
    main/dependency.c 
    main/e_msoft.h 
    main/entry.c 
    main/entry.h 
    main/error.c 
    main/error.h 
    main/field.c 
    main/field.h 
    main/flags.c 
    main/flags.h 
    main/fmt.c 
    main/fmt.h 
    main/gcc-attr.h 
    main/general.h 
    main/htable.c 
    main/htable.h 
    main/inline.h 
    main/keyword.c 
    main/keyword.h 
    main/kind.c 
    main/kind.h 
    main/lcpp.c 
    main/lcpp.h 
    main/lregex.c 
    main/lxcmd.c 
    main/lxpath.c 
    main/main.c 
    main/main.h 
    main/mbcs.h 
    main/mio.c 
    main/mio.h 
    main/nestlevel.c 
    main/nestlevel.h 
    main/numarray.c 
    main/numarray.h 
    main/objpool.c 
    main/objpool.h 
    main/options.c 
    main/options.h 
    main/output-ctags.c 
    main/output.h 
    main/parse.c 
    main/parse.h 
    main/parsers.h 
    main/pcoproc.c 
    main/pcoproc.h 
    main/promise.c 
    main/promise.h 
    main/ptag.c 
    main/ptag.h 
    main/ptrarray.c 
    main/ptrarray.h 
    main/read.c 
    main/read.h 
    main/repoinfo.c 
    main/repoinfo.h 
    main/routines.c 
    main/routines.h 
    main/selectors.c 
    main/selectors.h 
    main/sort.c 
    main/sort.h 
    main/strlist.c 
    main/strlist.h 
    main/trace.h 
    main/trashbox.c 
    main/trashbox.h 
    main/types.h 
    main/vstring.c 
    main/vstring.h 
    main/xtag.h 
    main/xtag.c 
    ${PARSERS_SOURCE})


add_library(ctags STATIC ${TAGS_SOURCES})

