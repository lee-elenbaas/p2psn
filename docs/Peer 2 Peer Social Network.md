Peer 2 Peer Social Network
==========================

Use Cases:
----------

Normal Installation on a single machine:
1. User downloads a p2psn installation and installs on his machine.
a. User gets 2 things installed on his machine: 
i. A functioning node, 
ii. and a web interface to that node.
b. User uses the web interface to set up some basic administration configurations.
c. User uses the web interface to set up his personal profile.
d. User uses the web interface to start getting social using his profile.

Synced Installation on a new machine:
1. User downloads a p2psn installation and installs on his machine.
2. User uses the web interface to set up some basic administration configurations.
3. User sets up a new profile, while checking the box stating that the given email is already used by a profile on another node.
a. An email will be sent to the other nodes to replicate their database to the new node.
b. After a responding emails are received and processed all nodes are in sync and will continue to remain in sync.
4. User gets social.

Inviting a friend
1. From the social web interface
2. add a friend window – place an email of the user to invite – and an invitation message.
a. An email message will be sent to that email address containing a predefined template that will include the message from the user, an explanation of what the social network is and how to get it, and the invitation object.
b. If this user already has a working p2psn installation attached to that email – that installation will place the invitation object into the db and display it accordingly.

System structure:
1. The p2psn network has the following main ingredients:
a. Profiles – each profile is connected to a single email (multiple email accounts can work just as well, and will solve the question of how to deal with email changes)
b. Nodes – each node serves as a server for one or more profiles. The node is responsible for synchronizing the profile between different nodes, and for the communication (online and offline) of this profile to other profiles.
c. Clients – are UI programs that authenticate with a node and perform operations on the profile using it.
2. Communication  is based on the following principles:
a. Communication between client and its node is assumed to be trivial and on-line.
i. The current intention is to base this communication on an json-rpc API that the node will expose to the clients.
b. Communication between nodes is done in two forms:
i. Off-line: for synchronizing nodes and off line communication between profiles. Currently I am assuming this will be based on email messages, but it can also use a dedicated messages server. Personally I think that it will be better to support just an email – and provide a free email with limited capacity if someone wants to create a new profile. (perhaps based on invites only) – but this will introduce the central point of control again.
ii. On-line: for synchronization between friends that are both on line, chatting and on line notifications. Currently I think it will be based on json-rpc API between the nodes – firewall issues will simply mean on line communication will not work. Later on a possible on line communication proxy can be placed on a central domain. (again introducing a central point of control.)

