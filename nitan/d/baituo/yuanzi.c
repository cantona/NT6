#include <room.h>
inherit ROOM;

void create()
{
        set("short", "院子");
        set("long", @LONG
這是一個大院子，打掃得一塵不染。四周裝點着幾株青青翠竹，
錯落有致。西邊是武器庫。東邊有一間儲藏室，房門關閉着。北邊是
白駝山莊的大廳。南邊就是大門了。
LONG );
        set("exits", ([
                "northup" : __DIR__"dating",
                "west"    : __DIR__"wuqiku",
                "east"    : __DIR__"storeroom",
                "south"   : __DIR__"damen",
        ]));
        create_door("east", "木門", "west", DOOR_CLOSED);
        set("coor/x", -49970);
        set("coor/y", 20010);
        set("coor/z", 20);
        setup();
}
