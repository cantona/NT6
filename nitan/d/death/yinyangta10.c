#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB "陰陽塔" NOR);
        set("long", HIB @LONG
這是地獄中最高的一座塔，高約三百餘尺，共有十八級。相傳塔頂
住有神獸朱雀，這個傳言也不知是真是假。
LONG NOR
        );

        set("exits", ([
              "up"   : __DIR__"yinyangta11",
              "down" : __DIR__"yinyangta9",
        ]));
        
        set("objects",([
        ]));
        
        set("no_magic", 1);
        setup();
        replace_program(ROOM);
}