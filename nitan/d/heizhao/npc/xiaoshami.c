// xiaoshami.c
inherit NPC;
#include <ansi.h>;
void create()
{
        set_name("小沙彌", ({"xiao shami","shami",}));
        set("long",
        "他是本寺小沙彌。\n");
        set("gender", "男性");
        set("age", 12);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("str", 20);
        set("int", 20);
        set("con", 22);
        set("dex", 25);

        set("max_qi", 150);
        set("max_jing", 100);
        set("neili", 150);
        set("max_neili", 150);

        set("combat_exp", 2000);
        set("score", 1000);

        set_skill("force", 30);
        set_skill("dodge", 20);
        set_skill("unarmed", 20);
        set_skill("parry", 20);
        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 5);

        setup();

        carry_object("/d/shaolin/obj/dao-cloth.c")->wear();
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob=this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
void greeting(object ob)
{
        mapping myfam;

        myfam=query("family", ob);
        if( !myfam ) return;
        if( (myfam["master_id"] == "yideng dashi") &&
                !query("exits/out", environment(this_object())) )
        {
message_vision(HIY"小沙彌對$N説：“你回來了。去見師父吧。”説着打開後門。\n"NOR, ob);
                set("exits/out", "/d/heizhao/zhulin1", environment(this_object()));
        }
        return;
}

int accept_object(object who, object ob)
{
        if ( !who || environment(who) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, who) ) return notify_fail("你沒有這件東西。\n");

        if( query("id", ob) != "huangbu xiaonan" )
                return notify_fail("小沙彌不想要這件東西。\n");
        set("exits/out", "/d/heizhao/zhulin1", environment(this_object()));
        message_vision(HIY"小沙彌點了點頭，把禪院後門打開來。\n"NOR, who);
        return 1;
}
