api = 2
core = 7.x

; WxT
projects[wetkit][type] = "core"
projects[wetkit][download][type] = "get"
projects[wetkit][download][url] = "http://ftp.drupal.org/files/projects/wetkit-7.x-4.0-rc1-core.tar.gz"

; Example for git
;projects[][version] = 1.x-dev
;projects[][subdir] = contrib
;projects[][type] = "module"
;projects[][download][type] = git
;projects[][download][revision] = ae778f2
;projects[][download][branch] = 7.x-1.x
;projects[][download][url] = "http://git.drupal.org/sandbox/joel_osc/2163409.git"

; Example for download
;projects[][version] = 3.0
;projects[][subdir] = contrib
;projects[][type] = "module"
;projects[][download][type] = "get"
;projects[][download][url] = "http://ftp.drupal.org/files/projects/backup_migrate-7.x-3.0.tar.gz"
;projects[][patch][] = 

; Theme Example
;projects[][version] = 1.0
;projects[][type] = themes
;projects[][download][type] = git
;projects[][download][branch] = 7.x-1.x
;projects[][download][url] = "git@govwbgp01.peigov:pei_bootstrap"

; PEI Theme

projects[pei_bootstrap][version] = 1.0
projects[pei_bootstrap][type] = theme
projects[pei_bootstrap][download][type] = git
projects[pei_bootstrap][download][branch] = 7.x-1.x
projects[pei_bootstrap][download][url] = "git@git.openplus.ca:PEI/pei_bootstrap.git"

; To be used later for GPEI's git
;projects[pei_bootstrap][version] = 1.0
;projects[pei_bootstrap][type] = theme
;projects[pei_bootstrap][download][type] = git
;projects[pei_bootstrap][download][branch] = 7.x-1.x
;projects[pei_bootstrap][download][url] = "git@govwbgp01.peigov:pei_bootstrap"

; PEI Custom modules, Features, and wetkit patches

projects[custom][version] = 1.0
projects[custom][type] = module
projects[custom][download][type] = git
projects[custom][download][branch] = 7.x-1.x
projects[custom][download][url] = "git@git.openplus.ca:PEI/custom.git"

; To be used later for GPEI's git
;projects[custom][version] = 1.0
;projects[custom][type] = module
;projects[custom][download][type] = git
;projects[custom][download][branch] = 7.x-1.x
;projects[custom][download][url] = "git@govwbgp01.peigov:custom"

projects[features][version] = 1.0
projects[features][type] = module
projects[features][download][type] = git
projects[features][download][branch] = 7.x-1.x
projects[features][download][url] = "git@git.openplus.ca:PEI/features.git"

; To be used later for GPEI's git
;projects[features][version] = 1.0
;projects[features][type] = module
;projects[features][download][type] = git
;projects[features][download][branch] = 7.x-1.x
;projects[features][download][url] = "git@govwbgp01.peigov:features"

projects[wetkit_patches][version] = 1.0
projects[wetkit_patches][type] = module
projects[wetkit_patches][download][type] = git
projects[wetkit_patches][download][branch] = 7.x-1.x
projects[wetkit_patches][download][url] = "git@git.openplus.ca:PEI/wetkit_patches.git"

; To be used later for GPEI's git
;projects[wetkit_patches][version] = 1.0
;projects[wetkit_patches][type] = module
;projects[wetkit_patches][download][type] = git
;projects[wetkit_patches][download][branch] = 7.x-1.x
;projects[wetkit_patches][download][url] = "git@govwbgp01.peigov:wetkit_patches"

; Example for features
;projects[][version] = 1.0
;projects[][subdir] = features
;projects[][type] = module
;projects[][download][type] = git
;projects[][download][branch] = 7.x-1.x
;projects[][download][url] = "git@govwbgp01.peigov:"

; Contrib Modules from drupal.org

