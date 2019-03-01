#include <ansi.h>

inherit F_CLEAN_UP;

int help();

int main(object me,string arg)
{
        string cmd,*res;
        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;
        if(!arg)
                return help();
        if(sscanf(arg,"%s %s",cmd,arg)!=2)
        {
                write("參數錯誤！\n");
                return help();
        }
        
        cmd=lower_case(cmd);
        if(cmd!="select")
                return notify_fail("暫時不能執行除了select以外的SQL查詢！\n");
        log_file("sqlcmd","\n"+ctime(time())+me->name()+"("+query("id", me)+")執行了SQL查詢：\n"+cmd+""+arg);
        res=DATABASE_D->do_sql(cmd+" "+arg);
        if(arrayp(res)&&sizeof(res))
                write("SQL查詢返回結果：\n"+save_variable(res)+"\n");
        else
                write("SQL查詢無返回結果！\n");
        return 1;
}

int help()
{
        write(NOR+"\nSQL查詢命令測試版！Written By JackyBoy\n\n"+
                "命令語法："+HIG+"sql <SQL語句> \n"+NOR
                "目前只支持"+HIR+"select"+NOR+"查詢！\n");
        return 1;
}