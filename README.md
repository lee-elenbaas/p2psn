# p2psn

peer 2 peer social network - an attempt to desing and create a social network that will use peer 2 peer architecture rather then central server philosophy

## Rational

There are several things that bother me with current social networks, the main issues are:
- Anyone can place data that integrates into my own data, without me having a say so in the matter. (This is actually improving as time goes by due to public pressure on the social networking companies.)
- Anyone can place data anonymousely, escaping responsibility for the results of the publication.
- The company hosting the social network also does not accept responsibility on the data.
- All the data is maintained in one central place providing one central point of failore for security, and ethical misuse of this information. It also adds in the accumulation of data from different sources and deducting things on the users without them knowing about it.

The solution is to design a social network where the "master" copy of each object resides with the user who created this object, allowing the user to control it. This leads to a peer 2 peer design of social network where each node provides the necesary services for its profiles to socialize with profiles on other nodes.

This project is currently centrelized on building a node implementation that can be the building block of such a peer to peer network. A web interface for this node that will allow performing operations in the network. And at the same time finalizing an API that will enable such a network to exists indipendently of the specific node implementation, or client application.

## Network Design

The peer to peer network will be a network of nodes, communicating with each other using peer to peer philosofy.
Each node will support several user profiles and will maintain a database of those profiles along with the objects accessible by those profiles. The node will be responsible for synchronizing those objects with other nodes that serve the same profile, and to send visible objects to other profiles.
Each node will allow clients to authenticate to a profile, and serve those clients as they perform operations on and for this profile.

## Node Design

The node will contain a cyrarchy of CppCMS web applications:

main - The main node app will simply provide links to the apps below it, and display some configuration information needed to configure clients to connect to the node.
 +-- api - The node json-rpc server that will expose the entire functionality to other nodes and client applications.
 +-- web_client - The web client interface implementation that will give some basic user interface to operate inside the network.
 +-- config - Web app that allows to configure the node itself, and to enable/disable the web interface

The the web-client application will communicate with the node web application using json-rpc - either from the server, or from the js on the client side.
The api node implementation will use email as the platform for offline communication between nodes, and json-rpc for online communication between nodes and node to clients.

## Web Client

Since the web client is supposed to work in exactly the same way as other UI elements will connect to the node. The interface will use static HTML and JS files delived from the CppCMS server that will communicate using json-rpc with the node_api CppCMS application.
The client can work offline as well - and not just served from the CppCMS.
The only thing that will be dynamic in this client is a default connection information (ip address and port) used to connect to the node_api, in order to allow a user to change those for himself easily. This default connection information will be a static file that will be generated when a new settings is saved by the node_confif app.

## Technology

The focus of this project is about the network of nodes. As a result the implementation language is less important then the protocol that will be used between the nodes.

The protocol is based on json-rpc, where each node exposes an API that allows to interact with it using a specific set of json objects.
The UI was chosen natually to be HTML+JavaScript (HTML 5 as much as possible).
The nodes are currently designed to use CppCMS.

The reason behind this choice of tools is simply this: this is a pet project of mine in its infancy. I want to learn CppCMS better, and on paper at least - it looks like a good choice in terms of capabilities performance and platform support.

