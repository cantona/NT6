// wang.c

#include <ansi.h>

inherit BUNCHER;
inherit F_DEALER;

void create()
{
        set_name("王合計", ({ "wang heji", "heji", "wang" }));
        set("title", "當鋪老闆");
        set("shen_type", 0);

        set("gender", "男性");
        set_max_encumbrance(100000000);
        set("age", 35);
        set("long", "他帶着一臉詭祕、奸詐的笑容。\n");
        set("no_get_from", 1);
        set("no_get", 1);

        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/attack", 30);
        set_temp("apply/damage", 15);

        set("combat_exp", 50000);
        set("attitude", "friendly");

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_sell", "sell");
        add_action("do_value", "value");
}

void die()
{
        message_vision("\n$N死了。\n", this_object());
        destruct(this_object());
}
