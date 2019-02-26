#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "百曲湖");
        set("long", @LONG
這是一個支流眾多的小河，四面都是菱葉。除了槳聲和菱葉與船
身相擦的沙沙輕聲，四下一片寂靜，湖上清風，夾着淡淡的花香，你
不禁心想：  "就算這樣一輩子，也好哇！"
LONG );
        set("outdoors", "yanziwu");
        set("objects",([
                "/d/yanziwu/obj/dodgebook":1,
        ]));
        setup();
        replace_program(ROOM);
}