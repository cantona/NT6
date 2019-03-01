// shiji4.c
// Modified by Winder June.25 2000

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "石級");
        set("long", @LONG
這是一段斜引向上的石級，大概有一百來級吧。缺乏光亮，又轉了
三個彎，隱隱聽到轟隆轟隆的水聲。
LONG );
        set("exits", ([
                "southdown" : __DIR__"fangjian3",
                "eastup"    : __DIR__"shiji5",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50010);
        set("coor/y", -21010);
        set("coor/z", -30);
        setup();
        replace_program(ROOM);
}