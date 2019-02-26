// goldbow.c

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
        set_name(HIY "點金盤龍弓" NOR, ({ "panlong gong", "gong", "panlong", "bow" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "張");
                set("long", HIY "這是一張金銅所鑄，盤龍雕紋，製作非常精細的長弓。\n" NOR);
                set("no_sell", "我的天…郡王府的東西你也敢拿來賣？");
                set("value", 80000);
                set("power", 250000);   // 攻擊威力
                set("accuracy", 120);   // 準確度120%
        }
        setup();
}