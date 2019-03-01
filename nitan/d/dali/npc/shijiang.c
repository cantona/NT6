// shijiang.c

inherit NPC;

void create()
{
        set_name("石匠",({ "shi jiang", "jiang" }) );
        set("gender", "男性" );
        set("age", 52);
        set("long", "他是一個打磨大理石的石匠，身上只穿了一件坎肩，全身布滿了厚實的肌肉。\n");
        set_temp("apply/defense", 15);
        set("combat_exp", 1700);
        set("shen_type", 1);
        set("per", 18);
        set("str", 24);
        set("dex", 25);
        set("con", 36);
        set("int", 15);
        set("attitude", "friendly");
        set("chat_chance",2);
        set("chat_msg", ({
"石匠有一下沒一下的鑿著手中的一塊碑文，嘴裡嘟囔著，“蒼山之腹盛產奇石，
世稱大理石，大理也因石而名揚天下。”\n"
        }));

        setup();
        carry_object("/clone/weapon/hammer")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
