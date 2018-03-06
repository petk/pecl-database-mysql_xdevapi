--TEST--
mysqlx table waiting options - shared, exclusive, nowait
--SKIPIF--
--INI--
error_reporting=E_ALL
--FILE--
<?php
require_once(__DIR__."/../../connect.inc");
require_once(__DIR__."/../row_locking_utils.inc");

assert_mysql_xdevapi_loaded();

$session = mysql_xdevapi\getSession($connection_uri);
$table = create_test_table($session);

$worker_process = run_worker(__FILE__);
if (is_resource($worker_process)) {
	recv_worker_started();

	// Call lockShared and worker tries to read a document locked using lockExclusive
	// and the 'NOWAIT' waiting option.
	// terminal/cmd 1
	$session->startTransaction();
	check_select_lock_one($table, '1', 1, $Lock_shared);

	send_let_worker_run_cmd();
 	recv_worker_ran_cmd();

	// terminal/cmd 1
	$session->commit();
	// commit the transaction open

	send_let_worker_rollback();
	recv_worker_rolled_back();

	send_let_worker_end();
}

verify_expectations();
print "done!\n";
?>
--CLEAN--
<?php
	require(__DIR__."/../../connect.inc");
	clean_test_db();
?>
--EXPECTF--
worker cmd-line:%s
worker started
let worker run cmd
worker ran cmd
let worker rollback
worker rolled back
let worker end
done!%A
