//Cracked by Kafei
// yideng quest room 9

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "廟前");
        set("long", @LONG
這裡是深山巔峰，平地上有一座小小寺院，廟前有一個荷塘，一
座小橋橫跨其上。旁邊陡峭的山崖上有一條鐵鏈和一些人工鑿出來的
台階，似乎是一條上下山的捷徑。
LONG );

        set("exits", ([
                "south" : __DIR__"yideng8",
                "enter" : __DIR__"yideng11",
                "down" : __DIR__"maze1",
        ]));

        set("invalid_startroom", 1);
        set("outdoors", "dali");
        set("no_magic", 1);
        setup();
}