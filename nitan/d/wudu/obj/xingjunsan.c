#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + YEL "諸葛行軍散" NOR, ({ "xingjun san", "xingjun", "san" }));
        set("unit", "包");
        set("long", NOR + YEL "這是一包預防瘴氣的藥散，帶在身上可以預防瘴氣。\n" NOR);
        set("no_sell", "這是啥破玩意兒？也想賣錢？");
        set("value", 1);
        set_weight(200);        
        setup();
}