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
  | Authors: Andrey Hristov <andrey@mysql.com>                           |
  +----------------------------------------------------------------------+
*/
#include "php_api.h"
extern "C" {
#include <ext/mysqlnd/mysqlnd.h>
#include <ext/mysqlnd/mysqlnd_debug.h>
#include <ext/mysqlnd/mysqlnd_alloc.h>
#include <ext/mysqlnd/mysqlnd_statistics.h>
}
#include "xmysqlnd/xmysqlnd.h"
#include "xmysqlnd/xmysqlnd_session.h"
#include "xmysqlnd/xmysqlnd_zval2any.h"
#include "php_mysqlx.h"
#include "mysqlx_class_properties.h"
#include "mysqlx_session.h"
#include "mysqlx_message__capability.h"
#include "mysqlx_message__capabilities.h"

#include "util/object.h"

namespace mysqlx {

namespace devapi {

namespace msg {

using namespace drv;

zend_class_entry *mysqlx_message__capabilities_class_entry;


ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_capabilities__add, 0, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_TYPE_INFO(0, capability, IS_OBJECT, 0)
ZEND_END_ARG_INFO()


/* {{{ proto bool mysqlx_connection::echo(object capability) */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_message__capabilities, add)
{
	zval* capabilities_zv{nullptr};
	st_mysqlx_message__capabilities* capabilities{nullptr};
	zval* capability_zv{nullptr};

	DBG_ENTER("mysqlx_connection::add");
	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OO",
												&capabilities_zv, mysqlx_message__capabilities_class_entry,
												&capability_zv, mysqlx_message__capability_class_entry))
	{
		DBG_VOID_RETURN;
	}
	MYSQLX_FETCH_MESSAGE__CAPABILITIES_FROM_ZVAL(capabilities, capabilities_zv);
	if (Z_REFCOUNTED_P(capability_zv)) {
		Z_ADDREF_P(capability_zv);
	}
	zend_hash_next_index_insert(&capabilities->capabilities_ht, capability_zv);
	RETVAL_ZVAL(capabilities_zv, 1 /*copy*/, 0 /*dtor*/);
	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ mysqlx_message__capabilities_methods[] */
static const zend_function_entry mysqlx_message__capabilities_methods[] = {
	PHP_ME(mysqlx_message__capabilities, add,			arginfo_mysqlx_capabilities__add,			ZEND_ACC_PUBLIC)
	{nullptr, nullptr, nullptr}
};
/* }}} */


static zend_object_handlers mysqlx_object_message__capabilities_handlers;
static HashTable mysqlx_message__capabilities_properties;


/* {{{ mysqlx_message__capabilities_free_storage */
static void
mysqlx_message__capabilities_free_storage(zend_object * object)
{
	st_mysqlx_object* mysqlx_object = mysqlx_fetch_object_from_zo(object);
	st_mysqlx_message__capabilities* message = (st_mysqlx_message__capabilities*) mysqlx_object->ptr;

	if (message) {
		zend_hash_destroy(&message->capabilities_ht);
		delete message;
	}
	mysqlx_object_free_storage(object);
}
/* }}} */


/* {{{ php_mysqlx_message__capabilities_object_allocator */
static zend_object *
php_mysqlx_message__capabilities_object_allocator(zend_class_entry * class_type)
{
	const zend_bool persistent = FALSE;
	st_mysqlx_object* mysqlx_object = (st_mysqlx_object*) mnd_pecalloc(1, sizeof(struct st_mysqlx_object) + zend_object_properties_size(class_type), persistent);
	st_mysqlx_message__capabilities* message = new struct st_mysqlx_message__capabilities;

	DBG_ENTER("php_mysqlx_message__capabilities_object_allocator");
	if (mysqlx_object && message) {
		mysqlx_object->ptr = message;

		message->persistent = persistent;
		zend_hash_init(&message->capabilities_ht, 0, nullptr /*hashfunc*/, ZVAL_PTR_DTOR, persistent);

		zend_object_std_init(&mysqlx_object->zo, class_type);
		object_properties_init(&mysqlx_object->zo, class_type);

		mysqlx_object->zo.handlers = &mysqlx_object_message__capabilities_handlers;
		mysqlx_object->properties = &mysqlx_message__capabilities_properties;

		DBG_RETURN(&mysqlx_object->zo);
	}
	if (message) {
		zend_hash_destroy(&message->capabilities_ht);
		delete message;
	}
	if (mysqlx_object) {
		mnd_pefree(mysqlx_object, persistent);
	}
	DBG_RETURN(nullptr);
}
/* }}} */


/* {{{ mysqlx_register_message__capabilities_class */
void
mysqlx_register_message__capabilities_class(INIT_FUNC_ARGS, zend_object_handlers * mysqlx_std_object_handlers)
{
	mysqlx_object_message__capabilities_handlers = *mysqlx_std_object_handlers;
	mysqlx_object_message__capabilities_handlers.free_obj = mysqlx_message__capabilities_free_storage;

	{
		zend_class_entry tmp_ce;
		INIT_CLASS_ENTRY(tmp_ce, "mysqlx_message__capabilities", mysqlx_message__capabilities_methods);
//		INIT_NS_CLASS_ENTRY(tmp_ce, "mysql_xdevapi", "message__capabilities", mysqlx_message__capabilities_methods);
		tmp_ce.create_object = php_mysqlx_message__capabilities_object_allocator;
		mysqlx_message__capabilities_class_entry = zend_register_internal_class(&tmp_ce);
	}

	zend_hash_init(&mysqlx_message__capabilities_properties, 0, nullptr, mysqlx_free_property_cb, 1);
}
/* }}} */


/* {{{ mysqlx_unregister_message__capabilities_class */
void
mysqlx_unregister_message__capabilities_class(SHUTDOWN_FUNC_ARGS)
{
	zend_hash_destroy(&mysqlx_message__capabilities_properties);
}
/* }}} */

} // namespace msg

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
