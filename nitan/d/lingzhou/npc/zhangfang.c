// zhangfang.c

inherit NPC;

int ask_for_gongzi();

void create()
{
       set_name("帳房先生", ({"zhang fang", "zhangfang", "xiansheng"}));
        set("long",
"他一身邋遢，整天迷迷糊糊的睡不醒模樣。\n");
        set("gender", "男性");
        set("attitude", "heroism");

        set("inquiry",([
                "工資"    : (: ask_for_gongzi :),
                "薪水"    : (: ask_for_gongzi :),
                "salary"  : (: ask_for_gongzi :),
                "payment" : (: ask_for_gongzi :),
                "gongzi"  : (: ask_for_gongzi :),
        ]));

        set("age", 61);
        set("shen_type", 0);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 25);
        set("max_qi", 500);
        set("max_jing", 100);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 100);
        set("combat_exp", 1000);
        set("apply/attack",  30);
        set("apply/defense", 30);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 5);
}

int ask_for_gongzi()
{
        object me, payment;
        int paytimes;

        me = this_player();
        if( query("yipin/joined", me) )
        {
                if( !query("yipin/lasttime", me) )
                {
                        paytimes = 1;
                        set("yipin/lasttime", time(), me);
                }
                else
                {
                        paytimes=(time()-query("yipin/lasttime", me))/86400;
                        set("yipin/lasttime", time(), me);
                }
                payment=new("/clone/money/gold");
                if (paytimes ==0)
                {
                        tell_object(me, "帳房先生道：你的餉銀已經領過了吧。\n");
                }
                else
                {
                        payment->set_amount(paytimes);
                        payment->move(me);
                        tell_object(me, "帳房先生道：這是你的餉銀，收好吧。\n");
                }
        }
        else tell_object(me,"帳房先生道：欺負我老糊塗？你根本不是一品堂的人！\n");
        return 1;
}
