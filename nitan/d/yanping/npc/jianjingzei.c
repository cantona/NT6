// /d/yanping/npc/qiangren.c

inherit NPC;

void create()
{
        set_name("剪徑賊", ({ "jianjing zei","zei" }) );
        set("gender", "男性");
        set("age", 30);
        set("long", "這家伙滿臉橫肉□一付兇神惡煞的模樣，令人望而生畏。\n");
        set("combat_exp", 10000);
        set("shen_type", -1);
        set("attitude", "aggressive");

        set("apply/attack", 20);
        set("apply/defense", 20);

        set("chat_chance", 30);
        set("chat_msg", ({
                "剪徑賊一聲大喊: 此山是我開，此樹是我栽，若要從此過，留下褲子來！\n",
        }) );

        set_skill("unarmed", 40);
        set_skill("sword", 20);
        set_skill("parry", 40);
        set_skill("dodge", 40);
        setup();

        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(CLOTH_DIR"cloth")->wear();
        add_money("silver", 1);
}