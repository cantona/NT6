inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "皇宮大道");
        set("long", @LONG
這裏是皇宮內的大道，分外的寬敞平整，不時有一些宮女和太監
經過，你不敢多看，還是快點朝前走吧，省得招來侍衞的盤查。
LONG );
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "north"    : __DIR__"hgdadao2",
                "south"    : __DIR__"ydmen",
        ]));

        set("objects", ([

        ]));
        setup();
        replace_program(ROOM);
} 
