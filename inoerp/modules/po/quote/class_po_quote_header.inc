<?php

/**
 * inoERP
 *
 * @copyright   2014 Nishit R. Das
 * @license     https://www.mozilla.org/MPL/2.0/
 * @link        http://inoideas.org
 * @source code https://github.com/inoerp/inoERP
 */

/**
 * po_quote_header
 * Contains all the quote information 
 *
 */
class po_quote_header extends dbObject {

 public static $table_name = "po_quote_header";
 public static $dependent_classes = ['po_quote_line', 'po_quote_detail'];
 public static $primary_column = "po_quote_header_id";
 public static $primary_column2 = "quote_number";
 public static $key_column = 'po_rfq_header_id';
 public static $module = "pur";
 public static $js_fileName = 'modules/po/js/multi_select.js';
 public static $system_info = [
  'name' => 'Quote',
  'number' => '2216',
  'description' => 'Create & Mainten Quote Related documents/transactions',
  'version' => '0.1.1',
  'db_version' => '1001',
  'mod_version' => '1.1.1',
  'dependent_class' => array('po_quote_line', 'po_quote_detail'),
  'primary_entity_cb' => '',
  'module_name' => 'po',
  'weight' => 1
 ];
 public $action_a = [
  'PRINT' => 'Print',
  'ACCEPTED' => 'Accept',
  'VIEW_HISTORY' => 'View History',
  'CANCEL' => 'Cancel',
  'CONVERT_STD_PO' => 'Convert to Standard PO',
  'CONVERT_BPA' => 'Convert to Blanket Agreement',
 ];
 public $checkbox = [
  "active_cb"
 ];
 public static $po_quote_type_a = [
  'BID' => 'Bid',
  'STANDARD' => 'Standard',
 ];
 public static $po_quote_status_a = [
  'INCOMLETE' => 'Incomplete',
  'CLOSED' => 'Closed',
  'ACCEPTED' => 'Accepted',
 ];
 public $field_a = [
  'po_quote_header_id',
  'po_rfq_header_id',
  'bu_org_id',
  'quote_number',
  'supplier_site_id',
  'supplier_id',
  'supplier_quote',
  'quote_type',
  'buyer',
  'description',
  'ship_to_id',
  'bill_to_id',
  'currency',
  'payment_term_id',
  'effective_start_date',
  'effective_end_date',
  'valid_date',
  'quote_status',
  'active_cb',
  'created_by',
  'creation_date',
  'last_update_by',
  'last_update_date',
 ];
 public $initial_search = [
  'quote_number',
  'quote_name',
  'quote_type',
 ];
 public $requiredField = [
  'supplier_site_id',
  'supplier_id',
 ];
 public $addressField = [
  'ship_to_id',
  'bill_to_id'
 ];
 public $numberField = [
  'header_amount',
  'exchange_rate'
 ];
 public $fields_inForm_notInDataBase = [

  "supplier_name",
  "supplier_number",
  "supplier_site_name",
  "ship_to_address",
  "bill_to_address",
  'multi_action_class_pc',
  'multi_action_class_pc_value',
  'action',
  'ship_to_phone',
  'ship_to_email',
  'ship_to_address',
  'ship_to_country',
  'ship_to_postal_code',
  'bill_to_phone',
  'bill_to_email',
  'bill_to_address',
  'bill_to_country',
  'bill_to_postal_code',
 ];
 public $search = [
  '_show_update_path' => 1,
  '_show_view_path' => 1,
 ];
 public $pageTitle = " Quotation "; //page Title
 public $po_quote_header_id;
 public $po_rfq_header_id;
 public $quote_number;
 public $supplier_site_id;
 public $supplier_id;
 public $supplier_quote;
 public $quote_type;
 public $buyer;
 public $description;
 public $ship_to_id;
 public $bill_to_id;
 public $currency;
 public $payment_term_id;
 public $effective_start_date;
 public $effective_end_date;
 public $valid_date;
 public $active_cb;
 public $quote_status;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $rfq_number;
 public $ship_to_address;
 public $bill_to_address;
 public $multi_action_class_pc;
 public $multi_action_class_pc_value;
 public $action;
 public $bill_to_address_name;
 public $ship_to_phone;
 public $ship_to_address_name;
 public $ship_to_country;
 public $ship_to_postal_code;
 public $bill_to_phone;
 public $bill_to_country;
 public $bill_to_postal_code;
 public $supplier_name;
 public $supplier_number;
 public $supplier_site_name;
 public $bu_org_id;

