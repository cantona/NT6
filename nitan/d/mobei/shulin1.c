// Room: /d/mobei/shulin1
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set ("short", "雜樹林");
        set ("long", @LONG
在漠北這片苦寒的土地上，這片雜樹林宛如沙漠中的綠州般令人驚
喜。林子不大，樹木也比較矮小，許多地方的灌木叢把路完全擋住了，
樹上殘留的幾片葉子在風中輕輕飄落。
LONG);
        set("outdoors","mobei");
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 4 */
                "west"  : __DIR__"shulin4",
                "east"  : __DIR__"caoyuan6",
                "south" : __DIR__"shulin3",
                "north" : __DIR__"shulin2",
        ]));
        set("coor/x", -230);
        set("coor/y", 5200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}