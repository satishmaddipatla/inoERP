<?php$module_info = [		array(				"module" => "org",				"class" => "org",				"key_field" => "org",				"primary_column" => "org_id"		)];$pageTitle = " Organization - Find Orgs ";?><?php include_once("../../include/basics/header.inc"); ?> <script src="org.js"></script><?php$search_form = search::search_form('org', 'find_org', 'org_search');if(!empty($pagination)){$pagination_statement = $pagination->show_pagination($pagination, 'find_org', $pageno, $query_string );}//include_find_page();?><?php  require_once(INC_BASICS . DS ."find_page.inc") ?>