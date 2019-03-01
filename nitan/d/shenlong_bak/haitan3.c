inherit DEMONROOM;

void create()
{
        set("short", "沙地");
        set("long",@LONG
這是神龍島東部的一片沙地。
LONG);

        set("exits", ([
                "west"  : __DIR__"haitan2", 
                "east"  : __DIR__"haitan4",

        ]));

                set("n_time", 60); 
                set("n_npc", 1); 
                set("n_max_npc", 4);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/shanhushe");

        set("outdoors", "shenlong");
        setup();
}
