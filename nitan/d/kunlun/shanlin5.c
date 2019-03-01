// Room: /d/kunlun/shanlin5.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "雲杉林");
        set("long",@long
這是一片蜿蜒無盡的翠綠的樹林，密密的雲杉像撐天的巨傘，重重
疊疊的枝丫，只漏下斑斑點點細碎的日影。林子十分幽靜，連鳥雀也少
飛來，只偶爾能聽到遠處的幾聲鳥鳴。
long);
        set("exits",([
                "north" : __DIR__"conglinggu",
                "east"  : __DIR__"shanlin6",
                "south" : __DIR__"shanlin"+(random(5)+1),
                "west"  : __DIR__"shanlin"+ (random(5)+1),
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -119990);
        set("coor/y", 40140);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}