// gui1-2.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIC"你忽然看見一個妙齡少女在草叢中呻吟不止，你快步走近，上前察看，" +
                   "不料少女驀的在你眼前消失。\n" +
                HIB"周圍景物剎那間忽地變的詭異莫測。\n"NOR; 

string *stya = ({ 
HIB"周圍不見活物，卻聽得女子的嬉笑聲從四面八方傳來，$N的神志有些迷糊。\n"NOR, 
HIB"一陣紅煙噴到面前，$N不由吸了一口，只覺五臟六腑猶如怒海孤舟般翻滾不止，說不出來的難受。\n"NOR, 
HIB"$N突覺脖頸上似有舌頭在輕輕舐舔，奇癢難忍，心中大駭。\n"NOR, 
HIB"$N感到一雙膩滑的雙手在身上撫摸，大驚失色，連忙後退數步。\n"NOR
}); 

string *styb = ({
HIC"$N對$n大喝道：“害人精，今日撞到本道爺手裡，讓你永不得超生！”\n"NOR,
HIC"$N將手中"HIY"符紙"HIC"拍出，一道強光射向$n。\n"NOR,
HIY"$N抖動手中的"HIM"桃木劍"HIY"，發出耀眼的光芒，道道金光向$n刺去。\n"NOR
});

void check_time();

void create()
{
    set_name("狐貍精", ({ "fox ghost", "ghost" }));
    set("gender", "女性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 30);
    set("long",
        "一個由千年狐貍修煉而成的精靈。常常變成美貌少女害人。\n");
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
