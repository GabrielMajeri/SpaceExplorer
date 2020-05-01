# Space Explorer
Program educativ care permite utilizatorului să exploreze o regiune a spațiului.

Programul vine inclus cu un model al Sistemului Solar și câteva stele apropiate.
Distanțele sunt la scară. Dimensiunile stelelor / planetelor nu sunt la scară (ar fi prea mici).

Se pot schimba setările în fișierul "Optiuni.txt", și se pot adăuga noi hărți foarte ușor.

### Control
Nava spațială se deplasează cu W/A/S/D (poate fi schimbat in setări).
Tastele + si - dau Zoom In, respectiv Zoom Out (pot fi schimbate in setări).
ESCAPE de 2 ori iese din program.

### Cerințe de sistem
* **Sistem de operare**: Windows / Mac / Linux
* **Procesor**: Pentium 4 sau mai nou, sau Athlon 64
* **Placa video**: suport pentru [OpenGL](https://www.opengl.org/) 2.0 sau mai nou
* **Monitor**: rezolutie 800x600 sau mai mare
* **Tastatură**: să aiba tastele W/A/S/D, Escape, Enter
* **RAM**: peste 512 MB
* **Spatiu de stocare**: cel puțin 50 MB spațiu liber

### Tehnologii folosite
* [GNU G++](https://gcc.gnu.org/)
* [SFML](https://www.sfml-dev.org/)

### Compilare
Pentru a compila și rula jocul, executați următoarele comenzi:
```sh
meson . build
ninja -C build
./build/SpaceExplorer
```

### Licență
[GNU General Public License V3](http://www.gnu.org/licenses/gpl-3.0.html)

### Resurse utilizate (imagini, documentație)
* NASA
* wikipedia.org
* Muzică: incompetech.com
