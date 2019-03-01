// Room: /d/hengshan/beiyuemiao.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "北岳廟");
        set("long", @LONG
北岳廟是個巍巍壯觀的宮殿廟宇，山門三重，高列阜上，其下石階
數層。這裡是北岳廟最大最高的“朝殿”。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "east"      : __DIR__"kutianjing",
                "west"      : __DIR__"jijiaoshi",
                "northup"   : __DIR__"beiyuedian",
                "southdown" : __DIR__"guolaoling",
        ]));
        set("objects", ([
                CLASS_D("hengshan")+"/he" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", 30);
        set("coor/y", 3170);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}
