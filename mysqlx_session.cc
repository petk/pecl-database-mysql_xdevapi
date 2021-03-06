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
#include <ext/mysqlnd/mysqlnd_debug.h>
#include <ext/mysqlnd/mysqlnd_alloc.h>
#include <ext/standard/url.h>
}
#include "xmysqlnd/xmysqlnd.h"
#include "xmysqlnd/xmysqlnd_session.h"
#include "xmysqlnd/xmysqlnd_schema.h"
#include "xmysqlnd/xmysqlnd_stmt.h"
#include "xmysqlnd/xmysqlnd_stmt_result.h"
#include "xmysqlnd/xmysqlnd_stmt_result_meta.h"
#include "xmysqlnd/xmysqlnd_utils.h"
#include "php_mysqlx.h"
#include "mysqlx_exception.h"
#include "mysqlx_class_properties.h"
#include "mysqlx_session.h"
#include "mysqlx_schema.h"
#include "mysqlx_sql_statement.h"
#include "util/object.h"
#include "util/string_utils.h"

namespace mysqlx {

namespace devapi {

using namespace drv;

zend_class_entry *mysqlx_session_class_entry;

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__create_schema, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__drop_schema, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__get_server_version, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__get_client_id, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__generate_uuid, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__sql, 0, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_TYPE_INFO(no_pass_by_ref, query, IS_STRING, dont_allow_null)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__quote_name, 0, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_TYPE_INFO(no_pass_by_ref, name, IS_STRING, dont_allow_null)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__get_schemas, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__get_schema, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__list_clients, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__start_transaction, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__commit, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__rollback, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__set_savepoint, 0, ZEND_RETURN_VALUE, 0)
		ZEND_ARG_INFO(no_pass_by_ref, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__rollback_to, 0, ZEND_RETURN_VALUE, 0)
		ZEND_ARG_TYPE_INFO(no_pass_by_ref, name, IS_STRING, dont_allow_null)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__release_savepoint, 0, ZEND_RETURN_VALUE, 0)
		ZEND_ARG_TYPE_INFO(no_pass_by_ref, name, IS_STRING, dont_allow_null)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__kill_client, 0, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_TYPE_INFO(no_pass_by_ref, client_id, IS_LONG, dont_allow_null)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_mysqlx_session__close, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

#define MYSQLX_FETCH_SESSION_FROM_ZVAL(_to, _from) \
{ \
	const st_mysqlx_object* const mysqlx_object = Z_MYSQLX_P((_from)); \
	(_to) = (st_mysqlx_session*) mysqlx_object->ptr; \
        if (!(_to) && !(_to)->session) { \
		if ((_to)->closed) { \
			php_error_docref(nullptr, E_WARNING, "closed session"); \
		} else { \
			php_error_docref(nullptr, E_WARNING, "invalid object of class %s", ZSTR_VAL(mysqlx_object->zo.ce->name)); \
		} \
		RETVAL_NULL(); \
		DBG_VOID_RETURN; \
	} \
} \


/* {{{ mysqlx_throw_exception_from_session_if_needed */
static zend_bool
mysqlx_throw_exception_from_session_if_needed(const XMYSQLND_SESSION_DATA session)
{
	const unsigned int error_num = session->m->get_error_no(session);
	DBG_ENTER("mysqlx_throw_exception_from_session_if_needed");
	if (error_num) {
		MYSQLND_CSTRING sqlstate = { session->m->get_sqlstate(session) , 0 };
		MYSQLND_CSTRING errmsg = { session->m->get_error_str(session) , 0 };
		sqlstate.l = strlen(sqlstate.s);
		errmsg.l = strlen(errmsg.s);
		mysqlx_new_exception(error_num, sqlstate, errmsg);
		if(session->error_info->persistent == FALSE){
			SET_EMPTY_ERROR(session->error_info);
		}
		DBG_RETURN(TRUE);
	}
	DBG_RETURN(FALSE);
}
/* }}} */