projects[addressfield][version] = 1.0-beta5
projects[addressfield][subdir] = contrib
projects[addressfield][type] = "module"
projects[addressfield][download][type] = "get"
projects[addressfield][download][url] = "http://ftp.drupal.org/files/projects/addressfield-7.x-1.0-beta5.tar.gz"

projects[backup_migrate][version] = 3.0
projects[backup_migrate][subdir] = contrib
projects[backup_migrate][type] = "module"
projects[backup_migrate][download][type] = "get"
projects[backup_migrate][download][url] = "http://ftp.drupal.org/files/projects/backup_migrate-7.x-3.0.tar.gz"

projects[better_exposed_filters][version] = 3.0
projects[better_exposed_filters][subdir] = contrib
projects[better_exposed_filters][type] = "module"
projects[better_exposed_filters][download][type] = "get"
projects[better_exposed_filters][download][url] = "http://ftp.drupal.org/files/projects/better_exposed_filters-7.x-3.0.tar.gz"

projects[boolean_formatter][version] = 1.3
projects[boolean_formatter][subdir] = contrib
projects[boolean_formatter][type] = "module"
projects[boolean_formatter][download][type] = "get"
projects[boolean_formatter][download][url] = "http://ftp.drupal.org/files/projects/boolean_formatter-7.x-1.3.tar.gz"

projects[calendar][version] = 3.5
projects[calendar][subdir] = contrib
projects[calendar][type] = "module"
projects[calendar][download][type] = "get"
projects[calendar][download][url] = "http://ftp.drupal.org/files/projects/calendar-7.x-3.5.tar.gz"

projects[computed_field][version] = 1.0
projects[computed_field][subdir] = contrib
projects[computed_field][type] = "module"
projects[computed_field][download][type] = "get"
projects[computed_field][download][url] = "http://ftp.drupal.org/files/projects/computed_field-7.x-1.0.tar.gz"

projects[conditional_fields][version] = 3.0-alpha1
projects[conditional_fields][subdir] = contrib
projects[conditional_fields][type] = "module"
projects[conditional_fields][download][type] = "get"
projects[conditional_fields][download][url] = "http://ftp.drupal.org/files/projects/conditional_fields-7.x-3.0-alpha1.tar.gz"

projects[conditional_styles][version] = 2.2
projects[conditional_styles][subdir] = contrib
projects[conditional_styles][type] = "module"
projects[conditional_styles][download][type] = "get"
projects[conditional_styles][download][url] = "http://ftp.drupal.org/files/projects/conditional_styles-7.x-2.2.tar.gz"

projects[ctools_facet_query_context][version] = 1.x-dev
projects[ctools_facet_query_context][subdir] = contrib
projects[ctools_facet_query_context][type] = "module"
projects[ctools_facet_query_context][download][type] = git
projects[ctools_facet_query_context][download][revision] = c9a557c
projects[ctools_facet_query_context][download][branch] = master
projects[ctools_facet_query_context][download][url] = "http://git.drupal.org/sandbox/joel_osc/2163409.git"

projects[custom_search_api_widget][version] = 1.x-dev
projects[custom_search_api_widget][subdir] = contrib
projects[custom_search_api_widget][type] = "module"
projects[custom_search_api_widget][download][type] = git
;projects[custom_search_api_widget][download][revision] = 0a1ad87
projects[custom_search_api_widget][download][revision] = bf240df
projects[custom_search_api_widget][download][branch] = 7.x-1.x
projects[custom_search_api_widget][download][url] = "http://git.drupal.org/sandbox/joel_osc/2394389.git"

projects[date_ical][version] = 3.3
projects[date_ical][subdir] = contrib
projects[date_ical][type] = "module"
projects[date_ical][download][type] = "get"
projects[date_ical][download][url] = "http://ftp.drupal.org/files/projects/date_ical-7.x-3.3.tar.gz"

