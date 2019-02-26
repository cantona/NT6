// beast.c

#include <race/beast.h>

mapping combat_action =
([
        "angel":([
                "action":        "$N用犄角惡狠狠地向$n一頂",
                "damage":        50,
                "damage_type":        "瘀傷",
        ]),
        "bite": ([
                "action":        "$N撲上來張嘴往$n的$l狠狠地一咬",
                "damage":        20,
                "damage_type":        "咬傷",
        ]),
        "claw": ([
                "action":        "$N用爪子往$n的$l一抓",
                "damage":        40,
                "damage_type":        "咬傷",
        ]),
        "hoof": ([
                "action":        "$N用後腿往$n的$l用力一蹬",
                "damage":        100,
                "damage_type":        "瘀傷",
        ]),
        "knock": ([
                "action":        "$N抬起蹄子往$n的$l一踹",
                "damage":        100,
                "damage_type":        "瘀傷",
        ]),
        "poke": ([
                "action":        "$N用尖嘴往$n的$l一陣猛啄",
                "damage":        30,
                "damage_type":        "抓傷",
        ]),
        "rope": ([
                "action":        "$N用身體纏住了$n用力一勒",
                "damage":        40,
                "damage_type":        "勒傷",
        ]),
        "snap": ([
                "action":        "$N展開四爪，飛身往$n猛裏一撲",
                "damage":        40,
                "damage_type":        "勒傷",
        ]),
        "snoot":([
                "action":        "$N用長鼻子惡狠狠地向$n捲去",
                "damage":        30,
                "damage_type":        "瘀傷",
        ]),
        "sting": ([
                "action":        "$N反轉身用尾巴尖對準$n的$l一刺",
                "damage":        20,
                "damage_type":        "咬傷",
        ]),
        "tail": ([
                "action":        "$N倒豎尾巴，對準$n的$l狠狠一抽",
                "damage":        20,
                "damage_type":        "咬傷",
        ]),
        "wind": ([
                "action":        "$N張開翅膀往$n的$l奮力一扇",
                "damage":        40,
                "damage_type":        "瘀傷",
        ]),
]);

string *actions;

void create()
{
        actions = keys(combat_action);
}

void setup_beast(object ob)
{
        mapping my;

        my = ob->query_entire_dbase();

        my["unit"] = "只";

        if( undefinedp(my["actions"]) )
        {
        set("actions", (:call_other,__FILE__,"query_action":), ob);
        set("default_actions", (:call_other,__FILE__,"query_action":), ob);
                if( pointerp(my["verbs"]) )
                        set("default_actions", (:call_other,__FILE__,"query_action":), ob);
                else
                        my["default_actions"] = ([
                                "action": "$N攻擊$n的%s，%s\n",
                        ]);
        }

        if( undefinedp(my["gender"]) ) my["gender"] = "雄性";
        if( undefinedp(my["age"]) ) my["age"] = random(40) + 5;

        if( undefinedp(my["str"]) ) my["str"] = random(41) + 5;
        if( undefinedp(my["int"]) ) my["int"] = random(11) + 5;
        if( undefinedp(my["per"]) ) my["per"] = random(31) + 5;
        if( undefinedp(my["con"]) ) my["con"] = random(41) + 5;
        if( undefinedp(my["dex"]) ) my["dex"] = random(41) + 5;
        if( undefinedp(my["kar"]) ) my["kar"] = random(21) + 5;
        if( undefinedp(my["cps"]) ) my["cps"] = random(21) + 5;
        if( undefinedp(my["cor"]) ) my["cor"] = random(41) + 5;

        if( undefinedp(my["max_jing"]) ) {
                if( my["age"] <= 3 ) my["max_jing"] = 50;
                else if( my["age"] <= 10 ) my["max_jing"] = 50 + (my["age"] - 3) * 20;
                else if( my["age"] <= 30 ) my["max_jing"] = 190 + (my["age"] - 10) * 5;
                else my["max_jing"] = my["max_jing"] = 290 + (my["age"] - 30);
        }
        if( undefinedp(my["max_qi"]) ) {
                if( my["age"] <= 5 ) my["max_qi"] = 50;
                else if( my["age"] <= 20 ) my["max_qi"] = 50 + (my["age"] - 5) * 25;
                else my["max_qi"] = my["max_qi"] = 425 + (my["age"] - 20) * 5;
        }
        //        NOTE: beast has no initial limbs defined, you must define it yourself.
        //        ob->init_limbs(LIMBS);
        if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 10)* 2000);
}

mapping query_action(object me)
{
        string *act;

        act=query("verbs", me);
        return combat_action[act[random(sizeof(act))]];
}
