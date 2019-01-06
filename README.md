### Weird experiments

#### Dkill

Assault a process with repeated SIGINTs as fast as possible. This can determine
if those processes reinstate their signal handler promptly enough or if they
allow it to lapse into the default handler. Some systems (like OpenBSD) do not
require handlers to reinstate themselves and block a storm of signals while a
handler is processing, so you won't be able to mess programs up.

Usage: ./dkill -p <pid> -x <times>

#### Catcher

A nice target for Dkill. It sleeps in the handler to open up a window of
attack.

#### Segrand

Generate a random number from a segfault. It overwrites memory until a segfault
happens, outputting the ptrdiff\_t offset each time. The segfault stops the
counter, and you can retrieve the final value as a random number.

How to get ten random numbers:

```sh
yes | head -n 10 | xargs -L 1 sh -c './segrand | tail -1'
```
