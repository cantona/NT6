// by rcwiz for yhonline
// 入夢神功

#include <ansi.h>

inherit FORCE;

string *dodge_msg = ({
        HIW "$n" HIW "手足忽的一晃，$N" HIW "竟然無法進擊，只能自保。\n" NOR,
        HIW "只見$n" HIW "身子輕輕晃動，$N" HIW "眼前頓時出現了無數個$n" HIW
        "的幻影，令$N" HIW "完全無法辨出虛實。\n" NOR,
        HIW "$n" HIW "往旁邊歪歪斜斜的邁出一步，卻恰好令$N" HIW "的攻擊失之"
        "毫釐。\n" NOR,
        HIW "$N" HIW "這一招來的好快，然後$n" HIW "一閃，似乎不費半點力氣，"
        "卻將$N" HIW "這一招剛好避開。\n" NOR,
        HIW "但見$n" HIW "輕輕一躍，已不見了蹤影，$N" HIW "心中大駭，卻又見"
        "$n" HIW "擦肩奔過，步法之奇巧，當真令人思索菲儀。\n" NOR,
});

string *parry_msg = ({
        HIW "$N" HIW "一招擊在$n" HIW "身上，力道竟消失得無影無蹤！\n" NOR,
        HIW "$n輕輕一帶，$N" HIW "發現自己招數回擊過來，嚇得往後倒退幾步。\n" NOR,
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bagua-shengong", 1);
        return lvl * lvl * 15 * 40 / 100 / 200;
}

mapping *action = ({
([
        "action": HIW "$N" HIW "單手一揮，剎那間狂風驟起， 令人不寒而慄。" NOR,
        "attack": 999,
        "dodge" : 999,
        "parry" : 999,
        "damage": 999,
        "force" : 999,
        "damage_type":  "神傷"
]),
([
        "action": HIG "$N" HIG "神情微變，猛然間狂風暴雨，天色大變。" NOR,
        "attack": 999,
        "dodge" : 999,
        "parry" : 999,
        "damage": 999,
        "force" : 999,
        "damage_type":  "神傷"
]),
});

string *usage_skills = ({ "unarmed", "strike", "claw", "hand", "cuff", "finger",
                          "sword", "blade", "hammer", "throwing", "club", "whip",
                          "staff", "dodge", "dagger", "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force)
{
        return 1;
}

int double_attack()
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object ob;
        int lvl;
        
        lvl = me->query_skill("force");
        
        if( query_temp("baguazhen", victim) >= 3 )
        {
                if (lvl / 2 + random(lvl) > victim->query_skill("force") )
                {
                      if (random(2))
                      {
                           victim->receive_wound("qi", 300);
                           addn("jing", -50, victim);
                      }
                      else 
                      {
                           message_vision(HIR "$N" HIR "對着$n" HIR "需點幾下，$n" HIR 
                                          "竟無法動彈了。\n" NOR, me, victim);
                                     
                           victim->start_busy(20 + random(20));                                            
                      }
                }
                return;
        }

        if (random(20) == 1)
        {
                message_vision(NOR + HIG "猛然間一陣青煙飄過，諸葛亮已"
                               "經不見了影蹤 ……\n", me, victim);               

                victim->move("/kungfu/class/sky/bagua");

                return;                
        }

        victim->receive_wound("qi", 500);
        addn("jing", -30, victim);

        return;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;

        if (random(10) == 0)
        {
                result = ([ "damage": -damage ]);

                result += (["msg" : HIW "$n" HIW "凌空虛點幾下，猛然間不見了蹤影。\n" NOR]);

                return result;
        }
}


