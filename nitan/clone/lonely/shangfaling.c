#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "賞善" HIR "罰惡" NOR "令" NOR,({ "shangfa ling", "ling" }) );
        set_weight(1000);
        set("long", @LONG
這是一面用黃銅所鑄的銅牌，正面刻着“賞善”，背面刻着“罰惡”。
LONG );
                set("unit", "面");
                set("value", 0);
                set("no_sell", 1);
                set("no_drop", 1);
                set("no_give", 1);
                set("no_get", 1);
                set("material", "steel");
                set("stable", 100);
        
        setup();
}