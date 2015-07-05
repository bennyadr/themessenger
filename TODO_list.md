# TODO list #

This is the TODO list with various things we want implemented.

The priority is descending from top to bottom.

### Finding out some of the protocol ###

The protocol for yahoo messenger seems to be proprietary
  * finding how to log in
  * is there any encryption envolved ?
  * how to get the "buddy list"

[authentication scheme code](http://search.cpan.org/src/VARUNK/Net-YMSG-1.2/YMSG/CRAM.pm)

[src1](http://search.cpan.org/src/VARUNK/Net-YMSG-1.2/YMSG.pm)

[protocol described in 2004](http://libyahoo2.sourceforge.net/ymsg-9.txt)


### Constructing a configuration file ###

It's very obvious why this is very **URGENT!!!**

This is very important because we can have multiple configuration

on various computers while developing.

If one sets constants in a source file the client will end up beeing

compiled with those constant values.

Links describing a library wich will be used for this:

[article1](http://www.xml.com/lpt/a/475)
[article2](http://www.codeproject.com/KB/XML/expatimpl.aspx?display=Print)

### Constructing a graphical interface ###

A very simple interface in Qt.