 public function _before_delete() {
  $line_exists = po_quote_line::find_by_parent_id($this->po_quote_header_id);
  if ($line_exists) {
   echo "<br>Delete is not allowed as quote Lines exists!. First delete lines and then try aagain ";
   return -99;
  } else {
   return 1;
  }
 }

 public function _before_save() {
  if (empty($this->po_quote_header_id)) {
   $this->quote_status = 'INCOMLETE';
  }

  if ((!empty($this->po_quote_header_id)) && !empty($this->quote_status) && (in_array('$this->quote_status', array('INPROCESS', 'CLOSED', 'CANCELLED')))) {
   echo "You cant make changes to quote in this status.";
   return -99;
  }

  if (($this->action == 'ACCEPTED')) {
   $this->quote_status = 'ACCEPTED';
  }

  if (($this->action == 'CONVERT_STD_PO')) {
   if ($this->quote_status == 'ACCEPTED') {
    $this->_convert_quote_toStdPO();
   } else {
    echo "Change quote status to Accepted, and try again. Current status " . $this->quote_status;
   }
   return 10;
  }

  if (($this->action == 'CONVERT_BPA')) {
   if ($this->quote_status == 'ACCEPTED') {
    $this->_convert_quote_toBPA();
   } else {
    echo "Change quote status to Accepted, and try again. Current status " . $this->quote_status;
   }
   return 10;
  }
 }

 public function _after_save() {

  if ((!empty($this->po_quote_header_id)) && empty($this->quote_number)) {
   $po_quote_header_id = $this->po_quote_header_id;
   $bu_org_id = $this->bu_org_id;
   $this->quote_number = $bu_org_id . '-' . $po_quote_header_id;
   echo ' System generated quote number is ' . $this->quote_number;
   $this->audit_trial();
   $this->save();
  }

  if ((!empty($this->ref_po_quote_header_id)) && empty($this->release_number) && !empty($this->po_quote_header_id) && ($this->po_quote_type == 'BLANKET_RELEASE')) {
   $this->release_number = $this->_find_relNumber();
   $this->audit_trial();
   $this->save();
  }

  if (($this->action == 'APPROVE')) {
   $pur_control = po_quote_purchasing_control::find_by_org_id($this->bu_org_id);
   if (empty($pur_control->po_quote_approval_hierarchy)) {
    $this->po_quote_status = 'APPROVED';
    $this->audit_trial();
    $this->save();
   } else {
    $this->_approve_po($_SESSION['user_id'], $pur_control->po_quote_approval_hierarchy);
   }
  }
 }

 public function _before_showing() {
  $address = new address();
  if (!empty($this->ship_to_id)) {
   $address_ship_to = $address->findBy_id($this->ship_to_id);
   if (!empty($address_ship_to)) {
    $this->ship_to_address_name = isset($address_ship_to->address_name) ? $address_ship_to->address_name : '';
    $this->ship_to_address = isset($address_ship_to->address) ? $address_ship_to->address : '';
    $this->ship_to_country = isset($address_ship_to->country) ? $address_ship_to->country : '';
    $this->ship_to_postal_code = isset($address_ship_to->postal_code) ? $address_ship_to->postal_code : '';
    $this->ship_to_phone = isset($address_ship_to->phone) ? $address_ship_to->phone : '';
   }
  }
  if (!empty($this->bill_to_id)) {
   $address_bill_to = $address->findBy_id($this->bill_to_id);
   if (!empty($address_bill_to)) {
    $this->bill_to_address_name = isset($address_bill_to->address_name) ? $address_bill_to->address_name : '';
    $this->bill_to_address = isset($address_bill_to->address) ? $address_bill_to->address : '';
    $this->bill_to_country = isset($address_bill_to->country) ? $address_bill_to->country : '';
    $this->bill_to_postal_code = isset($address_bill_to->postal_code) ? $address_bill_to->postal_code : '';
    $this->bill_to_phone = isset($address_bill_to->phone) ? $address_bill_to->phone : '';
   }
  }
 }

