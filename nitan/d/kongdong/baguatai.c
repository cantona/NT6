
inherit ROOM;
#include <room.h>
#include <ansi.h>



void create()
{
	set("short", YEL"八卦台"NOR);
	set("long",@LONG
這裏是倥侗派木靈子親自打造的銅製的八卦台，銅台上刻有一個巨大的
八卦圖案。按照子、醜、寅、卯、辰、巳、午、未、申、酉、戌、亥的方位
排布。倥侗弟子可以來這裏掐算占卜，非常靈驗。
LONG);
    set("need_clean", "崆峒派");
	set("exits",
	([
             "down" : __DIR__"18_yuan",
          	]));
    setup();

}
