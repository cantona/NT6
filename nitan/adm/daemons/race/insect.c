// insect.c 昆蟲

#ifndef __INSECT__
#define __INSECT__

// A normal insect is at least 1 g weight
#define BASE_WEIGHT 1
#endif

inherit F_DBASE;

mapping *combat_action_crawl = ({
([
        "action":                "$N爬上來張嘴往$n的$l狠狠地一咬",
        "damage":                30,
        "damage_type":        "咬傷",
]),
([
        "action":                "$N躍上來猛地往$n的$l叮了一下",
        "damage":                10,
        "damage_type":        "刺傷",
]),
([
        "action":                "$N反轉身用尾巴尖對準$n的$l一刺",
        "damage":                20,
        "damage_type":        "刺傷",
]),  
});

mapping *combat_action_fly = ({
([
        "action":                "$N飛過來張嘴往$n的$l狠狠地一咬",
        "damage":                30,
        "damage_type":        "咬傷",
]),
([
        "action":                "$N飛上來猛地往$n的$l叮了一下",
        "damage":                10,
        "damage_type":        "刺傷",
]),
([
        "action":                "$N反轉身用尾巴尖對準$n的$l一刺",
        "damage":                20,
        "damage_type":        "刺傷",
]),  
});

void create()
{
        seteuid(getuid());
        set("attitude", "heroism");
}

void setup_insect(object ob)
{
        mapping my;

        my = ob->query_entire_dbase();

        ob->set_default_action(__FILE__, "query_action");
	set("default_actions", (: call_other, __FILE__, "query_action" :), ob);
        
        my["unit"] = "只";
        
        if( undefinedp(my["gender"]) ) my["gender"] = (random(2))?"雌性":"雄性";
        if( undefinedp(my["age"]) ) my["age"] = random( 5) + 5;

        if( undefinedp(my["str"]) ) my["str"] = random( 5) + 5;
        if( undefinedp(my["int"]) ) my["int"] = random( 5) + 5;
        if( undefinedp(my["per"]) ) my["per"] = random( 5) + 5;
        if( undefinedp(my["con"]) ) my["con"] = random(10) + 5;
        if( undefinedp(my["dex"]) ) my["dex"] = random(15) + 5;
        if( undefinedp(my["kar"]) ) my["kar"] = random(10) + 5;

        if( undefinedp(my["max_jing"]) ) {
                if( my["age"] <= 5 ) my["max_jing"] = my["age"] * 5;
                else my["max_jing"]  = 25;
        }
        if( undefinedp(my["max_qi"]) ) {
                if( my["age"] <= 5 ) my["max_qi"] = my["age"] * 5;
                else my["max_qi"]  = 25;
        }
        if( undefinedp(my["max_jingli"]) ) {
                if( my["age"] <= 5 ) my["max_jingli"] = my["age"] * 5;
                else my["max_jingli"]  = 25;
        }
        ob->set_default_object(__FILE__);
        if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 5)* 100);

        if( query("subrace", ob) == "爬蟲"){
                set("dead_message",       "\n$N四腳朝天地翻了過來，死了。\n\n"        );
                set("unconcious_message", "\n$N四腳朝天地翻了過來，不動了。\n\n"      );
                set("revive_message",     "\n$N一下翻過身，又敏捷地四處爬動起來。\n\n");
                set("leave_msg",          "的草叢裏鑽了出去"            );
                set("arrive_msg",         "爬了過來"                              );
                set("fleeout_message",    "的草叢裏鑽了出去"            );
                set("fleein_message",     "緩緩爬了過來，動作有些遲滯"            );

                set("limbs", ({"頭部",        "背部",        "腹部", "觸角", "前腿",        "後腿", "尾巴"}) );
        }

        if( query("subrace", ob) == "飛蟲"){
                set("dead_message",       "\n$N掉在地上，掙扎了幾下就死了。\n\n"      );
                set("unconcious_message", "\n$N撲的跌在地上，昏了過去。\n\n"          );
                set("revive_message",     "\n$N張開翅膀撲騰了一下，又飛了起來。\n\n"  );
                set("leave_msg",          "嗡嗡嗡地叫着飛了出去"              );
                set("arrive_msg",         "嗡嗡地叫着飛了過來"                    );
                set("fleeout_message",    "嗡嗡地叫着飛了出去"                );
                set("fleein_message",     "緩緩飛了過來，動作有些遲滯"            );

                set("limbs", ({"頭部",        "背部",        "腹部",        "翅膀", "前腿",        "後腿", "尾巴"}) );
        }
}

mapping query_action(object me)
{
        if( query("subrace", me) == "爬蟲")return combat_action_crawl[random(sizeof(combat_action_crawl))];
        if( query("subrace", me) == "飛蟲")return combat_action_fly[random(sizeof(combat_action_fly))];
}
