inherit DEMONROOM;

void create()
{
        set("short", "千蛇洞");
        set("long",@LONG
這是蛇洞內的千蛇洞，只見四周滿是毒蛇，恐怖非常。
LONG);


        set("exits", ([
                "north"  : __DIR__"shedong4.3",                
                "south"  : __DIR__"shedong4.5",
        ]));

                set("n_time", 60);
                set("n_npc",5); 
                set("n_max_npc", 8);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/wangshe");

        setup();
}
