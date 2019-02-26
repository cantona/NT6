// Room /d/heimuya/midao02.c
// By haiyan

#include <room.h>
inherit ROOM;

void create()
{
     set("short", "祕道");
        set("long", @LONG
這是日月神教極其祕密的通道。日月神教武功多為詭祕異功，為
免外人打擾，故教中弟子多在此地練功。
LONG );
     set("exits", ([
         "west"    : __DIR__"midao01",
         "east"    : __DIR__"lwchang1",
         "south"   : __DIR__"lwchang2",
         "north"   : __DIR__"lwchang3",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