 private function _approve_po($approving_user_id, $approval_hierarchy = '') {
  /* 1. Check the approval option for the BU - Employee Supervisor or Position Base
    2. Find the employee details of the current user
    3. Find the position(if not available then job) of the current employee
    4. Get the approval limits of the position/job
    5. If approval limit is good then approve the po
    6. ELse create an approal notification for the superviosr/role and put the PO in inProcess
   */
  $po_quote_header_after_rev = new po_quote_header();
  $po_quote_header_after_rev->po_quote_header_id = $this->po_quote_header_id;
  $position_approval_details = hr_employee_position_v::find_by_userId_docType($approving_user_id, $this->_po_quote_type_document_mapping[$this->po_quote_type]);
  if (empty($position_approval_details)) {
   echo "<br>No approval limit found";
   return -99;
  }
  foreach ($position_approval_details as $obj) {
   if ($obj->limit_object == 'TOTAL_AMOUNT') {
    $amount_limit = $obj->amount_limit;
    if ($amount_limit >= $this->header_amount) {
     $po_quote_header_after_rev->po_quote_status = 'APPROVED';
     $comment_msg = " PO Approved By $approving_user_id ";
    } else {
     //create notification
     $po_quote_header_after_rev->po_quote_status = 'INPROCESS';
     $comment_msg = " Approval request is submitted by user id $approving_user_id ";
    }
   }
  }
  if ($po_quote_header_after_rev->po_quote_status == 'INPROCESS') {
   //create notification
   $notif = new sys_notification();
   $notif->notification_type = 'APPROVAL';
   $notif->notification_name = 'po_quote_APPROVAL';
   $notif->from_user_id = $approving_user_id;
//    $employee_details = hr_employee_p::find_by_id($this->employee_id);
   $notif->from_user = $position_approval_details[0]->first_name . ' ' . $position_approval_details[0]->last_name;
   if (empty($position_approval_details[0]->supervisor_employee_id)) {
    $comment_msg = " No Supervisor found for $notif->from_user ";
    $this->_write_comment($approving_user_id, $comment_msg);
    $po_quote_header_after_rev->po_quote_status = 'INCOMPLETE';
    $po_quote_header_after_rev->audit_trial();
    $po_quote_header_after_rev->save();
    return;
   }
   $supr_employee_details = hr_employee::find_by_id($position_approval_details[0]->supervisor_employee_id);
   $supr_user_details = user::find_by_employeeId($position_approval_details[0]->supervisor_employee_id);
   $notif->to_user_id = $supr_user_details->user_id;
   $notif->to_user = $supr_employee_details->first_name . ' ' . $supr_employee_details->last_name;
   $notif->to_email = $supr_employee_details->email;
   $notif->reference_key_name = 'po_quote_header';
   $notif->reference_key_value = $this->po_quote_header_id;
   $notif->status = 'OPEN';
   $notif->start_date = current_time(true);
   $notif->notification_subject = "PO Approval From " . $notif->from_user . ' PO#' . $this->po_quote_number;
   $notif->notification_subject .=!empty($this->release_number) ? " Release #" . $this->release_number : '';
   $notif->text_field1 = "<br>PO Type : $this->po_quote_type ";
   $notif->text_field1 .= "<br>PO Number : $this->po_quote_number &nbsp;&nbsp; Amount : $this->header_amount";
   $notif->text_field1 .= "<br>Supplier : $this->supplier_name (Supplier Id : $this->supplier_id) ";
   $notif->text_field1 .= "<br>Description : $this->description ";
   $notif->audit_trial();
   $notif->save();
   $notif->_after_save();
  }
  $po_quote_header_after_rev->approved_by = $position_approval_details[0]->first_name . ' ' . $position_approval_details[0]->last_name;
  $po_quote_header_after_rev->approved_date = current_time();
  $po_quote_header_after_rev->audit_trial();
  $po_quote_header_after_rev->update_changesOnly($po_quote_header_after_rev->po_quote_header_id);
  $po_quote_header_after_rev->write_comment($approving_user_id, $comment_msg);
 }

