#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "柴房");
        set("long", @LONG
這是一間矮小的瓦房，平時作為堆放雜物所用。房屋裏布
滿了蛛網，地面滿是灰塵。看樣子已經很久沒有人打掃了。柴
房的一角斜放着幾捆乾柴。
LONG);
        set("exits", ([
                "east" : __DIR__"houyuan",
        ]));
        set("region", "luoyang");
        set("no_clean_up", 0);
        set("objects", ([
                "/d/wudu/obj/ganchai" : 2,
        ]));
        set("coor/x", 40);
        set("coor/y", 40);
        set("coor/z", 0);
        setup();
}
