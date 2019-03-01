#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", BLK"烏石嶺"NOR);
        set("long", @LONG
這裡就是烏石嶺了，據說得名于滿地的烏巖所致，具體的原因就
無從考究了，近年來大宋和蒙古連年戰火，邊境早已民不聊生，這裡
早就成了人跡罕至之地了。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
              "north" :   __DIR__"shanlu2",
              "south" :   __DIR__"shanlu1",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}

