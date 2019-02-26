// Room: /d/mobei/shuchi.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "朮赤營帳");
        set("long", @LONG
朮赤是鐵木真的大兒子，他的營帳佈置得比較豪華，連掛在壁上的
弓箭都用金漆仔細描過。一張大紅的氈子鋪在帳幕中間，矮几上的金盃
裝滿了血色的葡萄酒。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/shuchi" : 1,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "north" : __DIR__"road2",
        ]));
        set("coor/x", -200);
        set("coor/y", 5230);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}