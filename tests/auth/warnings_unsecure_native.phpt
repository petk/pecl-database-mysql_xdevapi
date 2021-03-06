--TEST--
mysqlx authentication mechanisms - unsecure mysql_native_password warnings
--SKIPIF--
--INI--
error_reporting=E_ALL
default_socket_timeout=4
--FILE--
<?php
require_once(__DIR__."/../connect.inc");
require_once(__DIR__."/auth_utils.inc");

// setup
$test_user = $Test_user_native;
reset_test_user($test_user, 'mysql_native_password');

test_unsecure_connection($test_user, 'sha256_memory', false, true);
test_unsecure_connection($test_user, 'plain', false, true);
test_unsecure_connection($test_user, 'external', false, true);
test_unsecure_connection($test_user, 'unsupported', false, true);

test_unsecure_connection($Test_user_unknown, null, false, true);
test_unsecure_connection($Test_user_unknown, 'mysql41', false, true);

verify_expectations();
print "done!\n";
?>
--CLEAN--
<?php
	require_once(__DIR__."/../connect.inc");
	clean_test_db();
?>
--EXPECTF--
mysqlx://mysql_xdevapi_test_user_native:mysql_xdevapi_test_user_native_password@%s/?ssl-mode=disabled&auth=sha256_memory

Warning: mysql_xdevapi\getSession(): [1045][HY000] Invalid user or password in %s
----------------------
mysqlx://mysql_xdevapi_test_user_native:mysql_xdevapi_test_user_native_password@%s/?ssl-mode=disabled&auth=plain

Warning: mysql_xdevapi\getSession(): [1251][HY000] Invalid authentication method PLAIN in %s
----------------------
mysqlx://mysql_xdevapi_test_user_native:mysql_xdevapi_test_user_native_password@%s/?ssl-mode=disabled&auth=external

Warning: mysql_xdevapi\getSession(): [1251][HY000] Invalid authentication method EXTERNAL in %s
----------------------
mysqlx://mysql_xdevapi_test_user_native:mysql_xdevapi_test_user_native_password@%s/?ssl-mode=disabled&auth=unsupported
----------------------
mysqlx://mysql_xdevapi_test_user_unknown:mysql_xdevapi_test_user_unknown_password@%s/?ssl-mode=disabled

Warning: mysql_xdevapi\getSession(): [HY000] Authentication failed using MYSQL41, SHA256_MEMORY. Check username and password or try a secure connection in %s
----------------------
mysqlx://mysql_xdevapi_test_user_unknown:mysql_xdevapi_test_user_unknown_password@%s/?ssl-mode=disabled&auth=mysql41

Warning: mysql_xdevapi\getSession(): [1045][HY000] Invalid user or password in %s
----------------------
done!%A
