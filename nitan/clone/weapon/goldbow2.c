// goldbow.c

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
        set_name(HIR "赤鴛弩" NOR, ({ "chiyuan nu", "chiyuan", "nu", "bow" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "張");
                set("long", HIR "這是一張鉛鐵所鑄，舞鳳雕紋，制作非常精細的弩。\n" NOR);
                set("no_sell", "我的天…郡王府的東西你也敢拿來賣？");
                set("value", 80000);
                set("power", 200000);   // 攻擊威力
                set("accuracy", 200);   // 準確度200%
        }
        setup();
}