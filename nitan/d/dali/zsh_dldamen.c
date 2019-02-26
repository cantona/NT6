//zsh_dldamen.c

#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "前門");
        set("long", @LONG
這裏是紫衫會大理分會所在地。紫衫會近幾年俠義之舉得到江湖
上眾多正派人士的稱讚，而邪派之人則終日惶惶。許多江湖好漢均慕
名而來，紫衫會的勢力因之而得以不斷髮展壯大。
LONG );
        set("outdoors", "dali");
        set("exits", ([    
                "south"  :  "/d/dali/zsh_dlfh",
                "east"   :  "/d/dali/dahejiewest",
        ])); 
        set("objects", ([   
             "/d/suzhou/npc/zsh_guard" : 2,   
            ]));
               
	set("coor/x", -19150);
	set("coor/y", -6900);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "south") 
        {
           if( !query_temp("good_zsh", me) && query("bunch/bunch_name", me) != "紫衫會" )
               return notify_fail("守衞一把攔住你：“我紫衫會不歡迎外人，請回吧！”\n"); 
           else
           {
              delete_temp("good_zsh", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 