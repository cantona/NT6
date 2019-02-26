// Room: /d/huangshan/yixian.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "一線天");
        set("long", @LONG
天都下來，越磴道往文殊院去，經小心坡，蒲團鬆，便達沿垂直裂
系風化的“一線天”。這裏十分狹長，高達三十餘米的石壁緊緊夾峙最
寬處不過兩米，窄處只有半米，仰望長空，藍天一線。一線天西北便是
文殊院了。
LONG
        );
        set("exits", ([ 
                "west"    : __DIR__"wenzhu",
                "southup" : __DIR__"tiandu",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -565);
        set("coor/y", -1050);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}