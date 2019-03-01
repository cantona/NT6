inherit DEMONROOM;

void create()
{
        set("short", "蛇王洞");
        set("long",@LONG
這是蛇洞內的蛇王洞，此處是毒蛇王出沒的地方。
LONG);

        set("exits", ([
                "south"  : __DIR__"shedong3.3",
        ]));

                set("n_time", 75);
                set("n_npc", 1); 
                set("n_max_npc", 2);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/dushewang");

        setup();
}
