# ESP8266 Terminal
---

We can use the ESP8266 as a TTY device.

## Overview
We upload the Seria-TCP Chat sketch to the ESP8266. We then connect the ESP8266
to a Linux machine with serial, and open a terminal on the `/dev/ttyUSB0` port.
Then we connect with TCP to the ESP8266 (from another machine or even the same one), where
we'll get a login session to the Linux machine.

![image](https://github.com/yoav-klein/ESP8266/blob/main/ESP8266-Terminal/ESP-Terminal.png)

## Setup

### On the ESP8266
Upload the `SerialTCPChat` sketch.

### On the Linux machine
Connect the ESP8266 to the Linux machine using a USB-to-serial converter.
If your Linux runs on bare-metal, your machine should detect it with no problem.

If you're using VirtualBox, you need to set up the USB device in the USB Filters section in
the settings of the virtual machine. This is because the USB device cannot be used both by the host and
the guest operating systems, so you need to tell VirtualBox that once you connect that device, it will
be captured by the VM and not by the host.

Now we use `agetty` to get a TTY on the `/dev/ttyUSB0` TTY device.

```
$ sudo setsid agetty ttyUSB0 115200
```
We use `setsid` since in order for the terminal to be a controlling terminal, it has to run 
in a new session.

### On another machine (Linux/Windows)
Now our ESP8266 waits for an incoming TCP connection. Once such a connection is established, it will forward
bytes between this connection and the serial port.

Open a TCP connection using Hercules or whatever to the ESP8266, and you should be prompted
with a login session. After you login you have a shell in the Linux machine.

#### Signals
Now that your ESP8266 is acting as an old-style UART terminal, you can pass along ^C to the machine
and the line discipline will generate a signal to the foreground job of the terminal.
Try it: pass a `0x03` (^C) in the TCP connection.
