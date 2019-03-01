// xgrep.c 
//write by JackyBoy@CuteRabbit Studio for SDXL & CCTX 1999/6/1
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
        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;
        level=1;
        result="匹配文件有：\n";
        seteuid(geteuid(me));
        write("X grep 命令 v0.1  \nWrite By JackyBoy@CuteRabbit for CCTX & SDXL 1999/6/1\n"+
                "主頁：http://mud.yn.cninfo.net/jackyboy\n郵件：jackyboy@126.com\n");
    if (!arg) return help();
    if (sscanf(arg,"-d %s %s",path,pattern)!=2)
    {
            if(sscanf(arg,"-d%d %s %s",level,path,pattern)!=3)
                    if(sscanf(arg,"%s %s",path,pattern)!=2)
                    {
                            write ("\n參數解析錯誤。\n\n");
                            return help();
                    }
    }
    else
            level=15;//帶-d參數默認級別為所有級
    if(level<0) level=1;
    if(level>15) level=15;
    //處理path分解出wild
    path=resolve_path(query("cwd", me),path);
    write("未解析路徑：\t"+path+"\n");
    //write("欲搜索字符串：\t"+pattern+"\n");
    write("搜索目錄級別：\t"+level+"\n");
    wild=resolvePath(path,0);
    path=resolvePath(path,1);
    write("解析後路徑：\t"+path+"\n");
    write("解析後通配符：\t"+wild+"\n\n");
    do_grep(path,wild,level);
    write("\n搜索結束。\n");
    write(result+"\n");
        return 1;
}

int do_grep(string path,string wild,int level)
{
        //int i;
        //string *fs;
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
                                        result=result+"在"+path+file+"裏找到"+pattern+"\n";//應該是記錄下來，最後再輸出
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

X grep 命令 v0.1  Write By JackyBoy@CuteRabbit for CCTX & SDXL 1999/6/1
主頁：http://mud.yn.cninfo.net/jackyboy
郵件：jackyboy@126.com


指令格式 : xgrep [-d[0-15]] 路徑 想要搜索的字符串
此指令可讓你在指定(除了目錄，可以用通配符來指定)檔案或目錄裏尋找含有要
搜索的字符串的文件，並將其位置顯示出來。
注意，默認僅搜索當前目錄！
已知BUG：
對二進制文件進行搜索將會出錯，因為禁止將'\0'設置到一個string裏！
HELP
    );
    return 1;
}