===============================================================================

	Each node serves several profiles – but behaves as if it serves only a single profile (that means that communication between profiles served by the same node is done through the network just as if the profiles are not placed on the same node (this does not mean that the different profiles can not use the same storage system)
	Each client (the first one I am considering is a web interface) connects to one node as a single profile.
		Possible clients:
Fierefox plugin
Empathy plugin
Server web interface
	
The node will support multiple client connections on the same profile.
The general information flow is like this: 
1. When a client connects to node, the node authenticate the client. Client can not connect to a profile that does not belong to that node.
2. Node attempts to connect to each of the friends servers, to get chat connection to the user, along with any updates from the last update from their profile. And to notify them that this profile is now online.
3. Each client recieves (requests) a list of object metadata to update the data he received before from each of his frields servers. 
4. The client requests a list of object content from the friends server based on the metadata. To display to the clients.
5. Each time there is a change in the object metadata that is visible to any of the connected peer servers, and update of that metadata is being sent to that server – that server can then request the actual object this metadata relates too.

Every object in the server has the following  characteristics:
	a parent object
	an ACL that determine who can access it and what he can do with this object
	a a version number (every change to the object or to the metadata means a new version)
	a profile id
	is connected to the profile (including server and profile in that server identification)
	create date
	version date (last update date)
	last update date – the version date of the last time the content was changed
	last update date from the children objects (in all levels)
	last content update date from the children objects (in all levels)
	content – this can be of different types, and different formats. The same objects can have several formats attached to it (html/txt/pdf versions for example)
	everything is an objects: chat messages, those belong to the chat session object that exists between each pair of friends.
	Responses – their parent is the object that they respond too (that object can reside in some other profile – so the id must be complete – and to include the version it was generated for)
	folders are object types that their content is name and description
	files and creations are simply objects that reside under a folder.
	Each profile has several predefined objects defined for him: a root folder, a chat session with every friend(connected profiles) – the profiles page, the wall page...
ACL:
	The starting ACL for every object is inherited from its parent (or grandparent or whatever for-father that comes from the same profile) – this can be overwriten per object
	The ACL for the automatically created objects will have defined defaults – and will be controllable from the settings
	If an object has child objects from the same profile – there will be an option to override the ACL of child objects once it is being changed.
	

	each object is signed by the profile that the object belongs too
if an object is downloaded from another profile – it becomes a new object that the original object is its parent – and its ACL is a combination of the original and (not sure about this – perhaps it will be idetified as a remote object – simply stored in a cache – along with a calculated ACL that match both)

in any case – remote/cached objects that should appear to a friend will appear on the metadata and can be requested by the other friends
wach remote object is identified correctly by its original id – and has a remote level id
each ACL has also a maximum remote level allowed (can be infinite)

The ACL has two forms: the effective ACL, and the administrative form that the user manages.
The user is able to create user groups that contain other entities and can be included in other groups and ACLs (group circles will not be allowed)
other then that admin ACLs only contains the predefined security objects and profile identifications.
Effective ACL does not contain groups – only predefined objects and profiles (and is generated by a complete breakdown of the user managed ACL.)
The servers only use the effective ACL – and not the admin one. In order to control the access to an object.
Each communication between servers is signed by the sending profile, and encrypted for the receiving profile.

Identities
The main identification of a profile is the email
a profile can have several emails – once an email is set for a specific profile – the profile needs a gpg key attached to that email in order to sign and receive content for the profile.
Friends are based on trust relationships between gpg signatures
since every content is signed by the original creator, and every remote/cached object is also signed by every caching level – the content can be trusted


each object will be a a json object with the following structure:
{
	properties : {
		id : …, // string uri representation of the 
sample full object is like this: “p2psn:user@server/objectid”
		version : n, // numerical running number that is the version of the object, each object is created and maintained on a single server, as a result each object can have only a list of versions.
		type_ref : …, // the p2psn uri of the type this object belongs too – the type is a linked complex object – as implyed by the _ref suffix
		effectiveAcl : { // the effective acl tha
		},
		media { // the actual object content separated by media types – media types can be different formats (ODF, PDF, GIF... that all contain the same semantic content)
			mediaTypeName1 : { // the different media names should be recognized and used by the views and type objects of this object.
				mimeType : “application/pdf”, // the string mime type of this media type.
				content : … // the actual object content as primitive, or complex json object that contain primitives and references to other objects
			},
			mediaTypeName2 : {
				…
			},
			…
		}
	},
	signature : … // the RSA signature of the properties section of this object as signed by the creator account RSA key.
}
each response from the server will include an array of such objects, those objects should be stored in the client DB, if they pass signature validation.
Server response will have the following structure:
{
	objects :  [
		{
			properties : { … },
			signature : …
		}, …
	],
	signature : … // the signature of the objects section of the response as signed by the key of the responding server
{
	content : { // the actual contents of the object including primitives and other objects
		objectId : “p2psn:lee@server.com/123123dgwfk324213ljdf”, // the full id of the object
		version : 1, // the current running number of the object
		type_ref : “p2psn:types@p2psocial.com/2348798759dfvbv2”, // the type object identification of the object type. This type is merely a linked object – it can also be linked as below (very unlikely for type objects, but here for sample embedment of objects)
		type_embed : {
			content : {
				objectId :  “p2psn:types@p2psocial.com/2348798759dfvbv2”,
				version : 1,
				type_ref : “p2psn:types@p2psocial.com/sfjkh3223421j3”,
				defaultView_ref : “p2psn:views@p2psocial.com/sfjsdfgf34124234213”, // default view should probably be embeded by default for type objects
				defaultView_embed : {
					content : {
						objectId : “p2psn:views@p2psocial.com/sfjsdfgf34124234213”,
						version : 1,
						type_ref : “p2psn:types@p2psocial.com/asdhklhk322343”
						
		}
		… the actual contents of the object – embeded primitives, and either embeded or linked objects
	},
	version : 1, // the current running version number of the object

the current structure in my mind:

p2p server:
	cppcms json rpc providing the actual data to the client
	postgresql providing the server storage
p2p client:
	apache serving the static files
	static html 5 with js files accessing the apache server 
	cppcms application serving the js using json rpc – by requesting the necessary content from the server and perform all the digesting oberations to the client
p2p client display: browser displaying the results from the p2p client

I need to make sure that client stored server session works for json rpc – in order for the server to recognize the client correctly.

Road map:

1. Text objects only bult in view and type one user
2. Multiple users and servers
3. Type and view for text objects
4. Separating the client from the server
5. Enhance text objects with simple mark up and html and text media types
6. Add support for object references in both media types
7. Add image and folder objects.
8. Build profile wall photo gallery objects
9. Alpha with friends and public repository
10. Setting up public server


ok  here comes the latest eurika:

The comunication layer will have online and offline layers.
The online will be direct peer 2 peer between servers. And direct communication between client and server.
The offline will be based on emails. This will make the cpmmunication of this layer oblivious to connection settings. And make the use of gpg mail easier.
Perhaps there will be no need for server client separation


ok the image I have now is like this:

the network is built by nodes – each node have the following components:
1. Node Manager
1. Provides local storage for the profiles stored here.
2. Performs all access checks on objects
3. Perform the synchronization between this node and other nodes.
4. Each node is configured for serving specific set of profiles
1. Each profile configuration contain the email settings to communicate using the profile email (later possible the use of addon to other email programs)
2. The public-private keys attached to the email that will be used for communication with other nodes.
3. The public key of profile friends.
5. The node will be a CppCMS application with db backend that will provide json-rpc API for the display layers, for communication plugins (slow and fast)
2. Several Profile display layers
1. Each display layer is serving a single profile. And is identified by the node administrator and communicates with it in order to get the objects, their types and their views from the node manager.
2. When a profile display layer connects to the node manager – the node manager maintain a fast connection between the manager and the display. This allows the manager to inform the display on any incoming status changes as they occure. At the same time the node manager publish to the group of friends that he is currently online and how a fast connection can be achieved.
3. If any of the contact known to the manager has already published a way to create a fask link – an attempt is being made to open such a link. If it is a success – that user will be displayed as online once such a link is established. (??? connection refused will be displayed as busy ???)
4. There will be several possible display layers:
1. CppCMS application that will provide a web interface
2. Native applications (IM, email, feed readers and also a specific other things)
3. display layers will need a way to parse the view objects that should be xhtml 5 objects with javascript in them – in addition they will include rules based on regex on what media contents to bring as parameters into this view.

        Server info
 each p2psn node will maintain an active info object, it will contain a guide will be generated when the node set up . Protocol version node software name node software version setup comment that will be placed during node setup by the user to distinguish different nods that use the same storage.
The copy of the active server info will be placed as part of the meta data for each object generated on this node 
setting up a new profile will send a request to the profile email requesting all objects of this profile the request will include a copy of the active server info only nodes that don't match this server info will send information back (usually in several batches/emails.)  - this will be used to sync the same profile on several nodes.
Node configuration:
The node configuration will include the listening port for the clients, listening port for the immidiate communication channel. And possibly publish port for the immidiate communication channel. (if no publish port is provided – the actual listening port will be used.)
Each time a profile becomes online – the immidiate communication channel is published to all the people on the immidiate communication list (usually friends/peers)
Those who are online will attempt to create an open channel.
At the same time all the peers that has sent an invitation to an immidiate communication channel – an attempt will be made to open one with them.
Every peer that communication with its node is established – will display his online status as its node reports.
Each node will have defined the maximum size of messages generated by it.

Storage:
each object generated by the node will be generated in its open form – and then packed into its json form, signed and contains the meta-data.
Once the json form is generated – it will be passed over to other nodes in that form – then will store this form. Parse it if necessary, and keep it to communicate further. This way keeping a single form of the object signed by the same generating node and profile.

Terminology:
as a side note it might be better to set up a new terminology for this network.
Perhaps peers is better then friends in this case.

Why CppCMS

1. I didn't know CppCMS before I started on this project. And both of them came to me about the same time.
2. My first OO language was C++ - and I always kept a soft spot for it.
3. This framework is what I been missing from using C++ in my professional life.
4. It keeps my professional life and my pet project separated.
5. This project is all about protocol – not about the language it will be implemented in – so why not?
Ok i'll admit – lior had a point. Limiting the media size and relying on media hosting means a way to circumvent the security
so first thing is to limit the number of connections to each server. Offline connectoins can handle larger amount of connected users then online communication channels.
I think that online communication will follow the friends tree – each person will only be connected online to his direct friends. And even that will be limited to a max number of connections.

Phase 2 – moving from thinking about it to actually doing it

I set up a github repository p2psn
and I been starting to work on it and see how to work with it
I also started to set up the eclipse for working with CppCMS

-------- node users
a node is initially installed with 2 users set up: guest for guest access and admin (with predefined password) for configuration

admin user can set up the policy for users and set up more users.

The guest is defined as a community user (community user will request additional identification fields and catchu phrases that normal users will skip and the data will be taken from the user profile instead)
Each user will be given a set or rights about what type of objects it can offer.
The node will support a way to register more “normal” users – the admin can declare what normal user means – and then set each user settings individually after they register.

The idea to keep in mind is that each node will have a VERY limited amount of users (a family computer will have a user for each member)

Any registered user should be able to define trust relation with a user on another node – this means that this node will treat the trusted user objects as if they where placed by the trusting user on this node. (cache, ACL …)

ACL will include a deny list as well as allow list and will be evaluated as follows:
ACL allow on system groups
ACL deny on system groups
ACL allow individuals & user groups (user groups are flattened to user list)
ACL deny individuals & user groups

