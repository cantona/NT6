inherit DEMONROOM;

void create()
{
        set("short", "神祕巖洞結冰路面");
        set("long",@LONG
這是神龍島東南部巖洞，走在此處路面不知何故已經結了冰。
LONG);

        set("exits", ([
                "south"  : __DIR__"lin1.24", 
                "north"  : __DIR__"lin1.22",

        ]));

                set("n_time", 60); 
                set("n_npc", 1); 
                set("n_max_npc", 2);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/wangshe");

        set("outdoors", "shenlong");
        setup();
}
