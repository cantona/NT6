#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("元財", ({ "yuan cai", "yuan" }) );
        set("gender", "男性" );
        set("title",  "店主" );
        set("age", 43);
        set("long", "他是這裡的店主，看上去忠厚老實的樣子。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "老板");
        setup();
}

int accept_object(object who, object ob)
{
        
        if( query("money_id", ob) && ob->value() >= 5000 )
        {
                tell_object(who, CYN "元財一哈腰，說道：多謝客官，樓上請。\n" NOR);
                set_temp("rent_paid", 1, who);
                return 1;
        }
        return 0;
}