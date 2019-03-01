// Room: /d/kunlun/kuhanlou.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "苦寒樓");
        set("long",@long
這裡是昆侖派的苦寒樓，取名自“梅花香自苦寒來”之意，乃是昆
侖派前輩為了激勵後進昆侖派弟子而建的，是昆侖弟子靜修之所。
long);
        set("exits",([
                "west" : __DIR__"shanlin"+(random(5)+1),
                "enter" : __DIR__"kuhanlou1",
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119900);
        set("coor/y", 40130);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}