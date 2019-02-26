// gui4-2.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"天空中突然陰風大作，一朵黑雲遮住了太陽。頃刻間飛沙走石，天昏地暗。\n"NOR; 

string *stya = ({ 
HIB"一股黑霧從樹林深處瀰漫開來，一個半男半女的沙啞嗓音在其中陰磣磣的冷笑着。\n"NOR, 
HIB"一陣鬼哭狼嚎般的叫聲從四面八方湧過來，$N只覺得頭疼欲裂，眼冒金星！\n"NOR, 
HIB"地上突然裂開一條長長的口子，從裏邊飛出幾根粗大的藤條，牢牢的抓住你的四肢。拼命往裂縫裏拖。\n"NOR, 
HIB"$n渾身爆發出一股強烈的妖氣，從身上射出一股黑流，直擊$N的全身！\n"NOR
}); 

string *styb = ({ 
HIC"$N破開掌心，用氣血將手中神符定在"HIM"桃木劍"HIC"上，大吼一聲，疾刺而出！\n"NOR,
HIC"$N一聲長嘯，正氣直衝霄漢。$n凜冽的慘嗥頓時瀰漫在天地之間。\n"NOR,
HIY"$N揮動手中桃木劍，化做一條八丈神龍，口吐金光，將$n牢牢罩住。\n"NOR
});

void check_time();

void create()
{
    set_name("千年樹精", ({ "tree ghost", "ghost" }));
    set("gender", "男性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 22);
    set("long",
        "一種千年老樹修煉而成的妖魔，十分強悍。\n");
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
