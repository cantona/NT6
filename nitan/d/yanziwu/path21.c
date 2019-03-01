// Room: /d/yanziwu/path21.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "山澗小路");
        set("long", @LONG
小路穿過蔓陀峰下的山澗，兩側時而有流水滑落，把地上的路石染
成淡淡的綠色。山崖上是鬱鬱蔥蔥的鬆柏林，抬頭仰望，時有飛鳥越頂
而過。北邊是一片巨巖，光禿的，在萬頃湖光和周遭碧青山色環繞下，
好似一丸巨大的珍珠。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "east"   : __DIR__"path22",
                "enter"  : __DIR__"dong7",
        ]));
        set("coor/x", 1200);
        set("coor/y", -1270);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}