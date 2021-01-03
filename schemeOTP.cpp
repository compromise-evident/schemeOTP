/// schemeOTP - fast One-time pad for all files up to 1MB
/// Version 2, plausibility ratio = 1:256, number of plausible messages per cipherfile contains 2,408,240 decimal digits.
/// Use schemeOTP to send cipherfiles of unlimited plausible deniability.
/// Guess-keys  decrypt all  cipherfiles  into all the possible  plainfile
/// combinations while intended messages are known only by the key owners.
/// Nikolay Valentinovich Repnitskiy - License: WTFPLv2+ (wtfpl.net.)

/* Requires 1+GB RAM to get keys. 125 outgoing messages per user (250 if one-way.) Get 500MB of keys in 15m @2.1GHz.
As with all my OTPs, reserved randomness within the key files is appended to all plainfiles to get 1,000,007 bytes total,
then both that randomness and plainfile are encrypted. This prevents key fragment exposure and identifying file analytics
based on their size. All cipherfiles are 1,000,007 bytes. The first 7 contain encrypted file size--for exact reproduction.
Generate and share multiple folders to have spare keys.  The following 254 files conjure automated  dual-channel symmetry:
--------------------------------------------------------------------------------------------------------------------------
 * keys                           (Folder)
   * incoming                     (Folder within the keys folder.)
   * outgoing                     (Folder within the keys folder.)
     * 000 - 124                  (125 key files within the incoming folder, each file being 2,000,014 char, total ~=250MB.)
     * 000 - 124                  (125 key files within the outgoing folder, each file being 2,000,014 char, total ~=250MB.)
 * remaining.encrypt.txt          (Contains the number of times left to encrypt, this number is displayed before and after.)
 * remaining.decrypt.txt          (Contains the number of times left to decrypt, this number is displayed before and after.)
 * symmetry.entanglement          (After generating keys & sharing this folder privately,  the generator removes this file.)
 * swapped                        (For option 4--to be used on both ends. This file is created if not already existent, and
                                   removed otherwise. symmetry.entanglement is then removed & re-created using these rules.
                                   file_name_key_outgoing[] becomes file_name_key_incoming[] & vice versa, depending on the
                                   presence of symmetry.entanglement. swapped gives pure symmetry rather than entanglement.)
----------------------------------------------------------------------------------------------------------------------------
If your operation prefers one-way file sharing as you work on the field and your outgoing keys are coming to an end, you and
the party involved can swap and restore channels at any time (option 4.)  This gives you an additional 125 times to encrypt.
If you encrypted a file but did not send it,  inform the other party and they will remove keys manually until their contents
of the keys folder are symmetric with yours. They need also modify remaining.decrypt.txt to match your remaining.encrypt.txt.
If you send encrypted messages containing seeds for generating new symmetric keys,  perfect secrecy is reduced to guaranteed 
decryption difficulty as the number of plausible messages per ciphertext begins to narrow. And this applies to symmetric key
transformations and operations with additional components such as transformation determinants for the keys. Proof in link:
https://github.com/compromise-evident/OTP/blob/main/Perfect%20secrecy%20and%20computational%20difficulty%20proof.pdf

How to run the program - Software package repositories for GNU+Linux operating systems have all the developer tools needed.
Open a terminal and use the following command as root to install  Geany  and  g++  on your computer:  apt install geany g++
Geany is a fast & lightweight text editor and Integrated Development Environment (IDE) in which you can write and run code.
g++ is the GNU compiler for C++ which allows written code to run. The compiler operates in the background automatically and
displays errors in your code as you will see in the lower box in Geany. Create a folder somewhere on your machine. Open Geany
and paste this code into the blank Geany page.  Now you can get code-highlighting and set this document as a C++ source file.
Go to Document >> Set Filetype >> Programming Languages >> C++ source file. (A good tip for clarity in auditing is to enable
the indentation guides for the block braces. Go to View >> Show Indentation Guides.) Save the file as anything.cpp within the
newly-created folder (Geany will automatically suggest the .cpp extension.) This folder is now the home directory of OTP.cpp
which will create, write to, and read from files within this folder.  And now you can build then run the program.  Use the
following Geany shortcuts in order:  F9,  F5.  Whenever it is you wish to use the OTP again, open  Geany  and use the same
shortcuts. This will work for any single C++ file whether you paste over the current code or open a new file and repeat.*/

