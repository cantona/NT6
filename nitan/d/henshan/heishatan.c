#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "黑沙潭");
        set("long", @LONG
黑沙潭又稱黑龍潭，深不見底，水色蒼黑，瀑布流急，水中黑泡
共白沫徜徉，幽幽可怖。石壁上「海南龍湫」四字據載為大宋徽宗趙
佶所留。瘦金字體，一如往昔。
LONG );
        set("exits", ([ 
               "up"  : __DIR__"shanjian",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);
	set("coor/x", -6990);
	set("coor/y", -5560);
	set("coor/z", -10);
	setup();
}

int valid_leave(object me, string dir)
{
    if ((random((int)me->query_skill("dodge")) <= 30) && dir=="up")    
    {
        return notify_fail("你使勁兒一蹦，離瀑布頂還有數丈遠就掉了下來，摔的鼻青臉腫。\n");
    }
    if ((random((int)me->query_skill("dodge")) <= 35) && dir=="up")    
    {
        return notify_fail("你奮力一躍，卻離瀑布頂還有一丈多遠，看來是白費力氣。\n");
    }
    if ((random((int)me->query_skill("dodge")) <= 40) && dir=="up")    
    {
        return notify_fail("你縱身而起，離瀑布頂只差一點點了，再加把勁。\n");
    }

    return ::valid_leave(me, dir);
}