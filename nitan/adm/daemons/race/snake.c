// snake.c 蛇類

#ifndef __SNAKE__
#define __SNAKE__

// A normal beast is at least 1 g weight
#define BASE_WEIGHT 1
#endif

inherit F_DBASE;

mapping *combat_action = ({
([
        "action":                "$N爬上來張嘴往$n的$l狠狠地一咬",
        "damage":                30,
        "damage_type":        "咬傷",
]),
([
        "action":                "$N支起身猛地往$n的$l捲了上來",
        "damage":                30,
        "damage_type":        "瘀傷",
]),
});

void create()
{
        seteuid(getuid());
        set("attitude", "agressive");
        set("limbs", ({
                "頭部", "身體", "七寸", "尾巴"
        }) );

        set("dead_message",       "\n$N痛苦地扭動了幾下，全身軟軟地散了開來。\n\n"  );
        set("unconcious_message", "\n$N痛苦地扭了幾下，不動了。\n\n"                );
        set("revive_message",     "\n$N身軀一彈一滾，又在地上到處遊走開來。\n\n"    );
        set("leave_msg",          "嗖地一聲鑽了出去"                      );
        set("arrive_msg",         "蜿蜒地遊了過來"                              );
        set("fleeout_message",    "嗖地一聲鑽了出去"                      );
        set("fleein_message",     "緩緩地遊了過來，軟耷耷地在地上趴着"          );
}

void setup_snake(object ob)
{
        mapping my;

        my = ob->query_entire_dbase();

        ob->set_default_action(__FILE__, "query_action");
	set("default_actions", (: call_other, __FILE__, "query_action" :), ob);

        my["unit"] = "只";
        
        if( undefinedp(my["gender"]) ) my["gender"] = "雄性";
        if( undefinedp(my["age"]) ) my["age"] = random(10) + 5;

        if( undefinedp(my["str"]) ) my["str"] = random(20) + 5;
        if( undefinedp(my["int"]) ) my["int"] = random(10) + 5;
        if( undefinedp(my["per"]) ) my["per"] = random(10) + 5;
        if( undefinedp(my["con"]) ) my["con"] = random(30) + 5;
        if( undefinedp(my["dex"]) ) my["dex"] = random(20) + 5;
        if( undefinedp(my["kar"]) ) my["kar"] = random(10) + 5;

        if( undefinedp(my["max_jing"]) ) {
                if( my["age"] <= 20 ) my["max_jing"] = my["age"] * 5;
                else my["max_jing"]  = 100;
        }
        if( undefinedp(my["max_qi"]) ) {
                if( my["age"] <= 20 ) my["max_qi"] = my["age"] * 8;
                else my["max_qi"] = 160;
        }
        if( undefinedp(my["max_jingli"]) ) {
                if( my["age"] <= 20 ) my["max_jingli"] = my["age"] * 10;
                else my["max_jingli"] = 200;
        }
        ob->set_default_object(__FILE__);
        if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 10)* 2000);
}

mapping query_action(object me)
{
        return combat_action[random(sizeof(combat_action))];
}
