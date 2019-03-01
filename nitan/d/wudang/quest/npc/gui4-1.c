// gui4-1.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"突然一陣腥臭的濃霧籠罩了四周，眼前頓時漆黑一團。\n"NOR; 

string *stya = ({ 
HIB"忽然一道"HIW"白光"HIB"向$N疾射而來，手臂一麻，已被$n咬中。\n"NOR, 
HIB"$N身體被$n纏住，越裹越緊，幾乎透不過氣來。\n"NOR, 
HIB"$N背部一陣劇痛，被$n蛇尾擊中。\n"NOR
}); 

string *styb = ({ 
HIC"$N一聲暴喝，急揮手中"HIY"符紙"HIC"，向$n拍出。\n"NOR,
HIY"$N揮動手中的"HIM"桃木劍"HIY"，直刺$n七寸。\n"NOR
});

void check_time();

void create()
{
    set_name("百年蛇妖", ({ "snake ghost", "ghost" }));
    set("gender", "女性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 20);
    set("long",
        "一種毒蛇經過百年修煉而成的妖魔。\n");
    set("combat_exp", 500000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "牙齒", "手爪" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 450);
    set("apply/defense", 450);
    set_skill("parry", 450);
    set_skill("dodge", 500);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "ghoster.h"
