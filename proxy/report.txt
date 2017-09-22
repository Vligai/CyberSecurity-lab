Name: Vladislav Ligai

	I have had experience coding server and client before and mitm proxy is basically a combination of both. Mitm proxy acts as a server to client and as a client to the server. Just needed to add SSL to it, establishing encrypted link between server and a client. Before building a proxy create 'log.txt' file to keep the log for later examination and generate 'proxykey.pem' and 'proxycert.pem' as well as 2 others mentioned in the lab description. To build the proxy, go to the directory with a Makefile and type 'make re' or 'make clean' + 'make' and wait untill it is done compiling; this proccess will make an executable called vproxy, to run it type './vproxy [port number]'. After proxy is running start up ssl server and client (description in lab1.pdf).
	If client correctly verified the certificate presented by the server and certificate authorities are used for the client to verify server certificates, attacker could generate fake CA and make client believe that certificate is from the server. This will make client and server believe that they are communicating directly with each other, while mitm proxy captures all traffic between two.

for proxykey.pem:
openssl genrsa -out proxykey.pem 2048

for proxycert.pem:
openssl req -new -x509 -key proxykey.pem -out proxycert.pem -days 1095


