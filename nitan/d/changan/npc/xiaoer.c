//xiaoer.c

inherit KNOWER;

void create()
{
        set_name("店小二", ({"xiaoer","xiaoer","xiao","waiter","er"}));
        set("shop_id",({"waiter","xiaoer","xiao","er"}));
        set("shop_title","店小二");
        set("gender", "男性");
        set("combat_exp", 2000);
        set("age", 21);
        set("per", 23);
        set("attitude", "friendly");
        set("shen_type", 1);
        set_skill("unarmed", 10);
        setup();
        carry_object("/d/changan/npc/obj/linen")->wear();
        add_money("silver", 1);

}

void greeting(object ob)
{
        if (! ob || ! visible(ob) || environment(ob) != environment())
                return;
        say(name() + "笑咪咪地説道：這位" + RANK_D->query_respect(ob) +
            "，進來歇歇腳，休息一下吧。\n");
}

int accept_object(object who, object ob)
{
        if( query("money_id", ob) && ob->value() >= 300 )
        {
                tell_object(who, "小二一哈腰，説道：多謝您老，客官請上樓歇息。\n");
                set_temp("rent_paid", 1, who);
                return 1;
        }
        return 0;
}
