inherit ROOM;

void create()
{ 
        set("short", "無極幫門前");
        set("long", @LONG
這裡是無極幫襄陽總部的大門前面，無極幫的這個大廳只是發布
任務的所在，即使如此，這座建築也造的風格迥然，讓人一眼看上去，
就覺得氣勢不凡。
LONG );
        set("outdoors", "xiangyang");
        set("exits", ([
                "south" :  __DIR__"xiaorong1",
                "north" :  __DIR__"wjb_dating",
        ])); 
        set("objects", ([   
                __DIR__"npc/wjb-guard" : 2,   
        ]));
               
        set("coor/x", -7780);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "north") 
        {
           if( !query_temp("good_wjb", me) && query("bunch/bunch_name", me) != "無極幫" )
               return notify_fail("守衛一把攔住你，朗聲喝道：我無極幫怎由閒雜人等隨便進出。\n"); 
           else
           {
              delete_temp("good_wjb", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 