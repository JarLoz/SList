Kurssiprojekti

C++ Ohjelmointitekniikka


Kurssiprojektin tehtävänä oli luoda yhteen suuntaan linkitetty lista, joka säilöö string-arvoja ja
käyttäytyy STL-containerin tavoin. Ratkaisuni listalle on hyvin yksinkertainen: listan
funktionaalisuuden toteuttaa luokka SList, joka käyttää tietorakenteenaan linkitettyjä
SListNode-olioita. STL-tyyppiset iteraattorit on toteutettu sisäluokan avulla. Luokkien
määrittelyt on kirjoitettu SList.h-tiedostoon, ja toteutus SList.cpp-tiedostoon. SList ylläpitää
pointtereita sekä listan alkuun, että loppuun, ja näiden avulla tarjoaa siltä vaaditun
toiminnallisuuden. Funktioiden aikavaatimus on koetettu pitää järkevässä luokassa, mutta
eritoten toteutuksissa on keskitytty oikeellisuuden ylläpitämiseen. Luokalla on speksin
määrittelemä check()-funktio, mutta ilman dramaattisia muutoksia, luokan invariantti säilyy
kaikkien operaatioiden kohdalla.


Luokan testaus on suoritettu main.cpp-tiedostossa toteutetussa testDriver()-funktiossa.
testDriver() ajaa läpi kattavan joukon testejä, ja ylläpitää numeroa tavatuista virheistä.
testDriver() dokumentoi itse tekemisiään raportoimalla stdouttiin, mutta eri testit on myös
eroteltu lähdekoodissa kommentoinnilla.


Luokan toteuttaminen oli yllättävän yksinkertainen projekti, enkä törmännyt odottamattomiin
esteisiin, kunhan sain langan päästä kiinni. Koskapa tehtävä oli kovin suoraviivainen, en keksi
hirveästi enempää kommentoitavaa; koodi puhuu puolestaan ja testit toimivat.


Kimmo Heikkinen
13.12.2010

