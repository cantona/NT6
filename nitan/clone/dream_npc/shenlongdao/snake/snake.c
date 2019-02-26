//snake.c

inherit DREAM_NPC;
#include <ansi.h>

int is_snake(){return 1;}

void create()
{
        set_name("黑冠巨蟒", ({ "snake", "she" }) );
        //set("race", "蛇類");
        set("age", 20);
        set("long", "一隻龐然大物，它眼中噴火,好像要一口把你吞下。\n");
        set("attitude", "aggressive");
        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 500);
        set("max_jing", 500);
        set("str", 86);
        set("con", 80);
        set("limbs", ({ "頭部", "身體", "七寸", "尾巴" }) );
        set("verbs", ({ "bite" }) );
                set("max_neili", 25000);
                set("neili", 25000);

        set("combat_exp", 1000000);

        set_temp("apply/attack", 85);
        set_temp("apply/damage", 600);
        set_temp("apply/armor", 200);
        set_temp("apply/defence",80);

                set("gift/exp", 10);
                set("gift/pot", 5);
                set("oblist", ([
                        "/clone/fam/gift/con2" : 200,
                        "/clone/fam/gift/con3" : 5,
                        "/clone/armor/feima-xue" : 4,
                        "/clone/armor/feima-xue2" : 2,
                        "/clone/armor/biyu-chai" : 30,
                        "/clone/armor/biyu-chai2" : 20,
                        "/clone/armor/biyu-chai3" : 10,
                        "/clone/armor/heitie-kai1" : 70,
                        "/clone/armor/heitie-kai2" : 40,
                        "/clone/armor/heitie-kai3" : 20,
                        "/clone/armor/piaoxue" : 10,
                        "/clone/armor/piaoxue2" : 6,
                        "/clone/armor/piaoxue3" : 4,                        
                ]));

        setup();
                add_money("silver", 1 + random(3));
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she") return 0;
        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("你不能化蛇為杖。\n");

        return notify_fail("黑冠巨蟒身子太過粗大，無法化為蛇杖。\n");
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