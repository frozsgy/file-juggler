# File Juggler
A command-line tool to juggle files, and de-juggle juggled ones.

## Background
While taking the Operating Systems course, I have used many system calls and played with file systems, file descriptors, and other things. At the very end, while studying FAT file systems, the idea of using a linked-list-like structure to store files seemed like something that I would love to try. After a while I started to work on this, which lead to the creation of File Juggler.

## Description
File Juggler has two executable files, one for juggling files, and the other one is for dejuggling previously juggled ones. It is not meant to be used as a tool to encrypt data, but it provides scrambled non-sensical files enough to keep untrained eyes away. 

## Details
To juggle a file, you need to select the block size. Each block has an `unsigned integer` to store the next data block position. Therefore, a juggled file will have 0.4% to %0.01 overhead for each file depending on the block size. Juggling also inverts the data bits, so any plain-text file cannot be read by simply opening the file.

## Usage
1. Build the app using `make`.
2. To juggle files, use `./build/juggler block-size original-file target-file`
3. To de-juggle, use `./build/dejuggler starting-block juggled-file target-file`

Block size can be either 1, 2, 4, 8, 16 or 32 KB's. 

For example, to juggle a file named Pomplamoose-BustYourKneeCaps.flac using 32 KB blocks, you should type `./build/juggler 32 Pomplamoose-BustYourKneeCaps.flac JuggledPomplamoose.jgg`. This will give an output with the initial block number, which you must keep to de-juggle the file properly. Let's say the initial block is 47. Then, to de-juggle you should type `./build/dejuggler 47 JuggledPomplamoose.jgg BustYourKneeCaps.flac`

## Bugs, Feature Requests, Ideas
I love hearing feedback! Please let me know by sending an e-mail. Pull requests are always welcome.