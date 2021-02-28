# Robot-Arm-UStepper

## Disclaimer:
Designet er laget av nic6911 og kan hentes her: https://www.thingiverse.com/thing:3876856

## Intro:
Her skal jeg utforske robotikkfaget IN3140 gjennom å prøve ut det vi lærer i praksis da vi (trolig) ikke får gjort dette på skolen pga. covid-19. **NB: Bruker bibiloteket AccelStepper**, for instalasjon og hjelp se
[AccelStepper](http://www.airspayce.com/mikem/arduino/AccelStepper/index.html)

### Bilder av manipulatoren:
![Bilde fra siden](/src/armSide1.jpg)
![Bilde ovenfra](/src/armTop.jpg)

Jeg har valgt å oppkalle den [DUM-E](https://marvelcinematicuniverse.fandom.com/wiki/Dum-E_and_U) fra Marvel Cinematic Universe etter et nestenuhell, i tilegg til at de har visse likheter.

## Endelig mål:
* Lage den grenerell slik at det skal være enkelt å gi den nye koordinater, komandoer eller liknende.
* Kunne tegne forskjellige figurer med den. Kunne gi den en blyant og en tegning, (kanskje kunne bruke et slicingprogram som CURA/PrusaSlicer?)

**Se de forskjellige mappene for forskjellige løsninger:**
* Inverse_Kinematics_v1 for testing av invers Kinematikk (**Done**)
* RobotArm_objekt skal bli set samlet objekt (**IN progress**)

## Forward kinematics:
Setter de forskjellige koordinatsystemene:
![koordinatsystemer](/src/illustrasjonKoordinatsystemer.png)

Utregning av DH parametere
(**IN progress**)

## Backward kinematics:
(**IN progress**)
### Utregning av th_1
![Utregning av th_1](/src/illustrasjonRegne_th_1.png)

### Utregning av th_3
![Utregning av th_3](/src/illustrasjonRegne_th_3.png)

### Utregning av th_2
![Utregning av th_2](/src/illustrasjonRegne_th_2.png)

## Skal gjøre:
* Redesigne Structure_Right_Side.stl og Structure_Left_Side.stl med endestoppere så den kan finne "hjem" når den starter opp.
* Regne på Jacobian-matrisen for fart
* Modelere den i ROS
* Fikse problem 1, se problemer

## Problemer:
1)
Om verktøyet er i et punkt nært bakken (som grønt punkt P) og skal til en annet punkt (gult punkt G) der th_2 er relativt lik for begge punktene, men th_3 er ulikt vil armen med dagens oppsett prøve å gå gjennom bakken.
![Illustrasjon av problem 1](/src/illustrasjonProblem1.png)

## Timeline:
