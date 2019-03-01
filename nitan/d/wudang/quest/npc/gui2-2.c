// gui2-2.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"一陣悶響由遠及近，你急向響聲發出之處看去，" +
                "但見一具棺木似乎被劇烈的撞動著，突然棺蓋被一股怪力擊飛。\n" +
                HIR"一股血腥之氣筆直的向你撲來。\n"NOR; 

string *stya = ({ 
HIB"忽聽一陣破空之聲，$N不由感到一絲寒意襲來。\n"NOR, 
HIB"$N忽覺雙肩噗嗤一聲，被十指插入筋骨，幾乎痛暈過去。\n"NOR, 
HIB"$N突然覺得身上被咬了一下，劇痛難當。\n"NOR, 
HIB"$N突然覺得身上被緊緊抓住，大驚失色，連忙後退數步。\n"NOR
}); 

string *styb = ({ 
HIC"$N對$n喝道：“本道爺今日要將你打入十八層地獄，永不得超生。”\n"NOR,
HIY"$N急揮手中的"HIM"桃木劍"HIY"，劃出無數光環，將$n套在當中。\n"NOR
});

void check_time();

void create()
{
    set_name("僵屍", ({ "corpse ghost", "ghost" }));
    set("gender", "男性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 12);
    set("long",
        "一個人死後變成的僵屍，異常兇猛，常吸食各種生靈的血，使之枯竭而亡。\n");
    set("combat_exp", 50000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "牙齒", "手爪" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 260);
    set("apply/defense", 260);
    set_skill("parry", 250);
    set_skill("dodge", 300);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "ghoster.h"
