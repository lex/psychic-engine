#### Yleisrakenne

Ohjelmaa käsketään komentoriviltä. Erilaisia komentoja on enää vain kaksi: pakkaaminen ja purkaminen.

Pakatessa ohjelma saa sisään lähdetiedoston sijainnin ja ulos tulevan tiedoston sijainnin. Pakkaukseen käytetään Huffmanin algoritmiä, ja [tallennusalgoritmia](http://stackoverflow.com/a/759766).

Purkamiseen käytetään samasta vastauksesta löytyvää algoritmia. Työhön valitussa kielessä ei ollut mitään vastauksen kielen kaltaista helppoa tapaa käsitellä bittejä tässä tarkoituksessa, joten omaan toteutukseen kului melko paljon aikaa.

#### Aika- ja tilavaativuudet

Merkkien määrien laskeminen O(n) sekä ajallisesti, O(1) tilallisesti.

```python
    frequencies = [] // always size of 256
    
    for character in string:
        frequencies[character]++
```

Puun luonti ajallisesti O(256) + O(n log n) eli O(n log n). Tilallisesti O(n).

```python
    tree = PriorityQueue()
    character = 0
    
    while True:
        frequency = frequencies[character]
        
        node = Node(frequency, character)
        tree.push(node)
        
        // maximum value of a byte
        if character == 255:
            break
```

```python
    while (tree.size > 1):
        rightChild = tree.pop()
        leftChild = tree.pop()
        parent = Node(rightChild, leftChild)
        tree.push(parent)
```

Koodien generointi O(log n), tilallisesti sama.

```python
    def generate_code(node, code):
        if (leaf):
            codes[character] = code
            return
            
        generate_code(node.left, code + '0')
        generate_code(node.right, code + '1')
```

Koodatun merkkijonon generointi O(n).

```python
    encoded = ""
    
    for character in string:
        encoded += codes[character]
        
    return encoded
```

#### Puutteet

- Suuret (tai ainakaan erittäin suuret) tiedostot eivät pakkaudu.
- Ohjelma ei ota virhetilanteita huomioon erityisen hyvin.
- Ohjelma saattaa varata huomattavan määrän muistia.

#### Lähteet

https://en.wikipedia.org/wiki/Huffman_coding
http://bigocheatsheet.com
