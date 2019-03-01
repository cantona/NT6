inherit NPC;
void create()
{
    set_name("大灰狼", ({ "huilang", "lang" }) );
    set("race", "野獸");
    set("age", 10);
    set("long", "一頭高大的惡狼, 來勢如電, 露出白森森的獠牙。\n");
    set("attitude", "aggressive");
        set("limbs", ({ "頭部", "身體", "前腳", "後腳", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("max_qi", 300);
        set("max_jing", 200);
        set("eff_jingli", 200);
        set("combat_exp", 3000);
        set("chat_chance", 5);
        set("chat_msg", ({
                "「嗥~~~~」大灰狼發出一聲嗥叫。\n",
                "大灰狼發出一聲嗥叫，好象隨時都要撲上來！\n",
        }) );
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 8);
        set_temp("apply/damage", 10);
        set_temp("apply/armor", 4);
        set("senlin", 1);
        setup();
}
/*
void die()
{
        object ob;
        seteuid(getuid());
        message_vision("$N長嘯一聲，倒在地上，死了！\n", this_object());
        ob = new(__DIR__"obj/langpi");
        ob->move(environment(this_object()));
        destruct(this_object());

}
*/
