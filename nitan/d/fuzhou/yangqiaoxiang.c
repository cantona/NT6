// Room: /d/fuzhou/yangqiaoxiang.c
// Last Modifyed by Evil on Sep. 10 2002

inherit ROOM;

void create()
{
        set("short", "楊橋巷");
        set("long", @LONG
古名登俊坊，因西通楊橋而改名。附近有座雙拋橋, 傳說古時有一
對青年男女相愛, 不得如願，雙雙投河殉情, 故名“雙拋”。
LONG );

        set("exits", ([
                "west"    : __DIR__"nanhoujie1",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -80);
	set("coor/y", -6190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}