var re = /\\*(?=.*:)/
var sub = '/'

do
{
    var str = WScript.StdIn.ReadLine()
    WScript.Echo(str)
    str.replace(re, sub)
    WScript.Echo(str)
}
while (!WScript.StdIn.AtEndOfStream)