 private function _convert_quote_toStdPO() {
  global $dbc;

//   foreach($_POST['line_price'] as $amt_k => $amt_v ){
//    $header_amt += $amt_v;
//   }
  $poh = new po_header();
  $poh->po_type = 'STANDARD';
  foreach ($poh->field_a as $k => $v) {
   if (property_exists($this, $v)) {
    $poh->$v = $this->$v;
   }
  }
  $po_purchasing_control_i = po_purchasing_control::find_by_org_id($this->bu_org_id);
  $poh->bill_to_id = $po_purchasing_control_i->ship_to_id;
  $poh->ship_to_id = $po_purchasing_control_i->bill_to_id;
  if (!empty($poh->supplier_site_id)) {
   $supplier_site_details = supplier_site::find_by_id($poh->supplier_site_id);
   $poh->doc_currency = $supplier_site_details->currency;
   if (empty($poh->payment_term_id)) {
    $poh->payment_term_id = $supplier_site_details->payment_term_id;
   }
  }
  if (empty($poh->doc_currency)) {
   $poh->doc_currency = $poh->currency;
  }
  if (empty($poh->payment_term_id)) {
   $poh->payment_term_id = po_quote_purchasing_control::find_by_org_id($poh->bu_org_id)->payment_term_id;
  }
  $poh->exchange_rate_type = 'CORP';
  $poh->header_amount = .01;
  $poh->po_quote_status = 'ENTERED';
  try {
   $poh->_before_save();
   $poh->save();
   $poh->_after_save();
   $dbc->confirm();
   echo "<br> PO header is succefully created. Header Id - " . $poh->po_quote_header_id;
  } catch (Exception $e) {
   $dbc->rollback = true;
   echo "<br>Failed to save PO header.Error @ file" . __FILE__ . ' @@ L ' . __LINE__;
  }

  if (!empty($poh->po_header_id)) {
   //create PO line & details
   $this->_create_stdPOlines($poh, $po_purchasing_control_i);
  }
 }

 private function _convert_quote_toBPA() {
  global $dbc;

//   foreach($_POST['line_price'] as $amt_k => $amt_v ){
//    $header_amt += $amt_v;
//   }
  $poh = new po_header();


  foreach ($poh->field_a as $k => $v) {
   if (property_exists($this, $v)) {
    $poh->$v = $this->$v;
   }
  }
  $poh->po_type = 'BLANKET';
  $po_purchasing_control_i = po_purchasing_control::find_by_org_id($this->bu_org_id);
  $poh->bill_to_id = $po_purchasing_control_i->ship_to_id;
  $poh->ship_to_id = $po_purchasing_control_i->bill_to_id;
  if (!empty($poh->supplier_site_id)) {
   $supplier_site_details = supplier_site::find_by_id($poh->supplier_site_id);
   $poh->doc_currency = $supplier_site_details->currency;
   if (empty($poh->payment_term_id)) {
    $poh->payment_term_id = $supplier_site_details->payment_term_id;
   }
  }
  if (empty($poh->doc_currency)) {
   $poh->doc_currency = $poh->currency;
  }
  if (empty($poh->payment_term_id)) {
   $poh->payment_term_id = po_quote_purchasing_control::find_by_org_id($poh->bu_org_id)->payment_term_id;
  }
  $poh->exchange_rate_type = 'CORP';
  $poh->header_amount = .01;
  $poh->po_quote_status = 'ENTERED';
  try {
   $poh->_before_save();
   $poh->save();
   $poh->_after_save();
   $dbc->confirm();
   echo "<br> PO header is succefully created. Header Id - " . $poh->po_quote_header_id;
  } catch (Exception $e) {
   $dbc->rollback = true;
   echo "<br>Failed to save PO header.Error @ file" . __FILE__ . ' @@ L ' . __LINE__;
  }

  if (!empty($poh->po_header_id)) {
   //create PO line & details
   $this->_create_BPAlines($poh, $po_purchasing_control_i);
  }
 }

 private function _create_stdPOlines($poh, $po_purchasing_control_i) {
  global $dbc;
  $header_amount = 0;
  $quote_lines = po_quote_line::find_by_parent_id($this->po_quote_header_id);
  if (empty($quote_lines)) {
   echo "<br>Failed to create any PO line as no quote lines found.Error @ file" . __FILE__ . ' @@ L ' . __LINE__;
   return;
  }
  $line_number = 0;

  foreach ($quote_lines as $ql) {
   $line_number++;
   $po_line = new po_line();
   foreach ($po_line->field_a as $k => $v) {
    if (property_exists($ql, $v)) {
     $po_line->$v = $ql->$v;
    }
   }
   $po_line->po_header_id = $poh->po_header_id;
   $po_line->receving_org_id = $po_purchasing_control_i->default_inv_org_id;
   $po_line->line_number = $line_number;
   $po_line->line_type = $po_purchasing_control_i->default_line_type;
   $po_line->line_quantity = !empty($ql->minimum_order_quantity) ? $ql->minimum_order_quantity : 1;
   $po_line->unit_price = $ql->quote_unit_price;
   $po_line->line_price = $ql->quote_unit_price * $po_line->line_quantity;
   $header_amount += $po_line->line_price;
   try {
    $po_line->_before_save();
    $po_line->save();
    $po_line->_after_save();
    $dbc->confirm();
    echo "<br> PO Line is succefully created. Line Id - " . $poh->po_quote_header_id;
   } catch (Exception $e) {
    $dbc->rollback = true;
    echo "<br>Failed to save PO line.Error @ file" . __FILE__ . ' @@ L ' . __LINE__;
   }
   if (!empty($po_line->po_line_id)) {
    //create PO details
    $po_detail = new po_detail();
    $po_detail->po_header_id = $po_line->po_header_id;
    $po_detail->po_line_id = $po_line->po_line_id;
    $po_detail->shipment_number = 1;
    $po_detail->quantity = $po_line->line_quantity;
    $po_detail->need_by_date = current_time(1);
    $inv_org_details = inventory::find_by_org_id($po_line->receving_org_id);
    $po_detail->charge_ac_id = $inv_org_details->material_ac_id;
    $po_detail->accrual_ac_id = $inv_org_details->inv_ap_accrual_ac_id;
    $po_detail->ppv_ac_id = $inv_org_details->inv_ppv_ac_id;
    try {
     $po_detail->save();
    } catch (Exception $e) {
     echo "<br>Failed to save PO line.Error @ file" . __FILE__ . ' @@ L ' . __LINE__;
    }
   }
  }

  //update the header price
  $poh->header_amount = $header_amount;
  $poh->save();
 }

