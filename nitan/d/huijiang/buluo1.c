// Room: /d/huijiang/buluo1.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "回部部落");
        set("long", @LONG
此處三面是樹林，一面斜坡直連到大草原。你現在處身在幾個大帳
篷之間，東邊的一個帳篷看來特別的大一點。南邊有條小路通向樹林之
中。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "east"  : __DIR__"zhangpeng",
                "west"  : __DIR__"zhangpeng1",
                "north" : __DIR__"buluo2",
                "south" : __DIR__"buluo",
        ]));
        set("objects", ([ /* sizeof() == 4 */
                CLASS_D("honghua")+"/zhang-jin" : 1,
        ]));
        set("outdoors", "huijiang");
        set("coor/x", -50050);
        set("coor/y", 9050);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}