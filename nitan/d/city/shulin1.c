//By rama@lxtx

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{ 
        set("short", HIG"樹林"NOR);
        set("long", @LONG
忽然景色一轉，前面變成了一片幽深的樹林。你看看了看四周，
覺得周圍有些地方不太對頭，但是卻說上不上來。樹林裡面似乎有些
聲音傳來。到底要不要進去呢？你不由躊躇起來。
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "east" :  "/d/city/dujiangqiao",
                "north" : "/d/city/shulin",
        ])); 
        set("objects", ([   
             "/d/city/npc/xdh-guard" : 2,   
            ]));
               
	set("coor/x", -10);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir)
{
    if (! userp(me) && objectp(present("shou wei", environment(me))) && dir == "north")
        return notify_fail("NPC不進去。\n");
    return ::valid_leave(me, dir);
}