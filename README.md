# poco.windows.visualstudio

```
file: components.  I removed the mysql and postres stuff.  dont need it from my stuff.

CppUnit
Foundation
Encodings
XML
JSON
Util
Net
Crypto
NetSSL_OpenSSL
NetSSL_Win
SQL
SQL/ODBC
SQL/SQLite
Zip
PageCompiler
PageCompiler/File2Page
CppParser
MongoDB
Redis
PocoDoc
```

## OpenSSL
[how to get openssl](https://pocoproject.org/docs/00200-GettingStarted.html)  
```
$ cd %POCO_BASE%
$ rmdir /s /q openssl
$ git clone https://github.com/pocoproject/openssl
```

```
H:\github\pocoproject\poco>buildwin 150 build shared both x64
```

My projects are setup to pull poco build artifacts from the h:\{Path} above.