projects[elysia_cron][version] = 2.1
projects[elysia_cron][subdir] = contrib
projects[elysia_cron][type] = "module"
projects[elysia_cron][download][type] = "get"
projects[elysia_cron][download][url] = "http://ftp.drupal.org/files/projects/elysia_cron-7.x-2.1.tar.gz"

projects[email][version] = 1.3
projects[email][subdir] = contrib
projects[email][type] = "module"
projects[email][download][type] = "get"
projects[email][download][url] = "http://ftp.drupal.org/files/projects/email-7.x-1.3.tar.gz"

projects[entityqueue][version] = 1.0-rc1
projects[entityqueue][subdir] = contrib
projects[entityqueue][type] = "module"
projects[entityqueue][download][type] = "get"
projects[entityqueue][download][url] = "http://ftp.drupal.org/files/projects/entityqueue-7.x-1.0-rc1.tar.gz"

projects[expire][version] = 2.0-rc3
projects[expire][subdir] = contrib
projects[expire][type] = "module"
projects[expire][download][type] = "get"
projects[expire][download][url] = "http://ftp.drupal.org/files/projects/expire-7.x-2.0-rc3.tar.gz"


;projects[feeds][version] = 2.0-alpha8
;projects[feeds][subdir] = contrib
;projects[feeds][type] = "module"
;projects[feeds][download][type] = "get"
;projects[feeds][download][url] = "http://ftp.drupal.org/files/projects/feeds-7.x-2.0-alpha8.tar.gz"

projects[feeds][version] = 2.x-dev
projects[feeds][subdir] = contrib
projects[feeds][type] = "module"
projects[feeds][download][type] = git
projects[feeds][download][revision] = b244c04
projects[feeds][download][branch] = 7.x-2.x

projects[feeds_tamper][version] = 1.0
projects[feeds_tamper][subdir] = contrib
projects[feeds_tamper][type] = "module"
projects[feeds_tamper][download][type] = "get"
projects[feeds_tamper][download][url] = "http://ftp.drupal.org/files/projects/feeds_tamper-7.x-1.0.tar.gz"

projects[flexslider][version] = 2.0-alpha3
projects[flexslider][subdir] = contrib
projects[flexslider][type] = "module"
projects[flexslider][download][type] = "get"
projects[flexslider][download][url] = "http://ftp.drupal.org/files/projects/flexslider-7.x-2.0-alpha3.tar.gz"

projects[flood_unblock][version] = 1.4
projects[flood_unblock][subdir] = contrib
projects[flood_unblock][type] = "module"
projects[flood_unblock][download][type] = "get"
projects[flood_unblock][download][url] = "http://ftp.drupal.org/files/projects/flood_unblock-7.x-1.4.tar.gz"

projects[geocoder][version] = 1.2
projects[geocoder][subdir] = contrib
projects[geocoder][type] = "module"
projects[geocoder][download][type] = "get"
projects[geocoder][download][url] = "http://ftp.drupal.org/files/projects/geocoder-7.x-1.2.tar.gz"

projects[geofield][version] = 2.3
projects[geofield][subdir] = contrib
projects[geofield][type] = "module"
projects[geofield][download][type] = "get"
projects[geofield][download][url] = "http://ftp.drupal.org/files/projects/geofield-7.x-2.3.tar.gz"

projects[geophp][version] = 1.7
projects[geophp][subdir] = contrib
projects[geophp][type] = "module"
projects[geophp][download][type] = "get"
projects[geophp][download][url] = "http://ftp.drupal.org/files/projects/geophp-7.x-1.7.tar.gz"

projects[job_scheduler][version] = 2.0-alpha3
projects[job_scheduler][subdir] = contrib
projects[job_scheduler][type] = "module"
projects[job_scheduler][download][type] = get
projects[job_scheduler][download][url] = "http://ftp.drupal.org/files/projects/job_scheduler-7.x-2.0-alpha3.tar.gz"

