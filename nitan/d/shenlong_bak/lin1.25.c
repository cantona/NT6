inherit DEMONROOM;

void create()
{
        set("short", "神秘巖洞冰窖分岔口");
        set("long",@LONG
這是神龍島東南部巖洞深處的一個冰窖，這裡異常寒冷。
LONG);

        set("exits", ([
                "north"  : __DIR__"lin1.24",
                "east"   : __DIR__"dong3",
                "west"   : __DIR__"dong1",
                "south"  : __DIR__"dong2",

        ]));

                set("n_time", 60); 
                set("n_npc", 1); 
                set("n_max_npc", 2);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/xuanmang");

        setup();
}
