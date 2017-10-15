# Projekt
Cíl: bezpečnostní zařízení s využitím Arduino UNO a modulu ESP8266
- LED displej vyzívá k zadání hesla pro aktivaci systému
- po zadání správného hesla se spustí odpočet do aktivace alarmu
- po skončení odpočtu začne ultrazvukový senzor snímat vzdálenost k protější stěně
  - pokud se vzdálenost změní, spustí se odpočet do spuštění alarmu a objeví se výzva k zadání hesla
    - pokud je zadáno správné heslo, alarm se vypne a je nutné znovu zadat heslo pro jeho aktivaci
    - pokud heslo zadáno není, spustí se alarm
      - sputí se bzučák
      - rozsvítí se LED
      - odešle se E-mail
      - na displeji se objeví možnost zadání hesla pro vypnutí alarmu
        - po zadání správného hesla se vypne bzučák, zhasne LED a je nutné znovu zadat heslo pro opětovnou aktivaci
- možnost ovládat zařízení přes aplikaci díky modulu 8266
  - zkrátit nebo prodloužit časy
  - změnit heslo
  - nastavit automatické spuštění na určitou dobu
  - vypnout nebo zapnout systém na dálku
  - atd.
- 3.10.2017
    - dorazily součástky, začínám stavět
- 14.10.2017
  - CO FUNGUJE: 
    - hardware je až na modul ESP8266 složený a funkční
    - je možné alarm spouštět i vypínat, displej funguje jak má, chybové hlášky se vypisují jak mají
    - LED i bzučák fungují
  - CO NEFUNGUJE:
    - není možné vypnout alarm v daném intervalu do jeho spuštění - při zadávání hesla se zastaví odpočet, čímž se alarm v podstatě vypne       ať je heslo zadáno nebo ne - nutné vyřešit
    - stejný problém je při pokusu o přerušení odpočtu do aktivace alarmu
    - ESP8266 jsem ještě nezapojil - není možné komunikovat s PC, nezačal jsem ani psát samotnou aplikaci
- 15.10.2017
  - všechny problémy vyřešeny, zdá se, že vše funguje jak má
  - modul ESP8266 stále nezapojen, nutné vyřešit jeho napájení
  - nutné zjistit, jak arduino "uspat", když alarm není zapnutý
    
  
