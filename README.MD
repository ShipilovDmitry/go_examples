## Линковка с плюсами

Скомпилировать плюсы в статическую библиотеку. Перед компиляцией удостовериться, что утилиты `ranlib` и `ar` из пакета `binutils` находятся в `$PATH` перед системными утилитами.
```sh
❯ which -a ranlib
/usr/bin/ranlib
/usr/local/opt/binutils/bin/ranlib

❯ which -a ar
/usr/bin/ar
/usr/local/opt/binutils/bin/ar
```


```sh
gcc -c example.c
ar rcs libexample.a example.o
```

Указать путь к статической библиотеке в секции cgo LDFLAGS. 
