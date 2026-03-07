# Tartalom

[Felhasználói dokumentáció [1](#_Toc223644551)](#_Toc223644551)

[Szükséges komponensek
[1](#szükséges-komponensek)](#szükséges-komponensek)

[Telefonos alkalmazás használata
[2](#telefonos-alkalmazás-használata)](#telefonos-alkalmazás-használata)

[Fejlesztői dokumentáció
[5](#fejlesztői-dokumentáció)](#fejlesztői-dokumentáció)

[Telefonos alkalmazás kódja
[5](#telefonos-alkalmazás-kódja)](#telefonos-alkalmazás-kódja)

[Bluetooth kezelés [5](#bluetooth-kezelés)](#bluetooth-kezelés)

[Gombok [5](#gombok)](#gombok)

[Színválasztás [6](#színválasztás)](#színválasztás)

[Hardware [7](#hardware)](#hardware)

[Szükséges elektronikai eszközök
[7](#szükséges-elektronikai-eszközök)](#szükséges-elektronikai-eszközök)

[Elektronikai eszközök összekapcsolása
[7](#elektronikai-eszközök-összekapcsolása)](#elektronikai-eszközök-összekapcsolása)

[Arduino kód [10](#arduino-kód)](#arduino-kód)

# Felhasználói dokumentáció

## Szükséges komponensek 

- Telefon, amire telepítve van az alkalmazás

  - Tesztelés esetén egyébként lehet használni a Serial Bluetooth
    Terminal appot is

- Maga az Arduino projekt, ennek működtetéséhez pedig egy konnektor

<p align="center">
<img src="images/media/image1.jpeg"
style="width:3.62981in;height:4.84375in" />
</p>

## Telefonos alkalmazás használata

1.  Első lépésként adjunk áramot a projektnek.

2.  Ezután kapcsoljuk be a Bluetooth-t a telefonon és párosítsuk össze a
    LED elnevezésű Bluetooth eszközzel

> <img src="images/media/image2.png"
> style="width:6.29167in;height:0.89583in" />
>
> A párosítás során szükséges jelszót megadni, ez alapértelmezetten 1234
> vagy 0000 (ezt én megváltoztattam, 2018)

3.  Sikeres párosítást követően indíthatjuk az alkalmazást. Indítást
    követően ez a felület fogad minket:

<img src="images/media/image3.jpeg"
style="width:2.09375in;height:4.53808in" />

4.  Bal felső sarokban nyomjuk meg a Bluetooth ikonnal elátott gombot,
    ekkor megjelennek a párosított eszközeink listája:

<img src="images/media/image4.jpeg"
style="width:1.57155in;height:3.40625in" />

Válasszuk ki a LED eszközt.

5.  Sikeres csatlakozás esetén az alkalmazás visszadob a fő felületre,
    ahol már lehetőségünk van irányítani a led szalagot:

<img src="images/media/image5.jpeg"
style="width:1.72534in;height:3.73958in" />

A felületen található funkciók:

- Lecsatlakozás gombra kattintva le tudunk csatlakozni az aktuálisan
  csatlakoztatott Bluetooth eszközről

- Színfuttatás funkció

  - A led az elejétől a végéig 10-es csoportokban felkapcsolódnak.
    Egyszerre mindig cask 10 led ég, miközben a felkapcsolt ledek színei
    végigmennek az rgb színeken. Videó: Szinfuttatas.mp4

- Színátmenet

  - Az összes led ég és a ledek színei végigmennek az rgb színeken.
    Videó: Szinatmenet.mp4

- Karácsony

  - Páros és páratlan indexű ledek váltakozása, először minden páros
    indexű led ég, majd elhalványulva elalszik miközben minden páratlan
    kezd el égni és ezt így felváltva. Videó: Karacsony.mp4

- Színválasztó

  - A színválasztó képre kattintva vagy a színválasztó közepén található
    kis fekete gombbal van lehetőségünk egy bizonyos szín beállítására.

- Kikapcsoló gomb

  - A gomb megnyomásával “feketére” állítjuk a ledek színét, azaz
    kikapcsoljuk.

# Fejlesztői dokumentáció

## Telefonos alkalmazás kódja

### Bluetooth kezelés

<img src="images/media/image6.png" style="width:6.3in;height:1.89583in"
alt="A képen szöveg, képernyőkép, Betűtípus látható Előfordulhat, hogy az AI által létrehozott tartalom helytelen." />

A BluetoothDevices nevű komponens egy lista, amit rögtön feltöltök a
párosított eszközök MAC-címével és nevével.

Ezzel együtt megjelenik a Lekapcsolódás gomb is.

Miután a listából kiválasztunk egy eszközt és sikeresen csatlakozunk rá,
a led funkciók (gombok, színválasztás) felületet láthatóvá teszem és
megjelenítem az éppen aktuális eszköz MAC-címét és nevét.

### Gombok

<img src="images/media/image7.png" style="width:6.3in;height:1.97431in"
alt="A képen szöveg, képernyőkép, sor, Betűtípus látható Előfordulhat, hogy az AI által létrehozott tartalom helytelen." />

Mindegyik gombnyomás elküld egy karaktert a Bluetooth eszköznek.

- cometButton (Színátmenet) elküldi az ‘r’ karaktert.

- colorTransition (Színátmenet) elküldi a ‘t’ karaktert.

- christmasButton (Karácsony) elküldi az ‘x’ karaktert.

- turnOff (Kikapcsoló gomb) elküldi az ‘o’ karaktert.

### Színválasztás

<img src="images/media/image8.png" style="width:6.3in;height:4.00278in"
alt="A képen szöveg, képernyőkép, tervezés látható Előfordulhat, hogy az AI által létrehozott tartalom helytelen." />

Akkor fut le ez a kód, amikor a színválasztóra rábökünk.

Ekkor a színválasztó található gombot is áthelyezi arra a területre,
ahova böktünk.

Amikor rányomunk a színválasztóra, akkor a megadott pixel színét
(rgb-ben) visszakapjuk x és y koordináta alapján, amit összefűzök
vesszőkkel és a végén egy \n karakterrel. pl.: Rányomunk egy színre,
akkor ezt küldjük el a Bluetooth-on keresztül: vörös szín értéke, zöld
szín értéke, piros szín értéke\n

<img src="images/media/image9.png"
style="width:6.22716in;height:4.87355in"
alt="A képen szöveg, képernyőkép, tervezés látható Előfordulhat, hogy az AI által létrehozott tartalom helytelen." />

Amikor a kis gombot mozgatjuk a színválasztón, akkor a Dragged funkció
beállítja a gomb új helyzetét.

A TouchUp funkció ugyanúgy elküldi a Bluetooth eszköznek a beállított
rgb színt.

## Hardware

### Szükséges elektronikai eszközök

- Tápegység

  - A projektben a bemeneti feszültség 100V-240V, a kimeneti 5V,
    áramerrőség: 2.5 A.

- Arduino UNO

  - Ebben a projektben az UNO R3-as verzióját használom

- HC-05 bluetooth modul

- WS2812b led (40db)

- 330Ω, 2.2kΩ és 4.7kΩ ellenállások

- Jumper vezetékek

### Elektronikai eszközök összekapcsolása

Az egyszerűség kedvéért thinkercad-ben összeraktam egy kis projektet,
amin keresztül bemutatom a kapcsolást.

A thinkercad nem tartalmaz Bluetooth modult, ezért ezt egy sima led
elektronikai eszközzel helyettesítettem.

<img src="images/media/image10.png" style="width:6.3in;height:6.30903in"
alt="A képen szöveg, képernyőkép, diagram, térkép látható Előfordulhat, hogy az AI által létrehozott tartalom helytelen." />

Tápegység

- A 40 db led közvetlenül a tápegységbe van bekötve és nem a
  szerelőlapon keresztül.

Ez biztosítja, hogy nagyobb áram felvétele esetén ne történjen
feszültségingadozás.

- 1db led áramfelvétele max 60mA, jelen esetben ebből 40db van, így ez
  2400mA.

- A szerelőlap sínei általában nem bírnak ekkora áramot, hosszabb távon
  a sínek felmelegedhetnek, a burkolat megolvadhat.

- Az Arduino UNO és Bluetooth modulnak sokkal kevesebb szükséges, így
  amikor hirtelen nagy áramot kap a sín a ledek miatt az Arduino
  resetelhet vagy a Bluetooth lekapcsolódhat (ez meg is történt velem,
  amikor a ledeket is a sínen keresztül kötöttem be).

Ezért ajánlott a ledeket közvetlenül a tápegységbe bekötni és a többi
modult elkülönítve a szerelőlapon!

LED

- A tápegység pozitív vezetéke csatlakozik a szerelősín pozitív sínjébe,
  illetve a led 5V pinbe.

- A tápegység negatív vezetéke csatlakozik a szerelőlap negatív sínjébe,
  illetve a led GND pinbe.

- A lednek a DIN pinje az Arduino 8-as pinjébe csatlakozik egy sorosan
  összekapcsolt 330Ω-os ellenálláson keresztül. Az ellenállás nem
  kötelező, de erősen ajánlott jelstabilizálásra és jelvédelemre.

Arduino UNO

- Az Arduino UNO ugyanerről a tápegységtől kapja az áramot csak a
  szerelőlapon keresztül.

A tápegység pozitív vezetéke az Arduino 5V pinjébe csatlakozik, a
negatív vezeték pedig a GND pinbe.

Bluetooth modul

- A tápegység pozitív vezetéke a Bluetooth modul VCC pinjébe
  csatlakozik. A modul 3.3V – 6V feszültségre van tervezve, így az 5V
  megfelelő.

- A tápegység negatív vezetéke a Bluetooth modul GND pinjébe
  csatlakozik.

- A Bluetooth TX (Transmit) pinje az Arduino 2-es pinjébe csatlakozik.

  - A kódban az Arduino 2-es pinje RX-ként van értelmezve (Bluetooth ide
    küld, Arduino itt fogad adatot)

- A Bluetooth RX (Receive) pinje az Arduino 3-as pinjébe csatlakozik egy
  feszültségosztón keresztűl.

  - A Bluetooth RX pinje 3.3V logikai szintet vár, viszont az Arduino
    pinjei 5V-on küldenek jelet. Feszültségosztás nélkül hosszabb távon
    akár károsodhat is a Bluetooth modul!

> A feszültségosztóhoz egy 2.2kΩ és 4.7kΩ ellenállásokat használok.
>
> Arduino 3-as pinből a vezeték csatlakozik a 2.2kΩ ellenállás egyik
> lábával.
>
> A 2.2kΩ sorosan kapcsolódik a 4.7kΩ-os ellenállással, aminek az egyik
> lába össze van kötve a GND-vel.
>
> A két ellenállás közti ponton így létrejön a kb 3.3V-os feszültség,
> így a két ellenállás között helyeztem el a vezetéket, ami csatlakozik
> az Bluetooth RX pinjéhez.

- A kódban az Arduino 3-as pinje TX-ként van értelmezve.

## Arduino kód
