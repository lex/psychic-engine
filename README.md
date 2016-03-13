# psychic-engine

Huffman coding
***
<p align="center">
<img src="/doc/screenshot.png">
</p>
***
#### Usage

```shell
$ git clone https://github.com/lex/psychic-engine.git
$ cd psychic-engine/src
$ make
$ cat test.txt
fresh beer enjoyment 🍺🍺🍺
$ ./juuhman --encode test.txt -o encoded
$ ./juuhman --decode encoded -o decoded.txt
$ cat decoded.txt
fresh beer enjoyment 🍺🍺🍺
```

#### Examples of use:
	juuhman [option] [input file] -o [output file] 

#### Options:
	--encode
	--decode

#### Testing (OS X)

```shell
$ brew install boost
$ cd psychic-engine/tests
$ make
$ ./test
```

#### License

See [LICENSE](https://raw.githubusercontent.com/lex/psychic-engine/master/LICENSE "LICENSE") for more information.
