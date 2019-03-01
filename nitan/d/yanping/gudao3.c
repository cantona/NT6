// Room: /d/yanping/gudao3.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "閩贛古道");
        set("long", @LONG
福建境內數不盡的山坎相連。密林幽谷相繼，終日不見天光。山中
毒蟲猛獸出沒無常，行路艱辛。路邊有一年輕漢子倚在樹上，眯著眼打
量著你。
LONG );
        set("exits", ([
                "westup"    : __DIR__"gudao2",
                "northeast" : __DIR__"gudao4",
        ]));
        set("objects", ([
                "/d/qingcheng/npc/jia" : 1,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1300);
        set("coor/y", -6300);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}