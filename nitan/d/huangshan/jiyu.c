// Room: /d/huangshan/jiyu.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "鯽魚背");
        set("long", @LONG
過了探海鬆，便是鯽魚背了，一段長約十余丈，寬僅半丈，兩側凌
空，下臨深淵的石質刃脊，前人所謂“天都欲上路難通”指的就是這一
段，直到二仙另開一路，方才可以輕鬆登天都。過了鯽魚背，再經過前
面的“仙人把洞門”，便是天都峰了。
LONG
        );
        set("exits", ([ 
                "eastup" : __DIR__"tiandu",
                "west"   : __DIR__"guanyin",
                "north"  : __DIR__"erxian",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -585);
        set("coor/y", -1070);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}