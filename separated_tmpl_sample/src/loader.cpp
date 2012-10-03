#include "base.h"
#include "derived.h"

namespace {
	cppcms::views::generator my_generator; 

	struct loader { 
		loader() { 
			my_generator.name("my_skin");

			my_generator.add_view<my_skin::base,content::base>("base",true);
			my_generator.add_view<my_skin::derived,content::base>("derived",true);

			cppcms::views::pool::instance().add(my_generator);
		}
		~loader() {  
			cppcms::views::pool::instance().remove(my_generator); 
		}
	} a_loader;
} // anon 
