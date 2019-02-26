//jiaowei qin 焦尾琴

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIM"焦尾琴"NOR,({"jiaowei qin","qin"}));
        set("taskobj", 1);
        set_weight(500);
        if(clonep())
                 set_default_object(__FILE__);
        else{
                set("unit","張");
                set("value",0);
                set("material","steel");
                set("long","相傳這便是當年蔡文姬從火中所救出的焦木做成的美琴，琴的尾端仍可見焦黑色。\n");
                set("wield_msg",HIY"$N伸手輕輕一揮,一張焦尾琴便已出現在$N手中.\n"NOR);
                set("unwield_msg",HIY"$N十指一拂，琴聲曳然而止。$N收起焦尾琴，放進揹着的包袱裏。\n"NOR);
                set("unequip_msg",HIY"你十指一拂，琴聲曳然而止。你收起焦尾琴，放進揹着的包袱裏。.\n"NOR);
        }
        setup();
}

int wield()
{
        object ob = environment();

/*        if (ob && !wizardp(ob)) {
                tell_object(ob, name() + "是巫師用品，你不能使用，請馬上向巫師報告，否則後果自負。\n");
                call_out("let_him_die", 300, ob);
                return 0;
        }*/
        return ::wield();
}
/*
void let_him_die(object ob)
{
        if (ob = environment()) {
                addn("combat_exp", -30000, ob);
                set_temp("last_damage_from", "盜用巫師用品中毒", ob);
                ob->die();
        }
}
*/