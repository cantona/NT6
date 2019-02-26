// Room: /d/mobei/road.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "營帳間");
        set("long", @LONG
舉目所見，那都是密密麻麻的營帳，一個連着一個，蒙古部落遊牧
為生，平時所住就是蒙古包，拆解方便。北面的一個營帳前一杆高高的
長杆上飄着幾縷白毛，此旗所在處就是大汗居處。
LONG);
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/qinwei1" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors","mobei");
        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"yinzhang",
                "south" : __DIR__"road1",
                "east"  : __DIR__"wokuotai",
                "west"  : __DIR__"tuolei",
        ]));

        set("coor/x", -210);
        set("coor/y", 5250);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}