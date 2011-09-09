CONTENTS OF THIS FILE
---------------------

* Introduction
* Requirements
* Acknowledgements
* Contact

INTRODUCTION
------------

Have you ever created a node that needed to live under a parent menu item but didn't
want to actually create menu items for each node? Context Magic Menus solves this problem.
It traverses the menu links table and finds the closest menu link to its path and sets it
as active.

But.. aren't there modules that already do this like menu_position and even context? Both
of these solutions require you to specify what menu to activate based on the path. Context
Magic Menus will simply activate the closest parent item derived from the path.

Examples:

Lets say you have the following site structure:

  1. /news (A view listing news articles)
  2. /news/research-resources (A view listing nodes of type research resources)
  3. /news/gene-research (A view listing nodes of type gene-research)
  4. /news/research-resources/new-rna-sequence-descovered - A node of type research resources
  5. /news/research-resources/process-for-rapid-genome-sequencing - A node of type research resources
  6. /news/gene-research/dna/ATL-1 - node of type gene-research
  7. /news/gene-research/sequencing/protocol-121b - node of type gene-research

And have a context called "News" with the condition being:
path: "news*"

And a Main Navigation menu items consiting of items 1 (parent), 2 (child) and 3 (child). Ex:
  /news - News
  /news/research-resources - Research Resources News
  /news/gene-research - Gene Research News

By adding the "Magic Menus" reaction for this condition items 3 and 4 would set item 2 as their
active menu. Items 6 and 7 would set item 3 as their active item. Notice 6 and 7 are 2 levels below
item 3. Magic menus will traverse all the way up the menu path searching for a path.

This module is particularly useful when using Menu Blocks as it will trigger the appropriate menu block
of the activated menu item.

REQUIREMENTS
------------

- Drupal 7
- Context [2] 7.x-3.0-alpha3 or later

Optional:
- Menu Block 2 [1]

CONTACT
-------

Current maintainer:
- Nicholas G. Maloney (ngmaloney@gmail.com) -