/* {{{ proto mixed mysqlx_session::getServerVersion() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, getServerVersion)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};

	DBG_ENTER("mysqlx_session::getServerVersion");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object_zv, mysqlx_session_class_entry) == FAILURE) {
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);

	if (XMYSQLND_SESSION session = object->session) {
		RETVAL_LONG(session->m->get_server_version(session));
		mysqlx_throw_exception_from_session_if_needed(session->data);
	} else {
		RETVAL_FALSE;
	}

	DBG_VOID_RETURN;
}
/* }}} */

/* {{{ proto mixed mysqlx_session::getClientId() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, getClientId)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};

	DBG_ENTER("mysqlx_session::getClientId");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object_zv, mysqlx_session_class_entry) == FAILURE) {
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);

	if (XMYSQLND_SESSION session = object->session) {
		RETVAL_LONG(session->data->m->get_client_id(session->data));
		mysqlx_throw_exception_from_session_if_needed(session->data);
	} else {
		RETVAL_FALSE;
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_session::generateUUID() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, generateUUID)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};

	DBG_ENTER("mysqlx_session::generateUUID");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object_zv, mysqlx_session_class_entry) == FAILURE) {
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);

	RETVAL_FALSE;

	if (XMYSQLND_SESSION session = object->session) {
		auto uuid = session->session_uuid->generate();
		if (uuid.size() > 0) {
			RETVAL_STRINGL(uuid.data(), uuid.size());
		}
		mysqlx_throw_exception_from_session_if_needed(session->data);
	}

	DBG_VOID_RETURN;
}
/* }}} */

struct st_mysqlx_get_schemas_ctx
{
	zval* list;
};

/* {{{ get_schemas_handler_on_row */
static const enum_hnd_func_status
get_schemas_handler_on_row(void * context,
						   XMYSQLND_SESSION const session,
						   XMYSQLND_STMT * const stmt,
						   const XMYSQLND_STMT_RESULT_META * const meta,
						   const zval * const row,
						   MYSQLND_STATS * const stats,
						   MYSQLND_ERROR_INFO * const error_info)
{
	const st_mysqlx_get_schemas_ctx* ctx = (const st_mysqlx_get_schemas_ctx* ) context;
	DBG_ENTER("get_schemas_handler_on_row");
	if (ctx && ctx->list && row) {
		if (Z_TYPE_P(ctx->list) != IS_ARRAY) {
			array_init(ctx->list);
		}
		if (Z_TYPE_P(ctx->list) == IS_ARRAY) {
			const MYSQLND_CSTRING schema_name = { Z_STRVAL(row[0]), Z_STRLEN(row[0]) };
			XMYSQLND_SCHEMA * schema = session->m->create_schema_object(session, schema_name);
			if (schema) {
				zval zv;
				ZVAL_UNDEF(&zv);
				mysqlx_new_schema(&zv, schema);
				zend_hash_next_index_insert(Z_ARRVAL_P(ctx->list), &zv);
			}
		}
	}
	DBG_RETURN(HND_AGAIN);
}
/* }}} */


/* {{{ mysqlx_session_command_handler_on_error */
static const enum_hnd_func_status
mysqlx_session_command_handler_on_error(void * context,
											 XMYSQLND_SESSION session,
											 XMYSQLND_STMT * const stmt,
											 const unsigned int code,
											 const MYSQLND_CSTRING sql_state,
											 const MYSQLND_CSTRING message)
{
	DBG_ENTER("mysqlx_session_command_handler_on_error");
	if (session) {
				session->data->m->handler_on_error(session->data.get(), code, sql_state, message);
	}
	DBG_RETURN(HND_PASS_RETURN_FAIL);
}
/* }}} */


