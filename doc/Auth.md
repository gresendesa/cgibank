# Auth

Auth is a class that handles with authentication processes. The basic concept behind this web authentication is the client cookie. Once the user is authenticated through username and/or password the server creates a cookie on the client. This cookie has an unique string identificator. The server stores on database the relation to this string identificator with the client's user.

While the user keeps the cookie the server is able to identificate him without ask for username or password.