// Room: /d/yanziwu/path1.c
// Date: Jan.28 2000 by Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "綠泥小徑");
        set("long", @LONG
你走在蔓陀山莊中的綠泥小徑上。小徑兩側擺滿拉一盆盆茶花，結
了許許多多的五色茶花，時有蜂飛蝶舞戲弄花間。你不敢多留，急步前
行。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"path2",
                "west"   : __DIR__"dukou",
        ]));
        set("coor/x", 1210);
        set("coor/y", -1300);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}