/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 2006-2015 The PHP Group                                |
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

#ifndef XMYSQLND_ZVAL2ANY_H
#define XMYSQLND_ZVAL2ANY_H

#include "proto_gen/mysqlx_datatypes.pb.h"

enum_func_status zval2any(const zval * zv, Mysqlx::Datatypes::Any & any);
enum_func_status any2zval(const Mysqlx::Datatypes::Any & any, zval * zv);
void any2log(const Mysqlx::Datatypes::Any & any);
void scalar2log(const Mysqlx::Datatypes::Scalar & scalar);

#endif	/* XMYSQLND_ZVAL2ANY_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
