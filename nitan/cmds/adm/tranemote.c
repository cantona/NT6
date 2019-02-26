//tranemote.c
//Made by jason@pkuxkx
//FreeWare
#define ERROR "指令格式：tranemote emote 來源emote文件\n"
inherit F_SAVE;
string source_file="";
mapping emote=([]);
string query_save_file()
{
        return source_file;
}
int main(object me,string arg)
{
        mapping old_emote=([]);
        string ee,file,*key,*key2;

           if (! SECURITY_D->valid_grant(me, "(admin)")) 
              return 0; 
        if(!arg||arg=="")
                return notify_fail(ERROR);
        if(sscanf(arg,"%s %s",ee,file)!=2)
        {
                return notify_fail(ERROR);
        }
        if(file_size(file+".o")<=0)
                return notify_fail("讀emote源文件錯誤。\n" );
        source_file=file;
        if(!restore())
        {
                return notify_fail("emote源文件無法Restore。\n");
        }
        old_emote=emote;
        if(!mapp(old_emote)||sizeof(old_emote)<=0)
        {
                return notify_fail("emote源文件無法Restore。\n");
        }
        source_file="/data/emoted";
        if(!restore())
        {
                return notify_fail("emote目標文件錯誤。\n");
        }
        if(!mapp(emote)||sizeof(emote)<=0)
        {
                return notify_fail("emote目標文件無法Restore。\n");
        }
        key=keys(old_emote);
        if(wizardp(me)&&wizhood(me)=="(admin)")
        {
                int unit=0;
                string nowtime;
                if(ee=="-All")
                {
                        nowtime=""+time();
                        cp("/data/emoted.o","/data/emoted.o."+nowtime);
                        key2=keys(emote);
                        shout("Emote 文件轉換中。。。。\n");
                        for(int i=0;i < sizeof(key);i++)
                        {
                                reset_eval_cost();
                                if(member_array(key[i],key2)!=-1) continue;
                                if(!mapp(old_emote[key[i]])) continue;
                                EMOTE_D->set_emote(key[i],old_emote[key[i]]);
                                write(key[i]+"\n");
                                unit++;
                        }
                        write("Emote 文件 "+file+" 轉換進入/data/emoted.o成功！\
n");            
                        write("一共有"+chinese_number(unit)+"個emote轉換成功。\n
");
                        write("現有emote備份為"+"/data/emoted.o."+nowtime+"\n");
                        log_file("tran_emote",getuid(me)+"轉換 "+file+" 中的Emot
e進入當前Emote中。
\n"+
                        "時間："+ctime(time())+"\n"+
                        "現有emote備份為"+"/data/emoted.o."+nowtime+"\n");
                        return 1;
                }
        
        }
        ee=lower_case(ee);
        if(member_array(ee,key)==-1)
        {
                return notify_fail(ee+" 不存在於 "+file+"。\n");
        }
        if(!mapp(old_emote[ee]))
        {
                return notify_fail(ee+" 不是一個合法的emote。\n");
        }
        if(!undefinedp(emote[ee]))
        {
                return notify_fail(ee+" 存在於目標emote文件中，不能覆蓋。\n");
        }
        EMOTE_D->set_emote(ee,old_emote[ee]);
        write("Emote轉換 "+ee+" 成功。\n");
        return 1;
}
int help(object me)
{
        write(@HELP
指令格式：tranemote emote 來源emote文件
將來源emote文件中的指定emote加入當前emote文件中。
格式二：tranemote -All 來源emote文件
將來源emote文件中所有當前emote文件中沒有的emote加入。
同時給當前emote文件按時間備份。
HELP
        );
        return 1;
}
