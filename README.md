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

The node database will be SQLite using the CppDB library - this is a very lightweight database that has the folowing advantages: using this library it can be easily replaces by a larger database solution like postgresql. It is very light in its demands. It provides most of the necesary functionality and the rest can be wrapped rather easily. And lastly, i never worked with it, so i have something new to learn.

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


