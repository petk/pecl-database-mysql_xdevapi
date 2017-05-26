/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 2006-2017 The PHP Group                                |
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
extern "C" {
#include <php.h>
#undef ERROR
#undef inline
#include <ext/mysqlnd/mysqlnd.h>
#include <ext/mysqlnd/mysqlnd_debug.h>
#include <ext/mysqlnd/mysqlnd_alloc.h>
}
#include "xmysqlnd/xmysqlnd.h"
#include "xmysqlnd/xmysqlnd_node_session.h"
#include "xmysqlnd/xmysqlnd_node_schema.h"
#include "xmysqlnd/xmysqlnd_node_stmt.h"
#include "xmysqlnd/xmysqlnd_node_collection.h"
#include "xmysqlnd/xmysqlnd_crud_collection_commands.h"
#include "php_mysqlx.h"
#include "mysqlx_crud_operation_bindable.h"
#include "mysqlx_crud_operation_limitable.h"
#include "mysqlx_crud_operation_skippable.h"
#include "mysqlx_crud_operation_sortable.h"
#include "mysqlx_class_properties.h"
#include "mysqlx_exception.h"
#include "mysqlx_executable.h"
#include "mysqlx_expression.h"
#include "mysqlx_node_sql_statement.h"
#include "mysqlx_node_collection__modify.h"
#include "mysqlx_exception.h"
#include "phputils/allocator.h"
#include "phputils/object.h"

