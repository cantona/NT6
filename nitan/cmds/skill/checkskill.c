// checkskill.c
// Created by smallfish.
// Updated by jjgod. 2002/11/30.
// Updated by Lonely

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

string *valid_types = ({
        "force",
        "dodge",
        "unarmed",
        "cuff",
        "strike",
        "finger",
        "hand",
        "claw",
        "sword",
        "blade",
        "staff",
        "hammer",
        "club",
        "whip",
        "dagger",
        "throwing",
        "parry",
        "magic",
        "medical",
        "poison",
        "chuixiao-jifa",
        "tanqin-jifa",
        "guzheng-jifa",
        "cooking",
});

// 查詢技能的特性

// 鍵名代表呼叫此技能的函數名，須返回一個非 0 的結果
// 才會有輸出。對應名代表輸出的結果。

// $N 表示輸出查詢結果， $C 表示輸出查詢結果的中文，
// $S 表示排版後的查詢結果。
mapping skill_features = ([
        "type"              : "$C技能",
        "double_attack"     : "快速攻擊",
        "main_skill"        : "主技能為$C",
        "query_description" : "$S",
]);

// 這裏是為了按順序顯示
string *features = ({ "type", "double_attack", "main_skill", "query_description",  });

// 開頭的內容，為了保持對齊而設定
#define PREFIX_STR      "\t      "
// 每行的長度
#define LINE_LEN        40
// 表示合併使用的字符
#define COMBINE_STR     "，"
// 表示並列使用的字符
#define APPOSE_STR      " - "
// 水平線
#define HORIZONTAL_STR  HIC "──────────────"\
                        "───────────────\n" NOR

string sort_result(string str, int prefix);
string skill_combines(object sk);
string skill_enables(object sk);

mapping valid_type = ([
        "unarmed":      "拳腳", "medical":      "醫術",
        "claw":         "爪功", "cuff":         "拳功",
        "finger":       "指功", "strike":       "掌功",
        "hand":         "手功", "leg":          "腿功",
        "sword":        "劍法", "blade":        "刀法",
        "dagger":       "短兵", "brush":        "筆法",
        "spear":        "槍法", "hook":         "鈎法",
        "stick":        "棒法", "staff":        "杖法",
        "club" :        "棍法", "throwing":     "暗器",
        "whip":         "鞭法", "axe":          "斧法",
        "hammer":       "錘法", "force":        "內功",
        "dodge":        "輕功", "parry":        "招架",
        "poison":       "毒技", "cooking":      "廚藝",
        "chuixiao-jifa":"吹蕭", "guzheng-jifa": "古箏",
        "tanqin-jifa":  "彈琴",
]);

