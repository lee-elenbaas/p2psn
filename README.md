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

This project is currently centrelized on building a node implementation that can be the building block of such a peer to peer network. A web interface for this node that will allow performing operations in the network. And at the same time finalizing an API that will enable such a network to exists indipendently of the specific node implementation, or client application.

Network Design
--------------
The peer to peer network will be a network of nodes, communicating with each other using peer to peer philosofy.
Each node will support several user profiles and will maintain a database of those profiles along with the objects accessible by those profiles. The node will be responsible for synchronizing those objects with other nodes that serve the same profile, and to send visible objects to other profiles.
Each node will allow clients to authenticate to a profile, and serve those clients as they perform operations on and for this profile.

Node Design
-----------
The node will contain a cyrarchy of CppCMS web applications:

main - The main node app will simply provide links to the apps below it, and display some configuration information needed to configure clients to connect to the node.
 +-- api - The node json-rpc server that will expose the entire functionality to other nodes and client applications.
 +-- web_client - The web client interface implementation that will give some basic user interface to operate inside the network.
 +-- config - Web app that allows to configure the node itself, and to enable/disable the web interface

The the web_client application will communicate with the node web application using json_rpc - either from the server, or from the js on the client side.
The api node implementation will use email as the platform for offline communication between nodes, and json-rpc for online communication between nodes and node to clients.

Web Client
----------
Since the web client is supposed to work in exactly the same way as other UI elements will connect to the node. The interface will use static HTML and JS files delived from the CppCMS server that will communicate using json-rpc with the node_api CppCMS application.
The client can work offline as well - and not just served from the CppCMS.
The only thing that will be dynamic in this client is a default connection information (ip address and port) used to connect to the node_api, in order to allow a user to change those for himself easily. This default connection information will be a static file that will be generated when a new settings is saved by the node_confif app.

Technology
----------
The focus of this project is about the network of nodes. As a result the implementation language is less important then the protocol that will be used between the nodes.

The protocol is based on json-rpc, where each node exposes an API that allows to interact with it using a specific set of json objects.
The UI was chosen natually to be HTML+JavaScript (HTML 5 as much as possible).
The nodes are currently designed to use CppCMS.

The reason behind this choice of tools is simply this: this is a pet project of mine in its infancy. I want to learn CppCMS better, and on paper at least - it looks like a good choice in terms of capabilities performance and platform support.