/* {{{ mysqlx_session::getSchemas() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, getSchemas)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};

	DBG_ENTER("mysqlx_session::getSchemas");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object_zv, mysqlx_session_class_entry) == FAILURE) {
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);
	RETVAL_FALSE;
	if (XMYSQLND_SESSION session = object->session) {
		const st_xmysqlnd_session_query_bind_variable_bind var_binder{ nullptr, nullptr };
		const MYSQLND_CSTRING list_query{ "SHOW DATABASES", sizeof("SHOW DATABASES") - 1 };
		zval list;
		st_mysqlx_get_schemas_ctx ctx{ &list };
		const st_xmysqlnd_session_on_result_start_bind on_result_start{ nullptr, nullptr };
		const st_xmysqlnd_session_on_row_bind on_row{ get_schemas_handler_on_row, &ctx };
		const st_xmysqlnd_session_on_warning_bind on_warning{ nullptr, nullptr };
		const st_xmysqlnd_session_on_error_bind on_error{ mysqlx_session_command_handler_on_error, nullptr };
		const st_xmysqlnd_session_on_result_end_bind on_result_end{ nullptr, nullptr };
		const st_xmysqlnd_session_on_statement_ok_bind on_statement_ok{ nullptr, nullptr };

		ZVAL_UNDEF(&list);

		if (PASS == session->m->query_cb(session, namespace_sql, list_query, var_binder, on_result_start, on_row, on_warning, on_error, on_result_end, on_statement_ok)) {
			ZVAL_COPY_VALUE(return_value, &list);
		} else {
			zval_dtor(&list);
			mysqlx_throw_exception_from_session_if_needed(session->data);
		}
	}
	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ mysqlx_session::getSchema(string name) */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, getSchema)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};
	util::string_view schema_name;

	DBG_ENTER("mysqlx_session::getSchema");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(),
									 getThis(),
									 "Os", &object_zv,
									 mysqlx_session_class_entry,
									&(schema_name.str), &(schema_name.len)) == FAILURE) {
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);
	if (XMYSQLND_SESSION session = object->session) {
		XMYSQLND_SCHEMA * schema = session->m->create_schema_object(session, schema_name.to_nd_cstr());
		if (schema) {
			mysqlx_new_schema(return_value, schema);
		} else {
			mysqlx_throw_exception_from_session_if_needed(session->data);
		}
	} else {
		RETVAL_FALSE;
	}

	DBG_VOID_RETURN;
}
/* }}} */

struct st_mysqlx_list_clients__ctx
{
	zval* list;
};

/* {{{ list_clients__handler_on_row */
static const enum_hnd_func_status
list_clients__handler_on_row(void * context,
							 XMYSQLND_SESSION session,
							 XMYSQLND_STMT * const stmt,
							 const XMYSQLND_STMT_RESULT_META * const meta,
							 const zval * const row,
							 MYSQLND_STATS * const stats,
							 MYSQLND_ERROR_INFO * const error_info)
{
	const st_mysqlx_list_clients__ctx* ctx = (const st_mysqlx_list_clients__ctx* ) context;
	DBG_ENTER("list_clients__handler_on_row");
	if (ctx && ctx->list && row) {
		if (Z_TYPE_P(ctx->list) != IS_ARRAY) {
			array_init(ctx->list);
		}
		if (Z_TYPE_P(ctx->list) == IS_ARRAY) {
			const unsigned int field_count = meta->m->get_field_count(meta);
			zval zv;
			ZVAL_UNDEF(&zv);
			array_init_size(&zv, field_count);

			for (unsigned int i{0}; i < field_count; ++i) {
				const XMYSQLND_RESULT_FIELD_META * field_meta = meta->m->get_field(meta, i);
				if (field_meta) {
					zend_hash_add(Z_ARRVAL(zv), field_meta->zend_hash_key.sname, (zval *)&(row[i]));
				}
			}
			zend_hash_next_index_insert(Z_ARRVAL_P(ctx->list), &zv);
		}
	}
	DBG_RETURN(HND_AGAIN);
}
/* }}} */


