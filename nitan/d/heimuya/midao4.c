// Room /d/heimuya/midao4.c
// By haiyan

#include <room.h>
inherit ROOM;

void create()
{
     set("short", "祕道");
        set("long", @LONG
這是日月神教極其祕密的通道。是黑木崖與中原教眾取得聯繫的
捷徑。
LONG );
     set("exits", ([
         "northwest" : __DIR__"midao3",
         "south"     : __DIR__"midao5",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
