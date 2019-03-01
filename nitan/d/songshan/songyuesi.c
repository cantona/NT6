// Room: /d/songshan/songyueta.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "嵩岳寺");
        set("long", @LONG
這裡原是北魏離宮。孝明帝舍為佛院，至隋方有今名，寺圍闊大，
僧舍連雲。院內風動旌揚，鬆搖竹亂，別有一般清靜。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shandao3",
                "northwest" : __DIR__"shandao4",
                "west"      : __DIR__"songyueta",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 790);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}