/* {{{ mysqlx_session::listClients() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, listClients)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};

	DBG_ENTER("mysqlx_session::listClients");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object_zv, mysqlx_session_class_entry) == FAILURE) {
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);
	RETVAL_FALSE;
	if (XMYSQLND_SESSION session = object->session) {
		const st_xmysqlnd_session_query_bind_variable_bind var_binder{ nullptr, nullptr };
		const MYSQLND_CSTRING list_query{ "list_clients", sizeof("list_clients") - 1 };
		zval list;
		st_mysqlx_list_clients__ctx ctx{ &list };
		const st_xmysqlnd_session_on_result_start_bind on_result_start{ nullptr, nullptr };
		const st_xmysqlnd_session_on_row_bind on_row{ list_clients__handler_on_row, &ctx };
		const st_xmysqlnd_session_on_warning_bind on_warning{ nullptr, nullptr };
		const st_xmysqlnd_session_on_error_bind on_error{ mysqlx_session_command_handler_on_error, nullptr };
		const st_xmysqlnd_session_on_result_end_bind on_result_end{ nullptr, nullptr };
		const st_xmysqlnd_session_on_statement_ok_bind on_statement_ok{ nullptr, nullptr };

		ZVAL_UNDEF(&list);

		if (PASS == session->m->query_cb(session, namespace_xplugin, list_query, var_binder, on_result_start, on_row, on_warning, on_error, on_result_end, on_statement_ok)) {
			ZVAL_COPY_VALUE(return_value, &list);
		} else {
			zval_dtor(&list);
			mysqlx_throw_exception_from_session_if_needed(session->data);
		}
	}
	DBG_VOID_RETURN;
}
/* }}} */



