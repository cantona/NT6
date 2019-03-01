// Room: /d/songshan/eastpath3.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;
void create()
{
        set("short", "東廊");
        set("long", @LONG
這裡是環繞池塘的走廊，畫闌雕棟，卻也美侖美奐。一路走來，腳
底木板響動，別有韻味。嵩岳獨立天心，八方天風，只吹得天邊雲起雲
落，滿山樹浪起伏。
LONG );
        set("outdoors", "songshan");
        set("exits", ([
                "east" : __DIR__"eastwuchang",
                "west" : __DIR__"huayuan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -10);
        set("coor/y", 920);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}