 private function _create_BPAlines($poh, $po_purchasing_control_i) {
  global $dbc;
  $header_amount = 0;
  $quote_lines = po_quote_line::find_by_parent_id($this->po_quote_header_id);
  if (empty($quote_lines)) {
   echo "<br>Failed to create any PO line as no quote lines found.Error @ file" . __FILE__ . ' @@ L ' . __LINE__;
   return;
  }
  $line_number = 0;

  foreach ($quote_lines as $ql) {
   $line_number++;
   $po_line = new po_line();
   foreach ($po_line->field_a as $k => $v) {
    if (property_exists($ql, $v)) {
     $po_line->$v = $ql->$v;
    }
   }
   $po_line->po_header_id = $poh->po_header_id;
   $po_line->receving_org_id = $po_purchasing_control_i->default_inv_org_id;
   $po_line->line_number = $line_number;
   $po_line->line_type = $po_purchasing_control_i->default_line_type;
   $po_line->line_quantity = !empty($ql->minimum_order_quantity) ? $ql->minimum_order_quantity : 1;
   $po_line->unit_price = $ql->quote_unit_price;
   $po_line->line_price = $ql->quote_unit_price * $po_line->line_quantity;
   $header_amount += $po_line->line_price;
   try {
    $po_line->_before_save();
    $po_line->save();
    $po_line->_after_save();
    $dbc->confirm();
    echo "<br> PO Line is succefully created. Line Id - " . $poh->po_quote_header_id;
   } catch (Exception $e) {
    $dbc->rollback = true;
    echo "<br>Failed to save PO line.Error @ file" . __FILE__ . ' @@ L ' . __LINE__;
   }
  }

  //update the header price
  $poh->header_amount = $header_amount;
  $poh->save();
 }

 public function notification_action($obj) {
  $this->findBy_id($obj->reference_key_value);
  if ($obj->notification_action == 'APPROVE') {
   try {
    $this->_approve_po($obj->to_user_id);
   } catch (Exception $e) {
    $this->rollback = true;
    echo "<br> Unable to complete the approval process " . $e->getMessage();
   }
  } else if ($obj->notification_action == 'REJECT') {
   $this->po_quote_status = 'REJECTED';
   $this->approved_by = $obj->to_user;
   $this->approved_date = current_time();
   $this->audit_trial();
   $this->update($this->po_quote_header_id);
  }
 }

 public function findAll_releases($ref_po_quote_header_id = '') {
  $ref_po_quote_header_id = empty($ref_po_quote_header_id) ? $this->ref_po_quote_header_id : $ref_po_quote_header_id;
  $sql = " SELECT * FROM " . self::$table_name;
  $sql .= " WHERE ref_po_quote_header_id = :ref_po_quote_header_id ";
  $value_a = ['ref_po_quote_header_id' => $ref_po_quote_header_id];
  $result = $this->findBySql($sql, $value_a);
  return !empty($result) ? $result : false;
 }

 public static function find_by_refPOHeaderId_releseNumber($ref_po_quote_header_id, $release_number) {
  $sql = " SELECT * FROM " . self::$table_name;
  $sql .= " WHERE ref_po_quote_header_id = '{$ref_po_quote_header_id}' AND release_number = '{$release_number}' LIMIT 1 ";
  $result = self::find_by_sql($sql);
  return !empty($result) ? array_pop($result) : false;
 }

