// npc: /d/city/npc/bookboss.c
// Last Modified by Winder on Jul. 15 2000

inherit NPC;
inherit F_DEALER;
void create()
{
        set_name("馮老狗", ({ "feng laogou","feng" }) );
        set("title","書局老闆");
        set("gender", "男性" );
        set("age", 38);
        set("long", "馮老闆小名老狗，可你一看就知道他是個清心寡慾之人，一世賣書販畫為生，也頗為自得。\n");
        set("attitude","friendly");
        set("inquiry",([
                "書"   : "我這裏什麼書都有，你想買什麼？\n",
                "here" : "這是我花了三百兩銀子買來的店鋪。\n",
        ]));
        set("vendor_goods",({
                "/clone/book/lbook1",
                "/clone/book/lbook2",
                "/clone/book/lbook6",
                "/clone/book/lbook7",
                "/clone/book/lbook8",
                "/clone/book/blade_book0",
                "/clone/book/blade_book1",
                "/clone/book/dodge_book1",
                "/clone/book/dodge_book2",
                "/clone/book/sword_book1",
                "/clone/book/cuff_book",
                "/clone/book/unarmed_book",
        }));
        set("chat_chance", 15);
        set("chat_msg",(
        {
            "老闆手裏拿着一把雞毛撣子，輕輕撣去牆上，書架上的塵土。\n",
            "老闆笑着問道：“買書？還是看看字畫兒？”\n",
        }));

        setup();
        carry_object("/clone/cloth/male-cloth")->wear();
}
void init()
{
        ::init();
        add_action("do_list","list");
        add_action("do_buy","buy");
}