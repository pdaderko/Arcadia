Address decoder GAL for Arcadia 2MB cartridge

Signals implemented in GAL based on original "piggyback" cart signals

EP_CE (pin 12): 0 when /AS=0 and address between either 0x800000 and 0x9DFFFF (A23..A21=100 and A20..A17!=1111) or 0xF00000 and 0xF1FFFF (A23..A17=1111000), else 1  
EP_A19 (pin 13): 1 when address between 0xF00000 and 0xF1FFFF (A23..A17=1111000), else A19  
EP_A20 (pin 14): 1 when address between 0xF00000 and 0xF1FFFF (A23..A17=1111000), else A20  
NV_CE (pin 15): 0 when /AS=0 and address between 0x9E0000 and 0x9FFFFF (A23..A17=1001111), else 1  
OE (pin 16): 0 when reading (R/W=1), else 1  
NV_WE (pin 17): 0 when writing (/AS=0 and R/W=0), else 1

EP_A19 and EP_A20 remaps 0xF000000-0xF1FFFF to 0x980000-0x99FFFF (Amiga Kickstart attempts to execute from 0xF000000)