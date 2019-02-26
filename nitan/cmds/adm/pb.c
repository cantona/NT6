// Written by Lonely
// typeset.c

#include <ansi.h>

inherit F_CLEAN_UP;

string *deep_file_list(string dir);
int     to_format(object me, string dir, int n);
int     do_format(string file, int n);
int     help(object me);

void create() { seteuid(getuid()); } 

int main(object me, string arg)
{
        string dir;
        int n;
        
        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;
                
        if (! arg || sscanf(arg, "%s %d", dir, n) != 2) 
                return help(me);               

        if (n < 1) return help(me);
                
        if (file_size(dir) == -1)
                dir=resolve_path(query("cwd", me),dir);

        if (file_size(dir) > 0)
        { 
                if (! do_format(dir, n))
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

        write(HIG "\n現在系統正在批處理 " + dir + " 目錄房間描述，稍後彙報。\n" 
              HIG "進度：" + process_bar(0) + "\n"); 
                            
        if (me)
        {
                me->attach_system();
                me->write_prompt();
        }

        to_format(me, dir, n);
        return 1;
}
 
int to_format(object me, string dir, int n)
{
        int i, err, num;
        string *file;

        // file = deep_path_list(dir);        
        file = deep_file_list(dir);
                     
        if (! arrayp(file) || ! sizeof(file))
        {
                message_system("系統批量檔案處理完畢，請繼續遊戲。\n" ESC + "[K");  
                if (me)
                {
                        me->detach_system();
                }
                write(HIG "目錄 " + dir + " 下並沒有可供修改的文件\n" NOR); 
                return 1;
        }

        err = 0;
        num = 0;                        
        for (i = 0; i < sizeof(file); i++)
        {
                reset_eval_cost();

                message("system", ESC + "[1A" + ESC + "[256D"
                                  HIG "進度：" + process_bar((i + 1) * 100 / sizeof(file)) +
                                   "\n" + (me ? HIR "執行中" NOR "> " : ""),
                                   me ? me : filter_array(all_interactive(), (: wizardp :))); 
                                                   
                // if (sscanf(file[i], "%*s.c"))
                if (is_c_file(file[i]))
                {                                            
                        if (! do_format(file[i], n))
                                err++;
                        else  
                        if (do_format(file[i], n) == 1)     
                                num++;        
                }             
        }

        message_system("系統批量檔案處理完畢，請繼續遊戲。\n" ESC + "[K");  

        if (me)
        {
                me->detach_system();
        }
              
        write(HIG "目錄 " + dir + " 下共有 " + num + " 個房間描述整理成功。\n" NOR); 
        if (err)
                write(HIG "尚有 " + err + " 個文件整理失敗，詳情請查看LOG記錄。\n" NOR); 
                
        return 1;
}

int do_format(string file, int n)
{
        int i, begin1, begin2;
        string *filetext, *temptext;
        object ob;
        string long, err;
        string str1, str2, tempstr;
        
        err = catch(call_other(file, "???"));        
        if (err) 
        {
                log_file("typeset.log", sprintf("%s ERROR ** \n%s\n", file, err));
                return 0;
        }

        if (! (ob = get_object(file)))
        {
                log_file("typeset.log", sprintf("%s can not be load.\n", file)); 
                return 0;
        }
        
        //if( !inherits(ROOM,ob) || !query("long", ob) )
        if( !ob->is_room() || !query("long", ob) )
        {
                if (clonep(ob) && ! userp(ob)) 
                        destruct(ob);
                        
                return 2;
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
                        
        filetext = explode(read_file(file), "\n");

        n *= 2;
        temptext = explode(sort_string(long, n, 4) + "\n", "\n");
        temptext -= ({ "" });

        begin1 = 0;
        begin2 = 0;
        for (i = 0;i < sizeof(filetext);i ++)
        {
                tempstr = "";

                tempstr = replace_string(filetext[i], " ", "");
                tempstr = replace_string(tempstr, "\t", "");

                if (strsrch(tempstr, "set(\"long\",") != -1)
                {
                        begin1 = i;
                }
                if (strsrch(tempstr, "\);") != -1 && begin1)
                {
                        begin2 = i;
                        break;
                }
        }

        if (! begin1 || ! begin2) 
        {       
                log_file("typeset.log", sprintf("ROOM %s 的描述沒有被成功定位！\n", file));
                return 0;
        }

        str1 = "        set\(\"long\", @LONG\n";
        str2 = "LONG \);\n";
        rm(file);

        for (i = 0; i < begin1; i ++)
                write_file(file, filetext[i] + "\n", 0);

        write_file(file, str1, 0);
        
        for (i = 0; i < sizeof(temptext); i ++)
                write_file(file, temptext[i] + "\n", 0);

        write_file(file, str2, 0);

        for (i = begin2 + 1; i < sizeof(filetext); i ++)
                write_file(file, filetext[i] + "\n", 0);

        return 1;
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