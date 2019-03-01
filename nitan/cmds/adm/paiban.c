// Written by Lonely
// typeset.c

#include <ansi.h>

inherit F_CLEAN_UP;

string *deep_file_list(string dir);
int     to_format(object me, string dir, int len);
string *do_format(object me, mixed flist, int len);
int     help(object me);

void create() { seteuid(getuid()); } 

int main(object me, string arg)
{
        string dir;
        int len;
        
        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;
                
        if (! arg || sscanf(arg, "%s %d", dir, len) != 2) 
                return help(me);               

        if (len < 1) return help(me);
                
        if (file_size(dir) == -1)
                dir=resolve_path(query("cwd", me),dir);

        if (file_size(dir) > 0)
        { 
                if (! do_format(me, dir, len))
                        write(HIY "ROOM " + dir + " 的描述整理失敗，詳情請查看LOG記錄。\n" NOR); 
                else
                        write("ok.\n");     
                return 1;
        } 

        if (file_size(dir) == -2 && dir[strlen(dir) - 1] != '/') 
                dir += "/";

        if (file_size(dir) != -2) 
                return notify_fail(dir + " 並不是一個目錄。\n");
                
        if (dir[0..2] != "/d/" && dir[0..2] != "/u/")
                return notify_fail("為確保安全，只允許更改/d/和/u/目錄下面的房間描述。\n");                

        message_system("系統批量檔案處理中，請耐心等候...");                                                                    

        write(HIG "\n現在系統正在批處理 " + dir + " 目錄房間描述，稍後匯報。\n" 
              HIG "進度：" + process_bar(0) + "\n"); 
                            
        if (me)
        {
                me->attach_system();
                me->write_prompt();
        }

        to_format(me, dir, len);
        return 1;
}
 
int to_format(object me, string dir, int len)
{
        int i;
        string *flist, *result;

        flist = deep_path_list(dir);        
        // flist = deep_file_list(dir);
                     
        if (! arrayp(flist) || ! sizeof(flist))
        {
                message_system("系統批量檔案處理完畢，請繼續遊戲。\n" ESC + "[K");  
                
                if (me)
                        me->detach_system();

                write(HIG "目錄 " + dir + " 下並沒有可供修改的文件\n" NOR); 
                return 1;
        }
        
        result = do_format(me, flist, len);
        
        if (me)
                me->detach_system();
                
        message_system("系統批量檔案處理完畢，請繼續遊戲。\n" ESC + "[K");  
        
        if (! sizeof(result))
                write(HIG "目錄 " + dir + " 下所有房間描述整理成功。\n" NOR); 
        else
        {       
                write(HIG "尚有 " + sizeof(result) + " 個文件整理失敗，文件列表如下\n" NOR);           
                for (i = 0; i < sizeof(result); i++)
                {
                        if (eval_cost() < 100) set_eval_limit(0);
                        
                        write(HIG "file : " + dir + result[i] + "\n" NOR); 
 
                }
        }
        return 1;
}

string *do_format(object me, mixed flist, int len)
{
        int i, j, begin1, begin2;
        string *filetext, *temptext;
        string long, err;
        string str1, str2, tempstr;
        string *result = ({ });
        object ob;
        
        if (stringp(flist))
                flist = ({ flist });
                     
        for (i = 0; i < sizeof(flist); i++)
        {
                reset_eval_cost();
                message("system", ESC + "[1A" + ESC + "[256D"
                                  HIG "進度：" + process_bar((i + 1) * 100 / sizeof(flist)) +
                                   "\n" + (me ? HIR "執行中" NOR "> " : ""),
                                   me ? me : filter_array(all_interactive(), (: wizardp :))); 
                
                if (! is_c_file(flist[i])) 
                        continue;
                                                                     
                err = catch(call_other(flist[i], "???"));        
                if (err) 
                {
                        result += ({ flist[i] });
                        continue;
                }
                
                if (! (ob = get_object(flist[i])))
                {
                        result += ({ flist[i] });
                        continue;
                }                
        
                //if( !inherits(ROOM,ob) || !query("long", ob) )
                if( !ob->is_room() || !query("long", ob) )
                {
                        if (clonep(ob) && ! userp(ob)) 
                                destruct(ob);
                        
                        continue;
                }
        
                long=replace_string(query("long", ob),"\n","");
                long = replace_string(long, "“", "『");
                long = replace_string(long, "”", "』");
                long = replace_string(long, "<", "『");
                long = replace_string(long, ">", "』");
                long = replace_string(long, ",", "，");
                long = replace_string(long, ".", "。");
                long = replace_string(long, "?", "？");
                long = replace_string(long, ";", "；");
                long = replace_string(long, ":", "：");
                long = replace_string(long, "!", "！");         
                        
                filetext = explode(read_file(flist[i]), "\n");

                len *= 2;
                temptext = explode(sort_string(long, len, 4) + "\n", "\n");
                temptext -= ({ "" });

                begin1 = 0;
                begin2 = 0;
                for (j = 0;j < sizeof(filetext);j ++)
                {
                        tempstr = "";

                        tempstr = replace_string(filetext[j], " ", "");
                        tempstr = replace_string(tempstr, "\t", "");

                        if (strsrch(tempstr, "set(\"long\",") != -1)
                        {
                                begin1 = j;
                        }
                        if (strsrch(tempstr, "\);") != -1 && begin1)
                        {
                                begin2 = j;
                                break;
                        }
                }

                if (! begin1 || ! begin2) 
                {       
                        result += ({ flist[i] });
                        continue;
                }

                str1 = "        set\(\"long\", @LONG\n";
                str2 = "LONG \);\n";
                rm(flist[i]);

                for (j = 0; j < begin1; j ++)
                        write_file(flist[i], filetext[j] + "\n", 0);
                write_file(flist[i], str1, 0);
                for (j = 0; j < sizeof(temptext); j ++)
                        write_file(flist[i], temptext[j] + "\n", 0);
                write_file(flist[i], str2, 0);
                for (j = begin2 + 1; j < sizeof(filetext); j ++)
                        write_file(flist[i], filetext[j] + "\n", 0);
                        
        }
        return result;
}

string *deep_file_list(string dir)
{
        int i;
        string *flist, *result = ({ });
        string file;
        
        flist = get_dir(dir);
        
        for (i = 0; i < sizeof(flist); i++)
        {
                file = dir + flist[i];
                
                if (file_size(file + "/") == -2)
                        result += deep_file_list(file + "/");
                else 
                        result += ({ file });
        }
        
        return result;
}

int help(object me) 
{
        write(@HELP 
指令格式 : typeset | pb <目錄名> <字數>

這個指令可以將某個目錄下所有的房間的長描述自動排版成每行為指
定數目的漢字，當然第一行是少二個漢字的。
HELP ); 
        return 1; 
}