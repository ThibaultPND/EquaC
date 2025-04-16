# EquaC

**EquaC** est un programme en C qui permet de **résoudre un système d'équations linéaires** représenté sous forme de **matrice augmentée** (système d'équations transformé en matrice). Les équations sont chargées depuis un fichier CSV, transformées en une matrice de type `double`, puis le système est résolu en utilisant la méthode de **Gauss-Jordan**.

---

## 🔧 Compilation

Pour compiler le programme avec MinGW, utilisez la commande suivante :
```bash
gcc -Iinclude src/*.c -o EquaC.exe
```
- `-Iinclude` : indique à GCC de rechercher les fichiers d'en-tête dans le dossier `include/`
- `src/*.c` : compile tous les fichiers sources du dossier `src/`
- `-o EquaC.exe` : génère un exécutable nommé `EquaC.exe`

---

## 🚀 Utilisation

### 1. Préparation du fichier CSV

Le fichier CSV doit contenir **une ligne par équation**, chaque ligne comportant les coefficients suivis du terme constant, séparés par des virgules. Exemple de fichier `matrix.csv` :
```csv
1,1.02,1,6  
2,3,1,14  
1,2,3,14
```
Ce fichier représente le système :
- `1x + 1.02y + 1z = 6`
- `2x + 3y   + 1z = 14`
- `1x + 2y   + 3z = 14`

### 2. Extraction des données dans une matrice

Utilisez la fonction suivante pour charger les données du CSV dans une matrice dynamique :
```c
int loadMatrixFromCSV(Matrix *matrix, char *file_path);
```

- **matrix** : adresse vers la matrice (initialement matrix.matrix = `NULL`)
- **file_path** : chemin vers le fichier CSV

Cette fonction parse le CSV, alloue dynamiquement la matrice et remplit les valeurs.

### 3. Résolution du système par pivot de Gauss

Une fois la matrice chargée, résolvez le système en appelant :
```c
gaussJordanAlgorithm(Matrix *matrix);
```
Cette fonction effectue le pivot de Gauss, transformant la matrice augmentée en une forme où la partie gauche devient la matrice identité. Le format final attendu est :
```
1.00  0.00  0.00  |  solution_x  
0.00  1.00  0.00  |  solution_y  
0.00  0.00  1.00  |  solution_z
```
---

## 📏 Limites

- **Taille maximale par ligne du CSV** : 1024 caractères (environ **200 valeurs** maximum, soit 170 équations)
- Pour être sûr de ne pas atteindre la limite du buffer, je conseille de limiter le nombre d'équations à **150**.

---

## 💡 Exemple de Code

Voici un extrait d'utilisation :
```c
#include <stdio.h>
#include <stdlib.h>

#include "algebra.h"
#include "io.h"
#include "matrix.h"
#include "types.h"

int main(int argc, char *argv[]) {
    // Exemple de code
    Matrix_t matrix;

    loadMatrixFromCSV(&matrix, "matrix.csv");
    
    // Matrice sous forme de matrice augmentée. Modélisant un système d'équations.

    gaussJordanAlgorithm(&matrix);

    // Matrix sous forme identité avec les resultats à droite.

    // Memory free (very important ofc)
    FreeMatrix(&matrix);

    return 0;
}
```
---

## 📁 Structure du Projet
```graphql
EquaC
├── matrix.csv
├── README.md
├── include
│   ├── algebra.h
│   ├── io.h
│   ├── matrix.h
│   └── types.h
└── src
│   └── algebra.c
│   ├── io.c
│   ├── main.c
│   └── matrix.c
```
---

## 🛠️ À Faire / Améliorations Futures

- Gérer les cas de systèmes incompatibles ou indéterminés (sans solution unique).  
- Améliorer le parseur CSV pour plus de robustesse et pour gérer des délimiteurs alternatifs. 

---

## 👤 Auteur

**Thibaultpnd**  
[GitHub: Thibaultpnd](https://github.com/Thibaultpnd)

---

N'hésitez pas à signaler des problèmes ou à proposer des améliorations via GitHub Issues !