/* {{{ mysqlx_execute_session_query */
static void
mysqlx_execute_session_query(XMYSQLND_SESSION  session,
								  const MYSQLND_CSTRING namespace_,
								  const MYSQLND_CSTRING query,
								  const zend_long flags,
								  zval * const return_value,
								  const unsigned int argc,
								  const zval * args)
{
	XMYSQLND_STMT * stmt = session->m->create_statement_object(session);
	DBG_ENTER("mysqlx_execute_session_query");

	if (stmt) {
		zval stmt_zv;
		ZVAL_UNDEF(&stmt_zv);
		mysqlx_new_sql_stmt(&stmt_zv, stmt, namespace_, query);
		if (Z_TYPE(stmt_zv) == IS_NULL) {
			xmysqlnd_stmt_free(stmt, nullptr, nullptr);
		}
		if (Z_TYPE(stmt_zv) == IS_OBJECT) {
			zval zv;
			ZVAL_UNDEF(&zv);

			bool found{ false };
			for (unsigned int i{0}; i < argc; ++i) {
				ZVAL_UNDEF(&zv);
				mysqlx_sql_statement_bind_one_param(&stmt_zv, &args[i], &zv);
				if (Z_TYPE(zv) == IS_FALSE) {
					found = true;
					break;
				}
				zval_dtor(&zv);
			}
			if( false == found ) {
				ZVAL_UNDEF(&zv);

				mysqlx_sql_statement_execute(Z_MYSQLX_P(&stmt_zv), flags, &zv);

				ZVAL_COPY(return_value, &zv);
				zval_dtor(&zv);
			}
		}
		zval_ptr_dtor(&stmt_zv);
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_session::executeSql(string query [[, mixed param]]) */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, executeSql)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};
	MYSQLND_CSTRING query = {nullptr, 0};
	zval* args{nullptr};
	int argc{0};

	DBG_ENTER("mysqlx_session::executeSql");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Os*", &object_zv, mysqlx_session_class_entry,
																	   &(query.s), &(query.l),
																	   &args, &argc) == FAILURE)
	{
		DBG_VOID_RETURN;
	}

	RETVAL_FALSE;
	if (!query.l) {
		php_error_docref(nullptr, E_WARNING, "Empty query");
		DBG_VOID_RETURN;
	}
	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);

	if (object->session) {
		mysqlx_execute_session_query(object->session, namespace_sql, query, MYSQLX_EXECUTE_FLAG_BUFFERED, return_value, argc, args);
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_session::sql(string query) */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, sql)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};
	XMYSQLND_SESSION session;
	MYSQLND_CSTRING query = {nullptr, 0};

	DBG_ENTER("mysqlx_session::sql");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Os", &object_zv, mysqlx_session_class_entry,
																	   &(query.s), &(query.l)) == FAILURE)
	{
		DBG_VOID_RETURN;
	}

	if (!query.l) {
		php_error_docref(nullptr, E_WARNING, "Empty query");
		RETVAL_FALSE;
		DBG_VOID_RETURN;
	}
	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);

	if ((session = object->session)) {
		XMYSQLND_STMT * const stmt = session->m->create_statement_object(session);
		if (stmt) {
			mysqlx_new_sql_stmt(return_value, stmt, namespace_sql, query);
			if (Z_TYPE_P(return_value) == IS_NULL) {
				xmysqlnd_stmt_free(stmt, nullptr, nullptr);
				mysqlx_throw_exception_from_session_if_needed(session->data);
			}
		}
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_session::quoteName(string query) */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, quoteName)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};
	XMYSQLND_SESSION session;
	MYSQLND_CSTRING name = {nullptr, 0};

	DBG_ENTER("mysqlx_session::quoteName");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Os", &object_zv, mysqlx_session_class_entry,
																	   &(name.s), &(name.l)) == FAILURE)
	{
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);

	if ((session = object->session)) {
		MYSQLND_STRING quoted_name = session->data->m->quote_name(session->data, name);
		RETVAL_STRINGL(quoted_name.s, quoted_name.l);
		if (quoted_name.s) {
			mnd_efree(quoted_name.s);
		}
		mysqlx_throw_exception_from_session_if_needed(session->data);
	} else {
		RETVAL_FALSE;
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ mysqlx_session::createSchema(string name) */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, createSchema)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};
	MYSQLND_CSTRING schema_name = {nullptr, 0};

	DBG_ENTER("mysqlx_session::createSchema");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Os", &object_zv, mysqlx_session_class_entry,
																	   &(schema_name.s), &(schema_name.l)) == FAILURE) {
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);
	if (XMYSQLND_SESSION session = object->session) {
		XMYSQLND_SCHEMA* schema{nullptr};
		if (PASS == session->m->create_db(session, schema_name) &&
			(schema = session->m->create_schema_object(session, schema_name)))
		{
			DBG_INF_FMT("schema=%p", schema);
			mysqlx_new_schema(return_value, schema);
		} else {
			mysqlx_throw_exception_from_session_if_needed(session->data);
		}
	} else {
		RETVAL_FALSE;
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ mysqlx_session::dropSchema(string name) */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, dropSchema)
{
	zval* object_zv{nullptr};
	util::string_view schema_name;

	DBG_ENTER("mysqlx_session::dropSchema");
	if (zend_parse_method_parameters(
		ZEND_NUM_ARGS(), getThis(), "Os",
		&object_zv, mysqlx_session_class_entry,
		&(schema_name.str), &(schema_name.len)) == FAILURE) {
		DBG_VOID_RETURN;
	}

	auto& data_object = util::fetch_data_object<st_mysqlx_session>(object_zv);

	RETVAL_FALSE;
	try {
		auto session = data_object.session;
		if (PASS == session->m->drop_db(session, schema_name.to_nd_cstr())) {
			RETVAL_TRUE;
		} else {
			util::log_warning("cannot drop schema '" + schema_name.to_string() + "'");
		}
	} catch(std::exception& e) {
		util::log_warning(e.what());
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_session::startTransaction() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, startTransaction)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};
	MYSQLND_CSTRING query = {"START TRANSACTION", sizeof("START TRANSACTION") - 1};
	zval* args{nullptr};
	int argc{0};

	DBG_ENTER("mysqlx_session::startTransaction");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object_zv, mysqlx_session_class_entry) == FAILURE)
	{
		DBG_VOID_RETURN;
	}

	RETVAL_FALSE;
	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);

	if (object->session) {
		mysqlx_execute_session_query(object->session, namespace_sql, query, MYSQLX_EXECUTE_FLAG_BUFFERED, return_value, argc, args);
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_session::commit() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, commit)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};
	MYSQLND_CSTRING query = {"COMMIT", sizeof("COMMIT") - 1};
	zval* args{nullptr};
	int argc{0};

	DBG_ENTER("mysqlx_session::commit");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object_zv, mysqlx_session_class_entry) == FAILURE)
	{
		DBG_VOID_RETURN;
	}

	RETVAL_FALSE;
	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);

	if (object->session) {
		mysqlx_execute_session_query(object->session, namespace_sql, query, MYSQLX_EXECUTE_FLAG_BUFFERED, return_value, argc, args);
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ proto mixed mysqlx_session::rollback() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, rollback)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};
	MYSQLND_CSTRING query = {"ROLLBACK", sizeof("ROLLBACK") - 1};
	zval* args{nullptr};
	int argc{0};

	DBG_ENTER("mysqlx_session::rollback");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object_zv, mysqlx_session_class_entry) == FAILURE)
	{
		DBG_VOID_RETURN;
	}

	RETVAL_FALSE;
	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);

	if (object->session) {
		mysqlx_execute_session_query(object->session, namespace_sql, query, MYSQLX_EXECUTE_FLAG_BUFFERED, return_value, argc, args);
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ generate_savepoint_name*/
static util::string
generate_savepoint_name( const unsigned int name_seed )
{
	static const std::string SAVEPOINT_NAME_PREFIX{ "SAVEPOINT" };
	std::stringstream output;
	output << SAVEPOINT_NAME_PREFIX << name_seed;
	return output.str().c_str();
}
/* }}} */


/* {{{ proto mixed mysqlx_session::setSavepoint() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, setSavepoint)
{
	zval* object_zv{nullptr};
	DBG_ENTER("mysqlx_session::setSavepoint");
	util::string_view savepoint_name;

	if (zend_parse_method_parameters(
		ZEND_NUM_ARGS(), getThis(), "O|s",
		&object_zv, mysqlx_session_class_entry,
		&(savepoint_name.str), &(savepoint_name.len)) == FAILURE) {
		DBG_VOID_RETURN;
	}

	auto& data_object = util::fetch_data_object<st_mysqlx_session>(object_zv);
	RETVAL_FALSE;

	util::string query{ "SAVEPOINT " };
	util::string name;
	if( savepoint_name.empty() ) {
		//Generate a valid savepoint name
		name = generate_savepoint_name( data_object.session->data->savepoint_name_seed++ );
	} else {
		name = savepoint_name.to_string();
	}

	query += escape_identifier( name );

	if (data_object.session) {
		zval * args{ nullptr };
		int argc = 0;
		mysqlx_execute_session_query(
					data_object.session,
					namespace_sql,
					{query.c_str(), query.size()} ,
					MYSQLX_EXECUTE_FLAG_BUFFERED,
					return_value, argc, args);
	}
	RETVAL_STRINGL( name.c_str(), name.size() );

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ mysqlx_session::rollbackTo(string name) */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, rollbackTo)
{
	zval* object_zv = nullptr;
	util::string_view savepoint_name;

	DBG_ENTER("mysqlx_session::rollbackTo");
	if (zend_parse_method_parameters(
		ZEND_NUM_ARGS(), getThis(), "Os",
		&object_zv, mysqlx_session_class_entry,
		&(savepoint_name.str), &(savepoint_name.len)) == FAILURE) {
		DBG_VOID_RETURN;
	}


	util::string name = escape_identifier( savepoint_name.to_string() );
	auto& data_object = util::fetch_data_object<st_mysqlx_session>( object_zv);
	RETVAL_FALSE;
	const util::string query{ "ROLLBACK TO " + name };

	if (data_object.session) {
		zval * args{ nullptr };
		int argc = 0;
		mysqlx_execute_session_query(
					data_object.session,
					namespace_sql,
					{query.c_str(), query.size()} ,
					MYSQLX_EXECUTE_FLAG_BUFFERED,
					return_value, argc, args);
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ mysqlx_session::releaseSavepoint(string name) */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, releaseSavepoint)
{
	zval* object_zv = nullptr;
	util::string_view savepoint_name;

	DBG_ENTER("mysqlx_session::releaseSavepoint");
	if (zend_parse_method_parameters(
		ZEND_NUM_ARGS(), getThis(), "Os",
		&object_zv, mysqlx_session_class_entry,
		&(savepoint_name.str), &(savepoint_name.len)) == FAILURE) {
		DBG_VOID_RETURN;
	}


	util::string name = escape_identifier( savepoint_name.to_string() );
	auto& data_object = util::fetch_data_object<st_mysqlx_session>( object_zv);
	RETVAL_FALSE;

	const util::string query{ "RELEASE SAVEPOINT " + name };

	if (data_object.session) {
		zval * args{ nullptr };
		int argc = 0;
		mysqlx_execute_session_query(
					data_object.session,
					namespace_sql,
					{query.c_str(), query.size()} ,
					MYSQLX_EXECUTE_FLAG_BUFFERED,
					return_value, argc, args);
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ mysqlx_session::killClient() */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, killClient)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};
	zend_long client_id;

	DBG_ENTER("mysqlx_session::killClient");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &object_zv, mysqlx_session_class_entry,
																	   &client_id) == FAILURE)
	{
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);
	RETVAL_FALSE;

	if (object->session) {
		const MYSQLND_CSTRING query = { "kill_client", sizeof("kill_client") - 1 };
		zval c_id;
		ZVAL_LONG(&c_id, client_id);
		mysqlx_execute_session_query(object->session, namespace_xplugin, query, MYSQLX_EXECUTE_FLAG_BUFFERED, return_value, 1, &c_id);
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ mysqlx_session::close */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, close)
{
	zval* object_zv{nullptr};
	st_mysqlx_session* object{nullptr};

	DBG_ENTER("mysqlx_session::close");
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &object_zv, mysqlx_session_class_entry) == FAILURE) {
		DBG_VOID_RETURN;
	}

	MYSQLX_FETCH_SESSION_FROM_ZVAL(object, object_zv);
	if (XMYSQLND_SESSION session = object->session) {
		session->m->close(session, SESSION_CLOSE_EXPLICIT);
		object->closed = TRUE;
		RETVAL_TRUE;
	} else {
		RETVAL_FALSE;
	}

	DBG_VOID_RETURN;
}
/* }}} */


