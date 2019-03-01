// hadani.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("哈達尼", ({ "ha dani", "dani", "ha" }));
        set("gender", "男性" );
        set("age", 28);
        set("long",
                "這是一位年輕的小伙子，靠打造出售鐵器為生。\n");
        set("title", "鐵匠");
        set("combat_exp", 30000);
        set("attitude", "friendly");
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 30);

        set("vendor_goods", ({
                "/d/guanwai/obj/saw",
                "/d/guanwai/obj/axe",
        }));

        set("inquiry", ([
                "鋼鋸" : "我這裡有上好的鋼鋸，你要不要買一條？",
                "鋸"   : "我這裡有上好的鋼鋸，你要不要買一條？",
                "斧頭" : "我這兒有，來一把吧。",
                "斧子" : "我這兒有，來一把吧。",
        ]));

        setup();
        carry_object("/clone/cloth/cuttonp")->wear();
}

void init()
{        
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
