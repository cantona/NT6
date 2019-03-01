// Room: /d/changcheng/beisilou.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "北四樓");
        set("long", WHT@LONG
登上北四樓極目遠眺，但見長城從西南面的山脊曲折蜿蜒而來，莽
莽蒼蒼，橫亙天外，在這裡突然折向南面，不久再度逶迤東去，恰似一
條巨大的遊龍，不知其所來，也不知其所去。
LONG
NOR  );
        set("outdoors", "changcheng");
        set("exits", ([
                "southwest" :__DIR__"badaling",
                "southup"   :__DIR__"nansilou",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 2000);
        set("coor/y", 6000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}