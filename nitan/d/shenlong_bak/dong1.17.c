inherit DEMONROOM;

void create()
{
        set("short", "幽深隧道");
        set("long",@LONG
這是一條幽深的隧道深不見底。
LONG);

        set("exits", ([
                "east"   : __DIR__"dong1.16",
                "west"   : __DIR__"dong1.18",

        ]));

                set("n_time", 60); 
                set("n_npc", 4); 
                set("n_max_npc", 6);
                set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        set("outdoors", "shenlong");
        setup();
}
