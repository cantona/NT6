#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "厲鬼峰");
        set("long", @LONG
此處是絕情谷東面的厲鬼峰，谷中世代相傳，峰上有厲鬼
作崇，是以誰也不敢上來。一到這裡狂風大作，吹得人不禁毛
骨悚然，擔了一個寒顫。
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "southwest" : __DIR__"shanlu6",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}