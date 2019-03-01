//Cracked by Kafei
// yideng quest room 12

inherit ROOM;
void create()
{
        set("short", "廟後石室");
        set("long", @LONG
竹林深處的石室清雅幽靜，窗外滿眼是幽幽碧竹，正是禪宗參禪
之妙所。室中小幾上點著一爐檀香，幾旁一位老僧端坐在蒲團上。
LONG );

        set("exits", ([
                "south" : __DIR__"yideng11",
        ]));

        set("objects", ([
                CLASS_D("duan") + "/yideng" : 1,
                ]) );

        set("invalid_startroom", 1);
        set("coor/x", -38000);
        set("coor/y", -79990);
        set("coor/z", 500);
        setup();
}