 public function _find_relNumber($ref_po_quote_header_id = '') {
  $po_quote_header1 = $this->findBy_id($this->po_quote_header_id);
  if (!empty($po_quote_header1->release_number)) {
   return $po_quote_header1->release_number;
  }
  $ref_po_quote_header_id = empty($ref_po_quote_header_id) ? $this->ref_po_quote_header_id : $ref_po_quote_header_id;
  $sql = " SELECT MAX(release_number) as release_number FROM " . self::$table_name;
  $sql .= " WHERE ref_po_quote_header_id = :ref_po_quote_header_id ";
  $value_a = ['ref_po_quote_header_id' => $ref_po_quote_header_id];
  $result = $this->findBySql($sql, $value_a);
  return !empty($result) ? array_pop($result)->release_number + 1 : 1;
 }

//  public static function instantiate_extra_fields(&$array_of_objects) {
//   if (count($array_of_objects) > 0) {
//    foreach ($array_of_objects as &$this_object) {
//     $supplier_details = supplier::find_by_id($this_object->supplier_id);
//     $this_object->supplier_name = $supplier_details->supplier_name;
//     $this_object->supplier_number = $supplier_details->supplier_number;
//     $supplier_site_details = supplier_site::find_by_id($this_object->supplier_site_id);
//     $this_object->supplier_site_name = $supplier_site_details->supplier_site_name;
//    }
//   }
//   return $array_of_objects;
//  }

 Public static function po_quote_types() {
  $option_header = option_header::find_by_name('po_quote_TYPE');
  $po_quote_types = option_line::find_by_option_id($option_header->option_header_id);
  return $po_quote_types;
 }

 Public static function po_quote_status() {
  $option_header = option_header::find_by_name('po_quote_STATUS');
  $po_quote_status = option_line::find_by_option_id($option_header->option_header_id);
  return $po_quote_status;
 }

 public function copy($po_quote_header_id) {
  global $db;
  $sql1 = " CREATE TEMPORARY TABLE tmptable SELECT * FROM po_quote_header WHERE `po_quote_header_id` = '{$po_quote_header_id}' ";
  if ($db->query($sql1)) {
   $sql2 = "  UPDATE tmptable SET `po_quote_header_id` = '' ,
           `org_id` = '{$this->org_id}' 
          WHERE `po_quote_header_id` = '{$po_quote_header_id}' ";
   if ($db->query($sql2)) {
    $sql3 = " INSERT INTO `po_quote_header` SELECT * FROM tmptable WHERE `po_quote_header_id` = '' ";
    if ($db->query($sql3)) {
     $this->po_quote_header_id = $db->insert_id();
     $this->msg = 1;
    } else {
     $this->msg = 0;
    }
   }
  }
  return $this->msg;
 }

 public static function find_all_active_bpa($bu_org_id = '') {
  $sql = " SELECT poh.po_quote_header_id, poh.po_quote_number, sup.supplier_id, sup.supplier_name
            FROM po_quote_header poh
            LEFT JOIN supplier sup ON poh.supplier_id = sup.supplier_id";
  $sql .= " WHERE poh.po_quote_type = 'BLANKET' ";
  $sql .= " AND poh.po_quote_status = 'APPROVED' ";
//   $sql .= " AND poh.released_amount IS NULL ||  poh.released_amount < header_amount ";
  $sql .= " AND poh.aggrement_end_date IS NULL ||  poh.aggrement_end_date < CURDATE() ";
  if (!empty($bu_org_id)) {
   $sql .= " AND poh.bu_org_id = '{$bu_org_id}' ";
  }
  $result = self::find_by_sql($sql);
  return !empty($result) ? $result : false;
 }

//  public function save() {
//   $primary_column = static::$primary_column;
//   if (empty($this->$primary_column)) {
//    $this->po_quote_status = 'Entered';
//    $this->create();
//   } else {
//    $this->update($this->$primary_column);
//   }
//   return $this->msg;
//  }
 //multi select used for req to PO conversion

 public function multi_select_input_fields() {
  $multi_select_input = [
   'select_supplier_name',
   'supplier_site_name'
  ];
  return $multi_select_input;
 }

 public function multi_select_hidden_fields() {
  $multi_select_hidden = [
   'action_class_name',
   'mode',
   'action',
   'show_block',
  ];

  return $multi_select_hidden;
 }

}

//end of po_quote_header class
?>