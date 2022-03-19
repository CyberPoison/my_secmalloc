# my_secmalloc

### MY_SECMALLOC

### Dans un sous-repertoire nommé my_secmalloc à la racine du dépôt du projet.

### Notions évaluées Xp à gagner

### Rendre un projet 1

### Mise en oeuvre de logiciel sécurisé 19

### Fichier à rendre:

#### .

```
├── include
│ └── my_secmalloc.h
├── Makefile
├── src
│ └── *vos_fichiers*
└── test
└── *vos_test*
```
```
3 directories, 4 files
```
### Fichier fournit dans provided_files.zip :

#### .

```
├── my_secmalloc.h
└── sample
├── heap_overflow_from_file
├── heap_overflow_from_file.cc
├── Makefile
├── README.md
├── save1.db
├── save2.db
└── xploit_heap_overflow_from_file.py
```
```
1 directory, 8 files
```
# Sujet:

### Il s’agit de ré-écrire les fonctions suivantes:

```
#ifndef _SECMALLOC_H
#define _SECMALLOC_H
```
```
#include <stdlib.h>
```
```
void *my_malloc (size_t size );
void my_free (void *ptr );
void *my_calloc (size_t nmemb , size_t size );
void *my_realloc (void *ptr , size_t size );
```
```
#endif
```

### MY_SECMALLOC

### Le comportement sera similaire aux fonctions équivalentes décrites dans man 3 malloc.

### L’utilisation du malloc de la bibliothèque standard C, ainsi que les autres fonctions décrites

### dans le man malloc sont interdites. Vous aurez à utiliser mmap et munmap.

## 1 - Niveau de rendu¶

## Niveau 0 - Préliminaires¶

### Votre rendu contiendra un Makefile pour fabriquer les différentes parties du projet.

### Votre code devra respecter au maximum les consignes de l’université du michigan C

### Coding Standards concernant l’écriture du code C. De plus, l’usage d’une langue

### différente de l’anglais pour les identifiants est proscrite.

### Votre code devra respecter le principe de Test Driven Developpement, et ainsi contenir

### un répertoire de test, une directive de Makefile nommé ‘test’.

### L’utilisation d’un framework de test comme Ceedling ou criterion est fortement

### encouragé.

### La commande make test devra exécuter l’intégralité de vos test. Le nom des tests et

### l’affichage de ceux-ci devra être explicite sur la fonctionnalité testée.

### Vos tests doivent servir de preuve de l’implémentation des différentes fonctionnalités

### demandées dans le présent document.

## Niveau 1 - Bibliothèque statique¶

### Votre Makefile doit permettre de compiler un bibliothèque statique nommé

### libmy_secmalloc.a par la commande make static.

### Cette bibliothèque n’exportera comme symbole publique que ceux listé dans le header

### fournis.

```
$ nm libmy_secmalloc.a | grep " T " | cut -f3 -d' ' | sort
my_calloc
my_free
my_malloc
my_realloc
```
## Niveau 2 - Bibliothèque dynamique¶

### Votre Makefile doit permettre de compiler une bibliothèque dynamique nommé

### libmy_secmalloc.so par la commande make dynamic.

### Cette bibliothèque n’exportera comme symbole publique que ceux listé ici:

```
$ nm libmy_secmalloc.so | grep " T " | cut -f3 -d' ' | sort
calloc
free
```

### MY_SECMALLOC

```
malloc
my_calloc
my_free
my_malloc
my_realloc
realloc
```
### En utilisant les mécanismes de LD_PRELOAD, il vous sera possible de forcer

### l’utilisation de vos fonctions d’allocations mémoires pour n’importe quel programme.

### tel que:

```
$ ls
test
$ ls ~/my_secmalloc/libmy_secmalloc.so
libmy_secmalloc.so
$ LD_PRELOAD=~/my_secmalloc/libmy_secmalloc.so ls
test
$
```
## 2 - Objectif¶

### L’objectif de ce projet est de parfaire votre compréhension des domaines suivants:

### Système d’exploitation Linux,

### Mécanisme de gestion mémoire,

### Compréhension des “heap overflows”.

### Toutefois, il ne s’agit pas ici d’avoir un projet axés sur la performance mais sur la sécurité,

### ainsi l’emphase ne sera ni sur l’optimisation de la consommation de l’espace mémoire, ni sur

### le temps d’exécution des fonctions d’allocation/déallocation mais sur les informations

### obtenues pendant l’exécution d’un programme.

## 2.1 - Fonctionnalités de votre projet¶

## Rapport d’exécution du programme¶

### La présence de la variable d’environnement MSM_OUPUT provoquera la génération d’un

### rapport d’exécution dans le fichier décrit par la valeur de cette variable. Le format du rapport

### d’exécution est libre.

### Il devra toutefois permettre de tracer à minima:

### Type de fonction appelé (malloc, free, ...)

### Taille des blocs demandés

### Adresse obtenu (a des fins d’identification)

## Détection de malveillance¶


### MY_SECMALLOC

### L’emphase du projet est mis sur votre capacité à détecter les erreurs de manipulation de la

### mémoire et à les écrire dans le rapport d’exécution:

### Heap overflow

### Double free

### Et si vous êtes capables de détecter la fin de l’exécution d’un programme:

### Memory leak

## Autres fonctionnalités¶

### Vous êtes libre de proposer des fonctionnalités supplémentaires en rapport avec la sécurité

### des programmes tant que le cadre présenté ici est respecté.

## 2.2 - Soutenance¶

### Le projet sera évalués lors d’une soutenance.

### La soutenance se passera sur votre machine (passez en QWERTY svp).

### Une revue de code sera réalisé et vous serez évalué sur la qualité de votre code aussi

### bien esthétique que fonctionnel. La sécurité d’un code est corollaire de sa

### maintenabilité.

### Le niveau de rendu et la richesse des fonctionnalités proposés sont les critères

### principaux de votre évaluation.

### Vous pourrez être soumis à une session de recode. Une sous-fonction de votre rendu est

### effacée et vous devez la recodée pendant la soutenance.


