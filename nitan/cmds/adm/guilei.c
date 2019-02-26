// guilei.c
// by Smallfish

#include <ansi.h>
#include <armor.h>

inherit F_CLEAN_UP;

int guilei_dir(object me, string dir, string type, int continueable, int *total);
int guilei_file(object me, string file, string type);
nosave int all_num;        //判斷多少文件給歸類

int main(object me, string arg)
{
        string dir,type,type_name;
        int continueable;
        int *total = ({0});

           if (! SECURITY_D->valid_grant(me, "(admin)"))
              return 0;

        seteuid(geteuid(me));
        write("guilei 命令 v1.0  \n小魚兒(smallfish)於2002年1月8號編寫。\n"+"主頁：http://www.jdmr.com\n郵件：cunsun@sina.com\n");

        continueable = 1;
         if (!arg || !(sscanf(arg,"%s %s",dir,type) == 2))
                return notify_fail("格式：guilei <路徑> room|npc \n");

               dir=resolve_path(query("cwd", me),dir);

        if (dir[strlen(dir) - 1] != '/')
                dir += "/";

        if (file_size(dir) != -2)
                return notify_fail("沒有" + dir + "這個路徑。\n");

        //歸類類型
        switch(type)
        {
                case "room":
                        type_name = "房間";
                        break;
                case "npc":
                        type_name = "NPC";
                        break;
                case "obj":
                        type_name = "物品";
                        break;
                default:
                        return notify_fail("格式：guilei <路徑> room|npc \n");
        }

        set("cwd", dir, me);

        message_system("整理歸類" + type_name + "檔案中，請稍候...");
        if (! guilei_dir(me, dir, type, continueable, total))
        {
                write(HIR "歸類遇到錯誤中止。\n" NOR);
        }

        if (total[0] > 0)
        {
                write(HIC "總共有" + HIW + total[0] + HIC "個檔案被成功歸類！\n" NOR);
                write(HIC "歸類信息存放在" + HIW + "/log/static/" + type + HIC "之中！\n" NOR);
        } else
                write(HIC "沒有歸類任何檔案。\n" NOR);

        return 1;
}

int guilei_dir(object me, string dir, string type, int continueable, int *total)
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

                        if (! guilei_file(me, dir + filename, type) &&
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
                        if (! guilei_dir(me, dir + file[i][0], type, continueable, total) &&
                            ! continueable)
                                return 0;
                }
        }
        return 1;
}

