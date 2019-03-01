// Room: /d/kunlun/guangchange.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "廣場東");
        set("long",@long
這裡是一個平平開闊的大廣場，廣場上有昆侖派的弟子在習武，西
面是仍然是廣場，東面過去就是懸崖了，南面是下山的路。
long);
        set("exits",([
                "southwest" : __DIR__"shanlu04",
                "west"      : __DIR__"guangchang",
        ]));
        set("objects",([
                CLASS_D("kunlun")+"/yulingzi" :  1,
                __DIR__"npc/kl-dizi3" :  2,
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119980);
        set("coor/y", 40040);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}