# gDebugV2.0

The current  github address is at https://github.com/gxt-kt/gDebugV2.0

The gDebugV1.0 code is at https://github.com/gxt-kt/gDebug/ but is abandoned.

***

## how to use

If you have use the qDebuf() function of "Qt", you must use this module easily. And the qDebug is change name to gDebug here.

You can use the default gDebug/gDebug() function to output the debug stream such as `gDebug("hello world");`
Complexly you can write like `gDebug("hello") << "world";` and so on.  The detail code you can see example.

And the default gDebug/gDebug() has enable the space and newline.
If you use the class DebugStream create a new instantiation. The space function is exist but the newline is invalid.

## example1

**use the default qDebug**

```c++
#include "debugstream.h"

int main() {
  gDebug("hello world!");
  gDebug << "hello world!";
  gDebug << "11" << "22" << "33";
  gDebug.NoSpace() << "11" << "22" << "33";
  gDebug.NoSpace().NoNewLine() << "11" << "22" << "33";
  gDebug << "44";

  float f = 3.14159f;
  gDebug("f=%.3f", f);
  gDebug.NoSpace() << "f=" << gDebug("%.3f", f);
}
```

the stream out text:

```
hello world!
hello world!
11 22 33
112233
11223344
f=3.142
f=3.142

```

## example2

*create a new instantiation*
Attention that if you create a new instantiation, The space funciton is exist but the auto newline is invalid.
(It's because that add newline is accur in the destory construct, but the instantiation will not destory automatically)

```c++
#include "debugstream.h"

int main() {
  DebugStream mystream;

  mystream("hello world!\n");
  mystream << "11" << "22" << "33" << "44";
  mystream << "11" << "22" << "33" << "44" << endl;
  mystream.NoSpace() << "11" <<  "22" << "33" << "44"<< endl;
  mystream.Space();
  mystream << "11" << mystream("22 33 44");
}
```

the stream out text:

```
hello world!
1122 33 44 11 22 33 44
11223344
11 22 33 44
```
## example3
**create a new instantiation with your stream out function**

step:
1. Define a function with type `void YourFunName(const char *str, int num) {
   // ... such as  printf("%.*s",num,str); }`
2. Instantiate class `DebugStream demo(YourFunName,256);` the first var is your function name, the second var is the buffer size (default 256).
```c++
#include "debugstream.h"

void YourFunName(const char *str, int num) {
  printf("%.*s",num,str);
}

int main() {
  DebugStream demo(YourFunName,256);
  demo << "hello world!" << endl;
}
```

the stream out text:

```
hello world!


```
## something else

You can define the `NO_DEBUG_OUTPUT` , and there will not stream out. Notice that this will disable all the instantiation's streamout.

Also you can use `mystream.out_en(false);` to disable the current instantiation's stream out.

