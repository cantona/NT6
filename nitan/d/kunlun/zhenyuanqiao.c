// Room: /d/kunlun/zhengyuanqiao.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "鎮遠橋");
        set("long",@long
這座橋號稱“天下黃河第一橋”，氣勢極為雄偉，扼守西域，東往
中原。黃河水從橋底傾瀉而過，轟隆作響。
long);
        set("exits",([
                "west"      : __DIR__"shanlu",
                "southeast" : "/d/mingjiao/shanjiao",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" :  1,
                "/d/city/npc/bing" :     3,
                __DIR__"npc/seller" :  1,
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -60000);
        set("coor/y", 5000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}