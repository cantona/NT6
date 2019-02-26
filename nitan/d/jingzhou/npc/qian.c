#include <ansi.h>

inherit BUNCHER;
inherit F_BANKER;

void create()
{
    set_name("錢得發", ({"qian defa","qian", "defa"}));
    set("title", "錢莊老闆");
    set("gender", "男性");
    set("age", 34);

    set("str", 22);
    set("int", 24);
    set("dex", 18);
    set("con", 18);

    set("qi", 500); 
    set("max_qi", 500);
    set("jing", 100);
    set("max_jing", 100);
    set("shen", 0);

    set("combat_exp", 50000);
    set("shen_type", 1);
    set("attitude", "friendly");
    set("env/wimpy", 50);
    set("chat_chance", 2);
    set("chat_msg", ({
        CYN "錢得發驕傲的説道：本銀號已經有上百年的歷史，在江南可以説是第一家。\n" NOR,
        CYN "錢得發笑着説道：在本店存錢無利息，客官您看着辦吧。\n" NOR
        CYN "錢得發微微一笑，説道：本店還辦理不同面額貨幣的兑換業務。\n" NOR
        }));

    set_skill("unarmed", 50);
    set_skill("dodge", 50);
    set_temp("apply/attack", 100);
    set_temp("apply/defense", 100);
    set_temp("apply/damage", 40);

    setup();
    add_money("silver", 10);
    carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_check", "check");
        add_action("do_check", "chazhang");
        add_action("do_convert", "convert");
        add_action("do_convert", "duihuan");
        add_action("do_deposit", "deposit");
        add_action("do_deposit", "cun");
        add_action("do_withdraw", "withdraw");
        add_action("do_withdraw", "qu");
        delete_temp("busy");
}
