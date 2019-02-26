// Room /d/heimuya/midao6.c
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
         "northdown" : __DIR__"midao5",
         "southeast" : __DIR__"midao7",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
