inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short","威德居");
        set("long",@LONG
這是白自在的寢室，傢俱屋飾，極盡豪華，謂金碧輝煌，桂
殿蘭宮。但現在白自在已不知去向，只剩他的一個妾室，還在這
裏抽抽噎噎地哭。
LONG);
        set("exits",([
            "south"  : __DIR__"book",   
        ]));
        set("objects", ([  
                __DIR__"npc/yaoniang" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
