#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "大  門");
        set("long", @LONG
這裡是俠義盟襄陽總部的大門，一面大旗迎風招展，上書『鋤惡
務盡』四個大字。
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "west" :  __DIR__"jiekou2",
                "north" : __DIR__"xym_dating",
        ])); 
        set("objects", ([   
             __DIR__"npc/xym_guard" : 2,   
            ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "north") 
        {
           if( !query_temp("good_xym1", me) && query("bunch/bunch_name", me) != "俠義盟" )
               return notify_fail("守衛一把攔住你，朗聲喝道：我俠義盟怎由閒雜人等隨便進出。\n"); 
           else
           {
              delete_temp("good_xym1", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 
