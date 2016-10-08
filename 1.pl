use 5.010;
while(<>) {
	chomp;
	foreach $i (@w = split(/[^A-Za-z]+/, $_)) {
		$h{lc$i}++;
	}
}
foreach $w (sort{$h{$b} <=> $h{$a}} keys(%h)) {
	say "$w $h{$w}\r";
}

