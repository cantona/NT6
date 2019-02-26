inherit DEMONROOM;

void create()
{
        set("short", "九頭蛇洞");
        set("long",@LONG
這是蛇洞內的九頭蛇洞，據説，這裏是九頭蛇出沒的地方。
LONG);


        set("exits", ([
                "west"  : __DIR__"shedong4.6",                
                "south"   : __DIR__"shedong4.8",
        ]));

                set("n_time", 60);
                set("n_npc",1); 
                set("n_max_npc", 2);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/jiutoushe");

        setup();
}
