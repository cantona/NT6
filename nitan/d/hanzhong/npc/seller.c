// seller.c

inherit KNOWER;
inherit F_DEALER;

string ask_me();

void create()
{
        set_name("小販", ({ "seller" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long",
                "這是個小販，別看他長的老老實實，可你別想從他那兒掏便宜。\n");
        set("combat_exp", 300);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("count", 1);
        set("attitude", "friendly");
        set("vendor_goods", ({
                __DIR__"obj/stick",
                __DIR__"obj/bottle",
                __DIR__"obj/egg",
                "/d/xingxiu/obj/fire",
        }) );
        set("inquiry", ([
                "藥" : (: ask_me :),
                "藥材" : (: ask_me :),
        ]) );
        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
        add_money("coin", 100);
}

void init()
{
        ::init();
        add_action("do_list","list");
        add_action("do_buy", "buy");
}

string ask_me()
{
        object me=this_player();
        if( query_temp("tmark/藥", me)){
                return "我走南闖北，沒見過你這麼羅嗦的人！\n";
        }
        else
        {
                set_temp("tmark/藥", 1, me);
                return "當年我到極北森林中採藥，還真遇到了一些好藥材，要買得先交
錢。\n";
        }
}

int accept_object(object who, object ob)
{
        object obj;

        if( query("count", this_object())<0 )
        {
                write("小販說道：“既然您出得起價錢，還愁沒地買？我這是沒了。”\n");
                return 1;
        }
        if( (query("money_id", ob)) && (ob->value() >= 10000) && 
                (query_temp("tmark/藥", who)) )
        {
                obj = new(VEGETABLE_DIR"heshouwu");
                obj->move(who);
                addn_temp("tmark/藥", 0, who);
                write("小販說道：“既然您出得起價錢，這味藥可就歸您了。”\n");
                addn("count", -1);
                return 1;
        }
        else
                if( query("money_id", ob) )
                {
                        write("小販陰笑一聲，說道：“嘿嘿，給我這麼多錢哪。”\n");
                        return 1;
                }
                else
                {
                        return notify_fail("小販詫異地說道：“給我這個幹什麼？”\n");
                }
}
