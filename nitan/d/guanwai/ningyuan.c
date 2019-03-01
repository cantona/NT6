// /guanwai/ningyuan.c
inherit ROOM;

void create()
{
        set("short", "寧遠");
        set("long", @LONG
這裡是關外駐防的軍事重鎮。城高河寬，守備森嚴，城樓上不但有大量
的官兵駐防，甚至還有幾門紅衣火炮，架設其上。城門旁幾名官兵正在檢察
來往行人的物品，不時傳來幾聲叱罵之聲。
LONG );
        set("exits", ([
                "northeast" : __DIR__"road4",
                "south"     : __DIR__"road3",
        ]));
        set("no_clean_up", 0);
         set("outdoors", "guanwai");
        set("coor/x", 3970);
	set("coor/y", 9160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
