#include <Arduino.h>
#define LED_ALBASTRU_1 10
#define LED_ALBASTRU_2 9
#define LED_ALBASTRU_3 8
#define LED_ALBASTRU_4 7
#define RED_LED 4
#define GREEN_LED 5
#define BLUE_LED 6
#define INTERVAL 4000
#define BUTON_INCEPE 3
#define BUTON_OPRESTE 2

// Variabile globale
int baterie = 0;
int timpUltimaActualizare = 0;  // Redenumit din previousMillis
int incarcare = 0;  // Starea de încărcare (0 = oprire, 1 = în curs de încărcare)

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
  int buttonStart = digitalRead(BUTON_INCEPE);
  if (buttonStart == LOW) {
    delay(20);  // Anti-debouncing
    incarcare = 1;  // Se începe încărcarea
    timpUltimaActualizare = millis();  // Resetează timpul pentru controlul bateriei
  }
}

/**
 * Funcția citireButonOpreste verifică dacă butonul de stop este apăsat
 * și oprește procesul de încărcare.
 */
void citireButonOpreste() {
  int buttonStop = digitalRead(BUTON_OPRESTE);
  if (buttonStop == LOW) {
    delay(20);  // Anti-debouncing
    incarcare = 0;  // Se oprește încărcarea
    baterie = 0;  // Resetează nivelul de încărcare
  }
}

/**
 * Funcția actualizeazaLEDuri controlează LED-urile în funcție de starea
 * de încărcare (incarcare).
 * - Aprinde LED-ul verde când se încarcă.
 * - Aprinde LED-ul roșu când nu se încarcă.
 * - Asigură că LED-ul albastru este stins.
 */
void actualizeazaLEDuri() {
  if (incarcare) {
    digitalWrite(GREEN_LED, LOW);  // LED verde stins când se încarcă
    digitalWrite(RED_LED, HIGH);     // LED roșu aprins când se încarcă
    digitalWrite(BLUE_LED, LOW);    // LED albastru stins
  } else {
    digitalWrite(GREEN_LED, LOW);   // LED verde stins când nu se încarcă
    digitalWrite(RED_LED, LOW);    // LED roșu aprins când nu se încarcă
    digitalWrite(BLUE_LED, HIGH);    // LED albastru stins dar pentru ca nu imi merge ledul verdul din rgb am mers pe culoarea albastru
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
  if (incarcare) {
    int timpCurent = millis();  // Obține timpul curent

    // Controlează intervalul de încărcare
    if (timpCurent - timpUltimaActualizare >= INTERVAL) {
      // Dacă a trecut suficient timp (INTERVAL), execută acțiuni
      timpUltimaActualizare = timpCurent;
      baterie++;  // Crește nivelul bateriei
      if (baterie > 4) {
        baterie = 0;
        incarcare = 0;  // Oprește încărcarea când bateria este completă
      }
    }

    // Control LED-uri pentru progresul bateriei
    switch (baterie) {
      case 0:
        digitalWrite(LED_ALBASTRU_1, LOW);
        delay(500);
        digitalWrite(LED_ALBASTRU_1, HIGH);
        delay(500);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, LOW);
        digitalWrite(BLUE_LED, LOW);
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
        break;
    }
  }
}
