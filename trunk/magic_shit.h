#ifndef _MAGIC_SHIT
#define _MAGIC_SHIT  

#include "md5.h"
#include "sha.h"

#define IDENT  1 /* identify function */
#define XOR    2 /* xor with arg1 */
#define MULADD 3 /* multipy by arg1 then add arg2 */
#define LOOKUP 4 /* lookup each byte in the table pointed to by arg1 */
#define BITFLD 5 /* reorder bits according to table pointed to by arg1 */

#ifndef MIN
#define MIN(x,y) ((x)<(y)?(x):(y))
#endif

#ifndef MAX
#define MAX(x,y) ((x)>(y)?(x):(y))
#endif

static const char md5_salt_prefix[] = "$1$";
static const char b64t[65] ="./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

struct yahoo_fn
{
	int type; 
	long arg1, arg2;
};

int yahoo_xfrm( int table, int depth, int seed );
char *yahoo_crypt(char *key, char *salt);
void to_y64(unsigned char *out, const unsigned char *in, int inlen);


#endif

