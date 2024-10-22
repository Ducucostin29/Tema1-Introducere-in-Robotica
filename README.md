# Tema1-Introducere-in-Robotica
În această temă simulam o stație de încărcare pentru un vehicul electric, folosind mai multe LED-uri și butoane. În cadrul acestui task trebuie să țin cont de stările butonului și să folosesc debouncing, dar și să coordonez toate componentele ca într-un scenariu din viața reală. Led-ul RGB reprezintă disponibilitatea stației. Dacă stația este liberă led-ul va fi verde, iar dacă stația este ocupată se va face roșu. Led-urile simple reprezintă gradul de încărcare al bateriei, pe care îl vom simula printr-un loader progresiv (L1 = 25%, L2 = 50%, L3 = 75%, L4 = 100%). Loader-ul se încărca prin aprinderea succesivă a led-urilor, la un interval fix de 3s. LED-ul care semnifică procentul curent de încărcare va avea starea de clipire, LED-urile din urma lui fiind aprinse continuu, iar celelalte stinse. Apăsarea scurtă a butonului de start va porni încărcarea. Apăsarea acestui buton în timpul încărcării nu va face nimic. păsarea lungă a butonului de stop va opri încărcarea forțat și va reseta stația la starea liberă. Apăsarea acestui buton cat timp stația este liberă nu va face nimic.

## Componentele utilizate
- 4x LED-uri (pentru a simula procentul de încărcare)
- 1x LED RGB (pentru starea de liber sau ocupat)
- 2x Butoane (pentru start încărcare și stop încărcare)
- 9x Rezistoare (7x 220/330ohm, 2x 2K)
- Breadboard
- Linii de legătură
- Placa Arduino Uno R3 ATmega328P/PA

## Descriere

### Setup-ul fizic

# void citireButonIncepe()
   Ce face: Verifică dacă butonul de start (butonul conectat la pinul 3) este apăsat.
  Detalii: 
  - Când butonul este apăsat (detectat ca LOW), funcția inițiază procesul de încărcare:
  - Activează starea de încărcare (esteIncarcareInProgres = 1).
  - Resetează contorul de timp pentru a începe procesul de încărcare (timpUltimaActualizare = millis()).
  - Utilizează o întârziere (delay(DEBOUNCE_DELAY)) pentru a preveni multiple detectări rapide (debouncing).

```
void citireButonIncepe() {
  int stareButonStart = digitalRead(BUTON_INCEPE);
  if (stareButonStart == LOW) {// Verificăm dacă butonul este apăsat
    delay(DEBOUNCE_DELAY);  // Anti-debouncing
    esteIncarcareInProgres = 1;  // Se începe încărcarea
    timpUltimaActualizare = millis();  // Resetează timpul pentru controlul bateriei
  }
}
```
    
# void citireButonOpreste()
   Ce face: Verifică dacă butonul de oprire (butonul conectat la pinul 2) este apăsat.
  Detalii: 
  - Când butonul de oprire este apăsat (detectat ca LOW), funcția oprește procesul de încărcare:
  - Dezactivează starea de încărcare (esteIncarcareInProgres = 0).
  - Resetează nivelul de încărcare la 0 (nivelIncarcare = 0).
  - Utilizează și aici debouncing pentru a preveni multiple detectări rapide ale apăsării.

```
void citireButonOpreste() {
  int stareButonStop = digitalRead(BUTON_OPRESTE);
  if (stareButonStop == LOW) {// Verificăm dacă butonul este apăsat
    delay(DEBOUNCE_DELAY);  // Anti-debouncing
    esteIncarcareInProgres = 0;  // Se oprește încărcarea
    nivelIncarcare = 0;  // Resetează nivelul de încărcare
  }
}
```
    
# void actualizeazaLEDuri()
   Ce face: Controlează starea LED-urilor în funcție de procesul de încărcare.
Detalii:
   - Dacă încărcarea este în progres (esteIncarcareInProgres == 1):
   - LED-ul roșu este aprins (digitalWrite(RED_LED, HIGH)).
   - LED-ul verde și albastru sunt stinse (digitalWrite(GREEN_LED, LOW) și digitalWrite(BLUE_LED, LOW)).
 Dacă încărcarea nu este activă:
   - LED-ul albastru este aprins (digitalWrite(BLUE_LED, HIGH)).
   - LED-urile roșu și verde sunt stinse.
   - Toate LED-urile albastre care indică progresul încărcării sunt stinse.

```
void actualizeazaLEDuri() {
  if (esteIncarcareInProgres) {
    digitalWrite(GREEN_LED, LOW);  // LED verde stins când se încarcă
    digitalWrite(RED_LED, HIGH);   // LED roșu aprins când se încarcă
    digitalWrite(BLUE_LED, LOW);   // LED albastru stins
  } else {
    digitalWrite(GREEN_LED, LOW);  // LED verde stins când nu se încarcă
    digitalWrite(RED_LED, LOW);    // LED roșu stins când nu se încarcă
    digitalWrite(BLUE_LED, HIGH);  // LED albastru aprins
    digitalWrite(LED_ALBASTRU_1, LOW);
    digitalWrite(LED_ALBASTRU_2, LOW);
    digitalWrite(LED_ALBASTRU_3, LOW);
    digitalWrite(LED_ALBASTRU_4, LOW);
  }
}
```

