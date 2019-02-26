#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "峭壁");
        set("long", @LONG
自古有云：蜀道難，難於上青天，嗚呼。無怪大詩人李白如此寫。
路到了這裏真可謂驚險無比，一邊是滔滔的江水，一邊是如刀切般的
峭壁。你正爬在一個很危險的峭壁上，你還是快走吧，別一不小心掉
了下去。
LONG );
        set("exits", ([
                  "eastdown" : __DIR__"shudao7",
                  "westup" : __DIR__"shudao9",
           ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15060);
	set("coor/y", -1830);
	set("coor/z", -50);
	setup();
        replace_program(ROOM);
}