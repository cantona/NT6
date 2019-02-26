// Room: /d/huangshan/mingxuan.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "鳴弦泉");
        set("long", @LONG
泉水自高山石壁驟然落下，衝擊一塊橫卧山麓，左厚右薄中空，狀
如古琴的巖石，發出悦耳而有節奏的音響而得名。所以古詩讚道“卻按
工商仔細聽，二十五絃俱不在”。
LONG
        );
        set("exits", ([ 
                "south"        : __DIR__"sandie",
        ]));
        set("objects", ([
                __DIR__"obj/stone3" : 1,
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -615);
        set("coor/y", -1060);
        set("coor/z", -40);
        setup();
        replace_program(ROOM);
}