int guilei_file(object me, string file, string type)
{
        string document,err,logfile,armor_type;
        mapping all_obj,bookskill;
        string *ob_list;
        string the_id,the_name,the_object,file_name;
        int i,is_ok,num;
        object obj,*inv;

        if (file == "/cmds/adm/guilei.c")
                // 不自我讀本指令文件
                return 1;

        write (".");

        //歸類房間文件
        if (type == "room"){
                document = read_file(file);
                if (!document) return 0;
                is_ok = strsrch(document,"inherit ROOM",1);

                if (is_ok > 0) {
                        all_num ++;
                        file_name=query("short", get_object(file));
                        all_obj=query("objects", get_object(file));
                        if (!mapp(all_obj)) return 0;
                        ob_list = keys(all_obj);
                        for (i = 0; i < sizeof(ob_list); i++) {
                                the_object = ob_list[i] + ".c";
                                the_name = the_object->name(1);
                                the_id=query("id", get_object(the_object));
                                log_file("static/room", sprintf("%s|%s|%s|%s|%s\n",
                                        file,
                                        file_name,
                                        the_object,
                                        the_name,
                                        the_id,
                                ));
                        }
                }
        }

        //歸類NPC文件
        if (type == "npc")
        {
                document = read_file(file);
                if (!document) return 0;
                is_ok = strsrch(document,"inherit NPC",1);

                if (is_ok > 0)
                {
                        all_num ++;
                        obj = new(file);
                        if (!obj) return 0;
                        log_file("static/npc", sprintf("%s|%s|%s|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%s|%s|%s\n",
                                file,
                                query("id", obj),
                                query("name", obj),
                                query("combat_exp", obj),
                                query("jing", obj),
                                query("eff_jing", obj),
                                query("qi", obj),
                                query("eff_qi", obj),
                                query("jingli", obj),
                                query("max_jingli", obj),
                                query("neili", obj),
                                query("max_neili", obj),
                                query("shen", obj),
                                query("gender", obj),
                                query("race", obj),
                                query("family/family_name", obj )
                        ));

                        inv = all_inventory(obj);
                        if (sizeof(inv)) {
                                for (i = 0; i < sizeof(inv); i++)
                                {
                                        log_file("static/npc_obj", sprintf("%s|%s.c|%s|%s\n",
                                                file,
                                                base_name(inv[i]),
                                                query("id", inv[i]),
                                                inv[i]->name(1)
                                        ));
                                }
                        }

                        all_obj=query("vendor_goods", obj);
                        if (!mapp(all_obj)) return 0;
                        ob_list = keys(all_obj);
                        for (i = 0; i < sizeof(ob_list); i++) {
                                the_object = ob_list[i] + ".c";
                                log_file("static/npc_obj", sprintf("%s|%s|%s|%s\n",
                                        file,
                                        the_object,
                                        query("id", get_object(the_object)),
                                        the_object->name(1)
                                ));
                        }
                        destruct(obj);
                }
        }

        //歸類物品文件
        if (type == "obj"){
            if (strsrch(file, "/d/wizard/") > 0) return 0;
            if (strsrch(file, "/d/room/") > 0) return 0;
            if (strsrch(file, "/d/pk/") > 0) return 0;
            if (strsrch(file, "/d/death/") > 0) return 0;
            err = catch(obj = new(file));
            if (err) return 0;
            if (!obj) return 0;
            if (stringp(obj->query_save_file()))
            {
                destruct(obj);
                return 0;
            }

            //歸類ARMOR類物品
            if( mapp(query("armor_prop", obj)) && stringp(armor_type=query("armor_type", obj)) )
            {

                if (armor_type != "head" &&
                    armor_type != "neck" &&
                    armor_type != "cloth" &&
                    armor_type != "armor" &&
                    armor_type != "surcoat" &&
                    armor_type != "waist" &&
                    armor_type != "wrists" &&
                    armor_type != "shield" &&
                    armor_type != "hands"
                    ) {
                            destruct(obj);
                            return 0;
                    }

                switch(armor_type)
                {
                        case "head":
                                logfile = "head";
                                break;
                        case "neck":
                                logfile = "head";
                                break;
                        case "cloth":
                                logfile = "cloth";
                                break;
                        case "armor":
                                logfile = "armor";
                                break;
                        case "surcoat":
                                logfile = "armor";
                                break;
                        case "waist":
                                logfile = "armor";
                                break;
                        case "wrists":
                                logfile = "armor";
                                break;
                        case "shield":
                                logfile = "armor";
                                break;
                        case "hands":
                                logfile = "armor";
                                break;
                        default:
                                destruct(obj);
                                return 0;
                }

                num = 0;
                inv = children(file);
                if (!inv)
                    num = 0;
                else
                {
                    i = sizeof(inv);
                    if (i <= 0)
                        num = 0;
                    else {
                        while(i--)
                                if (environment(inv[i])) num++;
                    }
                }


                log_file("static/guilei/"+logfile, sprintf("        \"%s\":,\n",
                        file,
                ));

                all_num ++;
            }

            //歸類兵器
            if( mapp(query("weapon_prop", obj)) && stringp(armor_type=query("skill_type", obj)) )
            {

                if (armor_type != "blade" &&
                    armor_type != "club" &&
                    armor_type != "hammer" &&
                    armor_type != "staff" &&
                    armor_type != "sword"
                    ) {
                            destruct(obj);
                            return 0;
                    }

                switch(armor_type)
                {
                        case "blade":
                                logfile = "blade";
                                break;
                        case "club":
                                logfile = "staff";
                                break;
                        case "hammer":
                                logfile = "hammer";
                                break;
                        case "staff":
                                logfile = "staff";
                                break;
                        case "sword":
                                logfile = "sword";
                                break;
                        default:
                                destruct(obj);
                                return 0;
                }

                num = 0;
                inv = children(file);
                if (!inv)
                    num = 0;
                else
                {
                    i = sizeof(inv);
                    if (i <= 0)
                        num = 0;
                    else {
                        while(i--)
                                if (environment(inv[i])) num++;
                    }
                }

                log_file("static/guilei/"+logfile, sprintf("        \"%s\":,\n",
                        file,
                ));

                all_num ++;
            }

            //歸類書本
            if( mapp(bookskill=query("skill", obj)) )
            {
                if (undefinedp(bookskill["name"]) )
                {
                        destruct(obj);
                        return 0;
                }

                armor_type=query("skill/name", obj);
                if (file_size(SKILL_D(armor_type) + ".c") <= 0)
                {
                        destruct(obj);
                        return 0;
                }

                switch(SKILL_D(armor_type)->type())
                {
                        case "knowledge":
                                logfile = "knowledge";
                                break;
                        default:
                                logfile = "miji";
                                break;
                }

                num = 0;
                inv = children(file);
                if (!inv)
                    num = 0;
                else
                {
                    i = sizeof(inv);
                    if (i <= 0)
                        num = 0;
                    else {
                        while(i--)
                                if (environment(inv[i])) num++;
                    }
                }

                log_file("static/guilei/"+logfile, sprintf("        \"%s\":,\n",
                        file,
                ));

                all_num ++;
            }
                destruct(obj);
        }
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