/* This program is a part of NiTan3 mudlib
 * Copyright (C)2000-2008, by NiTan3. All rights reserved.
 * This software can not be used, copied, or modified
 * in any form without the written permission from authors. 
 -----------------------------------------
 * File   : header.c
 * Author : Lonely@NiTan3
 * Date   : 2008-06-02
 * Note   : 
 * Update :
 *  o 2008-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>

inherit F_CLEAN_UP;

string help = @HELP
可自動建立檔案標頭, 並可修改標頭內容
ex :
header filename.c //若 filename 尚無 NT 格式標頭, 則自動建立預設標頭, 作者為下此指令之人
header filename author lonely // 設定 filename 作者為 lonely
header filename update update_info // 自動往下遞增 update 資訊
header filename note note_info // 填寫 NOTE(註解) 欄

同時支援多行輸入
header filename author1/author2 輸入多名作者
header filename update1/update2 輸入多行更新資訊
header filename note1/note2     輸入多行註解資訊
HELP;

string default_header   = @HEADER
/* This program is a part of NiTan3 mudlib
 * Copyright (C)2000-2008, by NiTan3. All rights reserved.
 * This software can not be used, copied, or modified
 * in any form without the written permission from authors. 
 -----------------------------------------
 * File   : %^FILENAME%^
 * Author : %^AUTHOR%^
 * Date   : %^DATE%^
 * Note   : 
 * Update :
 *  o %^THISYEAR%^-00-00
 *
 -----------------------------------------
 */

HEADER;

int create_default_header(object me, string filename, string file)
{
        string header, create_date;
        
        
        create_date = TIME_D->replace_ctime(time());
        
        header = terminal_colour(default_header, 
                ([
                        "FILENAME"      : filename[(strsrch(filename, "/",-1)+1)..], 
                        "AUTHOR":capitalize(query("id", me))+"@NiTan3",
                        "DATE"          : create_date[6..9]+"-"+create_date[0..1]+"-"+create_date[3..4],
                        "THISYEAR"      : create_date[6..9],
                ]));

        file = header + file;
        
        return write_file(filename, file, 1);
}

string *single_quote_parse(string p)
{
        int i, j, size;
        string *ret = allocate(0), *tmp = explode(p, " ");

        size = sizeof(tmp);

        for(i=0;i<size;i++,j++)
        {
                if( tmp[i][0] == '\'' )
                {
                        ret += ({ tmp[i][1..] });

                        while( ++i < size )
                        {
                                ret[j] += " "+tmp[i];

                                if( tmp[i][0] && tmp[i][<1] == '\'' )
                                {
                                        ret[j] = ret[j][0..<2];
                                        break;
                                }
                        }
                }
                else ret += ({ tmp[i] });
        }

        return ret - ({ "" });
}


int help(object me) 
{
        write(help);       
        return 1; 
}

int main(object me, string arg)
{
        int line;
        string header, *parse, *efile;
        string file, filename, option, arg2;

        if( !SECURITY_D->valid_grant(me, "(admin)") )
                return 0;

        seteuid(getuid(me));

        if( !arg )
                return notify_fail("請輸入想要建立標頭的檔案名稱。\n" );
        
        parse = single_quote_parse(arg);
        arg = parse[0];

        if( sizeof(parse) >= 3 )
        {
                option = parse[1];
                arg2 = implode(parse[2..], " ");
        }

        if( file_size(arg) == -1 ) 
                arg=resolve_path(query("cwd", me),arg);

        filename = arg;
        
        if( file_size(filename) < 0 )
                return notify_fail("沒有 "+filename+" 這個檔案。\n");
        
        if( filename[<2..<1] == __SAVE_EXTENSION__ )
                return notify_fail("這個檔案型式不適合建立標頭。\n");

        file = read_file(arg);
        
        // 檢查是否已經建立標頭
        if( file[0..41] != "/* This program is a part of NiTan3 mudlib" )
        {
                if( create_default_header(me, filename, file) )
                {
                        write("\n"+filename+" 預設標頭建立完畢。\n");
                        return 1;
                }
                else
                        return notify_fail("你的權限不足以處理這個檔案。\n");
        }
        else if( !option || !arg2 )
                return notify_fail(filename+" 的標頭已經建立。\n");

        if( option && arg2 )
        {
                efile = explode(file, "\n");
                
                switch( lower_case(option) )
                {
                        case "author":
                        {
                                string author, *multi_author;
                                
                                multi_author = explode(arg2, "/");
                                
                                for(int i=0;i<sizeof(multi_author);i++)
                                {
                                        if( !i )
                                                author = capitalize(multi_author[i]) + NOR"@NiTan3";
                                        else
                                                author += "\n *          "+capitalize(multi_author[i])+NOR"@NiTan3";
                                }

                                for(int i=0;i<sizeof(efile);i++)
                                {
                                        if( efile[i][0..10] == " * Author :" )
                                        {
                                                efile[i] = efile[i][0..10]+" "+filter_color(author);
                                                break;
                                        }
                                }
                                                        
                                break;
                        }
                        case "update":
                        {
                                string update="", *multi_update;
                                string date = TIME_D->replace_ctime(time());
                                
                                multi_update = explode(arg2, "/");
                                
                                for(int i=0;i<sizeof(multi_update);i++)
                                {
                                        if( !i )
                                                update+="*o"+date[6..9]+"-"+date[0..1]+"-"+date[3..4]+""+capitalize(query("id", me))+""+multi_update[i]+NOR;
                                        else
                                                update+="\n*"+repeat_string("",16+strlen(query("id", me)))+multi_update[i]+NOR;
                                }
                                
                                for(int i=0;i<sizeof(efile);i++)
                                {
                                        if( efile[i][0..10] == " * Update :" )
                                        {
                                                if( efile[i+1][10..15] == "-00-00" )
                                                {
                                                        efile[i+1] = update;
                                                        break;
                                                }
                                                
                                                while( efile[++i] != " *" );
                                                
                                                efile = efile[0..i-1] + ({ update }) + efile[i..];
                                                
                                                break;
                                        }
                                }
                                
                                break;
                        }
                        case "note":
                        {
                                string note, *multi_note;
                                
                                multi_note = explode(arg2, "/");
                                
                                for(int i=0;i<sizeof(multi_note);i++)
                                {
                                        if( !i )
                                                note = multi_note[i]+NOR;
                                        else
                                                note += "\n *          "+multi_note[i]+NOR;
                                }
                                
                                for(int i=0;i<sizeof(efile);i++)
                                {
                                        if( efile[i][0..10] == " * Note   :" )
                                        {
                                                efile[i] = efile[i][0..10]+" "+note;
                                                break;
                                        }
                                }
                                
                                break;
                        }
                        default: return notify_fail("沒有 "+option+" 這個選項。\n");
                }
                
                line = member_array(" */", efile) + 1;
                
                if( write_file(filename, implode(efile, "\n"), 1) )
                {
                        write(me->query_idname()+"修改 "+filename+" 標頭。\n");
                        write(read_file(filename, 1, line) +"\n\n"+filename+" 預設標頭建立完畢。\n");
                        return 1;
                }
                else
                        return notify_fail("你的權限不足以處理這個檔案。\n");               
        }
}

