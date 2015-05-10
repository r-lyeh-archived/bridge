bridge
======

- Bridge provides a C++11 subset playground even if no C++11 is present.
- Bridge provides a few macro utils, aimed to cross-development.
- Bridge pollutes macros on purpose. Sorry but I think this is convenient.
- Bridge is cross-platform.
- Bridge is header-only.
- Bridge is zlib/libpng licensed.

## std:: library wrapper

- on C++11 platforms, bridge includes a few c++11 headers only.
- on C++03 platforms, bridge fallbacks to a few boost libraries.
- additionally 128-bit headers are included if possible.
- bridge recreates a safe std:: playground that wraps all `std::mutex` variants, `std::thread`, `std::function`, `std::bind`, `std::placeholders` and `std::(u)int\*_t` types (for now).

```c++
{
  std::thread( classA() ).detach();

  std::mutex m;
  std::scope_lock guard(m);

  std::function<int(int,const char**)> fn( main );

  using namespace std::placeholders;
  return std::bind( fn, _1 );
}
```

## Bridge macros
- Bridge macros can contain multiline text and/or code
- These macros can be located inside functions, global namespaces, and #if directives.

### Thread local storage
- `$tls(x)`

```c++
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

```c++
int main() {
  $msvc( __asm int 3 );
}
```

### Exception macros
- `$throw(...)`, `$telse(...)`

```c++
int main() {
  $throw(
    try {
      setup();
      game();
    } catch(...) {
      /*...*/
    }
  );
  $telse(
    setup();
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
- `$warning(...)`
- `$todo(...)`

```c++
$warning("line printed in compile time");
$todo("cook food");
int main()
{}
```

### Directive macros
- `$on(...)`
- `$is(...)`
- `$has(...)`

```c++
#if $on($windows))
#  include <windows.h>
#else
#  include <unistd.h>
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
int main() {
 $comment(
  print("this code...");
  print("...is never compiled");
 );
}
```

### C++03/11 macros
- `$cpp03(...)`
- `$cpp11(...)`

```c++
$cpp11(std::unique_ptr) $cpp03(std::auto_ptr) <std::string> str( new std::string("hi") );
```
