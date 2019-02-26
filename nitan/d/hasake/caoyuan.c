// caoyuan.c 草原
inherit ROOM;
void create()
{
        set("short", "草原邊緣");
        set("long", @LONG
這裏是大草原和沙漠接壤之地，青草由稀至密，向西綿綿延伸而去。
地上有幾行駱駝踏過的蹄印，看樣子這裏常常有商隊來往。西南方好像有
些炊煙。
LONG);
        set("exits", ([
            "east" : __DIR__"caoyuana",
            "southwest" : __DIR__"caoyuan1",
            "northwest" : __DIR__"caoyuan2",
            "north" : __DIR__"caoyuan3",
 //           "north" : __DIR__"caoyuana",
            "south" : __DIR__"caoyuana",
        ]));
        set("objects", ([
                    __DIR__"npc/biaoshi" : 1,
        ])); 
        set("outdoors", "hasake");
        setup();
}
/*
int valid_leave(object me, string dir)
{
       if( dir == "north")addn_temp("mark/steps", 1, me);
       if( dir == "south")addn_temp("mark/steps", -1, me);
        
       if( query_temp("mark/steps", me) == 4){
            me->move(__DIR__"hswz");
            delete_temp("mark/steps", me);
            return notify_fail("唉。。。\n");
           }  
     if( query_temp("mark/steps", me) == -4){
           me->move(__DIR__"caoyuan1");
           delete_temp("mark/steps", me);
             return notify_fail("唉。。。\n");
        }  
        return ::valid_leave(me, dir);
}
*/