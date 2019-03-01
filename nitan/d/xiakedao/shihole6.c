// /d/xiakedao/shihole6.c 俠客島 石洞6

inherit ROOM;
#include <ansi.h>

int do_learn(string arg);
void create()
{
        set("short", "石洞");
        set("long", @LONG
眼前燭光黯淡，四周未見任何裝飾，光禿粗糙的石壁上四字小篆，
正是最後一句總綱：「天人歸真」，下面又有一行小字(xiaozi)。幾
張石桌石凳隨意地擺放著，似是雜亂無章，又似內藏玄機。
LONG );
        set("exits", ([
                "out"   : __DIR__"shihole5",
                "north" : __DIR__"shiroom21",
                "south" : __DIR__"shiroom22",
                "east"  : __DIR__"shiroom23",
                "west"  : __DIR__"shiroom24",
        ]));
/*
        set("objects", ([
                CLASS_D("xiakedao")+"/long" : 1,
                CLASS_D("xiakedao")+"/mu"   : 1,
        ]));
*/
        set("item_desc", ([
                "xiaozi": 
"小字寫的是：「昔年余等沉溺無術，惟石公妙悟神功，蓋因...」，
後面的字跡已模糊難辨。\n"
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3090);
        set("coor/y", -25600);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);
}
/*
int valid_leave(object me, string dir)
{
   if (dir != "west" )  return ::valid_leave(me, dir);
   if( query_temp("winner", me))return ::valid_leave(me,dir);
   return notify_fail(HIW"一股強大的力量自石洞中湧出，將你擋在洞外。\n"NOR);
}
*/