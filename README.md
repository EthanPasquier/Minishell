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

