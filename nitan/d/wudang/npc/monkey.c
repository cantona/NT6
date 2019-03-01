// monkey.c

inherit NPC;

void create()
{
    set_name("猴子", ({ "monkey" }) );
    set("gender", "雄性");
    set("race", "野獸");
    set("age", 5);
    set("long",
        "這只猴子在在桃樹間跳上跳下，還不時津津有味地啃幾口著蜜桃。\n");
    set("combat_exp", 5000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "猴嘴", "前爪", "後爪", "尾巴" }) );
    set("verbs", ({ "bite", "claw" }) );

    set("apply/attack", 10);
    set("apply/defense", 10);

    set("chat_chance", 10);
    set("chat_msg", ({
        "猴子沖著你大扮鬼臉，嘰嘰歪歪一陣亂叫......!\n",
        "猴子忽然跳了過來，一個倒勾，前爪一伸摘了你的草帽!\n",
        "猴子轟的一聲一起從這株樹跳到那株樹，把你嚇了一大跳!\n",
    }) );

    set_skill("unarmed", 25);
    set_skill("parry", 20);
    set_skill("dodge", 20);

    setup();
}