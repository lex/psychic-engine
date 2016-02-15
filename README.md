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
$ ./juuhman --print-codes < main.cpp
$ ./juuhman --print-stats < test.txt
$ ./juuhman --print-encoded < test.txt
```

#### Examples of use:
	juuhman [option] < test.txt 
	head -n 50 /dev/urandom | juuhman [option]

#### Options:
	--print-codes
	--print-encoded
	--print-stats

#### Testing (OS X)

```shell
$ brew install boost
$ cd psychic-engine/tests
$ make
$ ./test
```

#### License

See [LICENSE](https://raw.githubusercontent.com/lex/psychic-engine/master/LICENSE "LICENSE") for more information.
