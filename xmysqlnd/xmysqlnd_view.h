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
  | Authors: Darek Slusarczyk <marines@php.net>                          |
  +----------------------------------------------------------------------+
*/
#ifndef XMYSQLND_VIEW_H
#define XMYSQLND_VIEW_H

namespace mysqlx {

namespace drv {

class View
{
	public:
		static st_xmysqlnd_node_stmt* create(
			st_xmysqlnd_node_session* session,
			const st_xmysqlnd_pb_message_shell& pb_msg);
		static st_xmysqlnd_node_stmt* alter(
			st_xmysqlnd_node_session* session,
			const st_xmysqlnd_pb_message_shell& pb_msg);
		static st_xmysqlnd_node_stmt* drop(
			st_xmysqlnd_node_session* session,
			const st_xmysqlnd_pb_message_shell& pb_msg);
};

} // namespace drv

} // namespace mysqlx

#endif /* XMYSQLND_VIEW_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
