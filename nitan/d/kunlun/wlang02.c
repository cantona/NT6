// Room: /d/kunlun/wlang02.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西外廊");
        set("long",@long
這是一條長廊，連接前廳和客房，不斷看見各種打扮的江湖人士走
過，看過廊外，是一片青色的樹林，幽靜雅致，只聽見不斷傳來的鳥鳴
聲。
long );
        set("exits",([
                "east" : __DIR__"wlang01",
                "west" : __DIR__"keting2",
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -120010);
        set("coor/y", 40060);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}