/* {{{ mysqlx_session::__construct */
MYSQL_XDEVAPI_PHP_METHOD(mysqlx_session, __construct)
{
}
/* }}} */


/* {{{ mysqlx_session_methods[] */
static const zend_function_entry mysqlx_session_methods[] = {
	PHP_ME(mysqlx_session, __construct, 	nullptr, ZEND_ACC_PRIVATE)
	PHP_ME(mysqlx_session, executeSql,		nullptr, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, sql,			arginfo_mysqlx_session__sql, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, quoteName,		arginfo_mysqlx_session__quote_name, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, getServerVersion, arginfo_mysqlx_session__get_server_version, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, getClientId, arginfo_mysqlx_session__get_client_id, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, generateUUID, arginfo_mysqlx_session__generate_uuid, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, createSchema, arginfo_mysqlx_session__create_schema, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, dropSchema, arginfo_mysqlx_session__drop_schema, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, getSchemas, arginfo_mysqlx_session__get_schemas, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, getSchema, arginfo_mysqlx_session__get_schema, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, startTransaction, arginfo_mysqlx_session__start_transaction, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, commit, arginfo_mysqlx_session__commit, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, rollback, arginfo_mysqlx_session__rollback, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, setSavepoint, arginfo_mysqlx_session__set_savepoint, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, rollbackTo, arginfo_mysqlx_session__rollback_to, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, releaseSavepoint, arginfo_mysqlx_session__release_savepoint, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, listClients, arginfo_mysqlx_session__list_clients, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, killClient, arginfo_mysqlx_session__kill_client, ZEND_ACC_PUBLIC)
	PHP_ME(mysqlx_session, close, arginfo_mysqlx_session__close, ZEND_ACC_PUBLIC)
	{nullptr, nullptr, nullptr}
};
/* }}} */

