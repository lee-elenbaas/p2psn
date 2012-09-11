/**
 * cryptographic tools used by p2psn
 *
 * providing easier to user API over the cryptografic tools cppcms provides
 */
#ifndef __STREAMUTILS_H
#define __STREAMUTILS_H

#include <ostream>
#include <iomanip>

namespace p2psn {
	namespace utils {

			namespace {

				template<typename Char>
				struct HexCharStruct
				{
				  Char c;
				  HexCharStruct(Char _c) : c(_c) { }
				};

				template<typename Char>
				struct HexBufferStruct
				{
					Char const * const buffer;
					unsigned length;
					HexBufferStruct(Char const * const buffer_, unsigned length_)
						: buffer(buffer_), length(length_) { }
				};
				
			}

			template<typename Char>
			inline std::ostream& operator<<(std::ostream& o, const HexCharStruct<Char>& hs)
			{
				std::ostream hexout(o.rdbuf());

				hexout << std::setw(2*sizeof(Char)) << std::setfill('0') << std::hex << static_cast<long>(hs.c);

				return o;
			}

			template<typename Char>
			inline std::ostream& operator<<(std::ostream& o, const HexBufferStruct<Char>& hs)
			{
				std::ostream hexout(o.rdbuf());

				hexout << std::setw(2*sizeof(Char)) << std::setfill('0') << std::hex;
			  
				for(unsigned i=0; i<hs.length;++i)
					hexout << static_cast<long>(hs.buffer[i]);

				return o;
			}

			template<typename Char>
			inline HexCharStruct<Char> hex(Char _c)
			{
			  return HexCharStruct<Char>(_c);
			}

			template<typename Char>
			inline HexBufferStruct<Char> hex(Char const * const buffer, unsigned length)
			{
			  return HexBufferStruct<Char>(buffer, length);
			}

	} // namespace utils
} // namespace p2psn

#endif // __STREAMUTILS_H
