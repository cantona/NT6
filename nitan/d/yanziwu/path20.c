// Room: /d/yanziwu/path20.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "山澗小路");
        set("long", @LONG
小路穿過蔓陀峯下的山澗，兩側時而有流水滑落，把地上的路石染
成淡淡的綠色。北面山崖上是鬱鬱葱葱的松柏林，抬頭仰望，時有飛鳥
越頂而過。南邊是一片巨巖，光禿的，在萬頃湖光和周遭碧青山色環繞
下，好似一丸巨大的珍珠。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "northup" : __DIR__"path19",
                "enter"   : __DIR__"dong1",
        ]));
        set("coor/x", 1200);
        set("coor/y", -1270);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}