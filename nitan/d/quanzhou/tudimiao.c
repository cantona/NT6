// Room: /d/quanzhou/tudimiao.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "土地廟");
        set("long", @LONG
這是一間十分破舊的土地廟，也不知荒廢了多久，樑上地下佈滿了
灰塵。土地神像後面的牆上有個洞口，老鼠爬進爬出，噁心極了。
LONG );
        set("exits", ([
                "west"   : __DIR__"luoyangqiao",
        ]));
        set("objects", ([
                "/d/village/npc/dipi" : 1,
        ]));
	set("coor/x", -850);
	set("coor/y", -7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}