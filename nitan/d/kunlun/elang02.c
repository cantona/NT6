// Room: /d/kunlun/elang02.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "東外廊");
        set("long",@long
這是一條長廊，連接前廳和客房，不斷看見各種打扮的江湖人士走
過，看過廊外，是一片青色的樹林，幽靜雅致，只聽見不斷傳來的鳥鳴
聲。
long);
        set("exits",([
                "west" : __DIR__"elang01",
                "east" : __DIR__"keting1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -119970);
        set("coor/y", 40060);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}