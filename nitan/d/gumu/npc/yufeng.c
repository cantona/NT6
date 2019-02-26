// yufeng.c 玉蜂

#include <ansi.h>
inherit NPC;

void create()
{
        set_name(HIW "玉蜂" NOR, ({"yufeng","feng","bee"}) );
        set("race", "昆蟲");
        set("subrace", "飛蟲");
        set("age", 8);
        set("long","這是一隻玉色的蜜蜂，個頭比普通蜜蜂大得多，\n翅膀上被人用尖針刺有字。\n");

        set("no_train", 1);
        set("str", 40);
        set("dex", 50);

        set_temp("apply/attack", 35);
        set_temp("apply/armor", 25);

        set("chat_chance", 2);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
"玉蜂在你頭頂轉了一圈，似乎發現這不是可採蜜的地方，就嗡嗡嗡地飛走了。\n",
"玉蜂圍繞着鮮花飛飛停停，似乎也不着重在採蜜上。\n",
        }) );

        setup();
}

/*
void init()
{
        mapping fam;
        object ob;

        ::init();
        if (interactive(ob = this_player()) &&
                (fam=query("family", ob)) && fam["family_name"] != "古墓派" )
        {
                message_vision(HIR"$N擅自闖入古墓禁地。\n"NOR,ob);
                remove_call_out("killob");
                call_out("killob", 1, ob); 
        }
}
*/

void die()
{
        message_vision("$N猛地振翅，飛走了。\n", this_object());
        destruct(this_object());
}
void killob(object ob)
{
        if (environment(ob)==environment())
         kill_ob(ob);
}
