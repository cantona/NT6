// Room: /d/taishan/sanyibai.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "三義柏");
        set("long", @LONG
萬仙樓位於紅門宮北，樓前有古柏三株，挺拔並列，蒼翠凌雲，碣
書“三義柏”。再前西崖題“勇登仙境”，下有洞，洞內有石龜，俗稱
龜洞。
LONG );
        set("exits", ([
                "north"     : __DIR__"wanxianlou",
                "southdown" : __DIR__"yitian",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 70);
	set("coor/y", 100);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}