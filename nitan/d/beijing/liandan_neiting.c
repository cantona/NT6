#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "回春堂藥店內廳");
        set("long", @LONG
這裏是回春堂藥店的內廳，你一走進這裏，發現藥的氣味比外面
還要濃上很多。你看見一個小童正在這裏埋着頭整理藥材。
LONG );
        set("no_fight", 1);
        set("objects", ([
                "/d/beijing/npc/liandan_tongzi"     : 1,
        ]));
        set("exits", ([
                "west" : "/d/beijing/huichuntang",
                "north": "/d/beijing/liandan_yaoshi",
        ]));

	set("coor/x", -2800);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
}