//Room: /d/dali/feilihu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","妃麗湖畔");
        set("long",@LONG
你站在妃麗湖的北岸，北邊不遠就是喜州城。此湖不大，但湖水
清澈，魚鱉皆有，不少台夷村民劃著竹筏在湖上捕魚。湖之南和東邊
半山上都有台夷村鎮，有道路繞湖東而過通向南邊。
LONG);
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"xizhou",
            "east"       : __DIR__"luwang",
            "southeast"  : __DIR__"feilihueast",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19130);
	set("coor/y", -6960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}