p2psn
=====

peer 2 peer social network - an attempt to desing and create a social network that will use peer 2 peer architecture rather then central server philosophy

Rational
--------

There are several things that bother me with current social networks, the main issues are:
- Anyone can place data that integrates into my own data, without me having a say so in the matter. (This is actually improving as time goes by due to public pressure on the social networking companies.)
- Anyone can place data anonymousely, escaping responsibility for the results of the publication.
- The company hosting the social network also does not accept responsibility on the data.
- All the data is maintained in one central place providing one central point of failore for security, and ethical misuse of this information. It also adds in the accumulation of data from different sources and deducting things on the users without them knowing about it.

The solution is to design a social network where the "master" copy of each object resides with the user who created this object, allowing the user to control it. This leads to a peer 2 peer design of social network where each node provides the necesary services for its profiles to socialize with profiles on other nodes.

Technology
----------

The focus of this project is about the network of nodes. As a result the implementation language is less important then the protocol that will be used between the nodes.

The protocol is based on json-rpc, where each node exposes an API that allows to interact with it using a specific set of json objects.
The UI was chosen natually to be HTML+JavaScript (HTML 5 as much as possible).
The nodes are currently designed to use CppCMS.

The reason behind this choice of tools is simply this: this is a pet project of mine in its infancy. I want to learn CppCMS better, and on paper at least - it looks like a good choice in terms of capabilities performance and platform support.

Licensing
---------
The current plan is to release this project under GPLv3.

Developers
----------

Lee Elenbaas - lee [dot] elenbaas [at] gmail [dot] com - Owner