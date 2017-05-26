#!/usr/bin/perl
$|=1;
use  lib '/home/httpd/cgi-bin';
require 'cgi-lib.pl';
if(-e "count.dat"){
if(not open(FILE,"< count.dat"))
{
	die "file open error\n";
}
$count = <FILE>;
close(FILE);
$count = $count + 1;
open(FILE,"> count.dat");
flock FILE,2;
print FILE $count;
close(FILE);
}
else
{
$count = 1;
open(FILE,"> count.dat");
flock FILE,2;
print FILE $count;
close(FILE);
}
print "Content-type: text/html; charset=UTF-8\n\n";
print "<HTML><BODY BGCOLOR=\"PINK\">\n";
print "<form method=\"post\"action=\"count2.cgi\">\n";
print "<H2 ALIGN=CENTER>あなたは$count番目の閲覧者です.</H2><hr>\n";
&ReadParse(*datai);
if($datai{'message'}){
$message = $datai{'message'};
$count--;
open(LOG1,"+>> log.dat");
print LOG1 "[$count] : $message\n";
close(LOG1);
}
open(tmp ,"<log.dat");
@messages = <tmp>;
foreach $datal(@messages){
print "<font size=+1>$datal</font><br>\n\n";
}
print "<br><hr><table><h3>メッセージを入力してください</h3>\n";
print "<input type=\"TEXT\"name=\"message\">\n";
print "<input value=\"更新\" type=\"submit\">\n";
print "<input value=\"クリア\" type=\"reset\">\n";
print "</table></body></html>\n";
__END__ 