#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB "陰陽塔" NOR);
        set("long", HIB @LONG
這是地獄中最高的一座塔，高約三百余尺，共有十八級。相傳塔頂
住有神獸朱雀，這個傳言也不知是真是假。
LONG NOR
        );

        set("exits", ([
              "up"   : __DIR__"yinyangta13",
              "down" : __DIR__"yinyangta11",
        ]));
        
        set("objects",([
        ]));
        
        set("no_magic", 1);
        setup();
        replace_program(ROOM);
}