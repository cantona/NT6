#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", GRN "【白虎穴】" NOR);
        set("long", GRN @LONG

                    白         虎         穴

    這裡是寂滅司後面黑森林最深處的一個洞穴，洞的上部空曠，存有
少量的空氣，你終于可以換氣了。傳說四神獸之一的白虎就棲息于此地。
洞內幽暗無比，令你根本看不清周圍的事物。

LONG NOR );

        set("objects", ([
                __DIR__"npc/baihu" : 1,
        ]));
        
        set("exits", ([
                "south" : __DIR__"heisenlin/exit",
        ]));

        set("baihu", 1);
        set("no_magic", 1);
        setup();
}