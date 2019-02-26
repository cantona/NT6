// Room: /d/songshan/westpath2.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;
void create()
{
        set("short", "西廊");
        set("long", @LONG
這裏是環繞池塘的走廊，畫闌雕棟，卻也美侖美奐。一路走來，腳
底木板響動，別有韻味。嵩嶽獨立天心，八方天風，只吹得天邊雲起雲
落，滿山樹浪起伏。
LONG );
        set("outdoors", "songshan");
        set("exits", ([
                "west"  : __DIR__"liangong",
                "south" : __DIR__"westting",
                "north" : __DIR__"westwuchang",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -40);
        set("coor/y", 910);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}