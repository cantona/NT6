// jingang-zhao.c

#include <armor.h>
#include <ansi.h>

inherit CLOTH;
inherit F_NOCLONE;

void create()
{
        set_name("金剛罩", ({ "jingang zhao", "zhao" }));
        set_weight(2000);
        set("unit", "件");
        set("long", @LONG
這是一件金光閃閃的袈裟，通體用天山雪蠶絲織成，堅韌無比刀劍
不能傷。此袈裟數百年前由達摩老祖攜入中原，邪魔見之辟易，乃
是佛家無上降魔法寶。
LONG );
        set("material", "cloth");
        set("value",1000000);
        set("no_sell", 1);
        set("wear_msg", HIY "只聽「譁」的一聲，$N展開一件金光閃閃的袈裟披在身上。
瞬時間日月為之失色，瑞氣千條，祥雲朵朵，一派莊嚴氣象。\n" NOR);
        set("remove_msg", HIY "$N將金剛罩從身上脱了下來，摺疊成小小的一團。\n" NOR);
        set("armor_prop/armor", 220);
        set("stable", 0);
        setup();
        check_clone();
}