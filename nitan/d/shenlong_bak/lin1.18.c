inherit DEMONROOM;

void create()
{
        set("short", "神祕巖洞");
        set("long",@LONG
這是神龍島東部的一個巖洞，這裏陰暗潮濕，令人覺得毛骨悚然。
LONG);

        set("exits", ([
                "south"  : __DIR__"lin1.19", 
                "north"  : __DIR__"lin1.17",

        ]));

                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 10);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/jinshewang");

        set("outdoors", "shenlong");
        setup();
}
