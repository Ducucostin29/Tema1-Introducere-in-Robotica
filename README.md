# Tema1-Introducere-in-Robotica
În această temă simulam o stație de încărcare pentru un vehicul electric, folosind mai multe LED-uri și butoane. În cadrul acestui task trebuie să țin cont de stările butonului și să folosesc debouncing, dar și să coordonez toate componentele ca într-un scenariu din viața reală.

Proiect de Încărcare cu LED-uri - Arduino
Descrierea task-ului / Cerințele
Acest proiect simulează procesul de încărcare a unei baterii utilizând LED-uri conectate la o placă Arduino. LED-urile albastre indică progresul încărcării bateriei, în timp ce un LED RGB arată starea generală a procesului de încărcare:

LED-ul roșu este aprins în timpul procesului de încărcare.
LED-ul verde indică faptul că bateria este complet încărcată.
LED-ul albastru indică faptul că încărcarea nu a început sau este oprită.
Încărcarea începe prin apăsarea unui buton și se oprește fie automat la finalizarea încărcării, fie manual, apăsând un alt buton.

Cerințe:
4 LED-uri albastre pentru a indica progresul încărcării.
LED RGB pentru a indica starea procesului (roșu = încarcă, verde = complet, albastru = inactiv).
Un buton pentru a începe procesul de încărcare.
Un buton pentru a opri manual procesul de încărcare.
Anti-debouncing pentru butoane pentru a evita detectarea falsă a apăsărilor multiple.
Simularea funcționalității în platforme precum Wokwi sau TinkerCAD, dar și pe hardware fizic.
Componente utilizate
Placă Arduino UNO
4 LED-uri albastre
1 LED RGB (cu pini pentru R, G și B)
2 butoane (push-button)
Rezistențe (220Ω pentru LED-uri și 10kΩ pentru butoane)
Breadboard și fire de conexiune
Poze ale setup-ului fizic
(Adăugați aici imagini cu setup-ul fizic al proiectului.)

Link/Video cu funcționalitatea montajului fizic
(Adăugați aici un link către un videoclip în care se vede funcționalitatea proiectului, cum ar fi un video YouTube.)

Schema electrică
Schema electrică a proiectului poate fi realizată și simulată în platforme precum Wokwi sau TinkerCAD. Aceasta include:

Conectarea LED-urilor albastre la pinii 7, 8, 9 și 10.
Conectarea LED-ului RGB la pinii 4, 5 și 6.
Conectarea butonului de start la pinul 3 și a butonului de stop la pinul 2.
Utilizarea rezistențelor pentru protecția LED-urilor și pentru stabilizarea butoanelor.
(Adăugați aici un link către schema electrică realizată în Wokwi sau TinkerCAD.)


