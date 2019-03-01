// gui1-1.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"你剛走過來，就覺一股陰冷的寒氣迎面襲來，不禁打了個哆嗦。\n"NOR;

string *stya = ({
HIB"一陣陰風襲來，$N忽然覺得全身血液似乎都被這股陰風凍住。\n"NOR,
HIB"$N感到一股寒氣順經脈流遍周身，不禁痛苦的悶哼了一聲。\n"NOR,
HIR"$N感到身上一陣劇痛。\n"NOR,
HIB"$N突覺身上被野鬼緊緊抓住，大驚失色，連忙後退數步。\n"NOR
});

string *styb = ({
HIC"$N對$n大喝道：“妖魔，你屢番害人性命，本道爺今日讓你永不得超生！”\n"NOR,
HIY"$N抖動手中的"HIM"桃木劍"HIY"，發出耀眼的光芒，道道金光向$n刺去。\n"NOR,
HIC"$N手中"HIM"桃木劍"HIC"劃出無數個金環，一圈一圈套向$n。\n"NOR
});

void check_time();

void create()
{
    set_name("野鬼", ({ "wild ghost", "ghost" }));
    set("gender", "男性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 10);
    set("long",
        "一個兇神惡剎、面目猙獰的鬼魂。它臉色慘白，牙齒又長又尖，十指仍在滴著
鮮血，正死死地盯著你。\n");
    set("combat_exp", 50000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "牙齒", "手爪" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 120);
    set("apply/defense", 120);
    set_skill("parry", 150);
    set_skill("dodge", 200);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "ghoster.h"
