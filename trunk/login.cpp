#include "login.h"
#include "bits.h"
#include "md5.h"
#include "sha.h"
#include "magic_shit.h"
#include "BuddyList.h"


c_Login::c_Login(c_Socket *socket,char* username,char* password)
	:c_Action(HIGH,CREATED),
	m_cSocket(socket)
{
	m_sUsername = strdup(username);
	m_sPassword = strdup(password);
	
};

c_Login::~c_Login()
{
	delete [] m_sUsername;
	delete [] m_sPassword;
};

void c_Login::CreateSendFirstAuthPacket()
{

	unsigned int user_name_size = strlen(m_sUsername);
	c_YPacket first_packet(15,YAHOO_SERVICE_AUTH,YAHOO_STATUS_AVAILABLE,0);
	
	unsigned char data[14];

	//add first 1 byte -- pidgin style :)
	memset(data,0x31,1);
	//add separator
	Bits::memset_short(data+1,YAHOO_STD_SEPARATOR,2);

	//add username
	memcpy(data+3,m_sUsername,user_name_size);

	//add separator
	Bits::memset_short(data+3+user_name_size,YAHOO_STD_SEPARATOR,2);	

	first_packet.SetData(data);
		
	m_cSocket->Write(first_packet);
	
};

void c_Login::RecvAndSendAuthResponse()
{
	c_YPacket receive_packet;
	m_cSocket->Read(receive_packet);
	CreateAuthResponse(receive_packet);
};

void c_Login::CreateAuthResponse(c_YPacket& packet)
{
	unsigned char *data_recv = packet.GetData();
	unsigned char *seed = NULL;
	int isUsername = memcmp(data_recv+3,m_sUsername,strlen(m_sUsername));
	if(*(data_recv+15) == '9' && *(data_recv+16) == '4' && *(data_recv)=='1' && !isUsername )
	{
		seed = data_recv+19;
		unsigned char magic_shit6[128];
		unsigned char magic_shit96[128];
		MagicShit(seed,magic_shit6,magic_shit96);

		unsigned char data[256];
		unsigned int username_len = strlen(m_sUsername);
		c_YPacket auth_packet(2*username_len+150,YAHOO_SERVICE_AUTHRESP,YAHOO_STATUS_AVAILABLE,0);

		//add first 1 byte -- pidgin style :)
		memset(data,0x31,1);

		//add separator
		Bits::memset_short(data+1,YAHOO_STD_SEPARATOR,2);

		//add username
		memcpy(data+3,m_sUsername,username_len);

		//add separator
		Bits::memset_short(data+3+username_len,YAHOO_STD_SEPARATOR,2);	

		memset(data+3+username_len+2,0x36,1);
	
		//add separator
		Bits::memset_short(data+6+username_len,YAHOO_STD_SEPARATOR,2);

		memcpy(data+8+username_len,magic_shit6,50);

		//add separator
		Bits::memset_short(data+58+username_len,YAHOO_STD_SEPARATOR,2);

		Bits::memset_short(data+username_len+60,0x3936,2);		

		//add separator
		Bits::memset_short(data+62+username_len,YAHOO_STD_SEPARATOR,2);

		memcpy(data+username_len+64,magic_shit96,50);				
		
		//add separator
		Bits::memset_short(data+114+username_len,YAHOO_STD_SEPARATOR,2);
	
		memset(data+username_len+116,0x31,1);

		//add separator
		Bits::memset_short(data+117+username_len,YAHOO_STD_SEPARATOR,2);
	
		//add username again
		memcpy(data+username_len+119,m_sUsername,username_len);
	
		//add separator
		Bits::memset_short(data+119+2*username_len,YAHOO_STD_SEPARATOR,2);	


		//the ending shit
		unsigned char funky_shit[29] = {0x32,0x34,0x34,0xC0,0x80,0x32,0x30,0x39,0x37,0x30,0x38,0x37,0xC0,
		0x80,0x31,0x33,0x35,0xC0,0x80,0x2E,0x31,0x2E,0x30,0x2E,0x34,0x32,0x31,0xC0,0x80};
		memcpy(data+121+2*username_len,funky_shit,29);
				
		auth_packet.SetData(data);
		
		if(m_cSocket->is_Opened())
		{
			m_cSocket->Write(auth_packet);
		}

    }
	else
		cout<<"CreateAuthResponse::invalid authentication method"<<endl;
	
};

void c_Login::Execute()
{
	CreateSendFirstAuthPacket();
	RecvAndSendAuthResponse();
	GetBuddyList();
	m_iStatus = DONE;
};

