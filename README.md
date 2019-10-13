## CNS
This repository contains the assignments done as a part of CNS (Cryptography and Network Security) Course.
The Folders are:
### Ciphers
It contains the implmentations of several substitution based cryptographic algorithms.
### Usage
Clone the repo: ```git clone https://github.com/DEBADRIBASAK/CNS.git```

Compile the headers:

e.g. ```g++ ciphers.h```

Use in codes:

```#include "ciphers.h"```

#### Using the python wrappers:


`
>>> from AES import AES,GF_2n
>>>
>>> g = GF_2n("x3+x+1") # the irreducible polynomial
>>>
>>> g.mul_inv(4) # multiplicative inverse in GF(2^n)
>>>
>>> a = AES('1234ABCDabcd#@$%')  # the key goes in argument
>>>
>>>a.encrypt('hello world hii!') # 16 characters block size
'\xbbj\x04\xcd\xf0\x0f\xa5\xcco[\xe8\x8d\xb2\xa4?*'
>>>
>>> a.decrypt('\xbbj\x04\xcd\xf0\x0f\xa5\xcco[\xe8\x8d\xb2\xa4?*')
'hello world hii!'
 `