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

# 記録用データファイルを，appendでopenする.
# データファイル名は"answer.log".
open(LOG1,">> reserve.log");
print LOG1 "\"$yourname\",\"$phone\",\"$email\",\"$date\",\"$\stay\",\"$answer1\",\"$answer2\"\n";
close(LOG1);

#ブラウザへのメッセージ出力
print "Content-type: text/html; charset=EUC-JP\n\n";
print "<HTML><BODY BGCOLOR=\"YELLOW\">\n";
print "$yourname 様、宿泊のご予約まことに有り難うございました。<P>\n";

print "宿泊予約の確認メールを $email 宛、送信させて戴きました。<P>\n";
print "</BODY></HTML>\n";

__END__
