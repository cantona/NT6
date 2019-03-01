#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "望月台");
        set("long", @LONG
望月台是祝融殿後一高聳巨石。每當夜籟，皓月當空，猶如玉盤
冰輪，漫洒萬裡清輝，清冷月色，輝映低昂的群峰。此時浩然萬裡，
舉七十二峰，峰峰貯冰壺中，始信下方無此月也。前人因此有詩句言
人間朗魄已皆盡，此地清光猶未低。
LONG );
        set("exits", ([
               "southup"    : __DIR__"zhurongdian",
               "up"    : "/d/reborn/jitan3",
        ]));

        set("objects", ([
                __DIR__"npc/youke"    : 3,
        ]));    

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6930);
	set("coor/y", -5480);
	set("coor/z", 30);
	setup();
}