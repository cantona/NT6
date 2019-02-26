// Room: /d/hengshan/sanjiaodian.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "三教殿");
        set("long", @LONG
這裏是全寺最高處的三教殿，也是懸空寺最大的殿宇。三層九脊，
全部由每根插入崖石的木樑承受，真是“公輸天巧”，古今奇蹟。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "down"   : __DIR__"xuankong1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 3180);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}