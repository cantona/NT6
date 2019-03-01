// wuchang-zhang.c 無常杖法

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"$N微一躬身，一招"HIG"「庸人自擾」"NOR"，$w帶著刺耳的吱吱聲，擦地掃向$n的腳踝",
        "lvl" : 0,
        "skill_name" : "庸人自擾"
]),
([        "action":"$N一招"HIM"「想入非非」"NOR"，右手托住杖端，左掌居中一擊，令其憑慣性倒向$n的肩頭",
        "lvl" : 7,
        "skill_name" : "想入非非"
]),
([        "action":"$N一招"HIR"「六神不安」"NOR"，舉起$w乒乒乓乓地滿地亂敲，讓$n左閃右避，狼狽不堪",
        "lvl" : 14,
        "skill_name" : "六神不安"
]),
([        "action":"$N一招"HIY"「面無人色」"NOR"，舉起$w，呆呆地盯了一會，突然猛地一杖打向$n的$l",
        "lvl" : 20,
        "skill_name" : "面無人色"
]),
([        "action":"$N將$w頂住自己的胸膛，一端指向$n，一招"HIB"「心驚肉跳」"NOR"，大聲叫喊著沖向$n",
        "lvl" : 25,
        "skill_name" : "心驚肉跳"
]),
([        "action":"$N一招"HIC"「行屍走肉」"NOR"，全身僵直，蹦跳著持杖前行，冷不防舉杖攔腰向$n劈去",
        "lvl" : 30,
        "skill_name" : "行屍走肉"
]),
([        "action":"$N面帶戚色，一招"HIM"「飲恨吞聲」"NOR"，趁$n說話間，一杖向$n張大的嘴巴捅了過去",
        "lvl" : 35,
        "skill_name" : "飲恨吞聲"
]),
([        "action":"$N一招"HIW"「力不從心」"NOR"，假意將$w摔落地上，待$n行來，一腳勾起，擊向$n的$l",
        "lvl" : 40,
        "skill_name" : "力不從心"
]),
([        "action":"$N伏地裝死，一招"HIG"「窮途沒路」"NOR"，一個翻滾，身下$w往橫裡打出，揮向$n的襠部",
        "lvl" : 45,
        "skill_name" : "窮途沒路"
]),
([        "action":"$N一招"HIR"「呆若木雞」"NOR"，身不動，腳不移，$w卻直飛半空，不偏不倚地砸向$n的$l",
        "lvl" : 50,
        "skill_name" : "呆若木雞"
]),
([        "action":"$N高舉$w，一招"HIG"「人鬼殊途」"NOR"，身形如鬼魅般飄出，對準$n的天靈蓋一杖打下",
        "lvl" : 55,
        "skill_name" : "人鬼殊途"
]),
([        "action":"$N一招"HIB"「我入地獄」"NOR"，單腿獨立，$w舞成千百根相似，根根砸向$n全身各處要害",
        "lvl" : 60,
        "skill_name" : "我入地獄"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("staff", 1) < (int)(int)me->query_skill("wuchang-zhang", 1))
                return notify_fail("你的基本杖法水平有限，無法領會更高深的無常杖法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<40 || query("neili", me)<30 )
                return notify_fail("你的內力或氣不夠練無常杖法。\n");
        me->receive_damage("qi", 35);
        addn("neili", -15, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -40;
        int d_e2 = -5;
        int p_e1 = 20;
        int p_e2 = 50;
        int f_e1 = 250;
        int f_e2 = 300;
        int m_e1 = 170;
        int m_e2 = 270;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("wuchang-zhang", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : "挫傷",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

void skill_improved(object me)
{
        if( (int)me->query_skill("zui-gun", 1) >= 200
        &&  (int)me->query_skill("wuchang-zhang", 1) >= 200
         && !query("sl_gift/zg", me)){
                addn("dex", 1, me);
                set("sl_gift/zg", 1, me);
                tell_object(me, "你的醉棍和無常杖學有所成，提高了你的身法。\n");
        }
}

string perform_action_file(string action)
{
        return __DIR__"wuchang-zhang/" + action;
}

int help(object me)
{
        write(HIC"\n無常杖法："NOR"\n");
        write(@HELP

    無常杖法為少林七十二絕技之一。

        學習要求：
                混元一氣功20級
                內力100
HELP
        );
        return 1;
}