projects[jstats][version] = 1.x-dev
projects[jstats][subdir] = contrib
projects[jstats][type] = "module"
projects[jstats][download][type] = git
projects[jstats][download][revision] = e0cdd50
projects[jstats][download][branch] = 7.x-1.x

projects[jump_menu][version] = 1.4
projects[jump_menu][subdir] = contrib
projects[jump_menu][type] = "module"
projects[jump_menu][download][type] = "get"
projects[jump_menu][download][url] = "http://ftp.drupal.org/files/projects/jump_menu-7.x-1.4.tar.gz"

projects[ldap][version] = 2.0-beta8
projects[ldap][subdir] = contrib
projects[ldap][type] = "module"
projects[ldap][download][type] = "get"
projects[ldap][download][url] = "http://ftp.drupal.org/files/projects/ldap-7.x-2.0-beta8.tar.gz"

projects[memcache][version] = 1.2
projects[memcache][subdir] = contrib
projects[memcache][type] = "module"
projects[memcache][download][type] = "get"
projects[memcache][download][url] = "http://ftp.drupal.org/files/projects/memcache-7.x-1.2.tar.gz"

projects[menu_attributes][version] = 1.0-rc3
projects[menu_attributes][subdir] = contrib
projects[menu_attributes][type] = "module"
projects[menu_attributes][download][type] = "get"
projects[menu_attributes][download][url] = "http://ftp.drupal.org/files/projects/menu_attributes-7.x-1.0-rc3.tar.gz"

projects[menu_import][version] = 1.6
projects[menu_import][subdir] = contrib
projects[menu_import][type] = "module"
projects[menu_import][download][type] = "get"
projects[menu_import][download][url] = "http://ftp.drupal.org/files/projects/menu_import-7.x-1.6.tar.gz"

projects[openlayers][version] = 2.0-beta9
projects[openlayers][subdir] = contrib
projects[openlayers][type] = "module"
projects[openlayers][download][type] = "get"
projects[openlayers][download][url] = "http://ftp.drupal.org/files/projects/openlayers-7.x-2.0-beta9.tar.gz"
projects[openlayers][patch][] = "https://www.drupal.org/files/issues/openlayers-2232445-remove-drush-make.diff"

projects[openlayers_icons_styles][version] = 3.0
projects[openlayers_icons_styles][subdir] = contrib
projects[openlayers_icons_styles][type] = "module"
projects[openlayers_icons_styles][download][type] = git
projects[openlayers_icons_styles][download][revision] = 2aa566c
projects[openlayers_icons_styles][download][branch] = 7.X-1.X
projects[openlayers_icons_styles][download][url] = "http://git.drupal.org/sandbox/Pol/1260668.git"

projects[phone][version] = 1.0-beta1
projects[phone][subdir] = contrib
projects[phone][type] = "module"
projects[phone][download][type] = "get"
projects[phone][download][url] = "http://ftp.drupal.org/files/projects/phone-7.x-1.0-beta1.tar.gz"

projects[piwik][version] = 2.7
projects[piwik][subdir] = contrib
projects[piwik][type] = "module"
projects[piwik][download][type] = "get"
projects[piwik][download][url] = "http://ftp.drupal.org/files/projects/piwik-7.x-2.7.tar.gz"

projects[proj4js][version] = 1.2
projects[proj4js][subdir] = contrib
projects[proj4js][type] = "module"
projects[proj4js][download][type] = "get"
projects[proj4js][download][url] = "http://ftp.drupal.org/files/projects/proj4js-7.x-1.2.tar.gz"

projects[redirect][version] = 1.0-rc1
projects[redirect][subdir] = contrib
projects[redirect][type] = "module"
projects[redirect][download][type] = "get"
projects[redirect][download][url] = "http://ftp.drupal.org/files/projects/redirect-7.x-1.0-rc1.tar.gz"

