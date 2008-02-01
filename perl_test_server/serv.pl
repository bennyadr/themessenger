#!/usr/bin/perl

use warnings;
use strict;

use POE qw(Component::Server::TCP);

POE::Component::Server::TCP->new
  ( Alias => "stuff",
    Port => 23000,
    ClientInput => sub {
        my ( $session, $heap, $input ) = @_[ SESSION, HEAP, ARG0 ];
        print "Session ", $session->ID(), " got input: $input\n";
        #$heap->{client}->put($input);
      }
  );

# Start the server.

$poe_kernel->run();
exit 0;
