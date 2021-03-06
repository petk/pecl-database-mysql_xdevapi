/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 2006-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Andrey Hristov <andrey@php.net>                             |
  +----------------------------------------------------------------------+
*/
#include "php_api.h"
extern "C" {
#include <ext/mysqlnd/mysqlnd.h>
#include <ext/mysqlnd/mysqlnd_alloc.h>
}
#include "php_mysqlx.h"
#include "mysqlx_object.h"
#include "mysqlx_class_properties.h"

namespace mysqlx {

namespace devapi {

/* {{{ mysqlx_fetch_object_from_zo */
st_mysqlx_object* mysqlx_fetch_object_from_zo(zend_object * obj)
{
	/* Go back `XtOffsetOf of zo in st_mysqlx_object` bytes from `obj`  */
	return (st_mysqlx_object*)((char*)(obj) - XtOffsetOf(struct st_mysqlx_object, zo));
}
/* }}} */


/* {{{ mysqlx_object_free_storage */
void
mysqlx_object_free_storage(zend_object * object)
{
	st_mysqlx_object* mysqlx_object = mysqlx_fetch_object_from_zo(object);
	zend_object_std_dtor(&mysqlx_object->zo);
}
/* }}} */


/* {{{ mysqlx_object_get_debug_info */
HashTable *
mysqlx_object_get_debug_info(zval *object, int *is_temp)
{
	st_mysqlx_object* mysqlx_obj = Z_MYSQLX_P(object);
	HashTable *retval;

	ALLOC_HASHTABLE(retval);
	ZEND_INIT_SYMTABLE_EX(retval, zend_hash_num_elements(mysqlx_obj->properties) + 1, 0);

	void* raw_property{nullptr};
	ZEND_HASH_FOREACH_PTR(mysqlx_obj->properties, raw_property) {
		st_mysqlx_property* property = static_cast<st_mysqlx_property*>(raw_property);
		zval rv, member;
		zval* value{nullptr};

		ZVAL_STR(&member, property->name);

		value = mysqlx_property_get_value(object, &member, BP_VAR_IS, 0, &rv);

		if (value != &EG(uninitialized_zval)) {
			zend_hash_add(retval, Z_STR(member), value);
		}
	} ZEND_HASH_FOREACH_END();

	*is_temp = 1;
	return retval;
}
/* }}} */

} // namespace devapi

} // namespace mysqlx

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
