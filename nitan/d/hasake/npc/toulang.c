inherit NPC;
inherit F_UNIQUE;
void create()
{
        set_name("頭狼", ({ "toulang", "lang" }) );
        set("race", "野獸");
        set("age", 10);
        set("unique", 2);
        set("long", "狼以群居，這只帶頭的大灰狼比其它的大一倍以上，低沉地吼著。\n");
        set("attitude", "aggressive");        
        set("limbs", ({ "頭部", "牙齒", "前腳", "後腳", "前爪" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("max_qi", 450);
        set("max_jing", 200);
        set("eff_jingli", 200);
        set("combat_exp", 9500);
        set("chat_chance", 20);
        set("chat_msg", ({
                "頭狼的雙目在黑暗中閃著紅光，緊緊地注視著你的一舉一動。\n",
                (: random_move :),
                "頭狼發出一聲嗥叫，好象隨時都要撲上來！\n",
        }) );
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 30);
        set_temp("apply/armor", 14);        
        set("senlin", 1);
        setup();
}

void die()
{
        object ob;
    message_vision("$N凄慘的嚎了幾聲, 在地上打了幾個滾，仰天死了。\n", this_object());
        ob = new(__DIR__"obj/langpi");
        ob->move(environment(this_object()));
        destruct(this_object());
}
        
