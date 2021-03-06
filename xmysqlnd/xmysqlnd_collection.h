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
#ifndef XMYSQLND_COLLECTION_H
#define XMYSQLND_COLLECTION_H

#include "xmysqlnd_driver.h"
#include "xmysqlnd_crud_collection_commands.h"
#include "util/allocator.h"

namespace mysqlx {

namespace drv {

struct st_xmysqlnd_schema;
struct st_xmysqlnd_session_on_error_bind;

typedef struct st_xmysqlnd_collection		XMYSQLND_COLLECTION;
typedef struct st_xmysqlnd_collection_data	XMYSQLND_COLLECTION_DATA;


typedef enum_func_status (*func_xmysqlnd_collection__init)(
			XMYSQLND_COLLECTION * const collection,
			const MYSQLND_CLASS_METHODS_TYPE(xmysqlnd_object_factory) * const object_factory,
			st_xmysqlnd_schema* const schema,
			const MYSQLND_CSTRING collection_name,
			MYSQLND_STATS * const stats,
			MYSQLND_ERROR_INFO * const error_info);

typedef XMYSQLND_COLLECTION * (*func_xmysqlnd_collection__get_reference)(XMYSQLND_COLLECTION * const collection);
typedef enum_func_status		(*func_xmysqlnd_collection__exists_in_database)(XMYSQLND_COLLECTION * const collection, struct st_xmysqlnd_session_on_error_bind on_error, zval* exists);
typedef enum_func_status		(*func_xmysqlnd_collection__count)(XMYSQLND_COLLECTION * const collection, struct st_xmysqlnd_session_on_error_bind on_error, zval* counter);
typedef st_xmysqlnd_stmt* (*func_xmysqlnd_collection__add)(XMYSQLND_COLLECTION * const collection,  XMYSQLND_CRUD_COLLECTION_OP__ADD * crud_op);
typedef st_xmysqlnd_stmt* (*func_xmysqlnd_collection__remove)(XMYSQLND_COLLECTION * const collection, XMYSQLND_CRUD_COLLECTION_OP__REMOVE * op);
typedef st_xmysqlnd_stmt* (*func_xmysqlnd_collection__modify)(XMYSQLND_COLLECTION * const collection, XMYSQLND_CRUD_COLLECTION_OP__MODIFY * op);
typedef st_xmysqlnd_stmt* (*func_xmysqlnd_collection__find)(XMYSQLND_COLLECTION * const collection, XMYSQLND_CRUD_COLLECTION_OP__FIND * op);
typedef enum_func_status		(*func_xmysqlnd_collection__free_reference)(XMYSQLND_COLLECTION * const collection, MYSQLND_STATS * stats, MYSQLND_ERROR_INFO * error_info);
typedef void					(*func_xmysqlnd_collection__free_contents)(XMYSQLND_COLLECTION * const collection);
typedef void					(*func_xmysqlnd_collection__dtor)(XMYSQLND_COLLECTION * const collection, MYSQLND_STATS * stats, MYSQLND_ERROR_INFO * error_info);

MYSQLND_CLASS_METHODS_TYPE(xmysqlnd_collection)
{
	func_xmysqlnd_collection__init init;

	func_xmysqlnd_collection__exists_in_database exists_in_database;
	func_xmysqlnd_collection__count count;

	func_xmysqlnd_collection__add add;

	func_xmysqlnd_collection__remove remove;
	func_xmysqlnd_collection__modify modify;
	func_xmysqlnd_collection__find find;

	func_xmysqlnd_collection__get_reference get_reference;
	func_xmysqlnd_collection__free_reference free_reference;

	func_xmysqlnd_collection__free_contents free_contents;
	func_xmysqlnd_collection__dtor dtor;
};

struct st_xmysqlnd_collection_data : public util::permanent_allocable
{
	st_xmysqlnd_schema* schema;
	MYSQLND_STRING  collection_name;
	zend_bool       persistent;
	unsigned int	refcount;

	const MYSQLND_CLASS_METHODS_TYPE(xmysqlnd_object_factory) * object_factory;
	MYSQLND_CLASS_METHODS_TYPE(xmysqlnd_collection) m;

};


struct st_xmysqlnd_collection : public util::permanent_allocable
{
	XMYSQLND_COLLECTION_DATA * data;

	zend_bool		persistent;
};


PHP_MYSQL_XDEVAPI_API MYSQLND_CLASS_METHODS_INSTANCE_DECLARE(xmysqlnd_collection);
PHP_MYSQL_XDEVAPI_API XMYSQLND_COLLECTION * xmysqlnd_collection_create(st_xmysqlnd_schema* schema,
																  const MYSQLND_CSTRING collection_name,
																  const zend_bool persistent,
																  const MYSQLND_CLASS_METHODS_TYPE(xmysqlnd_object_factory) * const object_factory,
																  MYSQLND_STATS * const stats,
																  MYSQLND_ERROR_INFO * const error_info);

PHP_MYSQL_XDEVAPI_API void xmysqlnd_collection_free(XMYSQLND_COLLECTION * const schema, MYSQLND_STATS * stats, MYSQLND_ERROR_INFO * error_info);

} // namespace drv

} // namespace mysqlx

#endif /* XMYSQLND_COLLECTION_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
