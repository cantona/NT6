// Room: /d/xingxiu/songmoya.c
// Last Modified by winder on Apr. 25 2001
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIM"頌摩崖"NOR);
        set("long", @LONG
頌摩崖又名黃龍碑。周圍山勢陡峭，兩山對峙，一泓中流，兩峽旁
有潭，淵深莫測。俗傳有黃龍自潭飛出，因名黃龍潭。潭左側摩崖成碑。
漢隸真跡，筆觸遒勁，刀刻有力，記敍了開天井道的過程。往東南是仇
池山，往西則是石門。
LONG);
        set("outdoors", "silu");
        set("no_clean_up", 0);
        set("exits", ([
                "eastdown" : __DIR__"silk2",
                "westdown" : __DIR__"silk3",
        ]));
        set("coor/x", -21000);
        set("coor/y", 600);
        set("coor/z", 100);
        setup();
}
#include "/d/xingxiu/job2.h";
