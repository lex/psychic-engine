# Testausdokumentti

- Testattu nopeutta ja toimivuutta binääritiedostoilla, tekstitiedostoilla sekä satunnaisdatalla.
- Yksikkötestit testaavat vain oikeaa (toivottua) ulosantia.

#### Nopeus

Erilaisia tiedostoja kokeiltaessa huomattiin, että putki on selvästi suurin pullonkaula ohjelman nopeudelle.

6,2 megatavun tekstitiedosto putkitettuna:
```shell
lex@steve ~/psychic-engine/src (master*) $ time ./juuhman --print-stats < big.txt
Calculating frequencies...
Creating a tree...
Generating Huffman code...
Generating the encoded string...

Original size:	6488666 bytes
Encoded size:	3683091 bytes (56.7619% of original)
./juuhman --print-stats < big.txt  1.39s user 0.06s system 99% cpu 1.455 total
```

Koodiin sisällytettynä:
```shell
lex@steve ~/psychic-engine/src (master*) $ time ./juuhman --print-stats
Calculating frequencies...
Creating a tree...
Generating Huffman code...
Generating the encoded string...

Original size:	6360209 bytes
Encoded size:	3568831 bytes (56.1119% of original)
./juuhman --print-stats  0.21s user 0.04s system 96% cpu 0.260 total
```

Eli noin 4,5 kertaa nopeampi.

Teksteissä oli joitakin tavuja eroa koossa laiskasta merkkien escapeamisesta johtuen.

Saa nähdä, hidastuuko ohjelma, kun siihen toteutetaan omat tietorakenteet C++:n standardikirjaston toteutuksien tilalle.

Nopeutta voisi myös nostaa reilusti (vaikka kyse onkin millisekunneista) käyttämällä useampaa säiettä. Merkkien määrien sekä koodien laskeminen rinnakkaistuisivat erittäin helposti.

#### Toimivuus

/dev/urandomin kanssa huomattiin, ettei ohjelma toiminutkaan toivotulla tavalla. Merkkien laskemisessa käytetty silmukka ei käynytkään kaikkia merkkejä läpi. Ongelma korjautui tarkastamalla ehto vasta silmukan jälkeen. UINT8_MAX kun on 255, johon alkuperäinen for-lauseke ei yllä.

```c++
    for (uint8_t i = 0; i < UINT8_MAX; ++i) {
    ...
```
muotoon
```c++
    uint8_t i = 0;
    do {
    ...
    } while (i++ < UINT8_MAX)
```
