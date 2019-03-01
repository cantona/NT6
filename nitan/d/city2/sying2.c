#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"步軍大營"NOR);
        set("long", @LONG
這裡就是「大宋」步軍大營，營內刀光耀眼，劍甲林立，大宋的
步軍為了對付蒙古人的騎兵，不惜花重金聘請江湖高手教習步兵地堂
刀絕技，一片片刀光卷地而過，讓人驚嘆不已。
LONG );
        set("train", "infantry");
        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "east" :   __DIR__"sying1",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
