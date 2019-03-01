#include <ansi.h>

inherit NPC;
inherit F_DEALER;

int redeem(string arg);

void create()
{
        set_name("陳朝奉", ({ "chen chaofeng", "chen", "chaofeng" }));
        set("title", "當舖老板");
        set("shen_type", 0);

        set("gender", "男性");
        set_max_encumbrance(100000000);
        set("age", 35);
        set("str", 100);
        set("long", "陳朝奉是水晶當的老板，據說為人還不錯。\n");
        set("no_get_from", 1);

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
