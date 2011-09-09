<?php

/**
 * Displays closest matching menu based on context path.
 */
class context_magic_menus extends context_reaction {
  function options_form($context) {
    $form = array();
    $form[] = array(
      '#markup' => t('By activating the "Magic Menus" reaction it is automatically triggered for this context.')
    );
    $form[] = array('magic_menus' => array('#type' => 'value', '#value' => TRUE));
    return $form;
  }

  function options_form_submit($values) {
    return array('magic_menus' => 1);
  }

  function execute(&$vars) {
    $contexts = context_active_contexts();
    $execute = false;

    // Because magic_menus is set to run per path and not ALL contexts
    // we only need to check if it has been set to execute per request
    foreach($contexts as $active_context) {
      if(!empty($active_context->reactions['context_magic_menus'])) {
        $execute = true;
      }
    }

    if(!$execute) {
      return;
    }

    // We only want to menu_set_item once per path so *I THINK*
    // there is no need to iterate through every context?
    // THANK YOU menu_position module for this section of code!!!

    $path = drupal_get_path_alias();
    $menu_match = FALSE;
    $original_router_item = menu_get_item();
    $menu_link = $this->get_first_menu_link($path);
    if($menu_link) {
      $menu_item = menu_link_load($menu_link);
      $router_item = $original_router_item;
      $router_item['href'] = $menu_item['link_path'];
      $router_item['access'] = TRUE;
      menu_set_item(NULL, $router_item);
    }
  }

  /**
    * Returns the closest menu link item to the path
    * If $path has a menu link association return false so as to not set again.
    * @param $path - Path to search
    * @return $mlid - Menu link id
  */
  private function get_first_menu_link($path) {
    $paths = explode('/',$path);
    $original_paths = $paths;
    while(count($paths) > 0) {
      $link_path = implode('/',$paths);
      $menu_link = db_query('SELECT mlid FROM {menu_links} WHERE link_path = :path', array(':path' => $link_path))->fetchCol();
      if(!empty($menu_link)) {
        //Stop processing if path contains the menu link to prevent conflicts.
        if(count($paths) == count($original_paths)) {
          return false;
        }
        return $menu_link[0];
      }
      array_pop($paths);
    }
    return false;
  }

}

