# Brightness

Since there was no f*cking lightweight utility to handle brightness, I decided to make mine!

Really simple, no bs, 77 lines, 12Ko final binary size.

## Installation

1. Clone the repo.
2. Compile the binary.
  - `gcc brightness.c -o brightness`
3. Change owner to root.
  - `sudo chown root:root brightness`
4. Give it SUID mode.
  - `sudo chmod u+xs brightness`
5. Move it in your `$PATH`, or wherever you want, I don't care.
6. ???
7. Profit

## Usage

```sh
# Increase brightness
brightness +

# Decrease brightness
brighntess -
```
Simple af right? :)

## Feeling like a h@ck3erman ?

Modify the `step` variable to your needs.

The system file used to control the brightness are:
- `/sys/class/backlight/intel_backlight/max_brightness`
- `/sys/class/backlight/intel_backlight/brightness`

You might want to adjust those according to your hardware.

## Shell Script?

Should work in theory, but since you can only SUID binaries, you'll have to run it as a priviledged user.
This might be inconvenient for key-bindings within your wm (I hope your wm doesn't run on root privilege :p).

## Disclaimer

USE AT YOUR OWN RISK!

License is MIT so do whatever the hell you want with this software ;)
