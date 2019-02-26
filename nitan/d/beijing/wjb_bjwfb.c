inherit ROOM;

void create()
{ 
        set("short", "無極幫門前");
        set("long", @LONG
這裏是無極幫北京分部的大門前面，無極幫的這個大廳只是發佈
任務的所在，即使如此，這座建築也造的風格迥然，讓人一眼看上去，
就覺得氣勢不凡。
LONG );
        set("outdoors", "beijing");
        set("exits", ([
                "west" :  "/d/beijing/yongdingdao",
                "east" : "/d/beijing/wjb_bjwdt",
        ])); 
        set("objects", ([   
             "/d/beijing/npc/wjb-guard" : 2,   
            ]));
               
	set("coor/x", -2790);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "east") 
        {
           if( !query_temp("good_wjb2", me) && query("bunch/bunch_name", me) != "無極幫" )
               return notify_fail("守衞一把攔住你，朗聲喝道：我無極幫怎由閒雜人等隨便進出。\n"); 
           else
           {
              delete_temp("good_wjb2", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 