int main(object me, string arg)
{
        string  file, dir, filename;
        string  msg, msg1;
        string  type;
        int     i, l, is_force, prefix;
        int     perform, exert;
        mixed   *all_file;
        string  *sub_skills, sub_skill;
        string  feature, temp, *feature_list;
        mixed   value;
        mapping sub_skill_list;
        object  sk;
        string  enable, combo;

        seteuid(getuid());

        if (! arg)
                return notify_fail("指令格式：checkskill <技能名稱> | <技能中文名>\n");

        if (! stringp(file = SKILL_D(arg)) || file_size(file + ".c") <= 0)
        {
                // 英文的找不到？那就找中文名
                if (! stringp(arg = CHINESE_D->find_skill(arg)))
                        return notify_fail("沒有這種技能存在。\n");

                write("Original: " + arg + "\n");
                // 根據中文名找到了英文名，看看是否真的有此技能
                if (! stringp(file = SKILL_D(arg)) || file_size(file + ".c") <= 0)
                        return notify_fail("沒有這種技能存在。\n");
        }

        msg = WHT + to_chinese(arg) + "(" + arg + ")的詳細屬性如下：\n" NOR;
        msg += HORIZONTAL_STR;
        msg += CYN + "  技能名稱：  " WHT + to_chinese(arg) + "(" + arg + ")\n" + NOR;

        is_force = 0;

        if (SKILL_D(arg)->valid_enable("force"))
                is_force = 1;

        // 獲取技能特性列表
        feature_list = ({ });
        foreach (feature in features)
        {
                if (value = call_other(SKILL_D(arg), feature))
                {
                        temp = skill_features[feature];

                        if (stringp(value))
                        {
                                temp = replace_string(temp, "$N", value);
                                temp = replace_string(temp, "$C", to_chinese(value));

                                if (strsrch(temp, "$S") != -1)
                                {
                                        prefix = strlen(implode(feature_list, COMBINE_STR)) +
                                                 strlen(COMBINE_STR);
                                        // 求取每行的餘數
                                        prefix %= LINE_LEN;
                                        temp = replace_string(temp, "$S",
                                                              sort_result((string)value, prefix));
                                }
                        }
                        feature_list += ({ temp });
                }
        }

        if (sizeof(feature_list))
                msg += CYN "\n  技能特性：  " WHT + implode(feature_list, COMBINE_STR) +
                       "\n" NOR;

        sk = get_object(SKILL_D(arg));

        combo = skill_combines(sk);

        if (combo != "")
        {
                msg += CYN "\n  技能互備：  " WHT + combo + "\n" NOR;
        }

        enable = skill_enables(sk);

        if (enable != "")
        {
                msg += CYN "\n  特殊技能：  " WHT + enable + "\n" NOR;
        }

        if (member_array(arg, valid_types) != -1)
        {
                msg += CYN "\n  技能所屬：  " WHT "基本技能\n" NOR;
                msg += HORIZONTAL_STR;
                write(msg);
                return 1;
        }

        /*
        // 暫時限制玩家不能查看自己沒有的武功的絕招
        if (! wizardp(me) && me->query_skill(arg) <= 0)
        {
                msg += HORIZONTAL_STR;
                write(msg);
                return 1;
        }
        */

        sub_skill_list = SKILL_D(arg)->query_sub_skills();
        if (mapp(sub_skill_list) && sizeof(sub_skill_list))
        {
                sub_skills = keys(sub_skill_list);
                msg += CYN "\n  技能合成：  " WHT;
                foreach (sub_skill in sub_skills)
                {
                        if (file_size(SKILL_D(sub_skill) + ".c") <= 0)
                                continue;

                        msg += to_chinese(sub_skill) + "(" +
                               sub_skill + ")\n" + PREFIX_STR;
                }
                msg += NOR;
        }

        // 查詢技能的 pfm 情況
        msg1 = "";
        perform = 0;
        dir = file;

        if (dir[strlen(dir) - 1] != '/')
                dir += "/";

        if (is_force)
                dir += "perform/";

        if (file_size(dir) != -2)
                msg1 += "";
        else
        {
                all_file = get_dir(dir);
                if (! sizeof(all_file))
                        msg1 += "";
                else
                {
                        for (i = 0; i < sizeof(all_file); i++)
                        {
                                if (i == 7) msg1 += "\n\t   ";
                                else if (i > 7 && i % 7 == 0)
                                        msg1 += "\n\t   ";

                                filename = all_file[i];
                                l = strlen(filename);
                                if (filename[l - 1] == 'c' && filename[l - 2] == '.')
                                {
                                        perform++;
                                        msg1 += (i == 0 ? "" : WHT + APPOSE_STR);
                                        msg1 += sprintf(WHT "%s" NOR, filename[0..l - 3]);
                                }
                        }

                        if (msg1 != "")
                        {
                                msg += CYN "\n  技能絕招：  " NOR;
                                msg += msg1;
                                msg += "\n";
                        }
                }
        }

        // 查詢內功的 exert 情況
        if (! is_force)
        {
                msg += HORIZONTAL_STR;
                if (perform) msg += WHT "共有" + chinese_number(perform) + "項絕招。\n" NOR;
                write(msg);
                return 1;
        }

        msg1 = "";
        exert = 0;
        dir = file;

        if (dir[strlen(dir) - 1] != '/')
                dir += "/";

        if (file_size(dir + "exert/") == -2)
                all_file = get_dir(dir + "exert/");
        else
        if (file_size(dir) == -2)
                all_file = get_dir(dir);
        else
        {
                msg += HORIZONTAL_STR;
                write(msg);
                return 1;
        }

        if (! sizeof(all_file))
        {
                write(msg);
                return 1;
        }

        for (i = 0; i < sizeof(all_file); i++)
        {
                filename = all_file[i];
                l = strlen(filename);
                if (filename[l - 1] == 'c' && filename[l - 2] == '.')
                {
                        exert++;
                        msg1 += (i == 0 ? "" : WHT + APPOSE_STR);
                        msg1 += sprintf(WHT "%s" NOR, filename[0..l - 3]);
                }
        }

        if (msg1 != "")
        {
                msg += CYN "\n  內功功能：  " NOR;
                msg += msg1;
                msg += "\n";
        }

        msg += HORIZONTAL_STR;

        if (perform)
        {
                msg += WHT "共有" + chinese_number(perform) + "項技能絕招";
                if (exert)
                        msg += "，" + chinese_number(exert) + "項內功功能。\n" NOR;
                else msg += "。\n" NOR;
        } else
        if (exert)
                msg += WHT "共有" + chinese_number(exert) + "項內功功能。\n" NOR;

        write(msg);
        return 1;
}

