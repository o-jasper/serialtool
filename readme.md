# Serial port communication
Little helper functions to make serial port communication obvious, and some 
examples.

### Help by analogy with Arduino code

`Serial.begin(baud_rate)` sortah corresponds to 
`int serial_open(const char *device, int baud)` computers have multiple
'serial outputs' in Linux they're represented as files. That is the `device` 
input argument. The function returns an integer that refers to this file,
henceforth called `fd`.

`Serial.available()`, `Serial.read()`, `Serial.write()` *dont* quite correspond.
Instead of first looking if it is already there, `read(fd,buffer,want_length)`,
and the same for `write()` returns the number of bytes received/sent. To get data, 
you run until you have(sent) some portion you can use.

### TODO
* Add 'portion getter' to automate that for the user?
* It seems that the arduino resets on closing, would be nicer if the user had
  the option not to.

## License
Released into the public domain.
