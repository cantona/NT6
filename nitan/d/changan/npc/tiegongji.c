//tiegongji.c

inherit BUNCHER; 
inherit F_BANKER;

void create()
{
        set_name("鐵公雞", ({"tie gongji", "tie", "gongji"}));
        set("title", "錢莊老板");
        set("gender", "男性");
        set("age", 46);
        set("kee", 800); 
        set("max_kee", 800);
        set("sen", 200);
        set("max_sen", 200);
        set("combat_exp", 50000);
        set("attitude", "friendly");
        set("env/wimpy", 50);
        set("chat_chance", 10);
        set("chat_msg", ({
                "鐵公雞嘿嘿嘿地笑了幾聲：我這把算盤幾十年來可從來沒算錯過。\n",
                "鐵公雞驕傲的說道：本銀號已經有上百年的歷史，在長安城可以說是第一家。\n"
        }));
        set_skill("unarmed", 60);
        set_skill("parry", 60);
        set_skill("dodge", 60);

        setup();
        carry_object("/d/changan/npc/obj/choupao")->wear();
        add_money("silver", 50);
}

void init()
{
        add_action("do_audit", "check");
        add_action("do_audit", "chazhang");
        add_action("do_convert", "convert");
        add_action("do_convert", "duihuan");
        add_action("do_deposit", "deposit");
        add_action("do_deposit", "cun");
        add_action("do_withdraw", "withdraw");
        add_action("do_withdraw", "qu");
        add_action("do_bcun","bcun");
        add_action("do_bqu","bqu");
        add_action("do_bcheck","bcheck");
}

void enough_rest()
{
        delete_temp("busy");
}
