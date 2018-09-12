This module adds a new realm that allows you to select the facets in a search api and display the select options as one form with one submit button.  It is recommended to be used with [Chosen](https://www.drupal.org/project/chosen) or another multi-select UI.

Installation & Config
1. Install like any other module.
2. Go to your facets section for your search index. *admin/config/search/search_api/index/\[YOUR_INDEX_NAME]\/facets*
3. You should see a new realm named Combo Facets listed as a local task.
4. Select the Combo Facets task.
5. Select all the facets you wish to display.
6. Configure each facet to use the Select (CBF Field) and set a title for the field item.
7. Go to your blocks page and configure your Combo Facet block.
8. Add to the correct page using the standard Blocks UI or Context.
9. Go to the configuration page /admin/config/search/cfb to sort the enabled facets.
10. Enjoy.

I recommend shutting off other facets that are not using the Select (CBF Field) widget if possible and all other facets in other realms, as I attempted to account for them, but they kind of defeat the purpose of this module if used.