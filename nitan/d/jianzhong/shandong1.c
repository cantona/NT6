#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","山洞");
        set("long",@LONG
這洞裡黑黝黝的，不知道裡面住著什麼武林異士，還是有什
麼山魈木怪。是不是再往裡走呢？你心裡拿不定主意。
LONG
        );
        set("exits",([
                "north":__DIR__"maigu",
                "out":__DIR__"dongkou",
        ]));
        set("coor/x", -400);
        set("coor/y", -440);
        set("coor/z", 0);
        setup();
}
        