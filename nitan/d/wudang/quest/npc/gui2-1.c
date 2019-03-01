// gui2-1.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIW"突然你感到一股十分強烈的怨氣直沖雲霄。\n"NOR;

string *stya = ({ 
HIB"一陣刺耳的長嘯傳來，$N感到心神不寧，異常難受。\n"NOR, 
HIB"$N聽到一聲凄慘的長嘆，頓感胸悶異常，忍不住噴出一口"HIR"鮮血"HIB"。\n"NOR
}); 

string *styb = ({
HIC"$N對$n喝道：“本道爺今日超渡于你，早日投胎轉世，勿再害人！”\n"NOR,
HIY"$N揮動手中的"HIM"桃木劍"HIY"，霎時天地間清風徐徐，怨氣漸消。\n"NOR
});

void check_time();

void create()
{
    set_name("冤魂", ({ "wrong ghost", "ghost" }));
    set("gender", "女性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 20);
    set("long",
        "一個含冤而死的人死後即變成冤魂，很難制服，常常攻擊無辜的生靈。\n");
    set("combat_exp", 100000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "牙齒", "手爪" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 250);
    set("apply/defense", 250);
    set_skill("parry", 250);
    set_skill("dodge", 300);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "ghoster.h"
