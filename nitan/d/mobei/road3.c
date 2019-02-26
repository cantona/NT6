// Room: /d/mobei/road3
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set ("short", "營帳間");
        set ("long", @LONG
舉目所見，那都是密密麻麻的營帳，一個連着一個，蒙古部落遊牧
為生，平時所住就是蒙古包，拆解方便。兩邊有道通向幾個帳幕，分別
是親衞和大將們的住所。
LONG);
        set("outdoors","mobei");
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 3 */
                "east"  : __DIR__"road1",
                "west"  : __DIR__"qinwei2",
                "south" : __DIR__"boershu",
                "north" : __DIR__"muhuali",
        ]));
        set("coor/x", -220);
        set("coor/y", 5240);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}