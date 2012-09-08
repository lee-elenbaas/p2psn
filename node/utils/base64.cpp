
#include "crypto.hpp"

#include <sstream>
#include <cppcms/base64.h>

using namespace p2psn::utils;
using std::string;
using cppcms::crypto::message_digest;

string signature::md5(const string& message) {
	return generate(message_digest::md5(), message);
}

string signature::sha1(const string& message) {
	return generate(message_digest::sha1(), message);
}

string signature::generate(std::auto_ptr<cppcms::crypto::message_digest> generator, const std::string& message) {
	unsigned hash_size = 2+generator->digest_size()/sizeof(char);

	char hash[hash_size];
	hash[hash_size-1]=hash[hash_size-2]=0;

	generator->append(message.c_str(), message.size()*sizeof(char));
	generator->readout(hash);

	std::ostringstream os;

	cppcms::b64url::encode(hash, hash+hash_size, os);

	return os.str();
}

