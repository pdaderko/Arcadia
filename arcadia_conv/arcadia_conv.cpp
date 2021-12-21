/*
Swaps bits according to arguments to allow conversion of Arcadia games from/to any security PAL
usage: arcadia_conv <input file name> <output file name> <input shuffle> <output shuffle>

example: arcadia_conv airh_1l.bin airh_1l_bowl.bin 50247613 76012345
Converts SportTime Table Hockey ROM to run with SportTime Bowling security PAL

example: arcadia_conv airh_1l.bin airh_1l_dec.bin 50247613 76543210
Outputs SportTime Table Hockey ROM with no scramble (decrypted ROM)

Note 1: Only the first low ROM should be bit swapped, none of the other ROMs require bit swapping
Note 2: On the single game piggyback boards, only the low ROM at U16 is bit swapped.
        In the case of all games except Aaargh, this is the OnePlay BIOS (SCPA marked ROM).
        The BIOS chip is the same/compatible for all OnePlay games, so any OnePlay game can be
        converted to another OnePlay game by simply swapping unmodified ROMs.
Note 3: To use ROMs from TenPlay on OnePlay, use the appropriate input shuffle and an output
        shuffle of 76543210 (i.e. no shuffle) on the first TenPlay low ROM (U6), and place ROMs in
        sockets starting at U15 (low) and U11 (high), leaving SCPA chip in place at U16 and U12.
Note 4: Aaargh! requires a different PAL8L14 (U3) to use the appropriate memory mapping, since it doesn't
        use the OnePlay BIOS.  It's first ROM is bit swapped instead of the BIOS.

Below is a list of known bit swaps, pulled from MAME source code
SportTime Table Hockey: 50247613
SportTime Bowling: 76012345
Blastaball: 41762035
World Darts: 40763125
Magic Johnson's Fast Break: 76543210
Leader Board: 23410756 (V2.5) or 76543210 (other versions)
Ninja Mission: 16574203
RoadWars: 31640527
Sidewinder: 63452107
World Trophy Soccer: 07165432
Spot: 76543210
Space Ranger: 47306521
Xenon: 31240567
Pharaohs Match: 76543210
Delta Command: 41762035
Aaargh!: 50247613
OnePlay BIOS (SCPA): 61023457
*/

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
  int i;
  ifstream infile;
  ofstream outfile;
  unsigned char inbyte, tempbyte, outbyte;

  if (argc!=5)
  {
    cout << "usage: " << argv[0] << " <input file name> <output file name> <input shuffle> <output shuffle>";
  }
  
  //do simple validation of shuffle inputs (correct number of characters and sum = 7+6+5+4+3+2+1+0)
  if ((strlen(argv[3])!=8)||(((argv[3][0]-'0')+(argv[3][1]-'0')+(argv[3][2]-'0')+(argv[3][3]-'0')+(argv[3][4]-'0')+(argv[3][5]-'0')+(argv[3][6]-'0')+(argv[3][7]-'0'))!=28))
  {
    cout << "Invalid input shuffle" << endl;
    return 1;
  }
  
  if ((strlen(argv[4])!=8)||(((argv[4][0]-'0')+(argv[4][1]-'0')+(argv[4][2]-'0')+(argv[4][3]-'0')+(argv[4][4]-'0')+(argv[4][5]-'0')+(argv[4][6]-'0')+(argv[4][7]-'0'))!=28))
  {
    cout << "Invalid output shuffle" << endl;
    return 1;
  }
  
	infile.open (argv[1], fstream::in | fstream::binary);
	if (infile.fail()) //make sure input file opened fine
  {
    cout << "Unable to open input file" << endl;
    return 1;
  }

	outfile.open (argv[2], fstream::out | fstream::binary);
	if (outfile.fail()) //make sure output file opened fine
  {
    cout << "Unable to open output file" << endl;
    return 1;
  }

  while(1)
	{
    inbyte=infile.get();
    if (infile.eof()) //end of files
      break;
    
    tempbyte=0;
    for (i=0; i<8; i++) //swap bits from input shuffle
      tempbyte|=((inbyte>>(argv[3][i]-'0')&1)<<(7-i));
    outbyte=0;
    for (i=0; i<8; i++) //swap bits to output shuffle
      outbyte|=(((tempbyte>>i)&1)<<(argv[4][7-i]-'0'));
    outfile.put(outbyte); //output byte with bits swapped
	}

  infile.close();
  outfile.close();
    
  return 0;
}
