bridge
======

- Bridge is a standard C++11 <--> C++03/boost compatibility layer, plus a few macro utils.
- Bridge is cross-platform. 
- Bridge is header-only.
- Bridge pollutes a few macros on purpose. Sorry but I think this is convenient.
- Bridge is BOOST licensed.

### API Macros

```
$yes(...)
$no(...)

$windows(...), $welse(...)
$linux(...), $lelse(...)
$apple(...), $aelse(...)
$undefined_os(...)

$msvc(...), $melse(...)
$gnuc(...), $gelse(...)
$clang(...), $celse(...)
$undefined_compiler(...)

$throw(...), $telse(...)

$warning(...)
$debug(...), $release(...)

$on(...)
$is(...)
$has(...)

$quote(...)

$comment(...)
$uncomment(...)

$cpp11(...)
$cpp03(...)

$tls(x)
```