void c_Login::GetBuddyList()
{
	c_YPacket list_pack;
	c_BuddyList *buddylist = new c_BuddyList();
	//read buddies
	do
	{
		m_cSocket->Read(list_pack);	
		if(list_pack.GetService() == YAHOO_SERVICE_BUDDYLIST)
		{
			buddylist->GetBuddyList(list_pack);
			list_pack.Clear();
		}
	}
	while(list_pack.GetService() == YAHOO_SERVICE_BUDDYLIST);	
	//get online buddies
	if(list_pack.GetService() == YAHOO_SERVICE_BUDDYLIST_ONLINE)
	{
		//TODO
	}

};

/*this wrapps arround the libyahoo2 auth function;
 even if I find this code obfuscated and kind of stupid,
using it it's the only solution for now*/
// I couldn't find a full description of the auth method 'till now
// and i'm not willing to spend time understanding this deprecated c code
// if you know one let me know!!	
void c_Login::MagicShit(unsigned char* seed,unsigned char *magic_shit,unsigned char *magic_shit1)
{
	md5_byte_t         result[16];
	md5_state_t        ctx;

	SHA_CTX            ctx1;
	SHA_CTX            ctx2;

	char *alphabet1 = "FBZDWAGHrJTLMNOPpRSKUVEXYChImkwQ";
	char *alphabet2 = "F0E1D2C3B4A59687abcdefghijklmnop";

	char *challenge_lookup = "qzec2tb3um1olpar8whx4dfgijknsvy5";
	char *operand_lookup = "+|&%/*^-";
	char *delimit_lookup = ",;";

	unsigned char password_hash[26];
	unsigned char crypt_hash[26];
	char *crypt_result = NULL;
	unsigned char pass_hash_xor1[64];
	unsigned char pass_hash_xor2[64];
	unsigned char crypt_hash_xor1[64];
	unsigned char crypt_hash_xor2[64];
	unsigned char chal[7];
	char resp_6[100];
	char resp_96[100];

	unsigned char digest1[20];
	unsigned char digest2[20];
	unsigned char magic_key_char[4];
	const unsigned char *magic_ptr;

	unsigned int  magic[64];
	unsigned int  magic_work=0;

	char comparison_src[20];

	int x, j, i;
	int cnt = 0;
	int magic_cnt = 0;
	int magic_len;
	int depth =0, table =0;

	memset(&pass_hash_xor1, 0, 64);
	memset(&pass_hash_xor2, 0, 64);
	memset(&crypt_hash_xor1, 0, 64);
	memset(&crypt_hash_xor2, 0, 64);
	memset(&digest1, 0, 20);
	memset(&digest2, 0, 20);
	memset(&magic, 0, 64);
	memset(&resp_6, 0, 100);
	memset(&resp_96, 0, 100);
	memset(&magic_key_char, 0, 4);

	/* 
	 * Magic: Phase 1.  Generate what seems to be a 30 
	 * byte value (could change if base64
	 * ends up differently?  I don't remember and I'm 
	 * tired, so use a 64 byte buffer.
	 */

	magic_ptr = (unsigned char *)seed;

	while (*magic_ptr != 0xC0 && *(magic_ptr+1) != 0x80) {
		char *loc;

		/* Ignore parentheses.  */

		if (*magic_ptr == '(' || *magic_ptr == ')') {
			magic_ptr++;
			continue;
		}

		/* Characters and digits verify against 
		   the challenge lookup.
		*/

		if (isalpha(*magic_ptr) || isdigit(*magic_ptr)) {
			loc = strchr(challenge_lookup, *magic_ptr);
			if (!loc) {
				/* This isn't good */
				continue;
			}

			/* Get offset into lookup table and lsh 3. */

			magic_work = loc - challenge_lookup;
			magic_work <<= 3;

			magic_ptr++;
			continue;
		} else {
			unsigned int local_store;

			loc = strchr(operand_lookup, *magic_ptr);
			if (!loc) {
				/* Also not good. */
				continue;
			}

			local_store = loc - operand_lookup;

			/* Oops; how did this happen? */
			if (magic_cnt >= 64) 
				break;

			magic[magic_cnt++] = magic_work | local_store;
			magic_ptr++;
			continue;
		}
	}

	magic_len = magic_cnt;
	magic_cnt = 0;

	/* Magic: Phase 2.  Take generated magic value and 
	 * sprinkle fairy dust on the values. */

	for (magic_cnt = magic_len-2; magic_cnt >= 0; magic_cnt--) {
		unsigned char byte1;
		unsigned char byte2;

		/* Bad.  Abort.
		 */
		if (magic_cnt >= magic_len) {
			cout<<"magic_cnt"<<magic_cnt<<"magic_len"<<magic_len<<endl;
			break;
		}

		byte1 = magic[magic_cnt];
		byte2 = magic[magic_cnt+1];

		byte1 *= 0xcd;
		byte1 ^= byte2;

		magic[magic_cnt+1] = byte1;
	}

	/* Magic: Phase 3.  This computes 20 bytes.  The first 4 bytes are used as our magic 
	 * key (and may be changed later); the next 16 bytes are an MD5 sum of the magic key 
	 * plus 3 bytes.  The 3 bytes are found by looping, and they represent the offsets 
	 * into particular functions we'll later call to potentially alter the magic key. 
	 * 
	 * %-) 
	 */ 
	
	magic_cnt = 1; 
	x = 0; 
	
	do { 
		unsigned int     bl = 0;  
		unsigned int     cl = magic[magic_cnt++]; 
		
		if (magic_cnt >= magic_len) 
			break; 
		
		if (cl > 0x7F) { 
			if (cl < 0xe0)  
				bl = cl = (cl & 0x1f) << 6;  
			else { 
				bl = magic[magic_cnt++];  
                              cl = (cl & 0x0f) << 6;  
                              bl = ((bl & 0x3f) + cl) << 6;  
			}  
			
			cl = magic[magic_cnt++];  
			bl = (cl & 0x3f) + bl;  
		} else 
			bl = cl;  
		
		comparison_src[x++] = (bl & 0xff00) >> 8;  
		comparison_src[x++] = bl & 0xff;  
	} while (x < 20); 

	/* Dump magic key into a char for SHA1 action. */
	
		
	for(x = 0; x < 4; x++) 
		magic_key_char[x] = comparison_src[x];

	/* Compute values for recursive function table! */
	memcpy( chal, magic_key_char, 4 );
        x = 1;
	for( i = 0; i < 0xFFFF && x; i++ )
	{
		for( j = 0; j < 5 && x; j++ )
		{
			chal[4] = i;
			chal[5] = i >> 8;
			chal[6] = j;
			md5_init( &ctx );
			md5_append( &ctx, chal, 7 );
			md5_finish( &ctx, result );
			if( memcmp( comparison_src + 4, result, 16 ) == 0 )
			{
				depth = i;
				table = j;
				x = 0;
			}
		}
	}

	/* Transform magic_key_char using transform table */
	x = magic_key_char[3] << 24  | magic_key_char[2] << 16 
		| magic_key_char[1] << 8 | magic_key_char[0];
	x = yahoo_xfrm( table, depth, x );
	x = yahoo_xfrm( table, depth, x );
	magic_key_char[0] = x & 0xFF;
	magic_key_char[1] = x >> 8 & 0xFF;
	magic_key_char[2] = x >> 16 & 0xFF;
	magic_key_char[3] = x >> 24 & 0xFF;

	/* Get password and crypt hashes as per usual. */
	md5_init(&ctx);
	md5_append(&ctx, (md5_byte_t *)m_sPassword,  strlen(m_sPassword));
	md5_finish(&ctx, result);
	to_y64(password_hash, result, 16);

	md5_init(&ctx);
	crypt_result = yahoo_crypt(m_sPassword, "$1$_2S43d5f$");  
	md5_append(&ctx, (md5_byte_t *)crypt_result, strlen(crypt_result));
	md5_finish(&ctx, result);
	to_y64(crypt_hash, result, 16);

	/* Our first authentication response is based off 
	 * of the password hash. */

	for (x = 0; x < (int)strlen((char *)password_hash); x++) 
		pass_hash_xor1[cnt++] = password_hash[x] ^ 0x36;

	if (cnt < 64) 
		memset(&(pass_hash_xor1[cnt]), 0x36, 64-cnt);

	cnt = 0;

	for (x = 0; x < (int)strlen((char *)password_hash); x++) 
		pass_hash_xor2[cnt++] = password_hash[x] ^ 0x5c;

	if (cnt < 64) 
		memset(&(pass_hash_xor2[cnt]), 0x5c, 64-cnt);

	shaInit(&ctx1);
	shaInit(&ctx2);

	/* The first context gets the password hash XORed 
	 * with 0x36 plus a magic value
	 * which we previously extrapolated from our 
	 * challenge. */

	shaUpdate(&ctx1, pass_hash_xor1, 64);
	if (j >= 3)
		ctx1.sizeLo = 0x1ff;
	shaUpdate(&ctx1, magic_key_char, 4);
	shaFinal(&ctx1, digest1);

	 /* The second context gets the password hash XORed 
	  * with 0x5c plus the SHA-1 digest
	  * of the first context. */

	shaUpdate(&ctx2, pass_hash_xor2, 64);
	shaUpdate(&ctx2, digest1, 20);
	shaFinal(&ctx2, digest2);

	/* Now that we have digest2, use it to fetch 
	 * characters from an alphabet to construct
	 * our first authentication response. */

	for (x = 0; x < 20; x += 2) {
		unsigned int    val = 0;
		unsigned int    lookup = 0;
		char            byte[6];

		memset(&byte, 0, 6);

		/* First two bytes of digest stuffed 
		 *  together.
		 */

		val = digest2[x];
		val <<= 8;
		val += digest2[x+1];

		lookup = (val >> 0x0b);
		lookup &= 0x1f;
		if (lookup >= strlen(alphabet1))
			break;
		sprintf(byte, "%c", alphabet1[lookup]);
		strcat(resp_6, byte);
		strcat(resp_6, "=");

		lookup = (val >> 0x06);
		lookup &= 0x1f;
		if (lookup >= strlen(alphabet2))
			break;
		sprintf(byte, "%c", alphabet2[lookup]);
		strcat(resp_6, byte);

		lookup = (val >> 0x01);
		lookup &= 0x1f;
		if (lookup >= strlen(alphabet2))
			break;
		sprintf(byte, "%c", alphabet2[lookup]);
		strcat(resp_6, byte);

		lookup = (val & 0x01);
		if (lookup >= strlen(delimit_lookup))
			break;
		sprintf(byte, "%c", delimit_lookup[lookup]);
		strcat(resp_6, byte);
	}

	/* Our second authentication response is based off 
	 * of the crypto hash. */

	cnt = 0;
	memset(&digest1, 0, 20);
	memset(&digest2, 0, 20);

	for (x = 0; x < (int)strlen((char *)crypt_hash); x++) 
		crypt_hash_xor1[cnt++] = crypt_hash[x] ^ 0x36;

	if (cnt < 64) 
		memset(&(crypt_hash_xor1[cnt]), 0x36, 64-cnt);

	cnt = 0;

	for (x = 0; x < (int)strlen((char *)crypt_hash); x++) 
		crypt_hash_xor2[cnt++] = crypt_hash[x] ^ 0x5c;

	if (cnt < 64) 
		memset(&(crypt_hash_xor2[cnt]), 0x5c, 64-cnt);

	shaInit(&ctx1);
	shaInit(&ctx2);

	/* The first context gets the password hash XORed 
	 * with 0x36 plus a magic value
	 * which we previously extrapolated from our 
	 * challenge. */

	shaUpdate(&ctx1, crypt_hash_xor1, 64);
	if (j >= 3)
		ctx1.sizeLo = 0x1ff;
	shaUpdate(&ctx1, magic_key_char, 4);
	shaFinal(&ctx1, digest1);

	/* The second context gets the password hash XORed 
	 * with 0x5c plus the SHA-1 digest
	 * of the first context. */

	shaUpdate(&ctx2, crypt_hash_xor2, 64);
	shaUpdate(&ctx2, digest1, 20);
	shaFinal(&ctx2, digest2);

	/* Now that we have digest2, use it to fetch 
	 * characters from an alphabet to construct
	 * our first authentication response.  */

	for (x = 0; x < 20; x += 2) {
		unsigned int val = 0;
		unsigned int lookup = 0;

		char byte[6];

		memset(&byte, 0, 6);

		/* First two bytes of digest stuffed 
		 *  together. */

		val = digest2[x];
		val <<= 8;
		val += digest2[x+1];

		lookup = (val >> 0x0b);
		lookup &= 0x1f;
		if (lookup >= strlen(alphabet1))
			break;
		sprintf(byte, "%c", alphabet1[lookup]);
		strcat(resp_96, byte);
		strcat(resp_96, "=");

		lookup = (val >> 0x06);
		lookup &= 0x1f;
		if (lookup >= strlen(alphabet2))
			break;
		sprintf(byte, "%c", alphabet2[lookup]);
		strcat(resp_96, byte);

		lookup = (val >> 0x01);
		lookup &= 0x1f;
		if (lookup >= strlen(alphabet2))
			break;
		sprintf(byte, "%c", alphabet2[lookup]);
		strcat(resp_96, byte);

		lookup = (val & 0x01);
		if (lookup >= strlen(delimit_lookup))
			break;
		sprintf(byte, "%c", delimit_lookup[lookup]);
		strcat(resp_96, byte);
	}
	/*	for(unsigned int i=0;i<100;i++)
				fprintf(stdout, "%02X ", resp_6[i]);
			cout<<endl;
		for(unsigned int i=0;i<100;i++)
			fprintf(stdout,"%02X ",resp_96[i]);
			cout<<endl;*/
		memcpy(magic_shit,resp_6,50);
		memcpy(magic_shit1,resp_96,50);
/*
	pack = yahoo_packet_new(YAHOO_SERVICE_AUTHRESP, yd->initial_status, yd->session_id);
	yahoo_packet_hash(pack, 0, sn);
	yahoo_packet_hash(pack, 6, resp_6);
	yahoo_packet_hash(pack, 96, resp_96);
	yahoo_packet_hash(pack, 1, sn);
	yahoo_send_packet(yid, pack, 0);
	yahoo_packet_free(pack);

	free(password_hash);
	free(crypt_hash);*/
};

