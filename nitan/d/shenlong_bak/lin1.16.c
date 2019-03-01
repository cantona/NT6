inherit DEMONROOM;

void create()
{
        set("short", "東部叢林危險地帶");
        set("long",@LONG
這是神龍島原始叢林深處，再往前走就是危險地帶了，小心。
LONG);

        set("exits", ([
                "enter"  : __DIR__"lin1.17", 
                "west"  : __DIR__"lin1.15",
                "south" : __DIR__"xiaoxi1",
                "east" : __DIR__"haitan1",

        ]));

                set("n_time", 60); 
                set("n_npc", 1); 
                set("n_max_npc", 1);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/qingshe");

        set("outdoors", "shenlong");
        setup();
}
