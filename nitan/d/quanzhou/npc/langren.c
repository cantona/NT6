// langren.c

inherit NPC;

void create()
{
        set_name("日本浪人", ({ "lang ren", "langren", "lang"}));
        set("gender", "男性");
        set("age", random(10) + 20);
        set("str", 25);
        set("dex", 16);
        set("long","這是個神態倨傲的東洋武士，頭戴鬥笠，身著灰黑色的和服，腰裡挎著把長長的武士刀。\n");
        set("combat_exp", 30000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_temp("apply/attack", 35);
        set_temp("apply/defense", 35);
        set_temp("apply/armor", 35);
        set_temp("apply/damage", 35);
        set_skill("blade", 35);
        set_skill("dodge", 35);

        setup();
        carry_object("/d/taiwan/npc/obj/wodao")->wield();
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( environment(ob) != environment() ) return;
        say("日本浪人輕蔑地瞪了你一眼，說道：中國人都象你這般沒用吧，哈哈哈！\n");
}
