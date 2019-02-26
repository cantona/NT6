// Room: /d/taishan/kaishan.c
// Last Modified by winder on Aug. 25 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "開山");
        set("long", @LONG
對松山北，高阜之上，雙崖夾道，舊稱雲門，今名開山，為清乾隆末
年改建盤道時所闢。這裏便是泰山十八盤的起點。此處向上，直到龍門，
被稱之為“慢十八盤”。
LONG );
        set("exits", ([
                "northup"   : __DIR__"man18",
                "southdown" : __DIR__"duisong",
        ]));

        set("objects", ([
                CLASS_D("taishan")+"/first" : 1,
        ]));

        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 30);
	set("coor/y", 240);
	set("coor/z", 140);
	setup();
        replace_program(ROOM);
}
