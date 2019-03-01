#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蒙古大營"NOR);
        set("long", @LONG
這裡就是「蒙古」軍大營了，四處都是大大小小的蒙古包，北面
的一個較大的蒙古包周圍都是來回巡邏的衛兵，估計應該是蒙古可汗
的帳營了。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
               "north" :   __DIR__"mying1",
               "south" :   __DIR__"myuanmen1",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}

