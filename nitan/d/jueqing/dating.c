#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "大廳");
        set("long", @LONG
絕情谷大廳正中擺放着一個紅棕色茶几，四周並排着幾個
椅子，椅背上刻有些許圖案，雖單調了點，但也顯得非常別緻，
廳角的幾盆花木散發出陣陣清香。
LONG);

        set("objects", ([
              __DIR__"npc/dizi1"  :  2,
              __DIR__"npc/dizi2"  :  2,
        ])); 
        set("exits", ([
               "out"   : __DIR__"shanzhuang",
               "north" : __DIR__"neitang",
               "west"  : __DIR__"changlang1",
               "east"  : __DIR__"xiaojing",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
