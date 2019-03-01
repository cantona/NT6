// Room: /d/kunlun/shanlin1.c
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
                "west"  : __DIR__"shanlin2",
                "east"  : __DIR__"shanlin4",
                "north" : __DIR__"shanlin3",
                "south" : __DIR__"huayuan",
        ]));
        set("objects",([
                __DIR__"obj/da-shugan" :  1,
                __DIR__"obj/xiao-shuzhi" :  1,
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119990);
        set("coor/y", 40140);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}