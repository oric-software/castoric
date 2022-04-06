import argparse
import sys, os, re


def main (arguments):
        
    parser = argparse.ArgumentParser(
        prog='cycle_count'
        , description='OSDK profiler cycle counter'
        , epilog = '''For exemple:
            cycle_count --init
        '''
        )

    parser.add_argument('--init'
                        , action=argparse.BooleanOptionalAction
                        , default=False
                        , help="Initialise printer_out.txt"
                        )


    args = parser.parse_args(arguments)
    filepathname = os.getenv('OSDK')+os.sep+'Oricutron'+os.sep+'printer_out.txt'
    if (not args.init):
        print("loading "+filepathname)
        with open(filepathname, 'r') as fic:
            lins = fic.readlines()
            cumul_frame = 0
            cumul_drawwalls = 0
            for la in lins:
                li=la.replace('\n','').strip()
                if li != "":
                    # print(li)
                    z = re.match('Frame:([0-9ABCDEF]+) Time=([0-9ABCDEF]+)', li)
                    if z:
                        # print (li, int(z.group(1), base=16), int(z.group(2), base= 16))
                        cumul_frame += int(z.group(2), base= 16)
                    z = re.match('Profiling started', li)
                    if (z): 
                        if ((cumul_frame != 0) or (cumul_drawwalls!=0)): print (f"Cumulated Time: {cumul_frame} cycles, drawWalls cycles {cumul_drawwalls}")
                        cumul_frame = 0
                        cumul_drawwalls = 0
                    z = re.match('([0-9ABCDEF]+)x([0-9ABCDEF]+) ([0-9ABCDEF]+) (.*)', li)
                    if z:
                        # print (z.group(4), int(z.group(3), base=16))
                        if (z.group(4)=="drawWalls"):
                            cumul_drawwalls += int(z.group(3), base=16)

            print (f"Cumulated Time: {cumul_frame} cycles, drawWalls cycles {cumul_drawwalls}")
        pass
    else:
        with open(filepathname, 'w') as fic:
            fic.write ("")

if __name__ == '__main__':
    # main('--init'.split())
    main (sys.argv[1:])