# void secventaIncarcare()
   Ce face: Controlează secvența de încărcare a bateriei, aprinzând progresiv LED-urile albastre.
Detalii:
   - Când încărcarea este activă (esteIncarcareInProgres == 1), verifică dacă a trecut un interval de 3 secunde (INTERVAL_INCARCARE).
   - Dacă acest interval a trecut, nivelul de încărcare crește (nivelIncarcare++), iar în funcție de nivel, LED-urile albastre se aprind treptat, simulând încărcarea bateriei:
   - La nivelul 0, toate LED-urile sunt stinse, dar primul LED începe să clipească.
   - La nivelul 1, primul și al doilea LED albastru sunt aprinse.
   - La nivelul 2, LED-urile 1, 2 și 3 sunt aprinse.
   - La nivelul 3, toate cele 4 LED-uri albastre sunt aprinse.
   - La nivelul 4, încărcarea este completă, toate LED-urile albastre rămân aprinse, iar procesul de încărcare se oprește automat (esteIncarcareInProgres = 0).
   - Funcția include și întârzieri scurte pentru a simula vizual un efect de progres pe LED-uri.

```
void secventaIncarcare() {
  if (esteIncarcareInProgres) {
    unsigned long timpCurent = millis();  // Obține timpul curent

    // Controlează intervalul de încărcare
    if (timpCurent - timpUltimaActualizare >= INTERVAL_INCARCARE) {
      timpUltimaActualizare = timpCurent;
      nivelIncarcare++;  // Crește nivelul de încărcare
      if (nivelIncarcare > 4) {
        nivelIncarcare = 0;
        esteIncarcareInProgres = 0;  // Oprește încărcarea când bateria este completă
      }
    }

    // Control LED-uri pentru progresul bateriei
    switch (nivelIncarcare) {
      case 0:
        digitalWrite(LED_ALBASTRU_1, LOW);
        delay(500);
        digitalWrite(LED_ALBASTRU_1, HIGH);
        delay(500);
        digitalWrite(LED_ALBASTRU_2, LOW);
        digitalWrite(LED_ALBASTRU_3, LOW);
        digitalWrite(LED_ALBASTRU_4, LOW);
        break;
      case 1:
        digitalWrite(LED_ALBASTRU_1, HIGH);
        digitalWrite(LED_ALBASTRU_2, LOW);
        delay(500);
        digitalWrite(LED_ALBASTRU_2, HIGH);
        delay(500);
        break;
      case 2:
        digitalWrite(LED_ALBASTRU_2, HIGH);
        digitalWrite(LED_ALBASTRU_3, LOW);
        delay(500);
        digitalWrite(LED_ALBASTRU_3, HIGH);
        delay(500);
        break;
      case 3:
        digitalWrite(LED_ALBASTRU_3, HIGH);
        digitalWrite(LED_ALBASTRU_4, LOW);
        delay(500);
        digitalWrite(LED_ALBASTRU_4, HIGH);
        delay(500);
        break;
      case 4:
        digitalWrite(LED_ALBASTRU_4, HIGH);
        digitalWrite(LED_ALBASTRU_1, LOW);
        digitalWrite(LED_ALBASTRU_2, LOW);
        digitalWrite(LED_ALBASTRU_3, LOW);
        digitalWrite(LED_ALBASTRU_4, LOW);
        delay(500);
        digitalWrite(LED_ALBASTRU_1, HIGH);
        digitalWrite(LED_ALBASTRU_2, HIGH);
        digitalWrite(LED_ALBASTRU_3, HIGH);
        digitalWrite(LED_ALBASTRU_4, HIGH);
        delay(500);
        break;
    }
  }
}
```

## Poze ale setup-ului fizic
![Poza 1 robo](https://github.com/user-attachments/assets/7b8e2189-875d-43c7-83ba-a880810b91f4)
![Poza 2 robo](https://github.com/user-attachments/assets/96b4e494-892d-44e8-81d7-b71011e935e2)
![Poza 3 robo](https://github.com/user-attachments/assets/fb0ecb40-c7fc-4b7b-9523-96b906dc4ac8)

## Video cu funcționalitatea montajului fizic
[![Watch the video] (https://www.youtube.com/watch?v=vYdteI34t-o&ab_channel=AlexandruApostu)

## Schema electrică (TinkerCAD)
- Conectarea LED-urilor albastre la pinii 7, 8, 9 și 10.
- Conectarea LED-ului RGB la pinii 4, 5 și 6.
- Conectarea butonului de start la pinul 3 și a butonului de stop la pinul 2.
- Utilizarea rezistențelor pentru protecția LED-urilor și pentru stabilizarea butoanelor.
![image](https://github.com/user-attachments/assets/d7585af1-ac0b-4dbe-8792-02024aa77800)
![image](https://github.com/user-attachments/assets/656cfee2-b10f-4a02-98b9-a2d16b7902db)





