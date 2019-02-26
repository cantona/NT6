// This program is a part of NITAN MudLIB

// grep.c 

inherit F_CLEAN_UP;

int help();
int do_grep(string,string,int);

nosave string pattern;
nosave string result;

string resolvePath(string path,int op)
{
        string *dn;
        string tmp;
        int i;
        if(path=="/")//對這個情況特殊處理
                return (op)?"/":"*";
        dn=explode(path,"/");
        if(op)//op為非0表示需要返回路徑
        {
                //dn=dn-({dn[sizeof(dn)-1]});
                //tmp=implode(dn,"/")+"/";
                //上面的程序不好，不能對同名路徑正確處理，比如不能在/log/log文件裏搜索
                tmp="/";
                for(i=0;i<sizeof(dn)-1;i++)
                {
                        //write("合併"+dn[i]+"\n");
                        tmp+=dn[i]+"/";
                }
                return tmp;
        }
        else
                return dn[sizeof(dn)-1];
}

int main(object me, string arg)
{
        string  path,wild;
        int level;

        seteuid(getuid()); 

        if (!arg) return help();
        
        if( !wizardp(me) && time()-query_temp("last_grep", me)<30 )
                return notify_fail("系統氣喘噓地歎道：慢慢來 ....\n");   

        if (sscanf(arg,"%s %s",path,pattern)!=2)
                    return help();
            
            if (path != "help" && path != "news" && path != "all")
                    return help();
            
            set_temp("last_grep", time(), me);
        
        if (path == "news" || path == "all")
        {
                write("正在新聞系統中搜索，請稍後 ……\n");
                NEWS_D->do_search(me, "document " + pattern);
                if (path == "news")
                {
                        write("為節約系統資源，在30秒內只能進行搜索一次。\n");
                        return 1;
                }
                write("\n\n");
        }

            level=1;//帶-d參數默認級別為所有級        
        path="/help";
        result="以下help幫助中包含你所要搜索的內容：\n";
        
        write("正在幫助系統中搜索，請稍後 ……\n");
        wild=resolvePath(path,0);
        path=resolvePath(path,1);

        do_grep(path,wild,level);
        write(result+"\n");
        write("為節約系統資源，在30秒內只能進行搜索一次。\n");
        return 1;
}

int do_grep(string path,string wild,int level)
{
        //int i;string *fs;
        string sbuffer,file;
        reset_eval_cost();//重新設置剩餘執行時間，必須設置！
        if( query("env/debug", this_player()) )
                write("開始搜索"+path+wild+"\n");
        if(level<0)
        {
                //write("級別限制，不能再進入搜索。\n");
                return 0;
        }
        //for(i=0;i<(sizeof(fs=get_dir(path+wild))-1);i++)
        //        write(fs[i]+"\n");
        
        foreach(file in get_dir(path+wild))
        {
                //write("檢查："+path+file+"\n");
                //write("file_size返回："+file_size(path+file)+"\n");
                if(file=="."||file=="..")
                        continue;
                
                switch(file_size(path+file))
                {
                        case -1:
                                //無法讀取該目錄，跳過
                                break;
                        case -2:
                                if(file!="."&&file!="..")
                                        do_grep(path+file+"/","*",level-1);
                                break;
                        default:
                                //write("檢查文件："+path+file+"\n");
                                if(!sbuffer=read_file(path+file))
                                //對太大的文件讀取可能要失敗！而且不能試圖讀取二進制文件，因為含有\0!
                                {
                                        write("讀文件"+path+file+"出錯！\n");
                                        return 0;
                                }
                                if(strsrch(sbuffer,pattern)!=-1)
                                        result=result+file + "\n";//應該是記錄下來，最後再輸出 
                        /*
                                if(strsrch(read_file(path+file),pattern)!=-1)
                                        write(path+file+"\n");
                                break;
                        */
                }
                
        }
        return 1;
}

int help()
{
        write(@HELP
指令格式：grep <help/news/all> 查找內容

該指令功能相當強大，用於在相應地方或全局搜索指定查找的內容。

help:   在所有help文件中搜索。
news:   在所有的新聞中搜索。
all:    在所有help文件和新聞中搜索。
ex:
        grep help 華山派
ps:
        在所有的help文件中查找包含字符串“華山派”的相關文件。

HELP
    );
        return 1;
}