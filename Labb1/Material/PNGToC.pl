#!/usr/bin/perl

use strict;
use GD;

my $image=GD::Image->newFromPng($ARGV[0],1);
die "Couldn't load image \"$ARGV[0]\"" unless $image;

my $width=$image->width;
my $height=$image->height;
my $rows=int(($height+7)/8);

printf "unsigned char ${ARGV[1]}[%d]=\n",$width*$rows;
print "{";

foreach my $row (0..$rows-1)
{
	foreach my $x (0..$width-1)
	{
		my $byte=0;
		foreach my $y (0..7)
		{
			my $c=$image->getPixel($x,$row*8+$y);
			my ($r,$g,$b)=$image->rgb($c);
			$byte|=1<<$y if $r+$g+$b<128*3;
		}

		my $i=$row*$width+$x;
		print "\n\t" if $i%15==0;
		printf "0x%02x,",$byte;
	}
}

print "};\n";


