inherit DEMONROOM;

void create()
{
        set("short", "神秘巖洞");
        set("long",@LONG
這是神龍島東南部的一個巖洞，這裡陰暗潮濕，令人覺得毛骨悚然。
LONG);

        set("exits", ([
                "south"  : __DIR__"lin1.23", 
                "north"  : __DIR__"lin1.21",

        ]));

                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 6);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/wangshe");

        set("outdoors", "shenlong");
        setup();
}