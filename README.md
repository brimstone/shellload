shellload
=========

Load shellcode into a new process, optionally hide under a false process name.

Usage
-----

Simple usage is to pipe your shellcode, hex encoded, into stdin. This runs the
shellcode in the current shellload process.

(The example shellcode provided will run the command `touch itworks`)

```
$ printf "6a3b589948bb2f62696e2f736800534889e7682d6300004889e652e80e000000746f756368206974776f726b730056574889e60f05" | ./shellload64
```

Intermediate usage is to pass the shellcode as an argument. This spawns a
background process that runs the shellcode.
```
$ ./shellload64 6a3b589948bb2f62696e2f736800534889e7682d6300004889e652e80e000000746f756368206974776f726b730056574889e60f05
```

Advanced usage is to change the process name and arguments when the shellload
process runs. Everything but the last argument is used as the cover process name
and argument.
```
$ ./shellload64 /usr/bin/apache2 -k start 6a3b589948bb2f62696e2f736800534889e7682d6300004889e652e80e000000746f756368206974776f726b730056574889e60f05
$ ps aux | grep apache2
brimsto+ 32364  0.0  0.0  25332  3440 ?        S    14:39   0:00 /usr/bin/apache2 -k start
```


Build
------

The default build target builds for 32 and 64 bit systems.
```
$ make
```
