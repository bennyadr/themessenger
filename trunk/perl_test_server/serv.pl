
#!/usr/bin/perl

use warnings;
use strict;

use POE;
use IO::Socket::INET;

use constant DATAGRAM_MAXLEN => 1024;


my $start_port = shift @ARGV;

POE::Session->create(
    inline_states => {
        _start       => \&server_start,
        get_datagram => \&server_read,
      }
);

POE::Kernel->run();
exit;

sub server_start {
    my $kernel = $_[KERNEL];
	warn "Listening on $start_port";

    my $socket = IO::Socket::INET->new(
        Proto     => 'tcp',
        LocalPort => $start_port,
    );

    die "Couldn't create server socket: $!" unless $socket;
    $kernel->select_read( $socket, "get_datagram" );
}

sub server_read {
    my ( $kernel, $socket ) = @_[ KERNEL, ARG0 ];

    my $remote_address = recv( $socket, my $message = "", DATAGRAM_MAXLEN, 0 );
    return unless defined $remote_address;

    my ( $peer_port, $peer_addr ) = unpack_sockaddr_in($remote_address);
    my $human_addr = inet_ntoa($peer_addr);
    print "(server) $human_addr : $peer_port sent us $message\n";

    $message =~ tr[a-zA-Z][n-za-mN-ZA-M];
    send( $socket, $message, 0, $remote_address ) == length($message)
      or warn "Trouble sending response: $!";
}
