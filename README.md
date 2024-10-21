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

## Poze ale setup-ului fizic
![Poza 1 robo](https://github.com/user-attachments/assets/7b8e2189-875d-43c7-83ba-a880810b91f4)
![Poza 2 robo](https://github.com/user-attachments/assets/96b4e494-892d-44e8-81d7-b71011e935e2)
![Poza 3 robo](https://github.com/user-attachments/assets/fb0ecb40-c7fc-4b7b-9523-96b906dc4ac8)

## Video cu funcționalitatea montajului fizic

## Schema electrică (TinkerCAD)
![image](https://github.com/user-attachments/assets/d7585af1-ac0b-4dbe-8792-02024aa77800)
![image](https://github.com/user-attachments/assets/656cfee2-b10f-4a02-98b9-a2d16b7902db)





