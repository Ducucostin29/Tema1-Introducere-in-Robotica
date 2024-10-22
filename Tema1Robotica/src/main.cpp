#include <Arduino.h>

#define LED_ALBASTRU_1 10
#define LED_ALBASTRU_2 9
#define LED_ALBASTRU_3 8
#define LED_ALBASTRU_4 7
#define RED_LED 6
#define GREEN_LED 4
#define BLUE_LED 5
#define INTERVAL_INCARCARE 3000
#define BUTON_INCEPE 3
#define BUTON_OPRESTE 2
#define DEBOUNCE_DELAY 20

// Variabile globale
int nivelIncarcare = 0;  // Nivelul curent al încărcării bateriei
unsigned long timpUltimaActualizare = 0;  // Timpul ultimei actualizări
int esteIncarcareInProgres = 0;  // Starea de încărcare (0 = oprit, 1 = în curs de încărcare)

// Prototipuri funcții
void citireButonIncepe();
void citireButonOpreste();
void actualizeazaLEDuri();
void secventaIncarcare();


// Funcția de inițializare (setup)
void setup() {
  // Configurare pini ca OUTPUT sau INPUT
  pinMode(LED_ALBASTRU_1, OUTPUT);
  pinMode(LED_ALBASTRU_2, OUTPUT);
  pinMode(LED_ALBASTRU_3, OUTPUT);
  pinMode(LED_ALBASTRU_4, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUTON_INCEPE, INPUT_PULLUP);
  pinMode(BUTON_OPRESTE, INPUT_PULLUP);
}

// Funcția principală (loop) care se execută continuu
void loop() {
  citireButonIncepe();  // Verifică dacă se apasă butonul de start
  citireButonOpreste(); // Verifică dacă se apasă butonul de stop
  actualizeazaLEDuri();  // Actualizează starea LED-urilor în funcție de stare
  secventaIncarcare();   // Controlează secvența de încărcare dacă e activă
}

/**
 * Funcția citireButonIncepe verifică dacă butonul de start este apăsat
 * și începe încărcarea.
 */
void citireButonIncepe() {
  int stareButonStart = digitalRead(BUTON_INCEPE);
  if (stareButonStart == LOW) {// Verificăm dacă butonul este apăsat
    delay(DEBOUNCE_DELAY);  // Anti-debouncing
    esteIncarcareInProgres = 1;  // Se începe încărcarea
    timpUltimaActualizare = millis();  // Resetează timpul pentru controlul bateriei
  }
}

/**
 * Funcția citireButonOpreste verifică dacă butonul de stop este apăsat
 * și oprește procesul de încărcare.
 */
void citireButonOpreste() {
  int stareButonStop = digitalRead(BUTON_OPRESTE);
  if (stareButonStop == LOW) {// Verificăm dacă butonul este apăsat
    delay(DEBOUNCE_DELAY);  // Anti-debouncing
    esteIncarcareInProgres = 0;  // Se oprește încărcarea
    nivelIncarcare = 0;  // Resetează nivelul de încărcare
  }
}

/**
 * Funcția actualizeazaLEDuri controlează LED-urile în funcție de starea
 * de încărcare (esteIncarcareInProgres).
 * - Aprinde LED-ul verde când se încarcă.
 * - Aprinde LED-ul roșu când nu se încarcă.
 */
void actualizeazaLEDuri() {
  if (esteIncarcareInProgres) {
    digitalWrite(GREEN_LED, LOW);  // LED verde stins când se încarcă
    digitalWrite(RED_LED, HIGH);   // LED roșu aprins când se încarcă
    digitalWrite(BLUE_LED, LOW);   // LED albastru stins
  } else {
    digitalWrite(GREEN_LED, HIGH);  // LED verde stins când nu se încarcă
    digitalWrite(RED_LED, LOW);    // LED roșu stins când nu se încarcă
    digitalWrite(BLUE_LED, LOW);  // LED albastru aprins
    digitalWrite(LED_ALBASTRU_1, LOW);
    digitalWrite(LED_ALBASTRU_2, LOW);
    digitalWrite(LED_ALBASTRU_3, LOW);
    digitalWrite(LED_ALBASTRU_4, LOW);
  }
}

/**
 * Funcția secventaIncarcare controlează procesul de încărcare,
 * incrementând nivelul bateriei la fiecare interval de timp definit
 * și actualizând LED-urile de progres ale bateriei.
 */
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
