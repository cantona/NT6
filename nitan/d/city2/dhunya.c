#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB"斷魂崖"NOR);
        set("long", @LONG
這裏就是天險斷魂崖了，是扼守南北的交通必經之路，歷來為兵
家必爭之地，由山頂幣制而下，只有一條狹窄的羊腸小道，兩面則是
萬丈深淵，看來斷腸二字，名不虛傳。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
              "east"  :   __DIR__"shanlu3",
              "south" :   __DIR__"shanlu2",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}
