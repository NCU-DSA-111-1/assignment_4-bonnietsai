# Data Structure Final Project: Rummikub
#### 電機4B 108501025 沈冠璋
#### 電機4B 108501537 蔡雨蓁

The program can let **3** players play Rummikub. 

How to play:
1. The program will show you which cards every players has at each truns
2. First,
3. Second, you should choose a mode to play card
    * Number "0" is **construct a new cardpile in field**
    * Number "1" is **Connect** or **cut** or **move** a card in current field
    * Number "2" is **return**
4. The system will show the change in the field after a players' turn
5. Repeat to step1 until someone win 
    
*  If you choose **Mode 0**, you have to type **how many** cards you want to play and type the info of these card (number and color in order), the system will judge whether these cards break the rules, and if they does, you should type again
*  If you choose **Mode 1**, you should choose an index in field you want to insert, cut, or move.
After you choose, you should choose another mode to tell system what you want to do
    * Number "0" is **cut**
    * Number "1" is **insert**
    * Number "2" is **move**
* **Follow the instructions system ask to you!!!**
 
## How to Compile & Run 
```sh
# Compile
gcc -o aa main.c card.c 

# Run (Playing a new game)
./aa

```