string skill_combines(object sk)
{
        int i, j;
        string str, *skills;
        mapping skill;

        skill = this_player()->query_skills();
        if (! mapp(skill) || sizeof(skill) < 1)
                return "";

        skills = keys(skill);

        for (i = 0; i < sizeof(skills); i++)
        {
                if (sk->valid_combine(skills[i]))
                        continue;

                skills[i] = 0;
        }

        skills -= ({ 0 });
        j = sizeof(skills);

        if (! j || j < 1)
                return "";

        str = "";
        for (i = 0; i < j; i++)
        {
                if (i == 2) str += "\n\t      ";
                else if (i > 2 && i % 2 == 0)
                        str += "\n\t      ";

                str += sprintf("%-14s ", CHINESE_D->chinese(skills[i]) + "(" + skills[i] + ")");

                /*
                if (i < j -1)
                        str += "- ";
                */
        }

        return str;
}

string skill_enables(object sk)
{
        int i, j;
        string str, *skills;

        skills = keys(valid_type);

        for (i = 0; i < sizeof(skills); i++)
        {
                if (sk->valid_enable(skills[i]))
                        continue;

                skills[i] = 0;
        }

        skills -= ({ 0 });
        j = sizeof(skills);

        if (! j || j < 1)
                return "";

        str = "";
        for (i = 0; i < j; i++)
        {
                if (i == 3) str += "\n\t      ";
                else if (i > 3 && i % 3 == 0)
                        str += "\n\t      ";

                str += sprintf("%-14s ", valid_type[skills[i]] + "(" + skills[i] + ")");

                /*
                if (i < j -1)
                        str += "- ";
                */
        }

        return str;
}

string sort_result(string str, int prefix)
{
        string *str_list;

        str = replace_string(str, "\r", "");
        str = replace_string(str, "\n\n", "$EOP");
        str = replace_string(str, "\n", "");
        str = replace_string(str, "$EOP$", "\n\n");

        str = sort_string(str, LINE_LEN, prefix);

        str_list = explode(str, "\n");
        str = implode(str_list, "\n" + PREFIX_STR);

        return str;
}

string input_file(string file)
{
        if (! previous_object() ||
            geteuid(previous_object()) != "Kungfu")
                return 0;

        return read_file(file);
}

int help(object me)
{
        write(@HELP
指令格式：checkskill <技能名稱> | <技能中文名>

這個指令讓你檢查指定的某種技能或技能（技能名稱可輸入中
文名）。如果你是巫師，或者本身具備這項技能，則會顯示出
該技能的絕招及作為內功的特殊功能。同時，你還可以查到技
能相關的一些特性，比如技能的類型、是否雙倍攻擊速度、主
技能是什麼等等，若這個技能內定義了相關的描述的話，你還
可以查到關於這個技能的一些掌故。

另外，如果這個技能是一個可被演練合併的技能，則可以顯示
出需用哪些技能來進行演練。

相關指令：skills

HELP);
        return 1;
}