projects[sarnia][version] = 1.x-dev
projects[sarnia][subdir] = contrib
projects[sarnia][type] = "module"
projects[sarnia][download][type] = git
projects[sarnia][download][revision] = 46f9ff6
projects[sarnia][download][branch] = 7.x-1.x
projects[sarnia][patch][] = https://www.drupal.org/files/issues/sarnia-2187869-8.patch
; 2115281
projects[sarnia][patch][] = https://www.drupal.org/files/add_proper_projections_openlayers.patch
; 2287823
projects[sarnia][patch][] = https://www.drupal.org/files/issues/autocomplete_combobox_js.patch
; Can't find the drupal.org issue for the below patch...
; projects[sarnia][patch][] = contextual_filters_as_strings.patch
; 2098523
projects[sarnia][patch][] = https://www.drupal.org/files/issues/id_field_fix.patch
; 1944430
projects[sarnia][patch][] = https://www.drupal.org/files/sarnia_features.patch
; 1409198
projects[sarnia][patch][] = https://www.drupal.org/files/service.inc_.patch
; 1950256
projects[sarnia][patch][] = https://www.drupal.org/files/issues/term_query_type_ui.patch
projects[sarnia][patch][] = https://www.drupal.org/files/issues/remove-sarnia.make-2466293-1.patch

projects[search_api][version] = 1.14
projects[search_api][subdir] = contrib
projects[search_api][type] = "module"
projects[search_api][download][type] = "get"
projects[search_api][download][url] = "http://ftp.drupal.org/files/projects/search_api-7.x-1.14.tar.gz"
projects[search_api][patch][] = https://www.drupal.org/files/issues/search-api-wrong-date-labels-2313291-7.patch

projects[search_api_attachments][version] = 1.5
projects[search_api_attachments][subdir] = contrib
projects[search_api_attachments][type] = "module"
projects[search_api_attachments][download][type] = "get"
projects[search_api_attachments][download][url] = "http://ftp.drupal.org/files/projects/search_api_attachments-7.x-1.5.tar.gz"

projects[search_api_db][version] = 1.4
projects[search_api_db][subdir] = contrib
projects[search_api_db][type] = "module"
projects[search_api_db][download][type] = "get"
projects[search_api_db][download][url] = "http://ftp.drupal.org/files/projects/search_api_db-7.x-1.4.tar.gz"

projects[search_api_et][version] = 2.x-dev
projects[search_api_et][subdir] = contrib
projects[search_api_et][type] = "module"
projects[search_api_et][download][type] = git
projects[search_api_et][download][revision] = cd607dc
projects[search_api_et][download][branch] = 7.x-2.x

projects[search_api_exclude][version] = 3.0
projects[search_api_exclude][subdir] = contrib
projects[search_api_exclude][type] = "module"
projects[search_api_exclude][download][type] = "get"
projects[search_api_exclude][download][url] = "http://ftp.drupal.org/files/projects/search_api_exclude-7.x-1.0.tar.gz"

projects[search_api_location][version] = 2.0-beta2
projects[search_api_location][subdir] = contrib
projects[search_api_location][type] = "module"
projects[search_api_location][download][type] = "get"
projects[search_api_location][download][url] = "http://ftp.drupal.org/files/projects/search_api_location-7.x-2.0-beta2.tar.gz"

projects[search_api_override][version] = 1.0-rc1
projects[search_api_override][subdir] = contrib
projects[search_api_override][type] = "module"
projects[search_api_override][download][type] = "get"
projects[search_api_override][download][url] = "http://ftp.drupal.org/files/projects/search_api_override-7.x-1.0-rc1.tar.gz"

