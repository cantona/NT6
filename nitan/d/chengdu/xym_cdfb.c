#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "俠義盟前");
        set("long", @LONG
這裏是俠義盟成都分部的大門前面，俠義盟的成都分部地理位置
極好，掩映在青山碧水之間。這是一幢別具風格的建築，讓人覺得一
股正氣浩存於天地之間。          
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
                "west" :  __DIR__"eastroad3",
                "east" : __DIR__"xym_cddt",
        ])); 
        set("objects", ([   
             __DIR__"npc/xym-guard" : 2,   
            ]));
               
        set("coor/x", -15190);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "east") 
        {
           if( !query_temp("good_xym2", me) && query("bunch/bunch_name", me) != "俠義盟" )
               return notify_fail("守衞一把攔住你，朗聲喝道：我俠義盟怎由閒雜人等隨便進出。\n"); 
           else
           {
              delete_temp("good_xym2", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 