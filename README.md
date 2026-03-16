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

[Bluetooth kezelés [5](#_Toc223644556)](#_Toc223644556)

[Gombok [5](#_Toc223644557)](#_Toc223644557)

[Színválasztás [6](#_Toc223644558)](#_Toc223644558)

[Hardware [7](#hardware)](#hardware)

[Szükséges elektronikai eszközök
[7](#szükséges-elektronikai-eszközök)](#szükséges-elektronikai-eszközök)

[Elektronikai eszközök összekapcsolása
[7](#elektronikai-eszközök-összekapcsolása)](#elektronikai-eszközök-összekapcsolása)

[Arduino kód [10](#_Toc223644562)](#_Toc223644562)

# Felhasználói dokumentáció

## Szükséges komponensek 

- Telefon, amire telepítve van a vezérlő alkalmazás

  - Tesztelés esetén lehet használni a Serial Bluetooth Terminal appot
    is

- Maga az Arduino projekt

<img src="images/media/image1.jpeg"
style="width:3.62981in;height:4.84375in" />

## Telefonos alkalmazás használata

1.  Első lépésként adjunk áramot a projektnek.

2.  Ezután kapcsoljuk be a Bluetooth-t a telefonon és párosítsuk össze a
    LED elnevezésű Bluetooth eszközzel

> <img src="images/media/image2.png"
> style="width:6.29167in;height:0.89583in" />
>
> A párosítás során szükséges jelszót megadni, ez alapértelmezetten 1234
> vagy 0000

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
    Egyszerre mindig cask 10 led ég, miközben a led színe folyamatosan
    változik. Videó: Szinfuttatas.mp4

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

Bővebb információ a MIT app kódról a MIT.md-ben olvasható.

## Hardware

### Szükséges elektronikai eszközök

- Tápegység

  - 5V, áramerrőség: 2.5 A.

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
helyettesíti.

<img src="images/media/image6.png"
style="width:4.16915in;height:4.17512in"
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

Ezért ajánlott a ledeket közvetlenül a tápegységbe bekötni, az Arduinot
és a többi modult elkülönítve a szerelőlapon!

LED

- A ledek közvetlenül vannak összekötve a tápegységgel.

- A lednek a DIN pinje az Arduino 8-as pinjébe csatlakozik egy 330Ω-os
  ellenálláson keresztül. Az ellenállás nem kötelező, de erősen ajánlott
  jelstabilizálásra és jelvédelemre.

Arduino UNO

- Az Arduino UNO ugyanettől a tápegységtől kapja az áramot csak a
  szerelőlapon keresztül.

A tápegység pozitív vezetéke az Arduino 5V pinjébe csatlakozik, a
negatív vezeték pedig a GND pinbe.

Bluetooth modul

- A Bluetooth modul VCC vezetéke a tápegység pozitív vezetéke
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

## Szoftver

### Setup

<img src="images/media/image7.png"
style="width:4.6875in;height:2.10417in" />

A ledek irányításához FastLED könyvtárt használok, a setup-ban beállítom
a FastLED-et a ledek adataival, illetve elindítom a Bluetooth-t.

### Loop

<img src="images/media/image8.png"
style="width:2.57292in;height:1.96875in"
alt="A képen szöveg, képernyőkép, Betűtípus, sor látható Előfordulhat, hogy az AI által létrehozott tartalom helytelen." />

Amikor küldünk egy adatot a Bluetooth-nak, akkor lefut a getCurrentMode
metódus, ami feldolgozza a beolvasott adatot és beállítja az aktuális
funkciót.

Az aktuális funkciók lehetséges értékei: OFF, RUNCOMET, CHRISTMAS,
COLORPICK,

NONE

getCurrentMode folyamatábra:

<img src="images/media/image9.png" style="width:6.3in;height:2.01597in"
alt="A képen diagram, szöveg, sor, Diagram látható Előfordulhat, hogy az AI által létrehozott tartalom helytelen." />

A beolvasás után a currentMode értéke alapján lefuttatjuk a kiválasztott
funkció függvényét.

- RUNCOMET esetében lefut a comet() függvény

- TRANSITION esetében lefut a colorTransition() függvény

- CHRISTMAS esetében lefut a christmas() függvény

- COLORPICK esetében lefut a setColorFromString(const String& msg)
  függvény

- OFF esetén a ledet kikapcsoljuk

## LED funkciói

### Színfuttatás – RUNCOMET – comet()

### Színátmenet – TRANSITION – colorTransition()

100 millisecundumonként váltunk színt az összes leden.

FastLED könyvtár fill_solid() funkciója beállítja egy adott színre az
összes ledet.

A színeket a hue változóval változtatjuk.

### Karácsony – CHRISTMAS – christmas()

### Színválasztó – COLORPICK – setColorFromString()
