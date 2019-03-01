// tangqian.c
#include <ansi.h>
inherit NPC;
inherit F_BANKER; 

void create()
{
        set_name("唐錢", ({"tang qian", "tang"}));
        set("title", "錢莊老板");
        set("nickname", HIR"見錢封喉"NOR);
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
                "唐錢驕傲的說道：本銀號已經有三百多年的歷史，在蜀中可以說是第一家。\n",
                "唐錢笑著說道：在本店存錢無利息，取錢嗎？你說要不要收取一定的費用啊。\n"
        }));
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 40);
        setup();
        add_money("gold", 5);
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
