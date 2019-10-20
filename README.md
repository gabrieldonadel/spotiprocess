# spotiprocess
A simple C project implementing message queue

## How to compile
Compiling the composer
```c
gcc composer.c -o composer -pthread
```

Compiling the listener
```c
gcc listener.c -o listener
```

to filter

./listener | grep 'Gospel;'
## Commands
A list of commands that can be used with this software

### Listener

| Commands        | default | description  |
| ------------- |:-------------:| -----|
| -g     | false | prints the whole song<br> in one line |
| -r     | Infinite| set the number of songs<br> that the process will listen for |