namespace mysqlx {

namespace devapi {

using namespace drv;

static zend_class_entry *mysqlx_node_collection__modify_class_entry;

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_node_collection__modify__sort, 0, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(no_pass_by_ref, sort_expr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_node_collection__modify__limit, 0, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_TYPE_INFO(no_pass_by_ref, rows, IS_LONG, dont_allow_null)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_node_collection__modify__skip, 0, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_TYPE_INFO(no_pass_by_ref, position, IS_LONG, dont_allow_null)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_node_collection__modify__bind, 0, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_TYPE_INFO(no_pass_by_ref, placeholder_values, IS_ARRAY, dont_allow_null)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_node_collection__modify__set, 0, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_TYPE_INFO(no_pass_by_ref, collection_field, IS_STRING, dont_allow_null)
	ZEND_ARG_INFO(no_pass_by_ref, expression_or_literal)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_node_collection__modify__unset, 0, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(no_pass_by_ref, variables)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_node_collection__modify__replace, 0, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_TYPE_INFO(no_pass_by_ref, collection_field, IS_STRING, dont_allow_null)
	ZEND_ARG_INFO(no_pass_by_ref, expression_or_literal)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_node_collection__modify__merge, 0, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_TYPE_INFO(no_pass_by_ref, document, IS_STRING, dont_allow_null)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_node_collection__modify__array_insert, 0, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_TYPE_INFO(no_pass_by_ref, collection_field, IS_STRING, dont_allow_null)
	ZEND_ARG_INFO(no_pass_by_ref, expression_or_literal)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_node_collection__modify__array_append, 0, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_TYPE_INFO(no_pass_by_ref, collection_field, IS_STRING, dont_allow_null)
	ZEND_ARG_INFO(no_pass_by_ref, expression_or_literal)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_node_collection__modify__array_delete, 0, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_TYPE_INFO(no_pass_by_ref, collection_field, IS_STRING, dont_allow_null)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_node_collection__modify__execute, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()


struct st_mysqlx_node_collection__modify : public phputils::custom_allocable
{
	XMYSQLND_CRUD_COLLECTION_OP__MODIFY * crud_op;
	XMYSQLND_NODE_COLLECTION * collection;
};


#define MYSQLX_FETCH_NODE_COLLECTION_FROM_ZVAL(_to, _from) \
{ \
	const struct st_mysqlx_object * const mysqlx_object = Z_MYSQLX_P((_from)); \
	(_to) = (struct st_mysqlx_node_collection__modify *) mysqlx_object->ptr; \
	if (!(_to) || !(_to)->collection) { \
		php_error_docref(NULL, E_WARNING, "invalid object of class %s", ZSTR_VAL(mysqlx_object->zo.ce->name)); \
		DBG_VOID_RETURN; \
	} \
} \


/* {{{ mysqlx_node_collection__modify::__construct */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, __construct)
{
}
/* }}} */


/* {{{ proto mixed mysqlx_node_collection__modify::sort() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, sort)
{
	struct st_mysqlx_node_collection__modify * object;
	zval * object_zv;
	zval * sort_expr = NULL;
	int    num_of_expr = 0;
	int    i = 0;

	DBG_ENTER("mysqlx_node_collection__modify::sort");

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O+",
									&object_zv,
									mysqlx_node_collection__modify_class_entry,
									&sort_expr,
									&num_of_expr))
	{
		DBG_VOID_RETURN;
	}


	MYSQLX_FETCH_NODE_COLLECTION_FROM_ZVAL(object, object_zv);

	RETVAL_FALSE;

	if (!( object->crud_op && sort_expr ) ) {
		DBG_VOID_RETURN;
	}

	for( i = 0 ; i < num_of_expr ; ++i ) {
		switch (Z_TYPE(sort_expr[i])) {
		case IS_STRING:
			{
				const MYSQLND_CSTRING sort_expr_str = { Z_STRVAL(sort_expr[i]),
												Z_STRLEN(sort_expr[i]) };
				if (PASS == xmysqlnd_crud_collection_modify__add_sort(object->crud_op,
															sort_expr_str)) {
					ZVAL_COPY(return_value, object_zv);
				}
			}
			break;
		case IS_ARRAY:
			{
				zval * entry;
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL(sort_expr[i]), entry) {
					const MYSQLND_CSTRING sort_expr_str = { Z_STRVAL_P(entry),
													Z_STRLEN_P(entry) };
					if (Z_TYPE_P(entry) != IS_STRING) {
						RAISE_EXCEPTION(err_msg_wrong_param_1);
					}
					if (FAIL == xmysqlnd_crud_collection_modify__add_sort(object->crud_op,
														sort_expr_str)) {
						RAISE_EXCEPTION(err_msg_add_sort_fail);
					}
				} ZEND_HASH_FOREACH_END();
				ZVAL_COPY(return_value, object_zv);
			}
			break;
		default:
			RAISE_EXCEPTION(err_msg_wrong_param_3);
			break;
		}
	}
	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_node_collection__modify::limit() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, limit)
{
	struct st_mysqlx_node_collection__modify * object;
	zval * object_zv;
	zend_long rows;

	DBG_ENTER("mysqlx_node_collection__modify::limit");

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol",
												&object_zv, mysqlx_node_collection__modify_class_entry,
												&rows))
	{
		DBG_VOID_RETURN;
	}

	if (rows < 0) {
		RAISE_EXCEPTION(err_msg_wrong_param_2);
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_NODE_COLLECTION_FROM_ZVAL(object, object_zv);

	RETVAL_FALSE;

	if (object->crud_op) {
		if (PASS == xmysqlnd_crud_collection_modify__set_limit(object->crud_op, rows)) {
			ZVAL_COPY(return_value, object_zv);
		}
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_node_collection__modify::skip() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, skip)
{
	struct st_mysqlx_node_collection__modify * object;
	zval * object_zv;
	zend_long position;

	DBG_ENTER("mysqlx_node_collection__modify::skip");

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol",
												&object_zv, mysqlx_node_collection__modify_class_entry,
												&position))
	{
		DBG_VOID_RETURN;
	}

	if (position < 0) {
		RAISE_EXCEPTION(err_msg_wrong_param_2);
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_NODE_COLLECTION_FROM_ZVAL(object, object_zv);

	RETVAL_FALSE;

	if (object->crud_op) {
		if (PASS == xmysqlnd_crud_collection_modify__set_skip(object->crud_op, position)) {
			ZVAL_COPY(return_value, object_zv);
		}
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_node_collection__modify::bind() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, bind)
{
	struct st_mysqlx_node_collection__modify * object;
	zval * object_zv;
	HashTable * bind_variables;

	DBG_ENTER("mysqlx_node_collection__modify::bind");

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oh",
												&object_zv, mysqlx_node_collection__modify_class_entry,
												&bind_variables))
	{
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_NODE_COLLECTION_FROM_ZVAL(object, object_zv);

	RETVAL_FALSE;

	if (object->crud_op) {
		zend_string * key;
		zval * val;
		ZEND_HASH_FOREACH_STR_KEY_VAL(bind_variables, key, val) {
			if (key) {
				const MYSQLND_CSTRING variable = { ZSTR_VAL(key), ZSTR_LEN(key) };
				if (FAIL == xmysqlnd_crud_collection_modify__bind_value(object->crud_op, variable, val)) {
					RAISE_EXCEPTION(err_msg_bind_fail);
				}
			}
		} ZEND_HASH_FOREACH_END();
		ZVAL_COPY(return_value, object_zv);
	}
	DBG_VOID_RETURN;
}
/* }}} */


enum ModifyTwoParamOp
{
	TWO_PARAM_OP__SET,
	TWO_PARAM_OP__REPLACE,
	TWO_PARAM_OP__ARRAY_INSERT,
	TWO_PARAM_OP__ARRAY_APPEND
};

/* {{{ mysqlx_node_collection__modify__2_param_op */
static void
mysqlx_node_collection__modify__2_param_op(INTERNAL_FUNCTION_PARAMETERS, const enum ModifyTwoParamOp op_type)
{
	struct st_mysqlx_node_collection__modify * object;
	zval * object_zv;
	const zval * value;
	MYSQLND_CSTRING collection_field = {NULL, 0};
	zend_bool is_expression = FALSE;
	const zend_bool is_document = FALSE;

	DBG_ENTER("mysqlx_node_collection__modify__2_param_op");

	RETVAL_FALSE;

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Osz",
												&object_zv, mysqlx_node_collection__modify_class_entry,
												&(collection_field.s), &(collection_field.l),
												(zval *) &value))
	{
		DBG_VOID_RETURN;
	}
	switch (Z_TYPE_P(value)) {
		case IS_OBJECT:
			if (op_type == TWO_PARAM_OP__SET) {
				if (is_a_mysqlx_expression(value)) {
					/* get the string */
					value = get_mysqlx_expression(value);
					is_expression = TRUE;
				}
				break;
			}
			/* fall-through */
		case IS_STRING:
		case IS_DOUBLE:
		case IS_TRUE:
		case IS_FALSE:
		case IS_LONG:
		case IS_NULL:
			break;
		default:{
			RAISE_EXCEPTION(err_msg_invalid_type);
			DBG_VOID_RETURN;
		}

	}
	MYSQLX_FETCH_NODE_COLLECTION_FROM_ZVAL(object, object_zv);