static zend_object_handlers mysqlx_object_session_handlers;
static HashTable mysqlx_session_properties;

const struct st_mysqlx_property_entry mysqlx_session_property_entries[] =
{
	{{nullptr,	0}, nullptr, nullptr}
};

/* {{{ mysqlx_session_free_storage */
static void
mysqlx_session_free_storage(zend_object * object)
{
	st_mysqlx_object* mysqlx_object = mysqlx_fetch_object_from_zo(object);
	st_mysqlx_session* inner_obj = (st_mysqlx_session*) mysqlx_object->ptr;
	delete inner_obj;
	mysqlx_object->ptr = nullptr;

	mysqlx_object_free_storage(object);
}
/* }}} */


/* {{{ php_mysqlx_base_session_object_allocator */
static zend_object *
php_mysqlx_session_object_allocator(zend_class_entry * class_type)
{
	DBG_ENTER("php_mysqlx_session_object_allocator");
	st_mysqlx_object* mysqlx_object = util::alloc_object<st_mysqlx_session>(
		class_type,
		&mysqlx_object_session_handlers,
		&mysqlx_session_properties);

	MYSQLND_STATS* stats{nullptr};
	MYSQLND_ERROR_INFO* error_info{nullptr};
	const MYSQLND_CLASS_METHODS_TYPE(xmysqlnd_object_factory) * const factory = MYSQLND_CLASS_METHODS_INSTANCE_NAME(xmysqlnd_object_factory);
	st_mysqlx_session* data_object = static_cast<st_mysqlx_session*>(mysqlx_object->ptr);
	if (!(data_object->session = xmysqlnd_session_create(0, FALSE, factory, stats, error_info))) {
		mnd_efree(data_object);
		mnd_efree(mysqlx_object);
		DBG_RETURN(nullptr);
	}

	DBG_RETURN(&mysqlx_object->zo);
}
/* }}} */


