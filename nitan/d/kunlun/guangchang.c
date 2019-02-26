// Room: /d/kunlun/guangchang.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "大廣場");
        set("long",@long
這裏是一個平平開闊的大廣場，廣場上有崑崙派的弟子在習武，前
面不遠處是個巨大的石屏風，後面就是崑崙派的前廳了，西面和東面仍
然是廣場。
long);
        set("exits",([
                "south" : __DIR__"shanlu04",
                "north" : __DIR__"pingfeng",
                "west"  : __DIR__"guangchangw",
                "east"  : __DIR__"guangchange",
        ]));
        set("objects",([
                CLASS_D("kunlun")+"/gaozecheng" :  1,
                __DIR__"npc/kl-dizi2" :  2,
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119990);
        set("coor/y", 40040);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}