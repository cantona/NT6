// enable.c

#include <ansi.h>

inherit F_CLEAN_UP;

mapping valid_types = ([
        "unarmed":      "拳腳",
        "sword":        "劍法",
        "arrow":        "箭法",
        "axe":          "斧法",
        "blade":        "刀法",
        "staff":        "杖法",
        "hammer":       "錘法",
        "club" :        "棍法",
        "spear":        "槍法",
        "throwing":     "暗器",
        "force":        "內功",
        "parry":        "招架",
        "dodge":        "輕功",
        "magic":        "法術",
        "whip":         "鞭法",
        "dagger":       "短兵",
        "finger":       "指法",
        "hand":         "手法",
        "cuff":         "拳法",
        "claw":         "爪法",
        "strike":       "掌法",
        "medical":      "醫術",
        "poison":       "毒技",
        "cooking":      "廚藝",
        "chuixiao-jifa" : "吹蕭",
        "guzheng-jifa"  : "古箏",
        "tanqin-jifa"   : "彈琴",
        "array"         : "陣法",
        "taoism"        : "道學心法",
]);

int main(object me, string arg)
{
        mapping map;
        string *types, *skill;
        string ski, map_to;
        string msg;
        int i, modify;

        seteuid(getuid());

        if (! arg)
        {
                map = me->query_skill_map();
                if (! mapp(map) || sizeof(map) == 0)
                        return notify_fail("你現在沒有使用任何特殊技能。\n");

                skill = keys(valid_types);
                msg = "以下是你目前使用中的特殊技能。\n";
                for (i = 0; i < sizeof(skill); i++)
                {
                        if (undefinedp(map[skill[i]]))
                                continue;

                        if (! me->query_skill(skill[i]))
                                continue;

                        modify=query_temp("apply/"+skill[i], me);
                        msg += sprintf("  %-20s： %-20s  有效等級：%s%3d\n" NOR,
                                valid_types[skill[i]] + " (" + skill[i] + ")",
                                undefinedp(map[skill[i]]) ? "無" : to_chinese(map[skill[i]]),
                                (modify==0 ? "" : (modify>0 ? HIC : HIR)),
                                me->query_skill(skill[i]));
                }
                write(msg);
                return 1;
        }

        if (arg == "?" )
        {
                msg = "以下是可以使用特殊技能的種類：\n";
                skill = sort_array(keys(valid_types), (: strcmp :) );
                for (i = 0; i < sizeof(skill); i++)
                        msg += sprintf("  %s (%s)\n", valid_types[skill[i]], skill[i]);
                write(msg);
                return 1;
        }

        if (sscanf(arg, "%s %s", ski, map_to) != 2)
                return notify_fail("指令格式：enable|jifa [<技能種類> <技能名稱>|none]\n");

        if (undefinedp(valid_types[ski]))
                return notify_fail("沒有這個技能種類，用 enable ? 可以查看有哪些種類。\n");

        if (map_to == "none")
        {
                me->map_skill(ski);
                me->reset_action();
                write(HIW "你從現在起取消" HIG + CHINESE_D->chinese(ski) +
                      HIW "的特殊技能。\n"NOR);
                return 1;
        } else if (map_to == ski)
        {
                write("「" + to_chinese(ski) + "」是所有" + valid_types[ski] +
                      "的基礎，不需要 enable。\n");
                return 1;
        }

        if (me->query_skill_mapped(ski) == map_to)
                return notify_fail("你現在正激發這種技能呢。\n");

        if (me->query_skill(map_to, 1) < 1)
                return notify_fail("你不會這種技能。\n");

        if (me->query_skill(ski, 1) < 1)
                return notify_fail("你還不會半點" + to_chinese(ski) + "呢。\n");

        if (! SKILL_D(map_to)->valid_enable(ski))
                return notify_fail("這個技能不能當成這種用途。\n");

        me->map_skill(ski, map_to);
        me->reset_action();
        write(HIW "你從現在起用" HIR + CHINESE_D->chinese(map_to) +
              HIW "作為" HIG + CHINESE_D->chinese(ski) + HIW "的特殊技能。\n" NOR);

        if (ski == "magic")
        {
                write("你改用另一種法術系，精力必須重新鍛練。\n");
                set("jingli", 0, me);
                me->receive_damage("jing", 0);
        }
        else if (ski == "force")
        {
                write("你改用另一種內功，內力必須重新鍛練。\n");
                set("neili", 0, me);
                me->receive_damage("qi", 0);
        }

        return 1;
}
int help(object me)
{
        write(@HELP
指令格式 : enable|jifa [<技能種類> <技能名稱> | none]
           enable|jifa ?

這個指令讓你指定所要用的技能，需指明技能種類和技能名稱。如果不加參
數則會顯示出技能種類及你目前所使用的技能名稱 ，如果加一個？會列出
所有能使用特殊技能的技能種類。

HELP );
        return 1;
}