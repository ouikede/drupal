Description
----------------------------------------------------------------------------------------------------------
This module adds views show options to your Drupal site for consuming restful json and xml.
The restful source can be json or xml source that responses to a http get.

Requirements
---------------------------------------------------------------------------------------------------------
Drupal 7.x
Views  3.x

 
Installation
----------------------------------------------------------------------------------------------------------
1. Copy the entire views_resful_client directory to the Drupal sites/all/modules directory. 

2. Login as an administrator. Enable the views_resful_client module in the "Administer" -> "Modules" 

3. Add a restful source configuration under "Administer" -> "Configuration" ->  "SEARCH AND METADATA" -> "Restful Client Settings" -> "Create and configure restful clients" 

4. Enter the restful source connection information and the data mappings

5. Add a view to display your information  under  "Administer" -> "Structure" -> "Views"  -> "Add new View"

6. In the Show field options select the name of your restful source