// bicanfeng.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "三蜈五蟆煙" NOR, ({"sanwuwuma yan", "fen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一袋劇毒的毒藥，如果用來煉暗器有見血封喉之效。\n");
                set("unit", "袋");
                set("value", 20000);
                set("poison_type", "yaowang_poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 180,
                        "id"    : "yaowang",
                        "name"  : "劇毒",
                        "duration": 15,
                ]));
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N仰頭把一小袋" + name() + "都嚥了下去。\n", me);
        set_temp("die_reason", "吸了三蜈五蟆煙，莫名其妙的見了閻王", me);
        me->die();
        destruct(this_object());
        return 1;
}
void init() 
{ 
        add_action("do_dian", "dian"); 
} 
// 後面的待寫!如果點燃後，在場的所有id根據本身內力的深厚來決定是否中毒。
// 並且此煙點燃的時間有限，在一個點燃的有效時間可以判斷有幾次中毒的機會。
// 此毒的載體可以放到火折、火把或者香煙一類。也可以考慮別的。

