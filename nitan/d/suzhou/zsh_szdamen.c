//zsh_szdamen.c

#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "紫衫會前門");
        set("long", @LONG
這裡是紫衫會總部所在地。紫衫會在江湖上行動神秘，屢行俠義
之舉，許多江湖好漢均慕名而來。
LONG );
        set("outdoors", "suzhou");
        set("exits", ([
                "south"  :  __DIR__"hehuating",
                "north"  :  __DIR__"zsh_szzb",
        ])); 
        set("objects", ([   
                __DIR__"npc/zsh_guard" : 2,   
        ]));
               
	set("coor/x", 1090);
	set("coor/y", -1070);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "north") 
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