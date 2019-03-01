//lang.c 狼
// Last Modified by winder on Aug. 1 2002

// inherit NPC_TRAINEE;
inherit "/inherit/char/trainee";

void create()
{
        set_name("母狼", ({ "mu lang","lang", "wolf" }) );
        set("race", "走獸");
        set("gender", "雌性");
        set("age", 15);
        set("long", "這是一頭灰色的母狼，正用紅色的眼睛盯著你，不時發出令人膽戰的嗥聲！\n");
        set("msg_fail","$n轉動脖頸對著$N就咬，$N忙縮回手");
        set("msg_succ","$N一揮手，$n的頭便跟著動了起來");
        set("msg_trained","$n伸出紅色的舌頭舔了舔$N的腳");
        set("auto_follow",1);
        set("wildness",9);
        set("attitude", "aggressive");
        
        set("str", 29);        
        set("con", 40);
        set("dex", 45);        
        set("int", 10);

        set("combat_exp", 14000);

        set_temp("apply/attack", 20);
        set_temp("apply/damage", 20);
        set_temp("apply/armor",  20);

        set("chat_chance", 10);
        set("chat_msg", ({
                "母狼發出一聲嗥叫，好象隨時都要撲上來！\n",
                "母狼的雙目在黑暗中閃著紅光，緊緊地注視著你的一舉一動。\n",
                "「嗥~~~~」母狼發出一聲嗥叫。\n",
        }) );
        
        setup();
}

