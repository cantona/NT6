#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "亂石灘");
        set("long", @LONG
這裏怪石林立，路極不好走，不小心就要摔個跟斗，過了
這片石灘，就是長江岸邊。
LONG);
        set("outdoors", "jingzhou");

        set("exits", ([
                "south" : __DIR__"road2", 
                "north" : "/d/jingzhou/nanshilu1",
        ]));

        setup();
        replace_program(ROOM);
}
