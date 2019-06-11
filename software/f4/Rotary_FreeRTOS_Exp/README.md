# `[ARCHIVED]`
# Rotary Helligkeitsänderung mit exponentieller Skalierung

Die Helligkeitsänderungen sind um einiges besser sichtbar als bei einer
linearen Skalierung.


## Limitierung
### Speed
Mehr als 6 Stufen(0,1,2,4,8,16) sind aktuell nicht realisierbar, da sich die
Helligkeit pro Stufe um Faktor 2 ändert. Dementsprechend wird die Frequenz des
PWM-Signals mit jeder weiteren Stufe halbiert, weshalb sie bereits bei 7 Stufen
zu langsam ist(=>sichtbares Blinken/Flackern).
