// Room: /d/yueyang/jiuxiangting.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "酒香亭");
        set("long", @LONG
酒香亭位于君山主峰酒香山頂，故老相傳，當年漢武帝聽說君山有
美酒數壇，飲之可仙，便派童男童女去取，回報只聞酒香，不見酒跡，
他只好作罷。從此，君山主峰才有了“酒香”之名，而建于其巔的多角
觀景亭，也以“酒香”命名。小亭呈四方形，掩映在翠竹籐蔓之中。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "north"    : __DIR__"jiuxiangshan",
                "south"    : __DIR__"shijie6",
                "eastdown" : __DIR__"shijie5",
                "westdown" : __DIR__"xiaolu9",
        ]));
        set("coor/x", -1780);
        set("coor/y", 2280);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}