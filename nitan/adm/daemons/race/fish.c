// fish.c 遊魚

#ifndef __FISH__
#define __FISH__

// A normal fish is at least 20 g weight
#define BASE_WEIGHT 20
#endif

inherit F_DBASE;

mapping *combat_action = ({
([
        "action":                "$N遊上來來張嘴往$n的$l狠狠地一咬",
        "damage":                20,
        "damage_type":        "咬傷",
]),
([
        "action":                "$N擺動尾巴往$n的$l猛地一拍",
        "damage":                20,
        "damage_type":        "淤傷",
]),
});

void create()
{
        seteuid(getuid());
        set("attitude", "peaceful");
        set("limbs", ({
                "頭部",        "腮部",        "背部",        "腹部",        
                "前鰭",        "後鰭", "尾巴"
        }) );

        set("dead_message",       "\n$N擺動了幾下，白白的肚子往上翻了起來。\n\n"    );
        set("unconcious_message", "\n$N擺動了幾下，紅紅的腮幫往外翻了出來。\n\n"    );
        set("revive_message",     "\n$N擺了幾下，又在水中遊了開去。\n\n"            );
        set("leave_msg",          "打了個水漂遊了出去"                    );
        set("arrive_msg",         "遊了過來，在水中靈活地打了個轉兒"            );
        set("fleeout_message",    "打了個水漂遊了出去"                    );
        set("fleein_message",     "搖頭擺尾地遊了過來，白白的肚子往上翻著"      );
}

void setup_fish(object ob)
{
        mapping my;

        my = ob->query_entire_dbase();

        ob->set_default_action(__FILE__, "query_action");
	set("default_actions", (: call_other, __FILE__, "query_action" :), ob);

        my["unit"] = "條";
        
        if( undefinedp(my["gender"]) ) my["gender"] = (random(2))?"雌性":"雄性";
        if( undefinedp(my["age"]) ) my["age"] = random(5) + 5;

        if( undefinedp(my["str"]) ) my["str"] = random(10) + 5;
        if( undefinedp(my["int"]) ) my["int"] = random( 5) + 5;
        if( undefinedp(my["per"]) ) my["per"] = random( 5) + 5;
        if( undefinedp(my["con"]) ) my["con"] = random(10) + 5;
        if( undefinedp(my["dex"]) ) my["dex"] = random(20) + 5;
        if( undefinedp(my["kar"]) ) my["kar"] = random(10) + 5;

        if( undefinedp(my["max_jing"]) ) {
                if( my["age"] <= 10 ) my["max_jing"] = my["age"] * 5;
                else my["max_jing"] = 50;
        }
        if( undefinedp(my["max_qi"]) ) {
                if( my["age"] <= 10 ) my["max_qi"] = my["age"] * 8;
                else my["max_qi"] = 80;
        }
        if( undefinedp(my["max_jingli"]) ) {
                if( my["age"] <= 10 ) my["max_jingli"] = my["age"] * 10;
                else my["max_jingli"] = 100;
        }
        ob->set_default_object(__FILE__);
        if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 5)* 500);
}

mapping query_action(object me)
{
        return combat_action[random(sizeof(combat_action))];
}
