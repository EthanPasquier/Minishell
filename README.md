# Minishell
The current repo contains a README in French, but an English version is available on the original repo, located on my teammate's GitHub account: https://github.com/Jalevesq/minishell.

## Introduction
Le projet Minishell de l'école 42 consiste en la création d'un programme de shell simplifié en langage C. L'objectif de ce projet est de comprendre le fonctionnement d'un shell et de mettre en pratique les connaissances en manipulation de processus et en gestion de fichiers (fd).
## Répartition des tâches
- Parsing : réalisé par [Epasquie](https://github.com/EthanPasquier)
- Exécuteur & Builtins: réalisé par [Jalevesq](https://github.com/Jalevesq)
## Fonctionnalités
- Lecture des commandes de l'utilisateur. (Main)
- Gestion des erreurs de saisie d'utilisateur. (Parsing)
- Lancement des exécutables (en utilisant les chemins relatifs et absolus ainsi que la variable d'environnement PATH). (Exécuteur)
- Gestion de l'historique des commandes. (Main)
- Gestion des variables d'environnement (substitution de la variable d'environnement $ par sa valeur). (Parsing)
- Implémentation des builtins (Exécuteur) :
  - echo avec l'option -n.
  - cd uniquement avec un chemin relatif ou absolu.
  - pwd sans aucune option.
  - export sans aucune option.
  - unset sans aucune option.
  - env sans aucune option ni argument.
  - exit sans aucune option.
- Gestion des redirections (<, >, >>, <<). (Exécuteur)
- Gestion des pipes (|). (Exécuteur)
- Gestion des signaux (ctrl-C, ctrl-D, ctrl-\\). (Main)
- Support des single quotes (') qui empêchent l'interprétation des méta-caractères dans la séquence entre guillemets. (Parsing)
- Support des double quotes (") qui empêchent l'interprétation des méta-caractères dans la séquence entre guillemets sauf pour le signe dollar $. (Parsing)
- Support de la substitution de $? par le statut de sortie de la dernière commande exécutée au premier plan. (Parsing)
## Utilisation
1. Cloner le dépôt :
   ```
   git clone https://github.com/EthanPasquier/minishell.git
   ```
2. Compiler le programme (le Makefile télécharge automatiquement la librairie Readline nécessaire pour le bon fonctionnement du programme) :
   ```
   make
   ```
   *Note : Veuillez noter que le téléchargement et la compilation de la librairie Readline peuvent prendre un certain temps, en fonction de votre connexion internet et des performances de votre ordinateur. Si vous rencontrez des problèmes lors du téléchargement ou de la compilation, vous pouvez réessayer en exécutant à nouveau la commande make ou make re.

   <img width="328" alt="Screen Shot 2023-04-27 at 10 52 15 AM" src="https://user-images.githubusercontent.com/114168621/234901152-61c95411-dca4-450a-ab9f-57d0561c6970.png">
3. Lancer le shell :
   ```
   ./minishell
   ```
   <img width="521" alt="Screen Shot 2023-04-27 at 9 49 12 AM" src="https://user-images.githubusercontent.com/114168621/234900101-f6df125b-47be-466b-9cd4-ff4ffff4f187.png">
4. Utiliser le shell en tapant des commandes standard ou en utilisant les fonctionnalités spécifiques.

### Fonctionnement
Le programme se décompose en plusieurs fichiers source :
```
.
├── include
├── libft
├── srcs
│   ├── built
│   ├── exec
│   ├── main
│   ├── parsing
│   └── tools
└── Makefile
```

# MiniShell - Parsing

Dans ce fichier README, nous expliquerons la partie Parsing du projet MiniShell de l'école 42.

## Fonctionnement du Parsing

1. Le parsing commence avec la fonction `ft_parser`, qui prend en paramètre un `char *str` correspondant à la commande de l'utilisateur.

2. On vérifie que la commande ne commence ni ne finit par des caractères indésirables ou impossibles.

3. La fonction `ft_write_cut` place des caractères 29 (caractères invisibles et itérables) pour pouvoir ensuite diviser les caractères et les mettre dans une liste chaînée. Cela permet de vérifier chaque commande une par une.
      * Exemple : `ls -lah | wc > test` deviendra `ls -lah29|29 wc 29>29 test`.
   
4. Une liste chaînée nommée `token` est créée et assignera chaque type à un numéro à la fin du parsing pour faciliter l'exécution.

5. La fonction `ft_parser_suite` (suite de `ft_parser`) est utilisée, car la norme de l'école 42 est stricte et exige moins de 25 lignes par fonction.

6. Dans cette fonction, une boucle vérifie chaque nœud de la liste chaînée. On vérifie si le nombre de guillemets (`"` et `'`) est pair et s'ils sont dans un ordre possible.
      * Exemple : `echo "'salut"'` ne fonctionne pas, mais `echo "'salut'"` fonctionne.
   
7. Si les conditions ne sont pas remplies, un message d'erreur est affiché et un code d'erreur est renvoyé pour le `$?`.

8. La fonction `ft_guillemet` supprime tous les guillemets qui ne doivent pas être affichés dans le shell. Elle gère également l'affichage des variables d'environnement si nécessaire, comme `echo "$USER"` qui devient `echo "epasquie"`.

9. L'option `-n` de `echo` est traitée pour transformer l'entrée (par exemple, `echo -nnn -nnnn -n test` en `echo -n test`).

10. On vérifie si l'export a été bien formaté s'il y en a un.

11. Dans `ft_setup_node`, on s'occupe de la syntaxe `| >`. Dans `ft_write_cut`, elle est notée `| >`, mais pour l'exécution, il faut la formater de manière à ce que `|` reste dans le nœud actuel et `>` soit décalé dans un nouveau nœud, décalant ainsi tous les nœuds après le `|`.

12. Après avoir effectué toutes les vérifications et modifications dans le parsing, on est presque sûr que la syntaxe de la commande est correcte. On peut assigner chaque type à son nombre grâce à la fonction `ft_assign_type`.

13. On envoie notre liste chaînée avec nos commandes et la liste chaînée des types dans l'exécuteur qui s'occupera du reste.

## Conclusion
Minishell est un projet intéressant pour se familiariser avec la programmation en C et la manipulation de processus. Il est également utile pour comprendre le fonctionnement d'un shell et les fonctionnalités de base telles que l'environnement système, les redirections et les pipes.
