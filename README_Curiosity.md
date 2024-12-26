
# Projet Curiosity

## Description

Le projet **Curiosity** consiste en un programme en C permettant de contrôler un robot dans un environnement défini par un fichier terrain. Le robot peut avancer, tourner, interagir avec le terrain et exécuter des programmes préalablement définis. Ce projet a également pour but de tester la performance et la robustesse de différents scénarios d'exécution.

## Fonctionnalités principales

- **Lecture de fichiers terrain** : Chargement d'un environnement défini par des fichiers terrain.
- **Contrôle du robot** : Initialisation, déplacement (avance, tourne) et interaction avec l'environnement.
- **Exécution de programmes robot** : Lecture et exécution de commandes définies dans des fichiers programme.
- **Tests automatisés** : Fichiers permettant d'évaluer la performance et les résultats du robot dans des scénarios variés.
- **Gestion des erreurs** : Détection et affichage des erreurs liées aux fichiers terrains et programmes.

## Organisation des fichiers

### Répertoire principal
- **curiosity.c** : Programme principal pour exécuter les scénarios standards.
- **curiosity_perf.c** : Programme pour tester les performances sur plusieurs terrains et configurations.
- **curiosity-test.c** : Programme pour effectuer des tests unitaires et valider les résultats du robot.

### Fichiers de configuration et tests
- **Fichiers terrains** : Fichiers définissant les environnements (obstacles, cases libres, etc.).
- **Fichiers programmes** : Programmes contenant les commandes que le robot doit exécuter.
- **Makefile** : Automatisation de la compilation et de la gestion des dépendances.

### Autres fichiers importants
- **environnement.c/h** : Gestion des environnements (lecture des terrains, état du robot).
- **programme.c/h** : Gestion des commandes et de la pile d'exécution.
- **robot.c/h** : Implémentation des fonctionnalités du robot (déplacement, orientation).
- **generation_terrains.c/h** : Génération aléatoire de terrains avec des obstacles.
- **interprete.c/h** : Exécution des commandes du programme robot.

## Compilation et exécution

### Prérequis
- **Compilateur C** : Par défaut, le projet utilise `clang` (configurable dans le Makefile).
- **Système Unix/Linux** : Nécessaire pour les scripts d'automatisation et les tests.

### Commandes principales
1. **Compilation** :
   ```bash
   make
   ```
   Cette commande génère tous les programmes nécessaires (tests, performance, exécution standard).

2. **Exécution d'un programme standard** :
   ```bash
   ./curiosity <terrain_file> <programme_file>
   ```
   Exemple :
   ```bash
   ./curiosity terrain.txt programme.txt
   ```

3. **Tests de performance** :
   ```bash
   ./curiosity_perf <programme> <N> <largeur> <hauteur> <densité> <graine> <pas_max> <fichier_resultats>
   ```

4. **Tests unitaires** :
   ```bash
   ./curiosity-test test_config.txt
   ```

### Nettoyage
Pour supprimer les fichiers compilés :
```bash
make clean
```

## Exemples d'utilisation

1. **Déplacement simple du robot** :
   - Terrain : Une grille vide de 5x5.
   - Programme : Le robot avance deux fois et tourne à gauche.

2. **Simulation de terrains générés aléatoirement** :
   - Le fichier `curiosity_perf.c` permet de générer des terrains aléatoires et d'évaluer les performances du robot.

## Résultats attendus

- **Succès** : Le robot atteint la sortie ou termine son programme sur une case valide.
- **Erreurs détectées** : Le robot tombe dans l'eau, s'écrase sur un obstacle ou rencontre une commande incorrecte.

