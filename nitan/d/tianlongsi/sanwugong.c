inherit ROOM;

void create()
{
        set("short", "三無宮");
        set("long", @LONG
這裡可以買香到後面參拜西方大士。幾個進香客正圍著一個老年
僧人討價還價。
LONG );
        set("exits", ([
                "southeast" : __DIR__"doushuai",
                "north" : __DIR__"cibeiyuan",
        ]));
        set("objects",([
                "/d/wudang/npc/guest" : 4,
                __DIR__"npc/laoniansengren" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}