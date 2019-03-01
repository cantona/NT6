// feilaifeng.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "飛來峰");
        set("long", @LONG
飛來峰又名靈鷲峰。沿著盤山小道往上走，只見溪盤巖石壁間雕
著一尊袒腹露胸，喜笑自若的彌勒佛。旁邊是一座氣魄雄偉的多聞天
王。北邊是下山的路。小路往上延伸向東西兩邊。
LONG);
        set("exits", ([
                "north"     : __DIR__"road1",
                "eastup"    : __DIR__"qinglindong",
                "westup"    : __DIR__"longhongdong",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
	set("coor/x", 740);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}