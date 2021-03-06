/***** Written by ken@NT.  All rights reserved. *****/
// tobig5.c
/****************************************************/
/* 中文字分兩種，中國大陸用GB碼，香港和台灣用BIG5碼 */
/* 由於內碼不同，就會出現亂碼的情況，GB碼的編碼是由 */  
/* 0xa1 - 0xf7 ，BIG5碼的編碼是由 0x40 - 0x7e，因此 */
/* 我們做有兩個字庫，分別是字庫 "BtoG.tab"   和字庫 */ 
/* "GtoB.tab" ，在對應的字庫中找出對應的文字， 這個 */
/* 動作由"/adm/daemons/languaed.c" 完成，本程序只需 */
/* 調用它裏面的函數就可以了。                       */
/****************************************************/

#include <ansi.h>
inherit F_CLEAN_UP;
#define CONVERT "/adm/daemons/languaged.c"

protected int help(object me);
protected int to_big5(string file);
protected string *deep_file_list(string dir);

int main(object me, string arg)
{
        string file;
        mixed *dir;
        int i, total;

        if (!SECURITY_D->valid_grant(me, "(admin)"))
                return 0; 

        if (!arg || sscanf(arg, "%s", file) != 1) 
                return help( me );
                
        seteuid(geteuid(me));
     
        if(!SECURITY_D->valid_write(file, me))
                return notify_fail("沒有足夠的讀寫權限.\n");
        
        if (file_size(file) == -1 )
                file=resolve_path(query("cwd", me),file);
                
        if(file_size(file) > 0)
        { 
                to_big5(file);
                write(HIW "文件∶" + file + "內所有內容轉換完成.\n" NOR);
                return 1;
        }
   
        else if(file_size(file) == -2) 
        {
                dir = deep_file_list(file);
                for(i=0; i<sizeof(dir); i++)
                {
                        reset_eval_cost();
                        if ( file_size(dir[i]) > 0)
                        {
                                to_big5(dir[i]);
                                total = total + 1;
                                write(dir[i] + " 文轉換完成。\n");
                        }
                }
                write("共把" + total + "個文件轉換成大五碼(BIG5)\n");
                return 1;
        }
        else return notify_fail("沒有這個文件或目錄.\n");
        return 1;               
}

protected string *deep_file_list(string dir)
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

protected int to_big5(string file)
{
        string *text;
        int i;   
        
        text = explode(read_file(file), "\n");
        rm(file);
        
        for(i=0; i<sizeof(text); i++)
        {
                text[i] = CONVERT-> toBig5(text[i]);                    
                write_file(file, text[i] + "\n");
        }       
        return 1;
}

protected int help(object me)
{ 
write(@HELP
Written by ken@NT. All rights reserved.
E-mail: printken@yahoo.com.hk

指令格式: tobig5 <文件或目錄>
本指令可讓你把文件或目錄轉換成BIG5碼。
比如togb /d/　會把 /d/　下的所有文件及目錄內的所有文都轉成BIG5
我不建意使用轉換目錄，除非你很瞭解你想要做什麼！
(此指令建議放在/cmds/adm/下)
注意：本命令比較危險，請小心使用。

HELP);
return 1;
}

