// yulin2.c

#include <ansi.h>
inherit NPC;

void create()
{
        set_name(HIC"御林軍"NOR, ({"yulin jun", "jun"}));
        set("gender", "男性");
        set("age", random(10) + 30);
        set("str", 25);
        set("dex", 16);
        set("long", "他站在那裏，的確有説不出的威風。\n");
        set("combat_exp", 100000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("unarmed", 60);
        set_skill("force", 60);
        set_skill("sword", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_skill("shaolin-shenfa", 50);
        set_skill("hunyuan-yiqi", 50);
        set_skill("damo-jian", 50);
        map_skill("sword", "damo-jian");
        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 30);

        set("neili", 400);
        set("max_neili", 400);
        set("jiali", 10);

        setup();
        carry_object("/d/city/obj/gangjian")->wield();
        carry_object("/d/city/obj/tiejia")->wear();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) &&
                (int)ob->query_condition("killer")) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
        if(interactive(ob =this_player())&&(int)ob->query_class("officer"))
        {
        message_vision("御林軍見到你都跪在地上説: 奴才給大人請安了\n"+
"       大人要面聖請到「御書房」侯駕,小的職責在身,不便照顧了。\n",this_player())
;
}
}
