// Room: /d/xingxiu/xinglongshan.c
// Last Modified by winder on Apr. 25 2001
inherit ROOM;

void create()
{
        set("short", "興隆山");
        set("long", @LONG
此山東西兩面山坡上，天然林密佈，有云杉、鬆、樺、柳、楊等喬
木及灌木叢。峯巒疊翠，四季長青。上有太白、玉液泉，匯成小溪山澗，
清流潺潺。中有大峽河，清澈見底，南北穿越峽谷。地陰潮濕，氣温較
低，為遊覽避暑勝地。
LONG);
        set("outdoors", "silu");
        set("exits", ([
                "northdown" : __DIR__"shimen",
        ]));
        set("objects", ([
                __DIR__"npc/yang" : 2,
        ]));
        set("coor/x", -22000);
        set("coor/y", 500);
        set("coor/z", 100);
        setup();
}
#include "/d/xingxiu/job2.h";