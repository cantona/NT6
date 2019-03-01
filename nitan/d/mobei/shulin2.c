// Room: /d/mobei/shulin2.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "雜樹林");
        set("long", @LONG
在漠北這片苦寒的土地上，這片雜樹林宛如沙漠中的綠州般令人驚
喜。林子不大，樹木也比較矮小，許多地方的灌木叢把路完全擋住了，
樹上殘留的幾片葉子在風中輕輕飄落。
LONG);
        set("no_clean_up", 0);
        set("outdoors","mobei");
        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"shulin5",
                "south" : __DIR__"shulin1",
        ]));
        set("coor/x", -230);
        set("coor/y", 5210);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}