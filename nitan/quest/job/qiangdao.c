// qiangdao.c 強盜
inherit NPC;
#include <ansi.h>
void move();

void create()
{
        set_name(HIW "強盜" NOR, ({ "qiang dao", "dao",}));
        set("gender", "男性");
        set("age", 28);
        set("long", "他是一個專靠打劫營生的強盜。\n");
        
        set("combat_exp",1000);
        set("attitude", "peaceful");
        
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        
         set("str",30);
         set("per",18);
         set("food",400);
         set("water",400);

        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        add_money("silver",10);
}

void init()
{
        remove_call_out("leave");
        call_out("leave",300);
}

void leave()
{
        object ob = this_object();
        if (!ob->is_fighting()) {
                message_vision(HIC "強盜鑽進路邊的雜草，不見了。\n" NOR,this_object());
                }
        else call_out("leave",10);
}

void die()
{
        object me = this_object()->query_temp("last_damage_from");
        object corpse, money;      
        int kar, exp, pot;
        kar = random(30);
        exp = kar + random(200);
        pot = 200 + random(50);

        message_vision(HIR "\n強盜倒在地上，掙紮了幾下就死了。\n" NOR,me);
        if (me->query("kill_qiangdao") == 1 && this_object()->query_temp("owner/id") == me->query("id")) {
                message_vision(HIW "$N被獎勵了：\n"
                + chinese_number(exp) + "點實戰經驗，\n"
                + chinese_number(pot) + "點潛能，\n"
                + chinese_number(10) + "點威望。\n" NOR, me);
                me->add("combat_exp", exp);
                me->add("potential", pot);
                me->add("weiwang", 10);
                me->delete("quest3");
                me->delete("kill_qiangdao");
                }
        else {
                message_vision(HIC "\n由于$N"HIC"殺錯了目標，防礙了別人做任務。現在倒扣經驗：\n"
                + chinese_number(200) + "點實戰經驗，\n"
                + chinese_number(100) + "點潛能，\n"
                + chinese_number(1000) + "點威望作為答謝。\n" NOR, me);
                me->add("combat_exp", -200);
                me->add("potential", -100);
                me->add("weiwang",-1000);
                }

        corpse = new("/clone/misc/corpse");
        corpse->set("name",HIW "強盜的屍體" NOR);
        corpse->set("long","他是一個曾經無惡不做的強盜，\n然而，他已經死了，剩下一具醜陋的屍體。\n");
        corpse->move(environment(this_object()));
        corpse->set_max_encumbrance(1000);        
        money = new("/clone/money/gold");
        money->move(corpse);
        me->add("MKS", 1);

        destruct(this_object());
}

