inherit DEMONROOM;

void create()
{
        set("short", "海灘");
        set("long",@LONG
這是神龍島東部沿岸沙灘。
LONG);

        set("exits", ([
                "west"  : __DIR__"haitan9", 
                "east"  : __DIR__"haitan11",

        ]));

                set("n_time", 60); 
                set("n_npc", 1); 
                set("n_max_npc", 6);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/qingshe");

        set("outdoors", "shenlong");
        setup();
}
