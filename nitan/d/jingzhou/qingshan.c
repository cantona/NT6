#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山頂");
        set("long", @LONG
爬上山頂，只覺空氣清新，登高望遠，心曠神怡。向東望去，只
見揚洲城有如一個小小的黑點，極目向西，卻茫茫而不見。南面，只
見一條大江如彩帶一般，那就是長江了。
LONG );
        set("exits", ([
                //"eastdown" : __DIR__"qingshan2",
                "north" : __DIR__"gumiao",
                "westdown" : __DIR__"qingshan1",
                "southdown" :__DIR__"chibi1"
        ]));
        set("objects", ([
                "/d/beijing/npc/youke" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("coor/x", -350);
        set("coor/y", -190);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
