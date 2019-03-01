#include <ansi.h>

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("花農", ({ "hua nong", "hua", "nong" }));
        set("title", HIY "洛陽苗舖" NOR); 
        set("gender", "男性");
        set("long", "一個衣著樸素的老農，他在洛陽苗舖栽花\n"
                    "種草數十年，如果你也想在此種花，可以\n"
                    "向他買一些種子。\n");
        set("str", 100);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);
        set("combat_exp", 800000);
        set("attitude", "friendly");

        set("vendor_goods", ([
                __DIR__"obj/huazhong": 1,
        ]));

        setup();

        carry_object("/clone/misc/cloth")->wear();
        set_max_encumbrance(100000000);
}

void init()
{
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
