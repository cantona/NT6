//xym_yzdamen.c

#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "大門");
        set("long", @LONG
這裡是俠義盟揚州分舵的大門，一面大旗迎風招展，上書『鋤惡
務盡』四個大字。
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "south" :  "/d/city/ximenroad",
                "north" :  "/d/city/xym_yzfb",
        ])); 
        set("objects", ([   
               "/d/city/npc/xym_guard" : 2,   
            ]));
               
	set("coor/x", -50);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "north") 
        {
                if( !query_temp("good_xym", me) && query("bunch/bunch_name", me) != "俠義盟" )
                        return notify_fail("守衛一把攔住你，朗聲喝道：我俠義盟怎由閒雜人等隨便進出。\n"); 
                else
                {
                        delete_temp("good_xym", me);
                        return ::valid_leave(me, dir);
                }
        }
        return ::valid_leave(me, dir); 
} 