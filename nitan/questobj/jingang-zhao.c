// jingang-zhao.c

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY"金剛"HIB"罩"NOR, ({ "jingang zhao", "zhao" }));
        set_weight(500);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","這是一件金光閃閃的袈裟，通體用天山雪蠶絲織成，堅韌\n無比刀劍不能傷。此袈裟數百年前由達摩老祖攜入中原，邪魔見之辟易，\n乃是佛家無上降魔法寶。\n");
                set("material", "cloth");
                set("unit", "件");
                set("wear_msg", HIY "只聽「嘩」的一聲，$N展開一件金光閃閃的袈裟披在身上。\n瞬時間日月為之失色，瑞氣千條，祥雲朵朵，一派莊嚴氣象。\n" NOR);
                set("remove_msg", HIY "$N將金剛罩從身上脫了下來，折疊成小小的一團。\n" NOR);
                set("armor_prop/armor",100);
        }
        setup();
}