inherit DEMONROOM;

void create()
{
        set("short", "幽深隧道");
        set("long",@LONG
這是一條幽深的隧道深不見底。
LONG);

        set("exits", ([
                "north"   : __DIR__"dong2.2",
                "south"   : __DIR__"dong2.4",

        ]));

                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 4);
                set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
