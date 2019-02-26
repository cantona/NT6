// beast.c 野獸

#ifndef __BEAST__
#define __BEAST__

// A normal beast is at least 50 kg weight
#define BASE_WEIGHT 30000
#endif

inherit F_DBASE;

mapping *combat_action = ({
([
        "action":                "$N撲上來張嘴往$n的$l狠狠地一咬",
        "damage":                50,
        "damage_type":        "咬傷",
]),
([
        "action":                "$N舉起爪子往$n的$l抓了過去",
        "damage":                30,
        "damage_type":        "抓傷",
]),
([
        "action":                "$N躍起來用前掌往$n的$l猛地一拍",
        "damage":                30,
        "damage_type":        "瘀傷",
]),  
});

void create()
{
        seteuid(getuid());
        set("attitude", "aggressive");
        set("limbs", ({
                "頭部",        "頸部",        "胸部",        "後背",        "腹部",        
                "前腿",        "後腿", "前爪",        "後爪", "尾巴"
        }) );

        set("dead_message",       "\n$N仰天慘嚎了一聲，趴在地上不動了。\n\n"      );
        set("unconcious_message", "\n$N低低地吼了一聲，滾倒在地上暈了過去。\n\n"  );
        set("revive_message",     "\n$N四肢慢慢動彈了一下，睜開眼醒了過來。\n\n"  );
        set("leave_msg",          "奔了過去"                                  );
        set("arrive_msg",         "呼地竄了出來，警惕地四周張望着"                  );
        set("fleeout_message",    "落荒而逃，慘叫聲不斷傳來"                    );
        set("fleein_message",     "搖搖擺擺地跑了過來，伸出舌頭呼呼地喘着粗氣");
}

void setup_beast(object ob)
{
        mapping my;

        my = ob->query_entire_dbase();

        ob->set_default_action(__FILE__, "query_action");
	set("default_actions", (: call_other, __FILE__, "query_action" :), ob);

        my["unit"] = "只";
        
        if( undefinedp(my["gender"]) ) my["gender"] = "雄性";
        if( undefinedp(my["age"]) ) my["age"] = random(40) + 5;

        if( undefinedp(my["str"]) ) my["str"] = random(40) + 5;
        if( undefinedp(my["int"]) ) my["int"] = random(10) + 5;
        if( undefinedp(my["per"]) ) my["per"] = random(30) + 5;
        if( undefinedp(my["con"]) ) my["con"] = random(40) + 5;
        if( undefinedp(my["dex"]) ) my["dex"] = random(40) + 5;
        if( undefinedp(my["kar"]) ) my["kar"] = random(20) + 5;

        if( undefinedp(my["max_jing"]) ) {
                if( my["age"] <= 3 ) my["max_jing"] = 50;
                else if( my["age"] <= 10 ) my["max_jing"] = 50 + (my["age"] - 3) * 20;
                else if( my["age"] <= 30 ) my["max_jing"] = 190 + (my["age"] - 10) * 5;
                else my["max_jing"] = 290 + (my["age"] - 30) * 2;
        }
        if( undefinedp(my["max_qi"]) ) {
                if( my["age"] <= 5 ) my["max_qi"] = 50;
                else if( my["age"] <= 20 ) my["max_qi"] = 50 + (my["age"] - 5) * 25;
                else my["max_qi"] = 425 + (my["age"] - 20) * 5;
        }
        if( undefinedp(my["max_jingli"]) ) {
                if( my["age"] <= 3 ) my["max_jingli"] = 100;
                else if( my["age"] <= 20 ) my["max_jingli"] = 100 + (my["age"] - 3) * 50;
                else my["max_jingli"] = 950 + (my["age"] - 20) * 10;
        }
        ob->set_default_object(__FILE__);
        if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 10)* 2000);
}

mapping query_action(object me)
{
        return combat_action[random(sizeof(combat_action))];
}