#include <cstdlib>    //For rand() & srand() (here: user-defined seeds only.)
#include <fstream>    //For file I/O (creates, writes to, and reads from ONLY the 254 files mentioned above.)
#include <iostream>
#include <sys/stat.h> /*For mkdir() (creating folders.) Here are some examples you might find useful as a GNU+Linux user:
------------------------------------------------------------------------------------------------------------------------
used, requires header   (create folders)-                             mkdir("keys", 0777);
used, requires header   (create folders within folders)-              mkdir("./keys/incoming", 0777);
used                    (file I/O in folders)-              out_stream.open("./keys/incoming/file_1");
                        (file I/O elsewhere)-               out_stream.open("//home//nikolay//Desktop//folder_1//file_1");
      requires header   (create folders elsewhere)-                   mkdir("//home//nikolay//Desktop//folder_1//keys", 0777);
----------------------------------------------------------------------------------------------------------------------------*/
using namespace std;

int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	cout << "\n(scheme One-time pad)\n\n"
	
	     << "(1) Encrypt\n"
	     << "(2) Decrypt\n"
	     << "(3) Get keys\n"
	     << "(4) Swap channels\n\n";
	
	in_stream.open("swapped"); //Checks if file swapped exists.
	if(in_stream.fail() == true)
	{	cout << "Enter option: ";
	}
	else
	{	cout << "(Channels currently swapped.) Enter option: ";
	}
	in_stream.close();
	
	int user_option;
	cin >> user_option;
	if((user_option != 1) && (user_option != 2) && (user_option != 3) && (user_option != 4)) {cout << "\nInvalid, program ended.\n"; return 0;}
	//(You can run each of the four ifs holding options 1, 2, and 3, and 4 in isolation--they are self-sustained.)
	
	
	
	
	
	//______________________________________________________Encrypt___________________________________________________//
	if(user_option == 1)
	{	ifstream in_stream;
		ofstream out_stream;
		
		//Checks if files exist.
		in_stream.open("swapped");
		if(in_stream.fail() == true) {in_stream.close(); in_stream.open("remaining.encrypt.txt");}
		else                         {in_stream.close(); in_stream.open("remaining.decrypt.txt");}
		
		if(in_stream.fail() == true) {cout << "\n\nCan't encrypt without keys.\n"; in_stream.close(); return 0;}
		char remaining_encrypt[3];
		for(int a = 0; a < 3; a++) {in_stream >> remaining_encrypt[a]; remaining_encrypt[a] -= 48;}
		in_stream.close();
		
		int remaining_encrypt_decimal = 0;
		if(remaining_encrypt[ 0] > 0) {remaining_encrypt_decimal += (remaining_encrypt[ 0] * 100);}
		if(remaining_encrypt[ 1] > 0) {remaining_encrypt_decimal += (remaining_encrypt[ 1] *  10);}
		if(remaining_encrypt[ 2] > 0) {remaining_encrypt_decimal += (remaining_encrypt[ 2]      );}
		if(remaining_encrypt_decimal == 0)   {cout << "\n\nEncryption keys depleted, consider swapping channels.\n"; return 0;}
		
		//Instructing user to give the file.
		if(remaining_encrypt_decimal == 1)   {cout << "\nYou may encrypt one more file." ;}
		else {cout << "\nYou may encrypt " << remaining_encrypt_decimal << " more files.";}
		
		cout << "\n\nPlace a copy of your file in this directory and rename it to \"plainfile\" without\n"
		     << "any extensions. Make sure it's 1 to 1,000,000 bytes in size. Continue? y/n: ";
		
		char wait; cin >> wait; if(wait != 'y') {return 0;}
		
		//Maintaining symmetry entanglement.
		char file_name_key_outgoing[20] = "./keys/outgoing/000";
		in_stream.open("symmetry.entanglement");
		if(in_stream.fail() == true)
		{	file_name_key_outgoing[ 7] = 'i';
			file_name_key_outgoing[ 8] = 'n';
			file_name_key_outgoing[ 9] = 'c';
			file_name_key_outgoing[10] = 'o';
			file_name_key_outgoing[11] = 'm';
		}
		in_stream.close();
		
		//Generates key file NAME based on existence.
		int file_numbering = 1000000; //Only the last 3 digits are used, size makes mod operations easier.
		for(int a = 0; a < 125; a++)
		{	in_stream.open(file_name_key_outgoing);
			if(in_stream.fail() == false) {in_stream.close(); break;}
			
			//Adjusts file numbering.
			file_numbering++;
			int temp_file_numbering = file_numbering;
			file_name_key_outgoing[18] = (temp_file_numbering % 10) + 48; //       ./keys/outgoing/0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^
			file_name_key_outgoing[17] = (temp_file_numbering % 10) + 48; //                      16 17 18    (element layout)
			temp_file_numbering /=    10;
			file_name_key_outgoing[16] = (temp_file_numbering % 10) + 48;
		}
		
		//Gets key file for encryption.
		unsigned char plainfile[2000014];
		char temp_file_item;
		int  temp_file_item_decimal;
		in_stream.open(file_name_key_outgoing);
		for(int a = 0; a < (2000014); a++)
		{	in_stream.get(temp_file_item);
			temp_file_item_decimal = temp_file_item;
			if(temp_file_item_decimal < 0) {plainfile[a] = (temp_file_item_decimal + 256);}
			else                           {plainfile[a] =  temp_file_item_decimal       ;}
		}
		in_stream.close();
		
		//Gets file items and overwrites plainfile[], leaving appended randomness.
		int file_size_counter = 0;
		in_stream.open("plainfile");
		if(in_stream.fail() == true) {in_stream.close(); cout << "\n\nplainfile not present or misspelled.\n"; return 0;}
		in_stream.get(temp_file_item);
		if(in_stream.eof() == true) {cout << "\n\nplainfile cannot be empty.\n"; return 0;}
		for(int a = 7; in_stream.eof() == false; a++)
		{	file_size_counter++;
			if(file_size_counter > 1000000) {cout << "\n\nplainfile too large!\n"; return 0;}
			
			temp_file_item_decimal = temp_file_item;
			if(temp_file_item_decimal < 0) {temp_file_item_decimal += 256;}
			plainfile[a] = temp_file_item_decimal;
			
			in_stream.get(temp_file_item);
		}
		in_stream.close();
		
		//Writes the file size to the first 7 plainfile[] elements. This will be encrypted.
		file_size_counter += 1000000000;
		for(int a = 6; a >= 0; a--)
		{	plainfile[a] = (file_size_counter % 10);
			file_size_counter /= 10;
		}
		
		///Encrypts plainfile using the remaining 1,000,007 in plainfile[].
		for(int a = 0; a < 1000007; a++)
		{	temp_file_item_decimal  = plainfile[a          ];
			temp_file_item_decimal += plainfile[a + 1000007];
			temp_file_item_decimal %= 256;
			plainfile[a] = temp_file_item_decimal;
		}
		
		//Creating and writing to cipherfile. Converts from (0 - 255) to (-128 - 127.)
		out_stream.open("cipherfile");
		for(int a = 0; a < 1000007; a++)
		{	if(plainfile[a] < 128) {out_stream.put(plainfile[a]      );}
			else                   {out_stream.put(plainfile[a] - 256);}
		}
		out_stream.close();
		
		//Removes the used key.
		remove(file_name_key_outgoing);
		remove("plainfile"); //Removing the raw file prevents accidentally sending it. (User is asked to place a COPY here.)
		
		//Overwriting RAM of array plainfile[].
		for(int a = 0; a < 2000014; a++)
		{	plainfile[a] = 255; plainfile[a] = 0;
		}
		
		//Adjusts file remaining.encrypt.txt.
		remaining_encrypt_decimal--;
		in_stream.open("swapped");
		if(in_stream.fail() == true) {in_stream.close(); out_stream.open("remaining.encrypt.txt");}
		else                         {in_stream.close(); out_stream.open("remaining.decrypt.txt");}
		
		if(remaining_encrypt_decimal < 100) {out_stream << "0";}
		if(remaining_encrypt_decimal <  10) {out_stream << "0";}
		out_stream << remaining_encrypt_decimal;
		out_stream << " files left to encrypt. Do not modify this file.";
		out_stream.close();
		
		//Displays # of files left to encrypt.
		cout << "\n\ncipherfile now resides in this directory.\n";
		if     (remaining_encrypt_decimal == 0) {cout << "Encryption keys depleted.\n";}
		else if(remaining_encrypt_decimal == 1) {cout << "You may encrypt one more file.\n";}
		else     cout << "You may encrypt " << remaining_encrypt_decimal << " more files.\n";
	}
	
	
	
	
	
	//______________________________________________________Decrypt___________________________________________________//
	if(user_option == 2)
	{	ifstream in_stream;
		ofstream out_stream;
		
		//Checks if files exist.
		in_stream.open("swapped");
		if(in_stream.fail() == true) {in_stream.close(); in_stream.open("remaining.decrypt.txt");}
		else                         {in_stream.close(); in_stream.open("remaining.encrypt.txt");}
		
		if(in_stream.fail() == true) {cout << "\n\nCan't decrypt without keys.\n"; in_stream.close(); return 0;}
		char remaining_decrypt[3];
		for(int a = 0; a < 3; a++) {in_stream >> remaining_decrypt[a]; remaining_decrypt[a] -= 48;}
		in_stream.close();
		
		int remaining_decrypt_decimal = 0;
		if(remaining_decrypt[ 0] > 0) {remaining_decrypt_decimal += (remaining_decrypt[ 0] * 100);}
		if(remaining_decrypt[ 1] > 0) {remaining_decrypt_decimal += (remaining_decrypt[ 1] *  10);}
		if(remaining_decrypt[ 2] > 0) {remaining_decrypt_decimal += (remaining_decrypt[ 2]      );}
		if(remaining_decrypt_decimal == 0)   {cout << "\n\nDecryption keys depleted, consider swapping channels.\n"; return 0;}
		
		//Instructing user to give the file.
		if(remaining_decrypt_decimal == 1)   {cout << "\nYou may decrypt one more file." ;}
		else {cout << "\nYou may decrypt " << remaining_decrypt_decimal << " more files.";}
		
		cout << "\n\nPlace the cipherfile in this directory if not already here. Continue? y/n: ";
		
		char wait; cin >> wait; if(wait != 'y') {return 0;}
		
		//Maintaining symmetry entanglement.
		char file_name_key_incoming[20] = "./keys/incoming/000";
		in_stream.open("symmetry.entanglement");
		if(in_stream.fail() == true)
		{	file_name_key_incoming[ 7] = 'o';
			file_name_key_incoming[ 8] = 'u';
			file_name_key_incoming[ 9] = 't';
			file_name_key_incoming[10] = 'g';
			file_name_key_incoming[11] = 'o';
		}
		in_stream.close();
		
		//Generates key file NAME based on existence.
		int file_numbering = 1000000; //Only the last 3 digits are used, size makes mod operations easier.
		for(int a = 0; a < 125; a++)
		{	in_stream.open(file_name_key_incoming);
			if(in_stream.fail() == false) {in_stream.close(); break;}
			
			//Adjusts file numbering.
			file_numbering++;
			int temp_file_numbering = file_numbering;
			file_name_key_incoming[18] = (temp_file_numbering % 10) + 48; //       ./keys/incoming/0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^
			file_name_key_incoming[17] = (temp_file_numbering % 10) + 48; //                      16 17 18    (element layout)
			temp_file_numbering /=    10;
			file_name_key_incoming[16] = (temp_file_numbering % 10) + 48;
		}
		
		//Gets key file for decryption.
		unsigned char cipherfile[2000014];
		char temp_file_item;
		int  temp_file_item_decimal;
		in_stream.open(file_name_key_incoming);
		for(int a = 0; a < (2000014); a++)
		{	in_stream.get(temp_file_item);
			temp_file_item_decimal = temp_file_item;
			if(temp_file_item_decimal < 0) {cipherfile[a] = (temp_file_item_decimal + 256);}
			else                           {cipherfile[a] =  temp_file_item_decimal       ;}
		}
		in_stream.close();
		
		//Gets file items and overwrites first half of plainfile[].
		in_stream.open("cipherfile");
		if(in_stream.fail() == true) {in_stream.close(); cout << "\n\ncipherfile not present.\n"; return 0;}
		for(int a = 0; a < 1000007; a++)
		{	in_stream.get(temp_file_item);
			temp_file_item_decimal = temp_file_item;
			if(temp_file_item_decimal < 0) {temp_file_item_decimal += 256;}
			cipherfile[a] = temp_file_item_decimal;
		}
		in_stream.close();
		
		///Decrypts the cipherfile. The following formula helps extract plaintext quickly.
		/*_____________________________________________ ________________________________________________
		|                                              |                                                |
		|          if sub-key <= cipherfile            |                     else                       |
		|   then plainfile = (cipherfile - sub-key)    |    plainfile = ((256 - sub-key) + cipherfile)  |
		|______________________________________________|_______________________________________________*/
		for(int a = 0; a < 1000007; a++)
		{	if(cipherfile[a + 1000007] <= cipherfile[a])
			{	cipherfile[a] = (cipherfile[a] - cipherfile[a + 1000007]);
			}
			else
			{	cipherfile[a] = ((256 - cipherfile[a + 1000007]) + cipherfile[a]);
			}
		}
		
		//Extracts the file size from the first 7 elements in cipherfile[].
		int extracted_file_size = 0;
		if(cipherfile[0] > 0) {extracted_file_size += (cipherfile[0] * 1000000);}
		if(cipherfile[1] > 0) {extracted_file_size += (cipherfile[1] *  100000);}
		if(cipherfile[2] > 0) {extracted_file_size += (cipherfile[2] *   10000);}
		if(cipherfile[3] > 0) {extracted_file_size += (cipherfile[3] *    1000);}
		if(cipherfile[4] > 0) {extracted_file_size += (cipherfile[4] *     100);}
		if(cipherfile[5] > 0) {extracted_file_size += (cipherfile[5] *      10);}
		if(cipherfile[6] > 0) {extracted_file_size +=  cipherfile[6]           ;}
		
		//Creating and writing to plainfile. Converts from (0 - 255) to (-128 - 127.)
		out_stream.open("plainfile");
		for(int a = 7; a < extracted_file_size + 7; a++)
		{	if(cipherfile[a] < 128) {out_stream.put(cipherfile[a]      );}
			else                    {out_stream.put(cipherfile[a] - 256);}
		}
		out_stream.close();
		
		//Removes the used key.
		remove(file_name_key_incoming);
		
		//Overwriting RAM of array cipherfile[].
		for(int a = 0; a < 2000014; a++)
		{	cipherfile[a] = 255; cipherfile[a] = 0;
		}
		
		//Adjusts file remaining.decrypt.txt.
		remaining_decrypt_decimal--;
		in_stream.open("swapped");
		if(in_stream.fail() == true) {in_stream.close(); out_stream.open("remaining.decrypt.txt");}
		else                         {in_stream.close(); out_stream.open("remaining.encrypt.txt");}
		
		if(remaining_decrypt_decimal < 100) {out_stream << "0";}
		if(remaining_decrypt_decimal <  10) {out_stream << "0";}
		out_stream << remaining_decrypt_decimal;
		out_stream << " files left to decrypt. Do not modify this file.";
		out_stream.close();
		
		//Displays # of files left to decrypt .
		cout << "\n\nplainfile now resides in this directory.\n";
		if     (remaining_decrypt_decimal == 0) {cout << "Decryption keys depleted.\n";}
		else if(remaining_decrypt_decimal == 1) {cout << "You may decrypt one more file.\n";}
		else     cout << "You may decrypt " << remaining_decrypt_decimal << " more files.\n";
	}
	
	
	
	
	
	//______________________________________________________Get_keys__________________________________________________//
	if(user_option == 3)
	{	ifstream in_stream;
		ofstream out_stream;
		
		//Checks if regular files already exist.
		in_stream.open("remaining.encrypt.txt");
		if(in_stream.fail() == false) {cout << "\n\nKeys already exist, run a new schemeOTP.cpp file in a different folder.\n"; return 0;}
		in_stream.close();
		
		//Fills user_seeds[].
		cout << "\nEnter a random nine-digit integer, repeat 90 times. (Get 500MB of keys in 15m.)\n\n";
		unsigned int user_seeds[90] = {0};
		for(int a = 0; a < 90; a++)
		{	if(a < 9) {cout << " " << (a + 1) << " of 90: ";} //Prints blank to align input status report (aesthetics.)
			else      {cout <<        (a + 1) << " of 90: ";}
			
			cin >> user_seeds[a];
		}
		
		//Fills table_private[] with randomness 0 - 255 (later converted to (-128 - 127) upon writing to files.)
		static unsigned char table_private[501000000] = {0};
		int temp_modular_arithmetic;
		for(int a = 0; a < 90; a++) //Constructively applies random digits to table_private[] based on the 90 seeds provided by the user.
		{	srand(user_seeds[a]);   //WRITES ALTERNATING BETWEEN LEFT TO RIGHT & RIGHT TO LEFT. Alternation is based on the 90 user seeds.
			
			if((user_seeds[a] % 2) == 0)
			{	for(int b = 0; b < 501000000; b++) //WRITES LEFT TO RIGHT.
				{	temp_modular_arithmetic = table_private[b];
					temp_modular_arithmetic += (rand() % 256);
					temp_modular_arithmetic %= 256;
					table_private[b] = temp_modular_arithmetic;
				}
			}
			else
			{	for(int b = 500999999; b >= 0; b--) //WRITES RIGHT TO LEFT.
				{	temp_modular_arithmetic = table_private[b];
					temp_modular_arithmetic += (rand() % 256);
					temp_modular_arithmetic %= 256;
					table_private[b] = temp_modular_arithmetic;
				}
			}
		}
		
		//Adding additional randomness in table_private[].
		unsigned int seeds_sum = 0;
		for(int a = 0; a < 90; a++)
		{	seeds_sum += user_seeds[a];
			seeds_sum %= 1000000000;
		}
		srand(seeds_sum); //A new 9-digit seed comes from the sum of ALL user-seeds.
		for(int a = 0; a < 501000000; a++) //WRITES LEFT TO RIGHT.
		{	temp_modular_arithmetic = table_private[a];
			temp_modular_arithmetic += (rand() % 256);
			temp_modular_arithmetic %= 256;
			table_private[a] = temp_modular_arithmetic;
		}
		
		//Again, adding additional randomness in table_private[].
		seeds_sum = 0;
		for(int a = 0; a < 90; a += 2)
		{	seeds_sum += user_seeds[a];
			seeds_sum %= 1000000000;
		}
		srand(seeds_sum); //Another new 9-digit seed comes from the sum of EVERY OTHER user-seed.
		for(int a = 500999999; a >= 0; a--) //WRITES RIGHT TO LEFT.
		{	temp_modular_arithmetic = table_private[a];
			temp_modular_arithmetic += (rand() % 256);
			temp_modular_arithmetic %= 256;
			table_private[a] = temp_modular_arithmetic;
		}
		
		//Creates initial file names in folders.
		mkdir("keys"           ,  0777); //Creates a folder.
		mkdir("./keys/incoming",  0777); //Creates a folder within that keys folder.
		mkdir("./keys/outgoing",  0777); //Creates another folder within that keys folder.
		char file_name_key_incoming[20] = "./keys/incoming/000";
		char file_name_key_outgoing[20] = "./keys/outgoing/000";
		
		//Writes 125 keys to folder incoming. Converts from (0 - 255) to values (-128 - 127.)
		int file_numbering = 1000000; //Only the last 3 digits are used, size makes mod operations easier.
		int write_bookmark = 0;
		for(int i = 0; i < 125; i++)
		{	out_stream.open(file_name_key_incoming);
			for(int a = 0; a < 2000014; a++)
			{	if(table_private[write_bookmark] < 128) {out_stream.put(table_private[write_bookmark]      );}
				else                                    {out_stream.put(table_private[write_bookmark] - 256);}
				
				write_bookmark++;
			}
			out_stream.close();
			
			//Adjusts file numbering.
			file_numbering++;
			int temp_file_numbering = file_numbering;
			file_name_key_incoming[18] = (temp_file_numbering % 10) + 48; //       ./keys/incoming/0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^
			file_name_key_incoming[17] = (temp_file_numbering % 10) + 48; //                      16 17 18    (element layout)
			temp_file_numbering /=    10;
			file_name_key_incoming[16] = (temp_file_numbering % 10) + 48;
		}
		
		//Writes 125 keys to folder outgoing. Converts from (0 - 255) to values (-128 - 127.)
		file_numbering = 1000000; //Resetting.
		for(int i = 0; i < 125; i++)
		{	out_stream.open(file_name_key_outgoing);
			for(int a = 0; a < 2000014; a++)
			{	if(table_private[write_bookmark] < 128) {out_stream.put(table_private[write_bookmark]      );}
				else                                    {out_stream.put(table_private[write_bookmark] - 256);}
				
				write_bookmark++;
			}
			out_stream.close();
			
			//Adjusts file numbering.
			file_numbering++;
			int temp_file_numbering = file_numbering;
			file_name_key_outgoing[18] = (temp_file_numbering % 10) + 48; //       ./keys/outgoing/0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^
			file_name_key_outgoing[17] = (temp_file_numbering % 10) + 48; //                      16 17 18    (element layout)
			temp_file_numbering /=    10;
			file_name_key_outgoing[16] = (temp_file_numbering % 10) + 48;
		}
		
		//Creates the encryption remaining counter file.
		out_stream.open("remaining.encrypt.txt");
		out_stream << "125 files left to encrypt. Do not modify this file.";
		out_stream.close();
		
		//Creates the decryption remaining counter file.
		out_stream.open("remaining.decrypt.txt");
		out_stream << "125 files left to decrypt. Do not modify this file.";
		out_stream.close();
		
		//Creates the symmetry entanglement file.
		out_stream.open("symmetry.entanglement");
		out_stream << 1;
		out_stream.close();
		
		//Overwrites RAM of user_seeds[].
		for(int a = 0; a < 90; a++)
		{	user_seeds[a] = 123456789;
			user_seeds[a] = 987604321;
			user_seeds[a] = 0;
		}
		
		//Overwrites RAM of array table_private[].
		for(int a = 0; a < 501000000; a++)
		{	for(int b = 0; b < 10; b++) {table_private[a] = b;}
		}
		
		cout << "\n\nFinished! Share this folder in private, then\n"
		     << "REMOVE file symmetry.entanglement on your end ONLY!\n\n";
	}
	
	
	
	
	
	//______________________________________________________Swap_channels_____________________________________________//
	if(user_option == 4)
	{	ifstream in_stream;
		ofstream out_stream;
		
		//Checks if files exist.
		in_stream.open("remaining.encrypt.txt");
		if(in_stream.fail() == true) {cout << "\n\nNo channels to swap, get keys first.\n"; in_stream.close(); return 0;}
		in_stream.close();
		
		cout << "\n\nThis option must be used on both ends and is reversible by using it necessarily\n"
		     << "on both ends again. This allows you to continue encrypting files when only your\n"
		     << "outgoing channel keys are coming to an end, where the other party is then faced\n"
		     << "with limited encryption--until channel ownership is restored. Continue? y/n: ";
		
		char wait; cin >> wait;
		
		if(wait != 'y')
		{	cout << "\n\nNothing changed.\n";
			return 0;
		}
		
		//Creates file swapped if non-existent, removes it otherwise. This is pure SYMMETRY rather than entanglement.
		in_stream.open("swapped");
		if(in_stream.fail() == true)
		{	out_stream.open("swapped");
			out_stream << 1;
			out_stream.close();
			cout << "\n\nSymmetry entanglement reconfigured!\n";
		}
		else
		{	remove("swapped");
			cout << "\n\nChannel ownership restored.\n";
		}
		in_stream.close();
		
		//Creates file symmetry.entanglement if non-existent, removes it otherwise. This is pure ENTANGLEMENT rather than symmetry.
		in_stream.open("symmetry.entanglement");
		if(in_stream.fail() == true)
		{	out_stream.open("symmetry.entanglement");
			out_stream << 1;
			out_stream.close();
		}
		else {remove("symmetry.entanglement");}
		in_stream.close();
	}
}
