// Room: /d/tiezhang/dong1.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "山洞");
        set("long", @LONG
一個黑漆漆的山洞，黑沉沉的一眼望不到底。兩側的石壁上生滿的
苔蘚，摸起來又濕又滑。這石洞似乎是人工開鑿的，從四周的石壁上仍
能看出斧鑿的痕跡。你站在這裏，一股恐懼由然而生，似乎身體隨時都
會被這片黑暗吞噬掉。
LONG
        );
        set("exits", ([
                "out"   : __DIR__"dezj",
                "enter" : __DIR__"dong2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2040);
        set("coor/y", -1800);
        set("coor/z", 70);
        setup();
        replace_program(ROOM);
}
