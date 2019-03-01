// Room: /d/mobei/yinzhang.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "鐵木真營帳");
        set("long", @LONG
蒙古人以遊牧為生，趕了牲口東遷西徙，追逐水草，並無定居，用
毛氈搭搭成帳篷以蔽風雪，就叫做蒙古包。這雖然是鐵木真的住處，卻
依然質樸無華，只是比尋常所用大了數倍不止。
LONG);
        set("valid_startroom",1);
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/tiemuzhen" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 1 */
                "south" : __DIR__"road",
        ]));
        set("coor/x", -210);
        set("coor/y", 5260);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}