<div id="all_contents">
 <div id="content_left"></div>
 <div id="content_right">
	<div id="content_right_left">
	 <div id="content_top"></div>
	 <div id="content">
		<div id="structure">
		 <div id="site_control_divId">
			<!--    START OF FORM HEADER-->
			<div class="error"></div><div id="loading"></div>
			<?php echo (!empty($show_message)) ? $show_message : ""; ?> 
			<!--    End of place for showing error messages-->

			<div id ="form_header">
			 <form action=""  method="post" id="site_control_header"  name="site_control_header">
				<div id="tabsHeader">
         <ul class="tabMain">
          <li><a href="#tabsHeader-1">Basic Info</a></li>
          <li><a href="#tabsHeader-2">Details</a></li>
					<li><a href="#tabsHeader-3">Common BOM</a></li>
         </ul>
				 <div class="tabContainer">
					<div id="tabsHeader-1" class="tabContent">
					 <div class="large_shadow_box"> 
						<ul class="column four_column">
						 <li><label>Org Name(1) : </label>
							<?php echo form::select_field_from_object('org_id', org::find_all_inventory(), 'org_id', 'org', $site_control_header->org_id, 'org_id', $readonly, '', ''); ?>
						 </li>
						 <li><label>BOM Id : </label>
							<?php echo form::text_field('site_control_header_id', $site_control_header->site_control_header_id, '15', '25', '', 'System Number', 'site_control_header_id', $readonly) ?>
							<a name="show" href="site_control.php?site_control_header_id=" class="show site_control_header_id">
							 <img src="<?php echo HOME_URL; ?>themes/images/refresh.png"/></a> 
						 </li>
						 <li><label>Item Id : </label>
							<?php form::text_field_drm('item_id'); ?>
						 </li>
						 <li><label>Item Number(2) : </label>
							<?php form::text_field_dm('item_number'); ?>
						 </li>
						 <li><label>Description: </label>
							<?php form::text_field_widr('item_description'); ?>
						 </li>
						 <li><label>UOM : </label>
							<?php echo form::select_field_from_object('uom', uom::find_all(), 'uom_id', 'uom', $$class->uom, 'uom'); ?>
						 </li>
						</ul>
					 </div>
					</div>
					<div id="tabsHeader-2" class="tabContent">
					 <div> 
						<ul class="column five_column">
						 <li><label>Alternate Bom : </label>
							<?php echo form::text_field_d('alternate_site_control'); ?>
						 </li>
						 <li><label>Revision : </label>
							<?php form::text_field_dm('site_control_revision'); ?>
						 </li>
						 <li><label>Effective Date : </label>
							<?php echo form::date_fieldAnyDay_m('effective_date', $$class->effective_date); ?>
						 </li>
						</ul>
					 </div>
					</div>
					<div id="tabsHeader-3" class="tabContent">
					 <div> 
						<ul class="column five_column">
						 <li><label>Common BOM Item Id: </label>
							<?php form::text_field_widsr('item_id'); ?>
						 </li>
						 <li><label>Item Number : </label>
							<?php form::text_field_wid('commonBom_item_number'); ?>
						 </li>
						 <li><label>Description: </label>
							<?php form::text_field_wid('commonBom_item_description'); ?>
						 </li>
						</ul>
					 </div>
					</div>
				 </div>

				</div>
			 </form>
			</div>

			<div id="form_line" class="form_line"><span class="heading">BOM Lines </span>
			 <form action=""  method="post" id="site_control_site"  name="site_control_line">
				<div id="tabsLine">
				 <ul class="tabMain">
					<li><a href="#tabsLine-1">Main</a></li>
					<li><a href="#tabsLine-2">Effectivity</a></li>
					<li><a href="#tabsLine-3">Control</a></li>
				 </ul>
				 <div class="tabContainer">
					<div id="tabsLine-1" class="tabContent">
					 <table class="form_line_data_table">
						<thead> 
						 <tr>
							<th>Action</th>
							<th>BOM Line Id</th>
							<th>BOM Sequence</th>
							<th>Routing Sequence</th>
							<th>Item Id</th>
							<th>Item Number</th>
							<th>Item Description</th>
							<th>UOM</th>
							<th>Usage Basis</th>
							<th>Quantity</th>
						 </tr>
						</thead>
						<tbody class="form_data_line_tbody">
						 <?php
						 $count = 0;
						 foreach ($site_control_line_object as $site_control_line) {
//							echo $count . ' is         : <pre>';
//							print_r($site_control_line);
							?>         
 						 <tr class="site_control_line<?php echo $count ?>">
 							<td>    
 							 <ul class="inline_action">
 								<li class="add_row_img"><img  src="<?php echo HOME_URL; ?>themes/images/add.png"  alt="add new line" /></li>
 								<li class="remove_row_img"><img src="<?php echo HOME_URL; ?>themes/images/remove.png" alt="remove this line" /> </li>
 								<li><input type="checkbox" name="line_id_cb" value="<?php echo htmlentities($site_control_line->item_description); ?>"></li>           
 								<li><?php echo form::hidden_field('site_control_header_id', $site_control_header->site_control_header_id); ?></li>
 							 </ul>
 							</td>
 							<td><?php form::text_field_wid2sr('site_control_line_id'); ?></td>
 							<td><?php form::text_field_wid2sm('site_control_sequence'); ?></td>
 							<td><?php echo !empty($routing_line_details) ? form::select_field_from_object('routing_sequence', $routing_line_details, 'site_control_routing_line_id', 'routing_sequence', $$class_second->routing_sequence, '',$readonly, 'usage_basis','',1) : form::text_field_wid2sm('routing_sequence'); ?></td>
 							<td><?php echo form::text_field('component_item_id', $$class_second->component_item_id, '8', '50', 1, '', '', 1, 'item_id'); ?></td>
 							<td><?php echo form::text_field('component_item_number', $$class_second->component_item_number, '20', '50', 1, '', '', '', 'item_number'); ?></td>
 							<td><?php echo form::text_field('component_description', $$class_second->component_description, '20', '50', '', '', '', 1, 'item_description'); ?></td>
 							<td><?php echo form::select_field_from_object('component_uom', uom::find_all(), 'uom_id', 'uom', $$class_second->component_uom, '', '', 'uom'); ?></td>
 							<td><?php echo form::select_field_from_object('usage_basis', site_control_header::site_control_charge_basis(), 'option_line_code', 'option_line_value', $$class_second->usage_basis, '', $readonly, 'usage_basis','',1); ?></td>
							<td><?php form::number_field_wid2s('usage_quantity'); ?></td>

 						 </tr>
							<?php
							$count = $count + 1;
						 }
						 ?>
						</tbody>
					 </table>
					</div>
					<div id="tabsLine-2" class="scrollElement tabContent">
					 <table class="form_line_data_table">
						<thead> 
						 <tr>
							<th>Start Date</th>
							<th>End Date</th>
							<th>ECO Number</th>
							<th>ECO implemented</th>
						 </tr>
						</thead>
						<tbody class="form_data_line_tbody">
						 <?php
						 $count = 0;
						 foreach ($site_control_line_object as $site_control_line) {
							?>         
 						 <tr class="site_control_line<?php echo $count ?>">
 							<td><?php echo form::date_fieldAnyDay('effective_start_date', $$class_second->effective_start_date); ?></td>
 							<td><?php echo form::date_fieldAnyDay('effective_end_date', $$class_second->effective_end_date); ?></td>
 							<td><?php form::text_field_wid2('eco_number'); ?></td>
 							<td>
								<?php echo form::checkBox_field('eco_implemented_cb', $$class_second->eco_implemented_cb, 'eco_implemented_cb', $readonly); ?>
 							</td>
 						 </tr>
							<?php
							$count = $count + 1;
						 }
						 ?>
						</tbody>
						<!--                  Showing a blank form for new entry-->
					 </table>
					</div>
					<div id="tabsLine-3" class="tabContent">
					 <table class="form_line_data_table">
						<thead> 
						 <tr>
							<th>Planning %</th>
							<th>Yield</th>
							<th>WIP Supply Type</th>
							<th>Sub inventory</th>
							<th>Locator</th>
							<th>In cost rollup</th>
						 </tr>
						</thead>
						<tbody class="form_data_line_tbody">
						 <?php
						 $count = 0;
						 foreach ($site_control_line_object as $site_control_line) {
							?>         
 						 <tr class="site_control_line<?php echo $count ?>">
 							<td><?php form::text_field_wid2('planning_percentage'); ?></td>
 							<td><?php form::text_field_wid2('yield'); ?></td>
							<td><?php echo form::select_field_from_object('wip_supply_type', site_control_header::wip_supply_type(), 'option_line_code', 'option_line_value', $$class_second->wip_supply_type, '', $readonly, '', '',''); ?></td>
 							<td><?php echo form::select_field_from_object('supply_sub_inventory', subinventory::find_all_of_org_id($$class->org_id), 'subinventory_id', 'subinventory', $$class_second->supply_sub_inventory, '', $readonly, 'subinventory_id', '',''); ?></td>
 							<td><?php echo form::select_field_from_object('supply_locator', locator::find_all_of_subinventory($$class_second->supply_sub_inventory), 'locator_id', 'locator', $$class_second->supply_locator, '', $readonly, 'locator_id', '',''); ?></td>
 							<td>
								<?php echo form::checkBox_field('include_in_cost_rollup_cb', $$class_second->include_in_cost_rollup_cb, 'include_in_cost_rollup_cb', $readonly); ?>
 							</td>
 						 </tr>
							<?php
							$count = $count + 1;
						 }
						 ?>
						</tbody>
						<!--                  Showing a blank form for new entry-->

					 </table>
					</div>
				 </div>
				</div>
			 </form>
			 <ul class="inline download_action">
				<li class="export_to_excel"><img  src="<?php echo HOME_URL; ?>themes/images/excel_16.png"  alt="export to excel" /></li>
			 </ul>
			</div>

			<!--END OF FORM HEADER-->
		 </div>
		</div>
		<!--   end of structure-->
	 </div>
	 <div id="content_bottom"></div>
	</div>
	<div id="content_right_right"></div>
 </div>

</div>

<?php include_template('footer.inc') ?>
