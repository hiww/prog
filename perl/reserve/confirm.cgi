#!/usr/bin/perl
#初期設定
##use lib '/home/httpd/cgi-bin/lib';
require 'cgi-lib.pl';
$|=1;
#送信されたデータの取り込み
&ReadParse(*in_data);
$yourname = $in_data{'yourname'};
$phone = $in_data{'phone'};
$email = $in_data{'email'};
$date = $in_data{'date'};
$stay = $in_data{'stay'};
$answer1 = $in_data{'q1'};
$answer2 = $in_data{'q2'};

#Input_check
if ((($yourname eq "") || ($phone eq "")) || ($email eq "")) {
	print "<HTML><BODY BGCOLOR=\"YELLOW\">\n";
	print "<H1 ALIGN=CENTER>お名前・電話番号・メールアドレスを必ず入力してください。。</H1>\n";
	print "</BODY></HTML>\n";
	die "入力エラー\n";
}

#data_convert
$yourname =~ s/\s*//g; #空白文字の削除
$yourname =~ tr/A-Z/a-z/; #ユーザ名を小文字に変換
$phone =~ s/\s*//g; #空白文字の削除
$email =~ s/\s*//g; #空白文字の削除

#output
print "<HTML><BODY BGCOLOR=\"YELLOW\">\n";
print "<FORM METHOD=\"POST\" ACTION=\"reservation.cgi\">\n";
print "$yourname様、ご予約フォームにご記入戴きありがとうございます．<P>\n";
print "ご予約される部屋の種類：";
if($answer1 eq "a1") { print "シングル（7,000円）"; }
if($answer1 eq "a2") { print "ツイン（12,000円）"; }
if($answer1 eq "a3") { print "ダブル（15,000円）"; }
if($answer1 eq "a4") { print "デラックスツイン（21,000円）"; }
if($answer1 eq "a5") { print "スイート（35,000円）"; }
print "<P>\nチェックイン日・宿泊数：$date から〜 $stay 泊";
print "<P>\n禁煙ルームのご希望：";
if($answer2 eq "a1") { print "禁煙ルームを希望"; }
if($answer2 eq "a2") { print "どちらでもよい"; }
print "<P>\n";
print "<INPUT TYPE=\"HIDDEN\" NAME=\"yourname\" VALUE=\"$yourname\">\n";
print "<INPUT TYPE=\"HIDDEN\" NAME=\"phone\" VALUE=\"$phone\">\n";
print "<INPUT TYPE=\"HIDDEN\" NAME=\"email\" VALUE=\"$email\">\n";
print "<INPUT TYPE=\"HIDDEN\" NAME=\"date\" VALUE=\"$date\">\n";
print "<INPUT TYPE=\"HIDDEN\" NAME=\"stay\" VALUE=\"$stay\">\n";
print "<INPUT TYPE=\"HIDDEN\" NAME=\"q1\" VALUE=\"$answer1\">\n";
print "<INPUT TYPE=\"HIDDEN\" NAME=\"q2\" VALUE=\"$answer2\">\n";

print "このお部屋を予約してよろしいですか？<INPUT TYPE=\"SUBMIT\" VALUE=\"Yes\">\n";

print "</FORM>\n";
print "</BODY></HTML>\n";

__END__
