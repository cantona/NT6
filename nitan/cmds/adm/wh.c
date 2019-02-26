#include <ansi.h>

inherit F_CLEAN_UP;

#define MR 15

int help();

int main(object me,string arg)
{
        string str;
        object env,*tmp=({});
        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;
        if(!arg)
                return help();
        str=NOR "開始搜索(最多隻列"+MR+"個搜索結果)：\n";
        foreach(object ob in objects())
        {
                if(ob->id(arg) && sizeof(tmp)<MR)
                        tmp+=({ob});
        }
        if(sizeof(tmp)<1)
                str+="沒有搜索到任何結果！\n";
        else        
                foreach(object ob in tmp)
                {
                        env=environment(ob);
                        if(objectp(env))
                        {
                                str+="\n發現"+ob->name()+"("+query("id", ob)+")源文件---"+HIY+file_name(ob)+NOR"\n";
                                str+=sprintf("--- %s(%s) 源文件 --- "+HIY+"%s\n"NOR,
                                        stringp(env->name())?env->name():(stringp(env->short())?env->short():"無名"),
                                        stringp(query("id", env))?query("id", env):"0",
                                        file_name(env)  );
                                while(objectp(env=environment(env)))
                                        str+=sprintf(" ├ %s(%s) 源文件 --- "+HIY+"%s\n"NOR,
                                        stringp(env->name())?env->name():(stringp(env->short())?env->short():"無名"),
                                        stringp(query("id", env))?query("id", env):"0",
                                        file_name(env)  );
                        }
                        else str+="\n發現無環境物件"+ob->name()+"("+query("id", ob)+")源文件---"+HIY+file_name(ob)+NOR"\n";
                }
        me->start_more(str);
        return 1;
}

int help()
{
        write("\n請輸入wh <id>來查找遊戲中指定ID的環境。（最多顯示15個物件）\n");
        return 1;
}