/* {{{ mysqlx_register_session_class */
void
mysqlx_register_session_class(INIT_FUNC_ARGS, zend_object_handlers * mysqlx_std_object_handlers)
{
	mysqlx_object_session_handlers = *mysqlx_std_object_handlers;
	mysqlx_object_session_handlers.free_obj = mysqlx_session_free_storage;

	{
		zend_class_entry tmp_ce;
		INIT_NS_CLASS_ENTRY(tmp_ce, "mysql_xdevapi", "Session", mysqlx_session_methods);
		tmp_ce.create_object = php_mysqlx_session_object_allocator;
		mysqlx_session_class_entry = zend_register_internal_class_ex(
			&tmp_ce, mysqlx_session_class_entry);
	}

	zend_hash_init(&mysqlx_session_properties, 0, nullptr, mysqlx_free_property_cb, 1);

	/* Add name + getter + setter to the hash table with the properties for the class */
	mysqlx_add_properties(&mysqlx_session_properties, mysqlx_session_property_entries);
}
/* }}} */


/* {{{ mysqlx_unregister_session_class */
void
mysqlx_unregister_session_class(SHUTDOWN_FUNC_ARGS)
{
	zend_hash_destroy(&mysqlx_session_properties);
}
/* }}} */


/* {{{ mysqlx_new_session */
enum_func_status
mysqlx_new_session(zval * return_value)
{
	DBG_ENTER("mysqlx_new_session");
	DBG_RETURN(SUCCESS == object_init_ex(return_value, mysqlx_session_class_entry)? PASS:FAIL);
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