The offline communication between nodes will be based on a time proven offline protocol: email. The specifics of how the email will be used is not clear to me yet. (The posibilities are: email client add on that communicates with the node using its json-rpc api. Direct pop3/imap and smtp use.

The node database will be contacted through the CppDB library. The default will be a Firebird embedded server that access a file next to the executable. For that i will implement a firebird backend of CppDB using ibpp library.

OpenID support will allow attaching multiple OpenID authentications to every user - and that authentication will be used as a way to login for that user (an opneId will only be allowed to be associated with one user on the same node.) 
The openID support wull use the library libopkele

Licensing
---------
The current plan is to release this project under GPLv3. 
And the static media content using CC Share alike license.

Developers
----------
Lee Elenbaas - lee [dot] elenbaas [at] gmail [dot] com - Owner

Known Issues
------------
Each node needs to deal with large amount of data (all the objects created by its users + all objects visible to the users) and large amount of communication bandwidth (communication of those said objects to other nodes + communication of online status info or other users)
At the same time each node is intended to run on a normal home PC with its limited capabilities.

Development Blog
----------------

2012-08-07

I been thinking about http://lovdbyless.com/ a bit more. And i think one of the selling points of my new social network - is that any 3rd party can generate new content types and new functionality that will natively be embeded into the social network infrastructure simply by placing a globaly visible node that will publish new object types.

Off to another topic. Since the client capabilities are not known, and communication between the client and the node serving it are meant to be trivial in terms of time and avaliability (supposed to be on the same machine or LAN). Then why not provide all the necesary functionality in the server, and rely on server client roundtrips rather then client side scripting.
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

and a view will be something like this:

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

all the js functions must assume no state, although i expect to keep an LRU in memory cache of them, each function can be gone from the cache with out any prior warning.

all this work on JS and creating some JS based hirarchy of views and types with actions and handlers and hooks etc... all this brings the question: is cppcms the correct option - or perhaps i am better of living in a nodejs server for example. (http://nodejs.org/)
if i continue with cppcms, i will need some js engine embeded in it - v8 is a good posibility https://developers.google.com/v8
Also i need to think how to handle JS dependancies within those embeded js functions (perhaps: http://requirejs.org/)

Lastly just a reminder so i will not lose it: i intend for the noded to be an openid provider for its profiles, and allow any openid authentication provider to be attached to the profiles. this way, people can authenticate using whatever website they want, and if they have a public node - they can also use it to authenticate elseware. (http://openid.net/ perhaps using http://kin.klever.net/libopkele/)

One more point: at some point i will want to place: https://flattr.com/ button in - but way into the future

2012-08-05

I been thinking about the client side of things.
The idea is that the server gives the latest (or specific) version of the object data. and gives the correct view for that object type and client type. The question is how to link them together properly.
The view will of course be an HTML5 fragment, with JS code attached to it. At the same time it should contain some data-binding schema that binds the object data into the html fragment and JS code.
Frst of there is a separation between the data-binding from the object to the view and the data-updating from the view to the server.
The data-updating will be done using the json-rpc api that will be exposed.
The data-binding have two options:

1. Perform the data-binding in the server, and then send the bnded HTML5+JS to the client after the binding.
2. Send the building blocks to the client (HTML5+JS with binding tags to the client, and JSON object representation) and then perform the binding using JS on the client.

I think both situations will be needed.

A few links i need to remember:

 * http://lovdbyless.com/ - an open source server based social network
 * http://www.requirejs.org/ - the way i see it - each view needs a template and a scripting support. a url that gives the correct view using a response to requirejs request, will give a very nice result in this.

I need to decide where how my view templates will look - and since i want them to be html5 complient - they can not use the usual <%...%> syntax. One way will be to use the data attributes in something like this: 

View: <a data-p2psn-bind-text="content.title" data-p2psn-bind-href="contenr.url" />
Json: { content : { title : "P2Psn", url : "https://github.com/lee-elenbaas/p2psn" } /* , more of the object udentification - like signature... */ }

Resulting html: <a href="https://github.com/lee-elenbaas/p2psn">P2Psn<a/>

Another approach is to use JS for the view template - this has the advantage of keeping things locally where each JS view function will recieve the following parameters:

     function form(
       formId, // string - unique for the page
       obj // json object of the viewed object
     )

this way views can be made indipendent and can handle their own id with no collusion for the objects within them.

2012-07-28

I have been reading about all sort of deelopment frameworks, and i am questioning my decision to go CppCMS. 
The one i liked best is www.meteor.com, a javascript only framework that work on client and server at the same time, with automatic synchronization between the server and all clients.
Actually this looks like a very very good solution for the node clients: the objects are the json objects exposed as the data, while the display layer are the javascript layouts.
the only problem is that the used layouts depends on the client app type and the approved layouts by the user. this can be overcome by properly quering the layout db. 
The real problem with the meteor solution is packaging. meteor requires a node.js server with mongodb - this means that the end installation is not a single executable like in cppcms, instead it needs a whole installation process. for development it will be ok, but for a finished product it is out of the question for me. 
So in the end i have stayed with my original decision of cppcms.

2012-07-10

I had a long talk a few days ago with a friend about the futility of this project. Very unpleasent, but i can't say his points are not not valid. Nevertheless I still feel that working on this project equals doing something to change the world we live in, rather then letting it fester on its own.

I had some thoughts about the logo for this project. The main idea is a mesh of poeple holding hands. The best idea for showing this is a star with the points being people and the lines hands those people are holding to each other. I wanted to see if i can get the help of a family member in making this idea for a logo a reality, and i will ask about it in the next few days.

Some thoughts about the working of other services with p2psn. In order to allow login to other sites using p2psn authentication, and allow accesss to the friends list or online communication infrastructure from p2psn in other websites, all the p2psn services needs to be accessible in the exact same way on every machine it is installed on. This means a static port, or a way to discover the ip, port & protocol used to access the p2psn api.
Since by design the ip address of the p2psn installation can be different on different home networks, there must be a way to rediscover the exact api url. I think that the best way to do that is by using a browser stored value that will be set after every successfull login to the web client. Then this value will be accessible to all external applications that will use the same browser.

2012-07-02

I been thinking about packing the p2psn application. 
Building it properly for *nix systems will mean that it will not compile for windows, or that my code needs to be polluted with #ifdef branches. So in the end i decided that at this point in the life of the project, i will build it only for *nix systems, with cygwin support, and just open myself issues and place TODO comments where i think windows incompatibility is creeping in.
The same issue is raised for the client interface. I wanted to use HTML5 technologies - sadly the subset of HTML5 supported by each browser is not the same at this point in time. So I decided to build for one browser only, and then find the solutions for the other browsers later on in the life of this project. Again issues and TODO comments will be placed where i think incompabilities are expected. The browser i selected right now is firefox.

The next question is what web-server to be using: The choice was made easy this time, and i selected to go with the internal CppCMS web server. Although it is for debugging, has bad performance compared to others, it has the advantages of being bundled with the application, with all its configuration sites comfortably with the rest of my configuration. I will need guids for how to set up the application on other web servers once it is done.

2012-06-30

In the past week i managed to reorgenize the repository a bit. And get myself to a working application based on the CppCMS tutorial applications and the documentation. Nothing is actuall being done yet - but the main framework is begining to unravel for me.

2012-06-24

I feel slightly better with C++11 now. I am still far from being able to use it fluently, but i decided it is time to start orgenizing the CppCMS project - a simple hellow world is enough for now.

2012-06-21

I been busy learning C++11 as the basis for this project.
And finally got myself a few functions that i think should work well. So now i need to finish the testing framework around it.

I am also attempting to get a friend into this project, i am missing somone to talk to about this.

2012-06-05

Ok, I started a few days after i started this repository.
The initial step was getting the idea strait inside my mind. It is not at all complete yet, but the major theams are already set i my mind.
After deciding that CppCMS is my tool of choice for this project, I decided to sit down and learn it. And came to the conclustion that i need a refresher in C++. I started with some math classes that i think will come in handy in this project, worst case, I learn C++11 this way.