projects[search_api_solr][version] = 1.6
projects[search_api_solr][subdir] = contrib
projects[search_api_solr][type] = "module"
projects[search_api_solr][download][type] = "get"
projects[search_api_solr][download][url] = "http://ftp.drupal.org/files/projects/search_api_solr-7.x-1.6.tar.gz"
projects[search_api_solr][patch][] = https://www.drupal.org/files/issues/1908990-30--excerpt_missing.patch
projects[search_api_solr][patch][] = "https://www.drupal.org/files/issues/2333133-2--fulltext_filters.patch"
projects[search_api_solr][patch][] = "https://www.drupal.org/files/issues/no_results_returned-2333133-9.patch"
projects[search_api_solr][patch][] = "https://www.drupal.org/files/issues/Empty_search_excerpts_produce_some_highlighted_text-2481715-2.patch"

projects[search_autocomplete][version] = 4.4
projects[search_autocomplete][subdir] = contrib
projects[search_autocomplete][type] = "module"
projects[search_autocomplete][download][type] = "get"
projects[search_autocomplete][download][url] = "http://ftp.drupal.org/files/projects/search_autocomplete-7.x-4.4.tar.gz"

projects[securepages][version] = 1.0-beta2
projects[securepages][subdir] = contrib
projects[securepages][type] = "module"
projects[securepages][download][type] = "get"
projects[securepages][download][url] = "http://ftp.drupal.org/files/projects/securepages-7.x-1.0-beta2.tar.gz"

projects[shield][version] = 1.2
projects[shield][subdir] = contrib
projects[shield][type] = "module"
projects[shield][download][type] = "get"
projects[shield][download][url] = "http://ftp.drupal.org/files/projects/shield-7.x-1.2.tar.gz"

projects[simplehtmldom][version] = 2.1
projects[simplehtmldom][subdir] = contrib
projects[simplehtmldom][type] = "module"
projects[simplehtmldom][download][type] = "get"
projects[simplehtmldom][download][url] = "http://ftp.drupal.org/files/projects/simplehtmldom-7.x-2.1.tar.gz"

projects[smtp][version] = 1.0
projects[smtp][subdir] = contrib
projects[smtp][type] = "module"
projects[smtp][download][type] = "get"
projects[smtp][download][url] = "http://ftp.drupal.org/files/projects/smtp-7.x-1.0.tar.gz"

projects[subpathauto][version] = 1.3
projects[subpathauto][subdir] = contrib
projects[subpathauto][type] = "module"
projects[subpathauto][download][type] = "get"
projects[subpathauto][download][url] = "http://ftp.drupal.org/files/projects/subpathauto-7.x-1.3.tar.gz"
projects[subpathauto][patch][] = https://www.drupal.org/files/issues/subpath-auto-1252502-whitelist-and-blacklist-13.patch
projects[subpathauto][patch][] = https://www.drupal.org/files/issues/subpathauto-not_loading_admin_theme-1814516-18.patch

projects[taxonomy_manager][version] = 1.0
projects[taxonomy_manager][subdir] = contrib
projects[taxonomy_manager][type] = "module"
projects[taxonomy_manager][download][type] = "get"
projects[taxonomy_manager][download][url] = "http://ftp.drupal.org/files/projects/taxonomy_manager-7.x-1.0.tar.gz"

projects[varnish][version] = 1.0-beta3
projects[varnish][subdir] = contrib
projects[varnish][type] = "module"
projects[varnish][download][type] = "get"
projects[varnish][download][url] = "http://ftp.drupal.org/files/projects/varnish-7.x-1.0-beta3.tar.gz"

projects[views_accordion][version] = 1.1
projects[views_accordion][subdir] = contrib
projects[views_accordion][type] = "module"
projects[views_accordion][download][type] = "get"
projects[views_accordion][download][url] = "http://ftp.drupal.org/files/projects/views_accordion-7.x-1.1.tar.gz"

projects[views_arguments_extras][version] = 1.x-dev
projects[views_arguments_extras][subdir] = contrib
projects[views_arguments_extras][type] = "module"
projects[views_arguments_extras][download][type] = git
projects[views_arguments_extras][download][revision] = 05fd1c2
projects[views_arguments_extras][download][branch] = 7.x-1.x

