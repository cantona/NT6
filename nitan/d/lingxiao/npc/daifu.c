inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("閻大夫", ({ "yan daifu", "yan", "daifu" }));
        set("str", 20);
        set("gender", "男性");
        set("age", 18);
        set("long", "閻大夫是凌宵城中的醫生，聲得稱讚。\n");
        set("combat_exp", 250);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/clone/misc/jinchuang",
                "/clone/misc/yangjing",
                "/clone/misc/dust",
                "/clone/misc/fashao",
                "/clone/misc/shanghan",
                "/clone/misc/xiaoshu",
                "/clone/misc/dongshang",
                "/clone/misc/zhike",
                "/d/shenlong/obj/xionghuang",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
