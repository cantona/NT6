// Room: /d/mobei/road2
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set ("short", "營帳間");
        set ("long", @LONG
舉目所見，那都是密密麻麻的營帳，一個連著一個，蒙古部落遊牧
為生，平時所住就是蒙古包，拆解方便。南邊是親衛營，北面的營帳前
拴了幾條獒犬。東面的營帳是術赤的住處。
LONG);
        set("outdoors","mobei");
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 4 */
                "west"  : __DIR__"road1",
                "east"  : __DIR__"qinwei",
                "south" : __DIR__"shuchi",
                "north" : __DIR__"chahe",
        ]));
        set("coor/x", -200);
        set("coor/y", 5240);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}