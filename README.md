# QtxXml

QtxXml provides classes for reading and writing data in XML format.

## Build

To build a dynamic library:

    $ qmake CONFIG+=dylib
    $ make
    
To build a static library:

    $ qmake CONFIG+=static
    $ make

## Test

To run the test suite, first configure and build QtxXml as a dynamic
library, which each test executable will link against.  Then invoke the `check`
target to execute all tests in the suite.

    $ qmake CONFIG+=dylib
    $ make
    $ make check

## Documentation

To generate API documentation, invoke the `docs` target.

    $ make docs

To view the documentation, open it in a web browser.

    $ open doc/qtxxml/qtxxml-module.html

## License

[Apache License, Version 2.0](http://opensource.org/licenses/Apache-2.0)

Copyright (c) 2009-2013 Jared Hanson <[http://jaredhanson.net/](http://jaredhanson.net/)>
