// guileiskill.c
// by Smallfish

#include <ansi.h>
#include <armor.h>

inherit F_CLEAN_UP;

int guilei_dir(object me, string dir, int continueable, int *total);
int guilei_file(object me, string file);
nosave int all_num;        //判斷多少文件給歸類
nosave mapping famskill;
nosave string *valid_types = ({
        "axe",
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
        "array",
});

int main(object me, string arg)
{
        string dir,type,type_name;
        int continueable,i,j;
        int *total = ({0});
        string *fams, *famskills;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        seteuid(geteuid(me));

        continueable = 1;

         if (!arg)
                return notify_fail("格式：guileiskill <路徑名> \n");

               dir=resolve_path(query("cwd", me),arg);

        if (file_size(dir) == -1) return notify_fail("目錄"+ dir + "不存在！\n");

        if (file_size(dir) == -2 && dir[strlen(dir) - 1] != '/') dir += "/";

        famskill = ([]);

        message_system("整理歸類" + type_name + "檔案中，請稍候...");
        if (! guilei_dir(me, dir, continueable, total))
        {
                write(HIR "歸類遇到錯誤中止。\n" NOR);
        }

        fams = keys(famskill);
        log_file("static/guilei/famskills","mapping famskill = ([\n");

        for (i = 0;i < sizeof(fams);i++)
        {
                log_file("static/guilei/famskills",sprintf("        \"%s\": ({\n",fams[i]));
                famskills = famskill[fams[i]];
                for (j = 0;j < sizeof(famskills);j++)
                        log_file("static/guilei/famskills",sprintf("                        \"%s\",\n",famskills[j]));
                log_file("static/guilei/famskills","                 }),\n");
        }
        log_file("static/guilei/famskills","]);");

        if (total[0] > 0)
        {
                write(HIC "總共有" + HIW + total[0] + HIC "個檔案被成功歸類！\n" NOR);
                write(HIC "歸類信息存放在" + HIW + "/log/static/" + type + HIC "之中！\n" NOR);
        } else
                write(HIC "沒有歸類任何檔案。\n" NOR);

        return 1;
}

int guilei_dir(object me, string dir, int continueable, int *total)
{
        int i;
        int l;
        int filecount, compcount;
        mixed *file;
        string filename;

        if (! is_root(previous_object()))
                return 0;

        file = get_dir(dir, -1);
        if (! sizeof(file))
        {
                if (file_size(dir) == -2)
                        write(dir + "這個目錄是空的。\n");
                else
                        write("沒有" + dir + "這個目錄。\n");
                return 1;
        }

        write (HIY "開始檢查目錄" + dir + "下面的所有文件。\n" NOR);
        i = sizeof(file);
        compcount = 0;
        filecount = 0;
        all_num = 0;
        while (i--)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                {
                        filecount++;
                        filename = file[i][0];
                        l = strlen(filename);
                        if (filename[l - 1] != 'c' || filename[l - 2] != '.')
                                continue;

                        if (! guilei_file(me, dir + filename) &&
                            ! continueable)
                                return 0;

                        compcount++;
                        total[0]++;
                        if ((compcount % 70) == 0)
                                write("\n");
                }

                // continue to compile next file
        }
        write(HIC "\n整理了目錄" + dir + "下的" + HIW + filecount + HIC +
              "個文件\n，檢查了其中" + HIW + compcount + HIC +
              "個檔案。\n，歸類了其中" + HIW + all_num + HIC + "個檔案。\n" + NOR );

        i = sizeof(file);
        while (i--)
        {
                reset_eval_cost();
                if (file[i][1] == -2)
                {
                        file[i][0] += "/";
                        write("\n");
                        if (! guilei_dir(me, dir + file[i][0], continueable, total) &&
                            ! continueable)
                                return 0;
                }
        }
        return 1;
}

int guilei_file(object me, string file)
{
        mapping fam,allskill;
        string fam_name,*skillkey,*famskills;
        int i,j;
        object obj;

        if (file == "/cmds/adm/guilei.c")
                // 不自我讀本指令文件
                return 1;

        write (".");

        catch(obj = new(file));
        if (!obj) return 0;
        if (!obj->is_character())
        {
                destruct(obj);
                return 0;
        }
        if( !mapp(fam=query("family", obj)) )
        {
                destruct(obj);
                return 0;
        }

        fam_name = fam["family_name"];

        if (!mapp(allskill = obj->query_skills()))
        {
                destruct(obj);
                return 0;
        }

        all_num++;
        skillkey = keys(allskill);

        for (i = 0;i < sizeof(skillkey); i++)
        {
                for (j = 0; j < sizeof(valid_types);j++)
                {
                        if (SKILL_D(skillkey[i])->valid_enable(valid_types[j]))
                        {
                                if (undefinedp(famskill[fam_name]))
                                {
                                        famskills = ({});
                                        famskills += ({ skillkey[i] });
                                        famskill[fam_name] = famskills;
                                } else
                                {
                                        famskills = famskill[fam_name];
                                        famskills -= ({ skillkey[i] });
                                        famskills += ({ skillkey[i] });
                                        famskill[fam_name] = famskills;
                                }
                                break;
                        }
                }
        }

        destruct(obj);

        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: guilei <路徑|文件名> <room|npc|obj>

這個指令讓你指定對一個文件或者一個目錄下的房間、人物、物品的
屬性進行歸類。
room參數表示歸類房間文件，信息包括文件名、房間名、房間裏的物
品文件名、物品中文名、物品英文名；
npc 參數表示歸類人物文件，信息包括文件名、中文名、英文名、門
派ID、門派中文名、身上物品的文件名、物品ID、物品中文名、人物
的給項HP屬性、人物的主要SCORE屬性；
obj 參數表示歸類物品文件，信息包括文件名、物品ID、物品中文名、
物品的價值等等；

歸類信息存放在/log/static目錄下。
絕地末日：smallfish

HELP );
        return 1;
}