# Log: working_uart_lwip
## 21.5.19
### entry 1
so the webserver is _actually_ just... running. with the command parser. but there is still the problem where the uart line size is to small... i'll see if increasing it (ok, doubling it) bricks the stm
### entry 2
Yup, that breaks it. It doesn't hard fault though, i could tell because that would turn on my error led. So yeah, i guess some task needs more space, either the uart task or the command parser itself.
### entry 3
sadly, that didn't fix it... so i tested the max storage space i could asign before it all crashes. The limit is somewhere between 56 and 63 bytes, and i'm too lazy to test it fully. Also 56 bytes is enough to prevent the uart from bugging, so i'm content. I'll now try to host the server from the [server demo](https://github.com/valentin-veluppillai/diplomprojekt/tree/master/software/f7/demo_webserver).
### entry 4
so the server works. and the parser too. i am done with this project now, ill move on to integrating the [rotary encoder](https://github.com/valentin-veluppillai/diplomprojekt/tree/master/software/f4/Rotary_FreeRTOS_Demo)
