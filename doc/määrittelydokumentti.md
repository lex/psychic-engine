# Määrittelydokumentti

#### Algoritmit ja tietorakenteet

Toteutan Huffman codingin. Tarkoituksena on pakata tekstiä. Käytettävät tietorakenteet ovat prioriteettijono ja binääripuu.

#### Minkä ongelman ratkaisen ja miksi

Ratkaisen pakkausongelman. Valitsin sen, koska se oli annetuista aiheideoista mielenkiintoisin.

#### Mitä syötteitä ohjelma saa ja miten näitä käytetään

Ohjelma tulee saamaan ainakin pakattavan tai purettavan datan stdiniin ja tulostamaan vastaavan datan ulos stdouttiin.

#### Tavoitteena olevat aika-ja tilavaativuudet

Olkoon n tavujen määrä alkuperäisessä datassa.

Aikavaativuus: O(n log n)
Pinoon lisäämisen aikavaativuus on O(log n), ja sitä tehdään pahimmassa tapauksessa n kertaa.

Tilavaativuus: O(n)
Algoritmi luo puun, jossa on maksimissaan 2n - 1 alkiota.

#### Lähteet

http://en.wikipedia.org/wiki/Huffman_coding
