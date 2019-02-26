// cheng.c 程老闆

inherit NPC;
inherit F_DEALER;

string ask_me1();
string ask_me2();

void create()
{
        set_name("程老闆", ({ "cheng laoban", "cheng" }));
        set("title", "全聚德老闆");
        set("shen_type", 1);

        set("str", 20);
        set("gender", "男性");
        set("age", 65);
        set("long", "程老闆經營祖傳下來的全聚德酒樓已有多年。\n");

        set("combat_exp", 50000);

        set("qi", 300);
        set("max_qi", 300);
        set("attitude", "friendly");

        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);

        set("vendor_goods", ({
                "/d/city/obj/hdjiudai",
                "/d/beijing/obj/kaoya",
                "/d/city/obj/kaoya",
        }));

        set("inquiry", ([
                "譚友紀" : (: ask_me1 :),
                "譚師爺" : (: ask_me1 :),
                "叫化雞" : (: ask_me2 :),
        ]) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

string ask_me1()
{
        if( query_temp("marks/雞2", this_player()) )
        {
                delete_temp("marks/雞2", this_player());
                set_temp("marks/雞3", 1, this_player());
                return "哦，是老譚讓你來的。到了這裏就別見外了。你找我有什麼事嗎？\n";
        }
        else if( query_temp("marks/雞3", this_player()) )
                return "我不是浙江人，也沒有你那麼羅嗦！\n";
        else
                return "去去去。哪裏來的泥腿子，這裏是北京城，天子腳下！！不懂別亂問！！\n";
}

string ask_me2()
{
        if( query_temp("marks/雞3", this_player()) )
        {
                say("既然你這麼喜歡吃叫化雞，又千里迢迢地跑來找我，就賣你一隻吧。\n");
                return "請先付五兩黃金，咱們一手交錢、一手交貨。\n";
        }
        else
                return "去去去。哪裏來的泥腿子，這裏是北京城，天子腳下！！懂不懂！！\n";
}

int accept_object(object who, object ob)
{
    object item;

    if( (query("money_id", ob)) && (ob->value() == 50000 )
          && (query_temp("marks/雞3", who)) )
        {
        item = new("/d/city/obj/jiaohuaji");
        item->move(who);
        delete_temp("marks/雞3", who);
        return 1;
    }
    else if (ob->value() < 50000)
        {
                command("say 這...這...，這我就卻之不恭了。");
                return 1;
    }
    return 0;
}
