#!/usr/bin/perl
#     __ __  ____ ____
#    |  T  T/    |    \
#    |  |  Y  o  |  D  )
#    l_   _|     |    /
#    |     |  _  |    \
#    |  |  |  |  |  .  Y
#    |__j__l__j__l__j\_j
#          xar - Perl filter for SMTP obfuscation
#
# This little guy needs IO::(Unc|C)ompress::G(un)?zip. On debian systems:
#     # apt install libio-compress-perl
#
# Usage:
#    $ xar.pl < some-source-data > packaged-data
#    $ tar c | xar.pl | mailto -s "here ya go" santa@north.pole
#
# Input is treated as raw, so you can feed it whatever you want
#
use MIME::Base64;
use IO::Compress::Gzip gzip;
binmode STDIN;

print do {local $/; <DATA>};
while (read STDIN, $xar, 4096) {
	gzip \(encode_base64($xar) =~ y/A-Za-z/n-zA-Ma-mN-Z/r) => \$gz;
	$gz = encode_base64($gz); chomp $gz;
	print "xar~~$gz~~xar";
}
print $/;

__DATA__
#!/usr/bin/perl -0777
# Hi! Unwrap me with
#      perl -0777 < me
use MIME::Base64;
use IO::Uncompress::Gunzip gunzip;
binmode STDOUT;
while(<DATA>=~m/xar~~(.*?)~~xar/msixg){
  gunzip \decode_base64($1)=>\$_;
  print decode_base64(y/n-zA-Ma-mN-Z/A-Za-z/r);
}

__DATA__
