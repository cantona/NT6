// Room: /d/yanping/gudao2.c
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
                "westdown" : __DIR__"gudao1",
                "eastdown" : __DIR__"gudao3",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yanping");
        set("coor/x", 1200);
        set("coor/y", -6300);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}