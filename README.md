# minishell
Readme pour la partie parsing de l'exercice MiniShell de l'école 42
La partie parsing de ce projet a pour but de comprendre la commande entrée par l'utilisateur et de la préparer pour son exécution. Pour ce faire, plusieurs fonctions sont utilisées :

## ft_parser
Cette fonction prend en entrée une chaîne de caractères représentant la commande entrée par l'utilisateur. Elle effectue les étapes suivantes :

1. Vérification de la validité de la commande : Elle vérifie que la commande ne commence ni ne se termine par des caractères indésirables ou impossibles, tels que des espaces ou des tabulations. Si ces conditions ne sont pas remplies, un message d'erreur est affiché et un code d'erreur est retourné pour le `$?`.

2. Séparation des éléments de la commande : Elle utilise la fonction `ft_write_cut` pour séparer les différents éléments de la commande en utilisant un caractère invisible et itérable. Cela permet de vérifier chaque élément de la commande séparément pour une analyse ultérieure.

## ft_write_cut
Cette fonction sert à séparer les différents éléments de la commande en utilisant un caractère invisible et itérable. Elle parcourt la commande entrée et place un caractère séparateur invisible entre chaque élément pour faciliter la vérification ultérieure de la syntaxe.

## ft_parser_suite
Cette fonction effectue les étapes suivantes :

1. Vérification de la syntaxe des guillemets : Elle examine chaque élément de la commande pour s'assurer que le nombre de guillemets (`"` et `'`) est pair et qu'ils sont dans un ordre possible. Si ces conditions ne sont pas remplies, un message d'erreur est affiché et un code d'erreur est retourné pour le `$?`.

2. Suppression des guillemets inutiles : Elle utilise la fonction `ft_guillemet` pour supprimer les guillemets inutiles et afficher les variables d'environnement si nécessaire.

3. Vérification de l'option `-n` de la commande `echo` : Elle vérifie si l'option `-n` est présente dans la commande `echo` et la traite en conséquence.

## ft_guillemet
Cette fonction supprime les guillemets inutiles et affiche les variables d'environnement si nécessaire. Elle parcourt la commande entrée et supprime les guillemets qui ne doivent pas être affichés dans le shell. Elle remplace également les références
