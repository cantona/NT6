// Room: /d/hengshan/hufengkou.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "虎風口");
        set("long", @LONG
過 "步雲橋" ， "望仙亭" ，就到了一個峯迴路轉的陡峭路口，
這裏是一處風口，大風來處，聲如虎嘯，比別處強勁多多，故有是
名。
LONG);
        set("exits", ([ /* sizeof() == 4 */
           "southwest" : __DIR__"daziling",
           "west"      : __DIR__"xuangengsong",
           "northeast" : __DIR__"guolaoling",
        ]));
        set("outdoors", "hengshan");
        set("no_clean_up", 0);
        set("coor/x", 20);
        set("coor/y", 3150);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}
