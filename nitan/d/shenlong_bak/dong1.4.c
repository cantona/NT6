inherit DEMONROOM;

void create()
{
        set("short", "幽深隧道");
        set("long",@LONG
這是一條幽深的隧道深不見底。
LONG);

        set("exits", ([
                "east"   : __DIR__"dong1.3",
                "west"   : __DIR__"dong1.5",

        ]));

                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 2);
                set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
