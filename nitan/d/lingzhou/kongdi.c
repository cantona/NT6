// Room: /lingzhou/kongdi.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "林中空地");
        set("long", @LONG
這是山谷中的一大塊空地，錯落有致的分佈着數十幢木屋，炊煙裊
裊的飄蕩在上空，幾個小孩正在追逐嬉鬧，兩條大狗沒精打采的趴在屋
檐下曬太陽，周圍山坡上同樣是巨木參天，看上去這裏就象一個氣氛祥
和的小村。靠北的空地上有座大木屋看上去有點引人注目。西北和東北
各有一條山路。
LONG );
        set("exits", ([
                "enter"     : __DIR__"dawu",
                "southwest" : __DIR__"tulu",
                "northwest" : __DIR__"qingxinquan", 
        ]));
        set("objects", ([
                __DIR__"npc/nan" : 1,
                "/d/city/npc/wolfdog" : 2,
        ]));
        set("outdoors", "lingzhou");
        set("coor/x", -6225);
        set("coor/y", 2965);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}