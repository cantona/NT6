#include <ansi.h>
inherit ITEM;

void create()
{
       set_name(HIW "千日醉" NOR, ({"qianri zui", "qianri", "zui"}));
       set("unit", "顆");
       set("long", HIW "這是一顆核桃大小的果實，散發着一股濃郁的酒香。\n" NOR);
       set("value", 200);
       set_weight(50);
       setup();
}