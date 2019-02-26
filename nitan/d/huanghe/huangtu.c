// Room: /huanghe/huangtu.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "黃土高原");
        set("long", @LONG
黃河像一把厲刃將黃土高原切開。無數條小溪流夾帶着泥沙匯入黃
河，形成千溝萬壑。溝壑之間的一塊塊平地叫做台塬。黃河沿蒙古高原
南邊向東流淌，遇太行山脈的阻攔，便轉頭南下，形成晉陝的分界。
LONG );
        set("exits", ([
                "northeast" : __DIR__"hetao",
                "southwest" : __DIR__"huanghe_2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -3000);
        set("coor/y", 500);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}