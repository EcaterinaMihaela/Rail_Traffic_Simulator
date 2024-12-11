Proiect POO-laborator
CĂPĂȚÎNĂ ECATERINA-MIHAELA
CR 2.1A
TEMA NR. 75
Simulare a transportului feroviar-gestionarea trenurilor și a stațiilor

Realizați o aplicație C++ care să simuleze transportul feroviar, gestionând trenurile și stațiile pe un traseu prestabilit. Aplicația trebuie să permită urmărirea trenurilor în timp real, gestionarea orarelor, planificarea rutelor între stații, precum și evidența pasagerilor. Fiecare tren va avea caracteristici precum tipul, capacitatea și viteza maximă, iar stațiile vor gestiona sosirea și plecarea trenurilor. De asemenea, aplicația trebuie să permită vânzarea de bilete, inclusiv opțiuni de reducere pentru studenți, și să simuleze eventualele incidente care pot afecta circulația trenurilor. Programarea va fi modulară, utilizând clase și obiecte(clase precum :tren,vagon,statie,bilet cu atributele specifice), iar codul va fi împărțit în fișiere header și fișiere de implementare.
Aplicația trebuie să implementeze următoarele funcționalități utilizând concepte de programare orientată pe obiecte (OOP), prin intermediul claselor și obiectelor aferente:
Cerințe:
Creează o clasă pentru trenuri care să gestioneze următoarele atribute:
1.	Gestionarea trenurilor:
•	Număr tren(identificator unic);
•	Tip tren(personal,rapid,etc);
•	Ruta trenului;
•	Starea trenului(în mișcare,nefuncțional,în întârziere,scos din circulație,în reparație,etc);
•	Serviciile trenului:Tipuri de clase(Clasa I,Clasa a II-a,cu sau fără cușetă,număr paturi);
•	Număr de vagoane;
•	Timp stationare statie;
•	Data și ora plecării;
•	Data și ora ajungerii la destinație;
•	Numărul de km parcurși până la destinație;
•	Timp estimat pentru ajungerea la destinație;
•	Ordinea vagoanelor;
2.	Gestionarea vagoanelor:
Creează o clasă pentru vagoane cu următoarele atribute:
•	Numărul vagonului(id);
•	Clasa(Clasa I,Clasa a II-a);
•	Direcția;
•	Număr de locuri;
•	Număr de locuri rezervate respective libere;
3.	Gestionarea stațiilor:
Creează o clasă pentru stații cu următoarele atribute:
•	Nume stație;
•	Număr de linii disponibile;
•	Linia la care trage un anumit tren;
•	Sosiri trenuri;
•	Trenuri prezente în stație;
4.	Atribute bilet:
Creează o clasă pentru bilete cu următoarele atribute :
•	ID;
•	Preț: Se va calcula pretul pentru fiecare ruta/ruta intermediara dupa numarul de km;
•	Tip Bilet(ex. Bilet standard/Dus-întors); 
•	Data Cumpărării;
•	Stare bilet(plătită, în așteptare în cazul biletelor online);
•	Ruta;
•	Numele trenului;
•	Data & ora plecării/ajungerii la destinație;
•	Tipul locului:clasa,numărul locului pe scaun sau fară loc pe scaun in cazul tipului de tren REGIO;
•	Tip Bilet(cu reducere pt student/pensionari/elevi sau întreg);


Specificații suplimentare:
•	Meniu interactiv:
o	Aplicația trebuie să includă un meniu interactiv care să permită utilizatorilor să acceseze diferitele funcționalități ale sistemului, precum:
	Vizualizarea informațiilor despre trenuri;
	Rezervarea și achiziționarea biletelor de tren;
	Afișarea informațiilor despre stații și trenurile disponibile;
	Vizualizarea trenurilor pentru ruta aleasa;
•	Aplicația trebuie să poată simula scenarii reale de funcționare: rezervarea unui bilet, verificarea stării unui tren si afișarea stațiilor disponibile.

