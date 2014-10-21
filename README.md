bridge
======

- Bridge is a standard C++11 <--> C++03/boost compatibility layer, plus a few macro utils.
- Bridge is cross-platform. 
- Bridge is header-only.
- Bridge pollutes a few macros on purpose. Sorry but I think this is convenient.
- Bridge is BOOST licensed.

### std::

Safe wrap around all `std::mutex` variants, `std::thread`, `std::function`, `std::bind`, `std::placeholders` and `std::(u)int\*_t` types. Also, includes 128-bit headers if possible.

### std::placeholders

```
{
  using namespace std::placeholders;
  return std::bind( fn, _1 );
}
```

### Thread local storage  
- `$tls(x)`

```
  static $tls(bool) acquired = false;
```

### Platform macros
- `$windows(...)`, `$welse(...)`
- `$linux(...)`, `$lelse(...)`
- `$apple(...)`, `$aelse(...)`
- `$undefined_os(...)`

```c++
int dir() {
$windows( return system("dir") );
$welse( return system("ls -la") );
return 0;
}
```

### Compiler macros
- `$msvc(...)`, `$melse(...)`
- `$gnuc(...)`, `$gelse(...)`
- `$clang(...)`, `$celse(...)`
- `$undefined_compiler(...)`

```
int main() {
  $msvc( __asm int 3 );
}
```

### Exception macros
- `$throw(...)`, `$telse(...)`

```
int main() {
  $throw(
    try {
      game(); 
    } catch(...) {
      /*...*/
    } 
  );
  $telse(
    game(); 
  );
}
```

### Debug/release macros
- `$debug(...)`, `$release(...)`

```c++
int main() {
  // disable logging
  $release({
    fclose(stderr);
    fclose(stdout) 
  });
}
```

### Warning macros
`$warning(...)`
`$todo(...)`

```c++
$warning("line printed in compile time");
int main()
{}
```

### Directive macros
- `$on(...)`
- `$is(...)`
- `$has(...)`

```c++
#if $on($windows))
#include <windows.h>
#else
#include <unistd.h>
#endif

int main()
if( $on($linux) && $on($release) ) {
print("linux-release");
}
}
```

### Stringify macro
- `$quote(...)`

```c++
std::string text = $quote(
this is a multine
string
);
```

### Un/Comment macros
- `$comment(...)`, `$uncomment(...)`

```c++
$comment(
print("this code is never compiled");
);
```

### C++11/03 macros
- `$cpp11(...)`
- `$cpp03(...)`

```c++
$cpp03( const void* get_null() { return 0; } );
$cpp11( std::nullptr_t get_null() { return nullptr; } );
```
