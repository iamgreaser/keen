#!/bin/sh
#bcc makeobj.c
cc -o makeobj makeobj.c || exit 1

#./makeobj c AUDIODCT.KDR ../kdradict.obj _audiodict
#./makeobj f AUDIOHHD.KDR ../kdrahead.obj _AudioHeader _audiohead
#./makeobj c CGADICT.KDR ../kdrcdict.obj _CGAdict
#./makeobj f CGAHEAD.KDR ../kdrchead.obj CGA_grafixheader _CGAhead
#./makeobj f CONTEXT.KDR ../context.obj
#./makeobj c EGADICT.KDR ../kdredict.obj _EGAdict
#./makeobj f EGAHEAD.KDR ../kdrehead.obj EGA_grafixheader _EGAhead
#./makeobj f GAMETEXT.KDR ../gametext.obj
#./makeobj c MAPDICT.KDR ../kdrmdict.obj _mapdict
#./makeobj f MAPHEAD.KDR ../kdrmhead.obj MapHeader _maphead
#./makeobj s PIRACY.SCN ../piracy.h 7
#./makeobj f STORY.KDR ../story.obj

#./makeobj c AUDIODCT.KDR kdradict.obj _audiodict
#./makeobj f AUDIOHHD.KDR kdrahead.obj _AudioHeader _audiohead
#./makeobj c CGADICT.KDR kdrcdict.obj _CGAdict
#./makeobj f CGAHEAD.KDR kdrchead.obj CGA_grafixheader _CGAhead
#./makeobj f CONTEXT.KDR context.obj
#./makeobj c EGADICT.KDR kdredict.obj _EGAdict
#./makeobj f EGAHEAD.KDR kdrehead.obj EGA_grafixheader _EGAhead
#./makeobj f GAMETEXT.KDR gametext.obj
#./makeobj c MAPDICT.KDR kdrmdict.obj _mapdict
#./makeobj f MAPHEAD.KDR kdrmhead.obj MapHeader _maphead
#./makeobj s PIRACY.SCN piracy.h 7
#./makeobj f STORY.KDR story.obj

./makeobj s AUDIODCT.KDR kdradict.h _audiodict
./makeobj s AUDIOHHD.KDR kdrahead.h _AudioHeader _audiohead
./makeobj s CGADICT.KDR kdrcdict.h _CGAdict
./makeobj s CGAHEAD.KDR kdrchead.h CGA_grafixheader _CGAhead
./makeobj s CONTEXT.KDR context.h
./makeobj s GAMETEXT.KDR gametext.h

#./makeobj s MAPDICT.KDR kdrmdict.h _mapdict
#./makeobj s MAPHEAD.KDR kdrmhead.h MapHeader _maphead
./makeobj s MAPDICT.RIP kdrmdict.h _mapdict
./makeobj s MAPHEAD.RIP kdrmhead.h MapHeader _maphead

./makeobj s EGADICT.KDR kdredict.h _EGAdict
./makeobj s EGAHEAD.KDR kdrehead.h EGA_grafixheader _EGAhead
#./makeobj s EGADICT.RIP kdredict.h _EGAdict
#./makeobj s EGAHEAD.RIP kdrehead.h EGA_grafixheader _EGAhead

./makeobj s PIRACY.SCN piracy.h 7
./makeobj s STORY.KDR story.h

