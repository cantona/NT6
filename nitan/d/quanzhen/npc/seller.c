#include <ansi.h>

inherit KNOWER;
inherit F_DEALER;

string ask_me();

void create()
{
        set_name("小販", ({ "xiao fan", "xiao", "fan" }));
        set("gender", "男性" );
        set("age", 32);
        set("long", "這是個小販，別看他長的老老實實，可你別\n"
                    "想從他那兒掏便宜。\n");
        set("combat_exp", 300);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "friendly");
        set("vendor_goods", ({
                __DIR__"obj/stick",
                __DIR__"obj/bottle",
                __DIR__"obj/egg",
                "/d/xingxiu/obj/fire",
        }));
        set("inquiry", ([
                "藥材"   : (: ask_me :),
                "首烏"   : (: ask_me :),
                "何首烏" : (: ask_me :),
        ]));

        set("count", 3);

        setup();
        carry_object(__DIR__"obj/cloth")->wear();
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
        object me = this_player();

        if (query("count") < 1)
        {
                return "實在對不住，現在我手裡也沒貨了。\n";
        } else
        if( query_temp("tmark/藥", me) )
        {
                return "我走南闖北，沒見過你這麼羅嗦的人。\n";
        } else
        {
                set_temp("tmark/藥", 1, me);
                return "我到極北森林中採藥，還真遇到了一些好藥材，要買得先交錢。\n";
        }
}

int accept_object(object who, object ob)
{
        object obj;

        if( !query("money_id", ob) )
        {
                write(CYN "小販詫異地說道：你給我這個幹什麼？\n" NOR);
                return 0;
        }

        if (query("count") < 1)
        {
                write(CYN "小販抱歉地說道：實在對不住，現在我手裡也沒貨了？\n" NOR);
                return 0;
        }

        if( !query_temp("tmark/藥", who) )
        {
                write(CYN "小販疑惑地說道：我又不是乞丐，你沒事給我錢幹嘛？\n" NOR);
                return 0;
        }

        if (ob->value() < 10000)
        {
                write(CYN "小販陰笑著說道：嘿嘿，給我這麼多錢哪。\n" NOR);
                return 0;
        }

        obj = new(__DIR__"obj/shouwu");
        obj->move(this_object());

        addn("count", -1);
        command("giveheshouwuto"+query("id", who));
        write(CYN "小販說道：既然您出得起價錢，這味藥可就歸您了。\n" NOR);
        return 1;
}
