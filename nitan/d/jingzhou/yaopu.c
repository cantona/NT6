inherit ROOM;

void create()
{
        set("short", "藥舖");
        set("long", @LONG
這裡是一家藥舖，一股濃濃的藥味讓你幾欲窒息，那是從藥櫃上
的幾百個小抽屜裡散發出來的。神醫華陀二世坐在茶幾旁，獨自喝著
茶，看也不看你一眼。一名小伙計站在櫃台後招呼著顧客。
LONG );
        set("objects", ([
                __DIR__"npc/huatuo" : 1,
                __DIR__"npc/huoji" : 1,
        ]));
        set("exits", ([
                "east" : __DIR__"beidajie2",
        ]));

        set("coor/x", -7110);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}