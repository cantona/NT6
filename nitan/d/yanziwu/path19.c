// Room: /d/yanziwu/path19.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "山澗小路");
        set("long", @LONG
小路穿過蔓陀峰下的山澗，兩側時而有流水滑落，把地上的路石染
成淡淡的綠色。山崖上是鬱鬱蔥蔥的鬆柏林，抬頭仰望，時有飛鳥越頂
而過。北望下山路，下面是一塊不大的草坪。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "northdown" : __DIR__"qingfeng",
                "southdown" : __DIR__"path20",
                "westup"    : __DIR__"qiuyu",
        ]));
        set("coor/x", 1200);
        set("coor/y", -1260);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}