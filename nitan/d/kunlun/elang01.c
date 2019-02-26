// Room: /d/kunlun/elang01.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "東長廊");
        set("long",@long
這是一條長廊，連接前廳和客房，不斷看見各種打扮的江湖人士走
過，看過廊外，是一片青色的樹林，幽靜雅緻，只聽見不斷傳來的鳥鳴
聲。
long);
        set("exits",([
                "west" : __DIR__"qianting",
                "east" : __DIR__"elang02",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -119980);
        set("coor/y", 40060);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}