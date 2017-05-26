#!/usr/bin/perl -w
while(<>) {
	chomp;
	foreach $i (@w = split(/[^A-Za-z]+/, $_)) {
		$h{lc$i}++;
	}
}
foreach $w (sort{$h{$b} <=> $h{$a}} keys(%h)) {
	print "$w $h{$w}\r\n";
}