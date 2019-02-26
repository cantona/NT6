// xiaoweri.c 校尉
// Last Modified by Winder on Jul. 15 2000

#include <ansi.h>
inherit NPC;

void create()
{
        set_name(YEL "校尉" NOR, ({ "xiao wei", "jiang" }));
        set("title","揚州守備");
        set("age", 31);
        set("gender", "男性");
        set("str", 24);
        set("dex", 16);
        set("combat_exp", 20000);
        set("shen_type", 1);

        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("blade", 40);
        set_skill("force", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 40);

        set("chat_chance", 30);
        set("chat_msg", ({
                "當了這麼多年兵，才是個校尉。。唉。。。。\n",
                "在揚州混了這麼多年了，卻好多地方沒去過。。。\n",
                "當兵真是無聊透頂了。。。\n",
                "校尉喝道：大膽刁民，竟敢殺官，莫不是想造反不成？\n",
                "校尉喝道：你還能逃出大宋國界不成，還是乖乖投降吧！\n",
        }));
        setup();
        carry_object(__DIR__"obj/gangdao")->wield();
        carry_object(__DIR__"obj/junfu")->wear();
        carry_object(__DIR__"obj/jitui")->wear();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && 
                (int)ob->query_condition("killer")) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
void greeting()
{
        object me = this_player();
        if( me->query_condition("killer") )
        {
                message_vision( "校尉對着$N大喝一聲：“殺人放火的刁民，快快受死吧！！！” \n", me );
                kill_ob(me);
        }
}

int accept_fight(object me)
{
        object *all;
        int i;
        if ( random(5) == 0 )
        {
                command("say 軍爺我今天心情好，別煩我，滾！！！！\n");
                return 0;
        }
        command("say 我看你今天是活得不耐煩了,"+RANK_D->query_rude(me)+",去死吧！\n");
        me->apply_condition("killer", 360);
        all = all_inventory(environment(me));
        for ( i = 0; i < sizeof( all ); i ++ )
        {
        if ( all[ i ]->id("shi bing") || all[ i ]->id("xiao wei")
                || all[ i ]->id("wu jiang") )
                all[ i ] -> kill_ob(me);
        }
        return 1;
}

int refuse_killing(object me)
{
    object *all;
    int i;

    me->apply_condition("killer", 360);
    all = all_inventory(environment(me));
    for ( i = 0; i < sizeof( all ); i ++ )
    {
        if ( all[i]->id("shi bing") || all[i]->id("xiao wei")
            || all[i]->id("wu jiang") )
            all[i] -> kill_ob(me);
    }
    return 1;
}
