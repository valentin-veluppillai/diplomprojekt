# `[ARCHIVED]`
# demo_webserver

this is the webserver used for the first presentation.

## purpose

this was intended as a proof of work, and was used for the first presentation.

## problems
### command parser
the uart command parser crashes the stm after executing a command. only reboot works, as it reboot before the crash. this happens whenever the webserver is working, just starting lwip does not break it.
#### fixes
i'll try seeing what part of the webserver breaks the parser, by working up from the [working_uart_lwip project](https://github.com/valentin-veluppillai/diplomprojekt/tree/master/software/f7/working_uart_lwip)

any progress will be in that project.