projects[views_fieldsets][version] = 1.3
projects[views_fieldsets][subdir] = contrib
projects[views_fieldsets][type] = "module"
projects[views_fieldsets][download][type] = "get"
projects[views_fieldsets][download][url] = "http://ftp.drupal.org/files/projects/views_fieldsets-7.x-1.3.tar.gz"

projects[views_limit_grouping][version] = 1.x-dev
projects[views_limit_grouping][subdir] = contrib
projects[views_limit_grouping][type] = "module"
projects[views_limit_grouping][download][type] = git
projects[views_limit_grouping][download][revision] = a6466fc
projects[views_limit_grouping][download][branch] = 7.x-1.x
projects[views_limit_grouping][patch][] = https://www.drupal.org/files/issues/views_limit_grouping-2472619-4.patch

projects[views_load_more][version] = 1.5
projects[views_load_more][subdir] = contrib
projects[views_load_more][type] = "module"
projects[views_load_more][download][type] = "get"
projects[views_load_more][download][url] = "http://ftp.drupal.org/files/projects/views_load_more-7.x-1.5.tar.gz"

projects[views_php][version] = 1.0-alpha1
projects[views_php][subdir] = contrib
projects[views_php][type] = "module"
projects[views_php][download][type] = "get"
projects[views_php][download][url] = "http://ftp.drupal.org/files/projects/views_php-7.x-1.0-alpha1.tar.gz"
projects[views_php][patch][] = https://www.drupal.org/files/issues/views_php-pager_missing-2276165-2.patch

projects[webform_ajax][version] = 1.1
projects[webform_ajax][subdir] = contrib
projects[webform_ajax][type] = "module"
projects[webform_ajax][download][type] = "get"
projects[webform_ajax][download][url] = "http://ftp.drupal.org/files/projects/webform_ajax-7.x-1.1.tar.gz"

projects[webform_phone][version] = 1.21
projects[webform_phone][subdir] = contrib
projects[webform_phone][type] = "module"
projects[webform_phone][download][type] = "get"
projects[webform_phone][download][url] = "http://ftp.drupal.org/files/projects/webform_phone-7.x-1.21.tar.gz"


projects[charts][version] = 7.x-2.0-rc1
projects[charts][subdir] = contrib
projects[charts][type] = "module"
projects[charts][download][type] = "get"
projects[charts][download][url] = "http://ftp.drupal.org/files/projects/charts-7.x-2.0-rc1.tar.gz"


; Libraries

; Example
;libraries[][download][type] = "get"
;libraries[][destination] = libraries
;libraries[][download][url] = ""
;libraries[][download][md5] = ""

libraries[autopager][download][type] = "get"
libraries[autopager][destination] = libraries
libraries[autopager][download][url] = "https://jquery-autopager.googlecode.com/files/jquery.autopager-1.0.0.js"

libraries[flexslider][download][type] = "get"
libraries[flexslider][destination] = libraries
libraries[flexslider][download][url] = "https://api.github.com/repos/woothemes/FlexSlider/zipball/version/2.4.0"

libraries[geoPHP][download][type] = "get"
libraries[geoPHP][destination] = libraries
libraries[geoPHP][download][url] = "http://sourceforge.net/projects/dokuwikispatial/files/geophp/geophp-1.1.tar.gz/download?use_mirror=iweb"

libraries[imagesloaded][download][type] = "get"
libraries[imagesloaded][destination] = libraries
libraries[imagesloaded][download][url] = "https://github.com/desandro/imagesloaded/archive/master.zip"

libraries[openlayers][download][type] = "get"
libraries[openlayers][destination] = libraries
libraries[openlayers][download][url] = "https://github.com/openlayers/openlayers/releases/download/release-2.11/OpenLayers-2.11.tar.gz"

libraries[autopager][download][type] = "get"
libraries[autopager][destination] = libraries
libraries[autopager][download][url] = "http://code.highcharts.com/zips/Highcharts-4.1.5.zip"

