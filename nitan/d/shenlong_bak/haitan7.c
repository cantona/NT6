inherit DEMONROOM;

void create()
{
        set("short", "仙人掌叢林");
        set("long",@LONG
這是神龍島東部一片仙人掌叢林，這裡四處都是一人高的仙人掌。
LONG);

        set("exits", ([
                "west"  : __DIR__"haitan6", 
                "east"  : __DIR__"haitan8",

        ]));

                set("n_time", 60); 
                set("n_npc", 1); 
                set("n_max_npc", 6);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/xiangweishe");

        set("outdoors", "shenlong");
        setup();
}
