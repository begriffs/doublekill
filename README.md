### Weird experiments


#### Segrand

Generate a random number from a segfault. It overwrites memory until a segfault
happens, outputting the ptrdiff\_t offset each time. The segfault stops the
counter, and you can retrieve the final value as a random number.

How to get ten random numbers:

```sh
yes | head -n 10 | xargs -L 1 sh -c './segrand | tail -1'
```
