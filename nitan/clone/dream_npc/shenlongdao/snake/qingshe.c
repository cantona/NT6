inherit DREAM_NPC;
#include <ansi.h>

int is_snake(){return 1;}

void create()
{
        set_name(NOR + GRN "竹葉青蛇" NOR, ({ "qing she", "qing", "she" }));
        set("long", GRN "這是一只讓人看了起雞皮疙瘩的竹葉青蛇。\n" NOR);

        set("age", 1);
        set("str", 15);
        set("dex", 200);
        set("max_qi", 3400);
        set("max_jing", 3400);
                set("max_neili", 25000);
                set("neili", 25000);        
        set("combat_exp", 600000);

        set("snake_poison", ([
                "level"  : 145,
                "perhit" : 125,
                "remain" : 145,
                "maximum": 145,
                "supply" : 22,
        ]));

        set("power", 10);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");

        set_temp("apply/dodge", 90);
        set_temp("apply/defense", 90);
        set_temp("apply/unarmed_damage", 40);

                set("gift/exp", 50);
                set("gift/pot", 25);
                set("oblist", ([
                        "/clone/fam/gift/dex2" : 100,
                        "/clone/armor/zi-feihun" : 2,
                        "/clone/armor/wuzhe-huwan" : 20,
                        "/clone/armor/wuzhe-huwan2" : 10,
                        "/clone/armor/wuzhe-huwan3" : 6,                        
                        "/clone/armor/zhanshen-toukui":60,
                        "/clone/armor/zhanshen-toukui2":40,
                        "/clone/armor/zhanshen-toukui3":30,                                        
                        "/clone/armor/yinyang-erhuan":20,
                        "/clone/armor/yinyang-erhuan2":10,
                        "/clone/armor/yinyang-erhuan3":8,
                        "/clone/tattoo/cangqiong": 40,                                
                ]));

        setup();
                add_money("silver", 2 + random(6));
}


mixed hit_ob(object me, object ob, int damage)
{
        mapping p;
        string  msg;
        int force;
        int dur;

        p=query("snake_poison", me);
        if (! p) return;
        if (damage / 3 + random(damage * 2 / 3) <
            query_temp("apply/armor", ob) )
        {
                // Defeated by armor
                return;
        }

        msg = "";
        dur = p["perhit"];
        if (dur > (int)p["remain"]) dur = p["remain"];
        p["remain"] = (int)p["remain"] - dur;
        this_object()->apply_condition("poison-supply", 1);
        if (! dur) return;


        force = (int)ob->query_skill("force");
        if (random(force / 2) + force / 2 >= (int)p["level"] &&
            query("neili", ob)>damage/5 )
        {
                if( query("qi", ob)<150 )
                {
                        msg = HIR "你覺得傷口有些發麻，連忙運功化解，但"
                              "是一時體力不支，難以施為。\n" NOR;
                } else
                if( query("jing", ob)<60 )
                {
                        msg = HIR "你覺得傷口有些發麻，連忙運功化解，但"
                              "是一時精神不濟，難以施為。\n" NOR;
                } else
                if( query("neili", ob)<damage/5+50 )
                {
                        msg = HIR "你覺得傷口有些發麻，連忙運功化解，但"
                              "是一時內力不足，難以施為。\n" NOR;
                } else
                {
                        addn("neili", -damage/5, ob);
                        ob->receive_damage("qi", 20);
                        ob->receive_damage("jing", 10);
                        return HIM "你覺得被咬中的地方有些發麻，連忙運功"
                               "化解毒性。\n" NOR;
                }
        }

        if (ob->affect_by("poison", ([ "level" : (int)p["level"] / 2,
                                       "name"  : "蛇毒",
                                       "id"    : "nature poison",
                                       "duration" : dur / 2, ])))
        {
                msg += HIR "$n" HIR "臉色一變，只覺被咬中的地方一陣麻木。\n" NOR;
        }
        return msg;
}