The offline communication between nodes will be based on a time proven offline protocol: email. The specifics of how the email will be used is not clear to me yet. (The posibilities are: email client add on that communicates with the node using its json-rpc api. Direct pop3/imap and smtp use.

The node database will be contacted through the CppDB library. The default will be a Firebird embedded server that access a file next to the executable. For that i will implement a firebird backend of CppDB using ibpp library.

OpenID support will allow attaching multiple OpenID authentications to every user - and that authentication will be used as a way to login for that user (an opneId will only be allowed to be associated with one user on the same node.) 
The openID support wull use the library libopkele

## Licensing

The current plan is to release this project under GPLv3. 
And the static media content using CC Share alike license.

Developers
----------
Lee Elenbaas - lee [at] elenbaas [dot] org [dot] il - Owner

Thanks
------
Lior Shterenberg for taking his time to sit with me on this. Allowing me to bounce ideas off his mind.
Anat Elenbaas for giving me the time to do this, and supporting me in making it

## Known Issues

Each node needs to deal with large amount of data (all the objects created by its users + all objects visible to the users) and large amount of communication bandwidth (communication of those said objects to other nodes + communication of online status info or other users)
At the same time each node is intended to run on a normal home PC with its limited capabilities.

## Development Blog

2012-12-24

> I managed to get back on the working track. The static file framework now works, although it has some bugs, i was able to leave it and get back to the admin website, and got it to be almost working.

> In addition i gave some thoughts to how the communication between the clients and the server should be performed, and i came to the conclusion that the best will be UDP (if you combine udp with ip filtering you get an inpenetrable listening port, and this was one of the major points for p2psn - social networking locally without opening my computer to others.

2012-12-14

> I managed in the last few days to get the compilation working dispite a few issues, and get further with the whitelist serving of static files.
> Currently the status is that i have an App that generates the whitelist for a single mime at a time, and with no support for normal copy (only soft & hard links). But i have a prufe of concept for serving the static files i need both for the client and for the node config.

> Another idea that came to my mind is to help separate the p2psn emails from the normal email, by allowing secondary emails to be defined as transport emails. Those emails should carry most of the p2psn conversations (with the exclusion of invitations) This way a normal p2psn user will not have his normal email polluted by messages he should have a program reading for him.
> Non p2psn emails in the transport emails will have some basic filtering rules into them (since i do not expect people to ever go into the transport emails to read them - perhaps during p2psn view development, but no more then that):
> - Discard all non p2psn emails
> - Forward all non p2psn emails to the normal/master email
> - Auto reply to non p2psn with a specified response

2012-12-11

> I reinstalled my machine in order to get GCC 4.7 with some more C++11 support. I got it, but i have to redo all my other dependancies. And right now i am stuck with boost.
> I tried to build it in the folder like i did before, and then point to that folder from the make file - did not work.
> Now i tried to follow this guide (http://ubuntuforums.org/showthread.php?t=1180792) and get the necesary libraries installed into the system - did not work either.
> I'll keep at it

2012-12-01 2

> After writing the ko part, i came to realize that i need to take a closer look at nodejs - and perhapse use it as the context for each client session processing.
> I will think about this option later on, but it sure will solve all the JS api issues.

2012-12-01

> Working on this becomes slower as my main work becomes more demanding. Only this time the regular work got me to learn knockout.js. 
> The main idea behind the views I had in mind is very similar to what ko has, have the object itself as a data model - and then have the correct view mapped to that object either at the client or at the server level. 
> So why not marry the two and have my views use ko as default. The problem is that this generates dependancies for clients.

> Right now the idea i have is like this:
> - The object itself is stored and accessed as a json string.
> - The client identification and session generate a js environment on the server that will be used to "prepare" the object to be sent to the client.
> - Inside this client JS environemnt there is a separate object for each view that is used. (inherited views are used views and exists as JS objects to allow the JS inheritance to provide the means for the view inheritance.
> - Each request from the client identifies an object, view and action: and basically translates to a function call inside JS like this: view.action(object)
> - The result of this processing is passed over to the client.
> - There will be helper objects (either passed over to the function call as arguments or exists inside the JS environemnt that will allow to perform allowed operations on the object (and other objects) as stored by the server. (fetching of other objects, creating a new version of the object, creating a new object...)

> The downsides of this approache are:
> - There are a lot of JS processing involved, and the time and resource cost of those calculations is unclear.
> - How to support existing JS libraries inside the server is still unclear - but there is a natural requirment for that. (require.js for example)

> The positive side (and why i think i will stick with this approach for the time being) is that this approach gives all the behaviors i wanted, at a fairly cheap price.
> - Inheritance bitween views is automatically supported using the lookup model of JS objects (i set the parent view as the prototype of the inheriting view)
> - Allows me to maintain a sandbox around each client session, to avoid both clients crushing each other.
> - Allows me to provide a clear API for view writers tat performs all the necesary checks internally.
> - Allows me to provide some very simple view implementations

> Back to where i started, i see no reason to allow for ko to be run on the server, although i can see how it can be used as a rendering mechanism - and perhaps i should consider it as such later. But ko is too DOM dependant to be used on the server side, on the other hand, i see no reason not to provide some very simple view that can server a client using ko to update a ko model from a server object, and generate actions using an object coming from ko.

2012-11-06

> Yet another link i plan on using and following its rules: http://semver.org/

2012-10-12

> Its been a while since i wrote anything. In that time i managed to get the user management to update the users into the session correctly.
> Then i went into the issue of serving static files in order to serve CSS file for the user management.
> The next detour was to go into splitting the build into separate translation units and use incremental build to speed the build process. This led me to some enhancment to the cppcms template system, and enhancment i delivered to Artyum to be included into the next version of cppcms.
> And now i am back into the issue of service static files, and generating an app that will serve static files using a white list, and a tool that will generate the whitelist for me.
> I plan to run this tool as part of my build process.

2012-09-11

> In the last several days i managed to get the admin users to perform its actions in the session. 
> (I still need to apply it and generate a new configuration from it.)
> But what bothered me while doing this was the lack of CSS, for that i needed to be able to serve static files.
> Serving a single css file was easy enough, but then came the need to serve others. and to keep the server from being exposed using the static files interface.
> The solution i initially thought of was hash the requested path, and service from a single folder a file named by that hash. 
> This solves the problem of visibility from the outside, while keeps all the html links readable. It presents 2 problems:

> - The development files needs to be hashed at build time, and this represent some build dificulties (i started developing a utility to do that for me)
> - The deployment will contain a folder that is very hard to understand and debug in case of need.

> There is a third problem that comes from a different direction: the web client was supposed to work offline as well, 
> this means that the html static files of the client needs to be able to use links between them. And hashing the client is not an option (unless we install 2 versions, one for server delivery and one for offline delivery)

> So the approach i am considering now is that of a white list: in the build, place a white list of allowed static paths, each of those can then be hold more then just the allow status, it can also hold the mime type and where 
> the file is physically located (and even if it should be served directly or using the web server send file capabilities).
> And on top of it, the deployment will be easy enough. I think i will still hash the path in order to get a key to this whitelist, but the necesity of hashing is really gone for this issue.

> This does raise a different issue: where will the whitelist be located. The obvious place is inside the config file. This makes it harder to build it, but not undoable. And i will still need a tool that will generate the whitelist for me, with the necesary set of rules for that.

> This second utility also brings up another issue: I need to break down the build process, this is getting painfull.

2012-08-30

> Diaspora or not to Diaspora (http://diasporaproject.org/). At a very late stage for me and a very early stage for this project i became aware of the diaspora project. Basically we are looking to solve very similar problems, but we go about it completely different. They decided to make a network of servers, where everyone is free to open up his own server, and users choose what server to trust and register with, but once that decision is made, it is final. (at least for that seed, a user can always open up a new seed.)
> This approach does eliminate the monopoly of companies over the server, but keeps the user data stored in 3rd party hands.
> My approach was to eliminate the main servers altogether, and install mini servers that are supposed to serve only a handfull of closely coupled profiles (family members, cubicle partners...) and rely on the transportation medium to do the data sync and management of profile comminications.
> With a few adjustments to diaspora, and the correct installation package - diaspora could support my philosophy as well. But i am not sure whether i am ready to give up on mine, or whether it can trully work inside the disapora ecosystem.

2012-08-13

> OK a fresh look at things.

> - A node will consist of several parts: The admin web app; the node API; And a web client installation;
 - The admin web app will be responsible for a single task: installation and setup of the node and its requirments. (IP filtering, administration users, port listening, database connection...)
 - The node API will be a json-rpc API that will allow openid authentication for registered profiles, and to access and manipulate the profile objects, and objects accesible by this profile after authentication. (Perhaps this API will support Server-Side-Events as well.)
 - The web client will be a static HTML+JS application (static so it will be able to work both from a web server and offline) that will access the node API and allow a user to use his profile.
 
> Right now i am still learning the quirks of CppCMS, and as a result i am focusing my efforts in the admin web app. While designing the node itself.

> Objects stored in a node will have:

> - an id (uuid generated on creation of first version) 
> - a version number (starts with 1, then added +1 with each new version) 
> - a version creator node id (the uuid of the node installation that created this version). This will help distinguish versions with the same number that are generated on different nodes in parallel, when such a conflict is noticed, a merge operation is in order (automatic or manual) that will result in a newer version that will override both.
> - parent versions list. The version number and creator node uuid of the versions this version is a descendant from.
> - Objects will be separated into 2 objects, local objects (objects that belong to a profile registered for this node, those objects maintain a certain amount of version history in the database, but only their latest version is used for the user) and remote objects (objects that where requested from this node, but belong to a different node, and where obtained from it) those objects will use an expiration policy to determine if they are kept in the db.
> - history policy, that will tell the node how far back to maintain history for this object. the longer the history that is kept, the better the offline sync between different nodes that maintain this same object, but this comes at the expense of storage space.
> - expiration policy, this will tell the node how to treat this object remotely. The expiration policy will include the creation date for the object, a date or duration where this object is to be refreshed in the background once it is used, and a date or duration where this object becomes invalid and should be removed from the remote storage.
> - local objects will have an unparsed ACL. This ACL will be in user friendly terms, and will be able to contain refrences to user defined groups.
> - local & remote objects will have a parsec ACL. This is a *white list* of all profiles allowed to view this object, along with the actions they are allowed to do on this object. This ACL will also support a Joker entry that will allow all those not listed specifically a certain set of permissions. The parsed ACL list will be maintained and updated by the node, and each new version of the ACL will generate anew version of the object.
> - type, each object will have a reference to its type object (also an object in itself)
> - content, Each obeject will have its JSON data fields
> - content signature, RSA signature of the JSON content using the profile that generated it signature.
> - metadata signature, RSA signature of the object metadata

> The node API will allow for retrieving the current object fully, or only its metadata summary (identification fields+ACL+signatures.) The idea is that if a node has a remote object that needs to be checked for its valitity, there is no point in requesting its content, it is better to first check if there is a need for refresh by accessing the metadata. (this might change later to an API that will be passed object identification+signatures and will return the full object only if necesary.)

> Type objects will be objects just like any other object, they will defere in their content alone.

> - Type objects will have a parent type reference
> - Action connection, a collection of named actions along with their action definition.
> - Default action names, a single name, or a client based map of action names to be used for a default action name based on the client type identification. (web interface does not need the same action functionality as an IM program plugin)
> - Distribution policy for objects of this type, whether such objects should be pushed to encouraged contacts, or only be accessible using polling from other nodes.

> The type actions definitions will have the folowing options:

> - null; nothing will be done by this action, in fact this is simply to allow removal of actions inherited from parent views
> - another action name, this will mean that when calling this action, a call to the named action will be performed instead.
> - a JS function; This function will be run by the node each time this node is accessed, and from this function object manipulations will be performed.

> Type objects once loaded into the node will be parsed and a complete JS code will be jenerated for them to be stored in the DB, after resolving all inheritance issues. This stored JS code will be used each time an object of that type is used.

> The cycle of handling an object request from a client by the node:

> 1. Find the proper object, return error is object could not be found.
> 2. Find the object type, return error is tye could not be found.
> 3. Determin what action to perform from the request, the client identification and type definition.
> 4. Run the type action on the object and the request, returning the result to the client.

> The default parent type will contain a JS template finding mechanism, and binding of data from the JSON object into the template. And thanks to inheritance, this mechanism will be made avaliable to all other types.

> Profiles will have objects linking them to other "followed" profiles. A followed profile is notified on this object, and if it wants it will place this followed on its "encouradged" list, encouradged contacts will recieve a pushed object of every object they are allowed to see (accoding to ACL) that belong to a type that its distribution policy is push. This means that those users will see the latest version first time they try to access that object, and will not have to wait for the object to update while they are looking at an older version.

> This means that profiles have 4 different types of relations to other profiles:

> - Not linked, in this case only a completely public objects from that profile will be visible (objects with a joker in their ACL), and those objects will be refreshed based on access (or a profile refresh policy.

2012-08-08

Ok after some thinking the rules will be like this:

 - The node will store an in memory JS vm LRU cache for each authenticated client (guest access is something i will have to think about)
 - This client VM will contain a JS object that will be used for the handling of all content by the server. This object will include a property for each of the used types - this way types can refer to each other.
 - Loading of a new type will be done by: converting the type definition from json with strings into JS code that will be run inside the VM. A type will reference its parent type as its prototype. Type names will be mangled by the server in order to generate uniqu names - and make them unusable directly - only through inheritance and object inclusions
 - The basic parent view will have no such prototyping, instead it will contain all the fundamental framework for handling node->client bindings
 - View actions will be again JS functions, refrences to other actions or to a specific action in another type. calling to another action in the same view can be done simply by using its name - calling actions from another type can be done only by referencing that action inside this view and then calling it by the referencing name.
 - The implementation of the actions will be as an actions object inside the view object. - again actions will prototype the actions of their parent view.
 - Each action will recieve the folling parameter:
    - the json object from the server this action relates too.
    - some information about the request: (json info recieved from the client for the action, client type, identification, profile, ...)
    - a response object used to make his response. This object will give API to perform operations on the object: new version, generate a child object of a certain type... This response will also be responsible for performing validity checks on the incoming json object, and will be able to return and attach responses to the server object. That server object will later be used for the rendering phase (along with any additions done to it on the action stage). This server object can also tell the server that a different object & view combination should be returned as a response.

Reading what i just wrote - i guess the binding phase is just another action being performed. So if that is the case perhaps i should just say so and be done with it by handling them together.

Thikning is a hard work...:)

2012-08-07 2

> Ok the logic here is this: node.js server is still not out of the picture, but i dislike that solution. This might be my next port for the node implementation. But i want a natively compiled node version with all the necesary functionality in it. Besides node.js provide sandboxing issues for the views - a bad view should not affect any user who is not viewing that view right now.

> the objects and types are static things - and as such should not contain any JS in them. The only dynamic part of the system are the views.

> Views are also objects in the system - so they shuold be stored statically - this means that the js code should be enclosed as a string literal.
views should behave differently for the different clients - so the client system remains - but is extended to the template as well. The client support mechanism is extended in the following ways: 

> - providing an "*" client will result in a catch all clients that will fit all clients that are not specifically listed.
 - Entries in the parent view are inherited unless they are overriden.
 - Each entry can contain either: a null value, another entry name, or a js function: function(...){...}
 - A null value will mean that this client have no specific definition and will fall back to the catch all definition.
 - another entry name will mean that whatever function that other entry name will be resolved to, this entry will be resolved too as well.
 - providing a single value will mean that it is used for all clients. (in effect it will mean that all inherited entries have been removed, and a single entry of * was inserted with that value in it. a single value must be a function for a view binder.

> The process of inheritance and function resolving will be done ONCE for the type as it is inserted into the db. and the functions will be stored in a single storage where all views using them will reference them. each function will also specify what view it is defined on. This way if a view updates, all inherited views need not update their function definitions. (not entirely true, changes in the function mappings of a view, will result in function mapping re-done for all inherited views, but function definitions can be replaces behind the scenes. (good for bug fixing)

> The binding schema of the template will be done by the default parent view - this way different binding schemas can be supported by providing a different binding function.

> Perhaps all those binding functions should be defined in a single JS node - providing a way to call one binding schema from another. this will add the need to handle loops in the binding functions - something i want to prevent. So i think the resolving will be done by the server when the type is loaded, and no calls between the different binding functions.

2012-08-07

> I been thinking about http://lovdbyless.com/ a bit more. And i think one of the selling points of my new social network - is that any 3rd party can generate new content types and new functionality that will natively be embeded into the social network infrastructure simply by placing a globaly visible node that will publish new object types.

> Off to another topic. Since the client capabilities are not known, and communication between the client and the node serving it are meant to be trivial in terms of time and avaliability (supposed to be on the same machine or LAN). Then why not provide all the necesary functionality in the server, and rely on server client roundtrips rather then client side scripting.
I think that support for client side scripting is important, but using the round trips will allow better type system support. But it will mean that the views will have to be run on the server, and since views are defined by their publishers, and are versionint objects themselvs, my best bet will be to have some "compiled"/"prepared" version of them in memory to be used whenever i need to serv an object of that type. (initial versions will not contain any caching of such things, but later an LRU cache is a natural development in my mind.)
So right now i see an object type as something like this:

    {
       // all the object regular identification fields, including the type that say this is a type object
       content {
         default-client-type: , // the default client type name expected to use this object - web-client or no-support normally - used to find the default view if no view is defined for the current client type. assumed to be no-support if missing
         default-views: {
           client-type-1: , // obj ref of the default view object for this type
           client-type-2: , // obj ref of the default view object for this type
           client-type-3: , // obj ref of the default view object for this type
           no-support: // obj ref of a p2psn no support view object - that object simply return the string: "Not Supported object type: "+type identification
         }
       },
       // all the signatures expected form any object
    }

> and a view will be something like this:

    {
       // all the object regular identification fields, including the type that say this is a view object
       content {
         base-view: , // obj reference for the view this view inherits from (optional, but if it is ommited, then view will inherit from the p2psn base view object (this is to make sure every view has the necesary functions)
         template: "", // optional string template that contain all the necesari obj2template binding - this binding is done by the server
         template-binder: "", // optionally a js function code that defines a function with the following signature: f(template, object) and returns a string of the binded template
         action_handlers: {
           action-1: "", // a js function that performs validation and handling on the json object returned from the client. this function follows the signature: f(obj /* the json object got from the action */, server /* the API object for performing server operations like creating a new object version, or generating a new child object */) 
         }
       },
       // all the signatures expected form any object
    }

> all the js functions must assume no state, although i expect to keep an LRU in memory cache of them, each function can be gone from the cache with out any prior warning.

> all this work on JS and creating some JS based hirarchy of views and types with actions and handlers and hooks etc... all this brings the question: is cppcms the correct option - or perhaps i am better of living in a nodejs server for example. (http://nodejs.org/)
if i continue with cppcms, i will need some js engine embeded in it - v8 is a good posibility https://developers.google.com/v8
Also i need to think how to handle JS dependancies within those embeded js functions (perhaps: http://requirejs.org/)

> Lastly just a reminder so i will not lose it: i intend for the noded to be an openid provider for its profiles, and allow any openid authentication provider to be attached to the profiles. this way, people can authenticate using whatever website they want, and if they have a public node - they can also use it to authenticate elseware. (http://openid.net/ perhaps using http://kin.klever.net/libopkele/)

> One more point: at some point i will want to place: https://flattr.com/ button in - but way into the future

2012-08-05

> I been thinking about the client side of things.
The idea is that the server gives the latest (or specific) version of the object data. and gives the correct view for that object type and client type. The question is how to link them together properly.
The view will of course be an HTML5 fragment, with JS code attached to it. At the same time it should contain some data-binding schema that binds the object data into the html fragment and JS code.
Frst of there is a separation between the data-binding from the object to the view and the data-updating from the view to the server.
The data-updating will be done using the json-rpc api that will be exposed.
The data-binding have two options:

> 1. Perform the data-binding in the server, and then send the bnded HTML5+JS to the client after the binding.
2. Send the building blocks to the client (HTML5+JS with binding tags to the client, and JSON object representation) and then perform the binding using JS on the client.

> I think both situations will be needed.

> A few links i need to remember:

> * http://lovdbyless.com/ - an open source server based social network
> * http://www.requirejs.org/ - the way i see it - each view needs a template and a scripting support. a url that gives the correct view using a response to requirejs request, will give a very nice result in this.

> I need to decide where how my view templates will look - and since i want them to be html5 complient - they can not use the usual <%...%> syntax. One way will be to use the data attributes in something like this: 

> View: <a data-p2psn-bind-text="content.title" data-p2psn-bind-href="contenr.url" />
> Json: { content : { title : "P2Psn", url : "https://github.com/lee-elenbaas/p2psn" } /* , more of the object udentification - like signature... */ }

> Resulting html: <a href="https://github.com/lee-elenbaas/p2psn">P2Psn<a/>

> Another approach is to use JS for the view template - this has the advantage of keeping things locally where each JS view function will recieve the following parameters:

     function form(
       formId, // string - unique for the page
       obj // json object of the viewed object
     )

> this way views can be made indipendent and can handle their own id with no collusion for the objects within them.

2012-07-28

> I have been reading about all sort of deelopment frameworks, and i am questioning my decision to go CppCMS. 
The one i liked best is www.meteor.com, a javascript only framework that work on client and server at the same time, with automatic synchronization between the server and all clients.
Actually this looks like a very very good solution for the node clients: the objects are the json objects exposed as the data, while the display layer are the javascript layouts.
the only problem is that the used layouts depends on the client app type and the approved layouts by the user. this can be overcome by properly quering the layout db. 
The real problem with the meteor solution is packaging. meteor requires a node.js server with mongodb - this means that the end installation is not a single executable like in cppcms, instead it needs a whole installation process. for development it will be ok, but for a finished product it is out of the question for me. 
So in the end i have stayed with my original decision of cppcms.

2012-07-10

> I had a long talk a few days ago with a friend about the futility of this project. Very unpleasent, but i can't say his points are not not valid. Nevertheless I still feel that working on this project equals doing something to change the world we live in, rather then letting it fester on its own.

> I had some thoughts about the logo for this project. The main idea is a mesh of poeple holding hands. The best idea for showing this is a star with the points being people and the lines hands those people are holding to each other. I wanted to see if i can get the help of a family member in making this idea for a logo a reality, and i will ask about it in the next few days.

> Some thoughts about the working of other services with p2psn. In order to allow login to other sites using p2psn authentication, and allow accesss to the friends list or online communication infrastructure from p2psn in other websites, all the p2psn services needs to be accessible in the exact same way on every machine it is installed on. This means a static port, or a way to discover the ip, port & protocol used to access the p2psn api.
Since by design the ip address of the p2psn installation can be different on different home networks, there must be a way to rediscover the exact api url. I think that the best way to do that is by using a browser stored value that will be set after every successfull login to the web client. Then this value will be accessible to all external applications that will use the same browser.

2012-07-02

> I been thinking about packing the p2psn application. 
Building it properly for *nix systems will mean that it will not compile for windows, or that my code needs to be polluted with #ifdef branches. So in the end i decided that at this point in the life of the project, i will build it only for *nix systems, with cygwin support, and just open myself issues and place TODO comments where i think windows incompatibility is creeping in.
The same issue is raised for the client interface. I wanted to use HTML5 technologies - sadly the subset of HTML5 supported by each browser is not the same at this point in time. So I decided to build for one browser only, and then find the solutions for the other browsers later on in the life of this project. Again issues and TODO comments will be placed where i think incompabilities are expected. The browser i selected right now is firefox.

> The next question is what web-server to be using: The choice was made easy this time, and i selected to go with the internal CppCMS web server. Although it is for debugging, has bad performance compared to others, it has the advantages of being bundled with the application, with all its configuration sites comfortably with the rest of my configuration. I will need guids for how to set up the application on other web servers once it is done.

2012-06-30

> In the past week i managed to reorgenize the repository a bit. And get myself to a working application based on the CppCMS tutorial applications and the documentation. Nothing is actuall being done yet - but the main framework is begining to unravel for me.

2012-06-24

> I feel slightly better with C++11 now. I am still far from being able to use it fluently, but i decided it is time to start orgenizing the CppCMS project - a simple hellow world is enough for now.

2012-06-21

> I been busy learning C++11 as the basis for this project.
And finally got myself a few functions that i think should work well. So now i need to finish the testing framework around it.

> I am also attempting to get a friend into this project, i am missing somone to talk to about this.

2012-06-05

> Ok, I started a few days after i started this repository.
The initial step was getting the idea strait inside my mind. It is not at all complete yet, but the major theams are already set i my mind.
After deciding that CppCMS is my tool of choice for this project, I decided to sit down and learn it. And came to the conclustion that i need a refresher in C++. I started with some math classes that i think will come in handy in this project, worst case, I learn C++11 this way.


