// Room: /d/mobei/road1.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "營帳間");
        set("long", @LONG
舉目所見，那都是密密麻麻的營帳，一個連着一個，蒙古部落遊牧
為生，平時所住就是蒙古包，拆解方便。兩邊有道通向幾個帳幕，分別
是親衞和大將們的住所，南面是轅門，幾面旌旗迎風招展。
LONG);
        set("outdoors","mobei");
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/qinwei1" : 1,
        ]));
        set("exits", ([ /* sizeof() == 4 */
                "north" : __DIR__"road",
                "east" : __DIR__"road2",
                "west" : __DIR__"road3",
                "south" : __DIR__"yuanmen",
        ]));
        set("coor/x", -210);
        set("coor/y", 5240);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}