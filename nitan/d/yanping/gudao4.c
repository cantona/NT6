// Room: /d/yanping/gudao4.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "閩贛古道");
        set("long", @LONG
福建境內數不盡的山坎相連。密林幽谷相繼，終日不見天光。山中
毒蟲猛獸出沒無常，行路艱辛。
LONG );
        set("exits", ([
                "southwest" : __DIR__"gudao3",
                "northeast" : __DIR__"ximen",
        ]));
        set("objects", ([
                __DIR__"npc/wubushe" : 1,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1400);
        set("coor/y", -6200);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}