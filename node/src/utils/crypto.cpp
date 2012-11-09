#include "crypto.hpp"

#include <stdexcept>
#include <booster/backtrace.h>
#include <sstream>
#include "streamutils.hpp"

using namespace p2psn::utils;
using namespace std;
using cppcms::crypto::message_digest;

istream& p2psn::utils::operator>>(istream& in, hash_algorithm& hash) {
	string str;

	in >> str;
	
	hash = (hash_algorithm)str;

	return in;
}

hash_algorithm operator(hash_algorithm)(const string& str) {
	if (str == "md5")
		return hash_algorithm::md5;
	
	if (str == "sha")
		return hash_algorithm::sha1;
	
	return hash_algorithm::illegel;
}

ostream& p2psn::utils::operator<<(ostream& out, hash_algorithm hash) {
	switch (hash) {
		case hash_algorithm::md5:
			out << "md5";
			break;
		case hash_algorithm::sha1:
			out << "sha1";
			break;
		case hash_algorithm::illegel:
			out << "illegel";
			break;
		default:
			out << "illegel(" << (int)hash << ')';
			break;
	}

	return out;
}

bad_hash_algorithm::bad_hash_algorithm() : msg_("p2psn::utils::bad_hash_algorithm") 
{
}
bad_hash_algorithm::bad_hash_algorithm(string const &s) : msg_("p2psn::utils::bad_hash_algorithm: "+s ) 
{
}
bad_hash_algorithm::bad_hash_algorithm(string const &s,hash_algorithm actual) : 
	msg_("p2psn::utils::bad_hash_algorithm: " + s)
{
	std::ostringstream msg;
	msg<<" error converting from "<<actual;
	msg_ +=msg.str();

}

bad_hash_algorithm::~bad_hash_algorithm() throw()
{
}
const char* bad_hash_algorithm::what() const throw()
{
	return msg_.c_str();
}

string signature::md5(const string& message) {
	return generate(message_digest::md5(), message);
}

string signature::sha1(const string& message) {
	return generate(message_digest::sha1(), message);
}

string signature::hash(hash_algorithm algo, const string& message) {
	switch (algo) {
		case hash_algorithm::md5:
			return md5(message);
		case hash_algorithm::sha1:
			return sha1(message);
//		default: // throw handled outside the switch
//			throw booster::bad_cast("unsupported hash algorithm");
	}

	throw bad_hash_algorithm("unsupported hash algorithm", algo);
	return ""; // only to bypass compiler warning
}

string signature::generate(std::unique_ptr<cppcms::crypto::message_digest> generator, const std::string& message) {
	unsigned hash_size = generator->digest_size();
	unsigned array_size = hash_size/sizeof(unsigned char);

	if ((hash_size%sizeof(unsigned char))>0)
		++array_size;

	unsigned char hash[array_size];

	generator->append(message.c_str(), message.size()*sizeof(char));
	generator->readout(hash);

	ostringstream os;

	os << hex(hash, array_size);

	return os.str();
}

