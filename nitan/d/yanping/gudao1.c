// Room: /d/yanping/gudao1.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "閩贛古道");
        set("long", @LONG
進入江西，還是不盡的山坎和密林幽谷，終日不見天光。放眼山中
毒蟲猛獸出沒無常，行路艱辛。一到這裏就聞到一股腥風撲鼻而來。
LONG );
        set("exits", ([
                "northwest" : "/d/henshan/hsroad2",
                "eastup"    : __DIR__"gudao2",
        ]));
        set("objects", ([
                __DIR__"npc/huananhu" : 1,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1100);
        set("coor/y", -6200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}