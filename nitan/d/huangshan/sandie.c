// Room: /d/huangshan/sandie.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "三疊泉");
        set("long", @LONG
虎頭巖西北的三疊巖是黃山二奇泉中的一個，因為高山下泄的泉水
流過三個陡坎形成三折而名。無論遠觀近看，傍著周圍清幽的山林，都
是無以倫比的勝境。三疊泉不遠是鳴弦泉。
LONG
        );
        set("exits", ([ 
                "southup" : __DIR__"zuishi",
                "north"          : __DIR__"mingxuan",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -615);
        set("coor/y", -1070);
        set("coor/z", -40);
        setup();
        replace_program(ROOM);
}