# EquaC

**EquaC** est un programme en C qui permet de **résoudre un système d'équations linéaires** représenté sous forme de **matrice augmentée** (système d'équations transformé en matrice). Les équations sont chargées depuis un fichier CSV, transformées en une matrice de type `double`, puis le système est résolu en utilisant la méthode du **pivot de Gauss**.

---

## 🔧 Compilation

Pour compiler le programme avec MinGW, utilisez la commande suivante :
```bash
gcc -Iinclude src/*.c -o EquaC
```
- `-Iinclude` : indique à GCC de rechercher les fichiers d'en-tête dans le dossier `include/`
- `src/*.c` : compile tous les fichiers sources du dossier `src/`
- `-o EquaC` : génère un exécutable nommé `EquaC`

---

## 🚀 Utilisation

### 1. Préparation du fichier CSV

Le fichier CSV doit contenir **une ligne par équation**, chaque ligne comportant les coefficients suivis du terme constant, séparés par des virgules. Exemple de fichier `equations.csv` :
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
int SetCsvDataToDoubleMatrix(double ***matrix, int *size, char *file_path);
```

- **matrix** : adresse d'un pointeur vers la matrice (initialement `NULL`)
- **size** : adresse d'un entier qui contiendra le nombre de lignes (équations)
- **file_path** : chemin vers le fichier CSV

Cette fonction parse le CSV, alloue dynamiquement la matrice et remplit les valeurs.

### 3. Résolution du système par pivot de Gauss

Une fois la matrice chargée, résolvez le système en appelant :
```c
GaussPivot(double **matrix, int size);
```
Cette fonction effectue le pivot de Gauss, transformant la matrice augmentée en une forme où la partie gauche devient la matrice identité. Le format final attendu est :
```
1.00  0.00  0.00  |  solution_x  
0.00  1.00  0.00  |  solution_y  
0.00  0.00  1.00  |  solution_z
```
---

## 📏 Limites

- **Taille maximale par ligne du CSV** : 1024 caractères (environ **200 valeurs** maximum, soit 200 équations)
- Pour être sûr de ne pas atteindre la limite du buffer, je conseille de limiter le nombre d'équations à **180**.

---

## 💡 Exemple de Code

Voici un extrait d'utilisation :
```c
#include <stdio.h>
#include <stdlib.h>
#include "equ.h"
#include "parseCSV.h"

int main() {  
 double **matrix = NULL;  
 int size = 0;  

 // Charger les données CSV dans la matrice  
 if (SetCsvDataToDoubleMatrix(&matrix, &size, "equations.csv") != 0) {  
  fprintf(stderr, "Erreur lors de la lecture du fichier CSV\n");  
  return 1;  
 }  

 // Résoudre le système par pivot de Gauss  
 GaussPivot(matrix, size);  

 // La matrice "matrix" est maintenant sous la forme [ I | solutions ]   

 // TODO Libérer la mémoire allouée pour la matrice (code non montré)  

 return 0;  
}
```
---

## 📁 Structure du Projet
```graphql
EquaC
├── include
│   ├── equ.h
│   └── parseCSV.h
├── equations.csv
├── README.md
└── src
│   └── equ.c
│   ├── main.c
│   └── parseCSV.c
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
