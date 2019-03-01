//zsh_bjdamen.c

#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "前門");
        set("long", @LONG
這裡是紫衫會北京分會所在地。紫衫會近幾年屢行俠義之事，勢
力不斷發展壯大，許多江湖好漢均慕名而來。
LONG );
        set("outdoors", "beijing");
        set("exits", ([
                "south"  :  "/d/beijing/zsh_bjfh",
                "north"  :  "/d/beijing/yong_3",
        ])); 
        set("objects", ([   
             "/d/beijing/npc/zsh_guard" : 2,   
            ]));
               
	set("coor/x", -2770);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "south") 
        {
           if( !query_temp("good_zsh", me) && query("bunch/bunch_name", me) != "紫衫會" )
               return notify_fail("守衛一把攔住你：“我紫衫會不歡迎外人，請回吧！”\n"); 
           else
           {
              delete_temp("good_zsh", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 