	RETVAL_FALSE;

	if (object->crud_op) {
		enum_func_status ret = FAIL;
		switch (op_type) {
			case TWO_PARAM_OP__SET:
				ret = xmysqlnd_crud_collection_modify__set(object->crud_op, collection_field, value, is_expression, is_document);
				break;

			case TWO_PARAM_OP__REPLACE:
				ret = xmysqlnd_crud_collection_modify__replace(object->crud_op, collection_field, value, is_expression, is_document);
				break;

			case TWO_PARAM_OP__ARRAY_INSERT:
				ret = xmysqlnd_crud_collection_modify__array_insert(object->crud_op, collection_field, value);
				break;

			case TWO_PARAM_OP__ARRAY_APPEND:
				ret = xmysqlnd_crud_collection_modify__array_append(object->crud_op, collection_field, value);
				break;
		}

		if (PASS == ret) {
			ZVAL_COPY(return_value, object_zv);
		}
	}
	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_node_collection__modify::set() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, set)
{
	DBG_ENTER("mysqlx_node_collection__modify::set");
	mysqlx_node_collection__modify__2_param_op(INTERNAL_FUNCTION_PARAM_PASSTHRU, TWO_PARAM_OP__SET);
	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_node_collection__modify::replace() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, replace)
{
	DBG_ENTER("mysqlx_node_collection__modify::replace");
	mysqlx_node_collection__modify__2_param_op(INTERNAL_FUNCTION_PARAM_PASSTHRU, TWO_PARAM_OP__REPLACE);
	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_node_collection__modify::merge() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, merge)
{
	struct st_mysqlx_node_collection__modify * object;
	zval * object_zv;
	MYSQLND_CSTRING documentContents;

	DBG_ENTER("mysqlx_node_collection__modify::merge");

	if (FAILURE == zend_parse_method_parameters(
		ZEND_NUM_ARGS(), getThis(), "Os",
		&object_zv, mysqlx_node_collection__modify_class_entry,
		&(documentContents.s), &(documentContents.l)))
	{
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_NODE_COLLECTION_FROM_ZVAL(object, object_zv);

	RETVAL_FALSE;

	if (object->crud_op) {
		MYSQLND_CSTRING emptyDocPath = { NULL, 0 };
		zval zvDocumentContents;
		ZVAL_STRINGL(&zvDocumentContents, documentContents.s, documentContents.l);
		if (FAIL == xmysqlnd_crud_collection_modify__merge(object->crud_op, emptyDocPath, &zvDocumentContents)) {
			RAISE_EXCEPTION(err_msg_merge_fail);
		}
		ZVAL_COPY(return_value, object_zv);
	}
	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_node_collection__modify::arrayInsert() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, arrayInsert)
{
	DBG_ENTER("mysqlx_node_collection__modify::arrayInsert");
	mysqlx_node_collection__modify__2_param_op(INTERNAL_FUNCTION_PARAM_PASSTHRU, TWO_PARAM_OP__ARRAY_INSERT);
	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_node_collection__modify::arrayAppend() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, arrayAppend)
{
	DBG_ENTER("mysqlx_node_collection__modify::arrayAppend");
	mysqlx_node_collection__modify__2_param_op(INTERNAL_FUNCTION_PARAM_PASSTHRU, TWO_PARAM_OP__ARRAY_APPEND);
	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_node_collection__modify::arrayDelete() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, arrayDelete)
{
	struct st_mysqlx_node_collection__modify * object;
	zval * object_zv;
	MYSQLND_CSTRING arrayIndexPath;

	DBG_ENTER("mysqlx_node_collection__modify::arrayDelete");

	if (FAILURE == zend_parse_method_parameters(
		ZEND_NUM_ARGS(), getThis(), "Os",
		&object_zv, mysqlx_node_collection__modify_class_entry,
		&(arrayIndexPath.s), &(arrayIndexPath.l)))
	{
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_NODE_COLLECTION_FROM_ZVAL(object, object_zv);

	RETVAL_FALSE;

	if (object->crud_op) {
		if (FAIL == xmysqlnd_crud_collection_modify__array_delete(object->crud_op, arrayIndexPath)) {
			RAISE_EXCEPTION(err_msg_arridx_del_fail);
		}
		ZVAL_COPY(return_value, object_zv);
	}
	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_node_collection__modify::unset() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, unset)
{
	struct st_mysqlx_node_collection__modify * object;
	zval * object_zv;
	zval * variables = NULL;
	zend_bool op_failed = FALSE;
	int    num_of_variables = 0, i = 0;

	DBG_ENTER("mysqlx_node_collection__modify::unset");

	if (FAILURE == zend_parse_method_parameters(
		ZEND_NUM_ARGS(), getThis(), "O+",
		&object_zv,
		mysqlx_node_collection__modify_class_entry,
		&variables,
		&num_of_variables))
	{
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_NODE_COLLECTION_FROM_ZVAL(object, object_zv);

	RETVAL_FALSE;

	if ( !object->crud_op || num_of_variables <= 0) {
		DBG_VOID_RETURN;
	}

	for( i = 0 ; i < num_of_variables; ++i ) {
		switch (Z_TYPE(variables[i]))
		{
		case IS_STRING:
			{
				const MYSQLND_CSTRING variable = { Z_STRVAL(variables[i]),
										Z_STRLEN(variables[i]) };
				if (FAIL == xmysqlnd_crud_collection_modify__unset(object->crud_op,
																variable)) {
						RAISE_EXCEPTION(err_msg_unset_fail);
				}
			}
			break;
		case IS_ARRAY:
			{
				zval * entry;
				enum_func_status ret = FAIL;
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL(variables[i]), entry) {
					if (Z_TYPE_P(entry) != IS_STRING) {
						RAISE_EXCEPTION(err_msg_wrong_param_1);
					}
					const MYSQLND_CSTRING variable = { Z_STRVAL_P(entry),
											Z_STRLEN_P(entry) };
					if (FAIL == xmysqlnd_crud_collection_modify__unset(object->crud_op,
																	variable)) {
							RAISE_EXCEPTION(err_msg_unset_fail);
					}
				} ZEND_HASH_FOREACH_END();
			}
			break;
		default:
			RAISE_EXCEPTION(err_msg_wrong_param_3);
			break;
		}
	}

	ZVAL_COPY(return_value, object_zv);
	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_node_collection__modify::execute() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_node_collection__modify, execute)
{
	struct st_mysqlx_node_collection__modify * object;
	zval * object_zv;

	DBG_ENTER("mysqlx_node_collection__modify::execute");

	if (FAILURE == zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O",
												&object_zv, mysqlx_node_collection__modify_class_entry))
	{
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_NODE_COLLECTION_FROM_ZVAL(object, object_zv);

	RETVAL_FALSE;

	DBG_INF_FMT("crud_op=%p collection=%p", object->crud_op, object->collection);
	if (object->crud_op && object->collection) {
		if (FALSE == xmysqlnd_crud_collection_modify__is_initialized(object->crud_op)) {
			RAISE_EXCEPTION(err_msg_modify_fail);
		} else {
			XMYSQLND_NODE_STMT * stmt = object->collection->data->m.modify(object->collection, object->crud_op);
			if (stmt) {
				zval stmt_zv;
				ZVAL_UNDEF(&stmt_zv);
				mysqlx_new_node_stmt(&stmt_zv, stmt);
				if (Z_TYPE(stmt_zv) == IS_NULL) {
					xmysqlnd_node_stmt_free(stmt, NULL, NULL);
				}
				if (Z_TYPE(stmt_zv) == IS_OBJECT) {
					zval zv;
					ZVAL_UNDEF(&zv);
					zend_long flags = 0;
					mysqlx_node_statement_execute_read_response(Z_MYSQLX_P(&stmt_zv), flags, MYSQLX_RESULT, &zv);

					ZVAL_COPY(return_value, &zv);
					zval_dtor(&zv);
				}
				zval_ptr_dtor(&stmt_zv);
			}
		}
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ mysqlx_node_collection__modify_methods[] */
static const zend_function_entry mysqlx_node_collection__modify_methods[] = {
	PHP_ME(mysqlx_node_collection__modify, 	__construct,	NULL,												ZEND_ACC_PRIVATE)

	PHP_ME(mysqlx_node_collection__modify,	bind,		arginfo_mysqlx_node_collection__modify__bind,			ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_node_collection__modify,	sort,		arginfo_mysqlx_node_collection__modify__sort,			ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_node_collection__modify,	limit,		arginfo_mysqlx_node_collection__modify__limit,			ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_node_collection__modify,	skip,		arginfo_mysqlx_node_collection__modify__skip,			ZEND_ACC_PUBLIC)

	PHP_ME(mysqlx_node_collection__modify,	set,		arginfo_mysqlx_node_collection__modify__set,			ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_node_collection__modify,	unset,		arginfo_mysqlx_node_collection__modify__unset,			ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_node_collection__modify,	replace,	arginfo_mysqlx_node_collection__modify__replace,		ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_node_collection__modify,	merge,		arginfo_mysqlx_node_collection__modify__merge,			ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_node_collection__modify,	arrayInsert,arginfo_mysqlx_node_collection__modify__array_insert,	ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_node_collection__modify,	arrayAppend,arginfo_mysqlx_node_collection__modify__array_append,	ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_node_collection__modify,	arrayDelete,arginfo_mysqlx_node_collection__modify__array_delete,	ZEND_ACC_PUBLIC)

	PHP_ME(mysqlx_node_collection__modify,	execute,	arginfo_mysqlx_node_collection__modify__execute,		ZEND_ACC_PUBLIC)

	{NULL, NULL, NULL}
};
/* }}} */


static zend_object_handlers mysqlx_object_node_collection__modify_handlers;
static HashTable mysqlx_node_collection__modify_properties;

const struct st_mysqlx_property_entry mysqlx_node_collection__modify_property_entries[] =
{
	{{NULL,	0}, NULL, NULL}
};

/* {{{ mysqlx_node_collection__modify_free_storage */
static void
mysqlx_node_collection__modify_free_storage(zend_object * object)
{
	struct st_mysqlx_object * mysqlx_object = mysqlx_fetch_object_from_zo(object);
	struct st_mysqlx_node_collection__modify * inner_obj = (struct st_mysqlx_node_collection__modify *) mysqlx_object->ptr;

	if (inner_obj) {
		if (inner_obj->collection) {
			xmysqlnd_node_collection_free(inner_obj->collection, NULL, NULL);
			inner_obj->collection = NULL;
		}
		if (inner_obj->crud_op) {
			xmysqlnd_crud_collection_modify__destroy(inner_obj->crud_op);
			inner_obj->crud_op = NULL;
		}
		mnd_efree(inner_obj);
	}
	mysqlx_object_free_storage(object);
}
/* }}} */


/* {{{ php_mysqlx_node_collection__modify_object_allocator */
static zend_object *
php_mysqlx_node_collection__modify_object_allocator(zend_class_entry * class_type)
{
	DBG_ENTER("php_mysqlx_collection__modify_object_allocator");
	st_mysqlx_object* mysqlx_object = phputils::alloc_object<st_mysqlx_node_collection__modify>(
		class_type,
		&mysqlx_object_node_collection__modify_handlers,
		&mysqlx_node_collection__modify_properties);
	DBG_RETURN(&mysqlx_object->zo);
}
/* }}} */


/* {{{ mysqlx_register_node_collection__modify_class */
void
mysqlx_register_node_collection__modify_class(INIT_FUNC_ARGS, zend_object_handlers * mysqlx_std_object_handlers)
{
	mysqlx_object_node_collection__modify_handlers = *mysqlx_std_object_handlers;
	mysqlx_object_node_collection__modify_handlers.free_obj = mysqlx_node_collection__modify_free_storage;

	{
		zend_class_entry tmp_ce;
		INIT_NS_CLASS_ENTRY(tmp_ce, "mysql_xdevapi", "NodeCollectionModify", mysqlx_node_collection__modify_methods);
		tmp_ce.create_object = php_mysqlx_node_collection__modify_object_allocator;
		mysqlx_node_collection__modify_class_entry = zend_register_internal_class(&tmp_ce);
		zend_class_implements(mysqlx_node_collection__modify_class_entry, 5,
							  mysqlx_executable_interface_entry,
							  mysqlx_crud_operation_bindable_interface_entry,
							  mysqlx_crud_operation_limitable_interface_entry,
							  mysqlx_crud_operation_skippable_interface_entry,
							  mysqlx_crud_operation_sortable_interface_entry);
	}

	zend_hash_init(&mysqlx_node_collection__modify_properties, 0, NULL, mysqlx_free_property_cb, 1);

	/* Add name + getter + setter to the hash table with the properties for the class */
	mysqlx_add_properties(&mysqlx_node_collection__modify_properties, mysqlx_node_collection__modify_property_entries);
}
/* }}} */


/* {{{ mysqlx_unregister_node_collection__modify_class */
void
mysqlx_unregister_node_collection__modify_class(SHUTDOWN_FUNC_ARGS)
{
	zend_hash_destroy(&mysqlx_node_collection__modify_properties);
}
/* }}} */


/* {{{ mysqlx_new_node_collection__modify */
void
mysqlx_new_node_collection__modify(
	zval* return_value,
	const phputils::string_input_param& search_expression,
	XMYSQLND_NODE_COLLECTION* collection)
{
	DBG_ENTER("mysqlx_new_node_collection__modify");

	if (SUCCESS == object_init_ex(return_value, mysqlx_node_collection__modify_class_entry) && IS_OBJECT == Z_TYPE_P(return_value)) {
		const struct st_mysqlx_object * const mysqlx_object = Z_MYSQLX_P(return_value);
		struct st_mysqlx_node_collection__modify * const object = (struct st_mysqlx_node_collection__modify *) mysqlx_object->ptr;
		if (!object) {
			goto err;
		}
		object->collection = collection->data->m.get_reference(collection);
		object->crud_op = xmysqlnd_crud_collection_modify__create(mnd_str2c(object->collection->data->schema->data->schema_name),
																  mnd_str2c(object->collection->data->collection_name));
		if (!object->crud_op) {
			goto err;
		}
		if (search_expression.empty() ||
			(FAIL == xmysqlnd_crud_collection_modify__set_criteria(object->crud_op, search_expression.to_std_string())))
		{
			goto err;
		}
		goto end;
err:
		DBG_ERR("Error");
		php_error_docref(NULL, E_WARNING, "invalid object of class %s", ZSTR_VAL(mysqlx_object->zo.ce->name));
		zval_ptr_dtor(return_value);
		ZVAL_NULL(return_value);
	}
end:

	DBG_VOID_RETURN;
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