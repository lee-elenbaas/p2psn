#include "crypto.hpp"

#include <sstream>
#include <iomanip>

using namespace p2psn::utils;
using namespace std;
using cppcms::crypto::message_digest;

string signature::md5(const string& message) {
	return generate(message_digest::md5(), message);
}

string signature::sha1(const string& message) {
	return generate(message_digest::sha1(), message);
}

string signature::generate(std::auto_ptr<cppcms::crypto::message_digest> generator, const std::string& message) {
	unsigned hash_size = generator->digest_size();
	unsigned array_size = hash_size/sizeof(unsigned char);

	if ((hash_size%sizeof(unsigned char))>0)
		++array_size;

	unsigned char hash[array_size];

	generator->append(message.c_str(), message.size()*sizeof(char));
	generator->readout(hash);

	ostringstream os;

	os << "hash \""<< message<< "\" hash_size="<<hash_size<<" array_size="<<array_size<<" hash:";

	for (unsigned i=0; i<hash_size;++i)
		os << setw(2) << setfill('0') << hex << static_cast<unsigned>(hash[i]);

	return os.str();
}

