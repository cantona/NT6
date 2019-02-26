// gui3-1.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"你突然聽到一聲厲嘯，彷彿感到一個長髮怪物一閃而過。\n"NOR; 

string *stya = ({ 
HIB"$N感到長髮從臉上掃過，頓時一陣火辣辣的疼痛。\n"NOR, 
HIB"$N忽覺嘴脣被緊緊吸住，一股"HIR"鮮血"HIB"從口內急瀉而出。\n"NOR, 
HIR"$n張開正滴着血的大口，在$N身上一陣亂咬。\n"NOR, 
HIB"$N突然覺得身上被緊緊抓住，大驚失色，連忙後退數步。\n"NOR
}); 

string *styb = ({ 
HIC"$N舉起手中的"HIY"符紙"HIC"，看清$n來勢，疾拍而出。\n"NOR,
HIY"$N揮動"HIM"桃木劍"HIY"，幻化出無數金光劍影，手腕一抖，向$n刺出。\n"NOR
});

void check_time();

void create()
{
    set_name("吸血鬼", ({ "leech ghost", "ghost" }));
    set("gender", "女性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 25);
    set("long",
        "一種專門吸食人血的鬼魂。常常變成美麗的女子迷惑多情的男人，吸乾他的血。\n");
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
