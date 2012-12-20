/**
 * Content declarations for communication between the node_admin and its skin.
 *
 * The content types used by the node_admin to pass values into its skin for rendering the result HTML pages.
 */
#ifndef __P2PSN_ADMIN_MENU_CONTENT_H
#define __P2PSN_ADMIN_MENU_CONTENT_H

#include "../admin_shared/admin_shared_content.hpp"

namespace p2psn {
    namespace node_admin {
        namespace content  {

			struct admin_menu : public master {
			public:
				bool has_new_settings;
			};

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_ADMIN_MENU_CONTENT_H
