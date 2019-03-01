// bird.c 飛禽

#ifndef __BIRD__
#define __BIRD__

// A normal bird is at least 50 g weight
#define BASE_WEIGHT 50
#endif

inherit F_DBASE;

mapping *combat_action = ({
([
        "action":                "$N用爪子往$n的$l猛地一抓",
        "damage":                10,
        "damage_type":        "抓傷",
]),
([
        "action":                "$N飛過來往$n的$l狠狠地一啄",
        "damage":                30,
        "damage_type":        "刺傷",
]),
([
        "action":                "$N用翅膀向$n的$l拍了過去",
        "damage":                30,
        "damage_type":        "刺傷",
])
});

void create()
{
        seteuid(getuid());
        set("attitude", "peaceful");
        set("limbs", ({
                "頭部",        "頸部",        "後背",        "腹部",        "腳爪",        "翅膀"
        }) );

        set("dead_message",       "\n$N發出一聲凄厲的鳴叫，從半空中跌了下來。\n\n"    );
        set("unconcious_message", "\n$N從半空中砰地跌下來，暈了過去。\n\n"            );
        set("revive_message",     "\n$N醒過來動彈了一下，雙翅一振，又飛了起來。\n\n"  );
        set("leave_msg",          "疾飛而去"                                      );
        set("arrive_msg",         "飛了過來"                                      );
        set("fleeout_message",    "凄鳴著疾飛而去"                        );
        set("fleein_message",     "緩緩地飛了過來，沉重地在半空中打著旋兒"        );
}

void setup_bird(object ob)
{
        mapping my;

        my = ob->query_entire_dbase();

        ob->set_default_action(__FILE__, "query_action");
	set("default_actions", (: call_other, __FILE__, "query_action" :), ob);

        my["unit"] = "只";
        
        if( undefinedp(my["gender"]) ) my["gender"] = "雄性";
        if( undefinedp(my["age"]) ) my["age"] = random(20) + 5;

        if( undefinedp(my["str"]) ) my["str"] = random(10) + 5;
        if( undefinedp(my["int"]) ) my["int"] = random(10) + 5;
        if( undefinedp(my["per"]) ) my["per"] = random(20) + 5;
        if( undefinedp(my["con"]) ) my["con"] = random(50) + 5;
        if( undefinedp(my["dex"]) ) my["dex"] = random(60) + 5;
        if( undefinedp(my["kar"]) ) my["kar"] = random(20) + 5;

        if( undefinedp(my["max_jing"]) ) {
                if( my["age"] <= 3 ) my["max_jing"] = 30;
                else if( my["age"] <= 10 ) my["max_jing"] = 30 + (my["age"] - 3) * 10;
                else if( my["age"] <= 30 ) my["max_jing"] = 100 + (my["age"] - 10) * 3;
                else my["max_jing"] = 160 + (my["age"] - 30);
        }
        if( undefinedp(my["max_qi"]) ) {
                if( my["age"] <= 5 ) my["max_qi"] = 30;
                else if( my["age"] <= 20 ) my["max_qi"] = 30 + (my["age"] - 5) * 15;
                else my["max_qi"] = 255 + (my["age"] - 20) * 5;
        }
        if( undefinedp(my["max_jingli"]) ) {
                if( my["age"] <= 5 ) my["max_jingli"] = 20;
                else if( my["age"] <= 20 ) my["max_jingli"] = 20 + (my["age"] - 5) * 20;
                else my["max_jingli"] = 320 + (my["age"] - 20) * 5;
        }
        ob->set_default_object(__FILE__);
        if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 5)* 1000);

        if( query("subrace", ob) == "走禽"){
                set("dead_message",       "\n$N發出一聲凄厲的鳴叫，栽倒在地上死了。\n\n"      );
                set("unconcious_message", "\n$N凄鳴一聲栽倒在地，暈了過去。\n\n"              );
                set("revive_message",     "\n$N醒過來動彈了一下，雙翅撲騰了幾下站了起來。\n\n");
                set("comeout_message",    "往$d疾奔而去。\n"                                      );
                set("comein_message",     "跑了過來。\n"                                      );
                set("fleeout_message",    "一聲凄鳴，往$d疾奔而去。\n"                        );
                set("fleein_message",     "搖搖擺擺的跑了過來。\n"                            );
        }
}

mapping query_action(object me)
{
        return combat_action[random(sizeof(combat_action))];
}
