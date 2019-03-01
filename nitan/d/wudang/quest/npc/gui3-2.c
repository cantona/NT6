// gui3-2.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIW"忽然間一道白影閃過，你正驚疑，小腿一緊，已被裹屍布纏住。\n"NOR; 

string *stya = ({ 
HIB"$N眼前一花，脖子已被裹屍布緊緊勒住，頓感氣息不暢，雙眼發黑。\n"NOR, 
HIB"$N腿上的裹屍布被一股怪力一拉，立足不穩，向前撲倒在地。\n"NOR, 
HIB"只聽噗嗤一聲，$N覺得身上已被十指戳入，不禁面色慘白。\n"NOR, 
HIB"$N腳下被裹屍布一絆，仰天摔倒。\n"NOR
}); 

string *styb = ({ 
HIC"$N對$n喝道：“何處妖魔，來此作孽？本道爺今日要將你變成死鬼！”\n"NOR,
HIW"$N揮動手中的"HIM"桃木劍"HIW"，道道劍光將裹屍布震成碎片，漫天飛舞。\n"NOR
});

void check_time();

void create()
{
    set_name("木乃伊", ({ "mummy ghost", "ghost" }));
    set("gender", "男性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 15);
    set("long",
        "一種人死後屍體不腐而變成的鬼魂。身上纏滿了裹屍布，十分可怖。\n");
    set("combat_exp", 100000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "牙齒", "手爪" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 350);
    set("apply/defense", 350);
    set_skill("parry", 350);
    set_skill("dodge", 400);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "ghoster.h"
