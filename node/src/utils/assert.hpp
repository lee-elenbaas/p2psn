#ifndef __ASSERT_H
#define __ASSERT_H

#ifndef FREE_RUN
	#define ASSERT(cond, exception) if (!(cond)) throw (exception)
#else
	#define ASSERT(cond, exception)
#endif

#endif // __ASSERT_H
