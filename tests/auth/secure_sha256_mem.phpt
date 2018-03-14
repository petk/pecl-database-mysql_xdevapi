--TEST--
mysqlx authentication mechanisms - secure caching_sha2_password
--SKIPIF--
--INI--
error_reporting=1
default_socket_timeout=4
--FILE--
<?php
require_once(__DIR__."/../connect.inc");
require_once(__DIR__."/auth_utils.inc");

// setup
$test_user = 'user_sha256_mem';

$ssl_query = prepare_ssl_query();

// ----------
reset_test_user($test_user, 'caching_sha2_password');

test_secure_connection($test_user, 'shA256_Memory', false);
// will login with PLAIN
test_secure_connection($test_user, null);
test_secure_connection($test_user, 'MYSQL41', false);
test_secure_connection($test_user, 'sHA256_MEMORy');
test_secure_connection($test_user, 'PLAIN');
test_secure_connection($test_user, 'SHA256_MEMORY');
test_secure_connection($test_user, 'EXTERNAL', false);
test_secure_connection($test_user, 'UNSUPPORTED', false);

// ----------
reset_test_user($test_user, 'caching_sha2_password');

test_secure_connection($test_user, 'mysql41', false);
test_secure_connection($test_user, 'plain');
test_secure_connection($test_user, 'sha256_memory');
test_secure_connection($test_user, 'external', false);
test_secure_connection($test_user, 'nonworking', false);
test_secure_connection($test_user, null);

// ----------
reset_test_user($test_user, 'caching_sha2_password');

test_secure_connection($test_user, 'MySQL41', false);
test_secure_connection($test_user, 'plAin');
test_secure_connection($test_user, 'ShA256_MeMorY');
test_secure_connection($test_user, 'ExTeRnAl', false);
test_secure_connection($test_user, 'NonSupporteD', false);

verify_expectations();
print "done!\n";
?>
--CLEAN--
<?php
	require_once(__DIR__."/../connect.inc");
	clean_test_db();
?>
--EXPECTF--
done!%A