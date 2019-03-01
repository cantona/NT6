// Room: /d/yueyang/chaguan.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "巴陵茶館");
        set("long", @LONG
你一走進來，就聞到一股茶香沁入心脾，精神為之一爽：那是洞庭
春的味道啊。幾個衙門胥吏模樣的人也在茶館裡翹著二郎腿喝茶。一些
打扮齊整的客商和汗流浹背的苦力各自自成一堆，或輕品，或驢飲，各
具神態。
LONG );
        set("resource/water", 1);
        set("exits", ([
                "north" : __DIR__"dongjie",
        ]));
        set("objects", ([
                __DIR__"npc/chaboshi" : 1,
                __DIR__"npc/xingren" : 1,
        ]));
	set("coor/x", -6190);
	set("coor/y", -3020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}