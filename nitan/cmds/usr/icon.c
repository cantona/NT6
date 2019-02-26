#include <ansi.h>

inherit F_CLEAN_UP;
#define MAX_ICONS 2159

int help();

int main(object me,string arg)
{
        mixed tmp;
        int ico;
        string str="",icon=HIR"空，沒有設置"NOR;
        if( (tmp=query("icon", me)) )
        {
                if( intp(tmp) )
                {
                        icon = sprintf("%d",tmp);
                        str=L_ICON(icon);
                }
                else if( stringp(tmp) )
                {
                        icon = tmp;
                        str=L_ICON(icon);
                }
        }

        str+=NOR+"你原來的頭像編號是"+HIY+icon+NOR+"！\n";

        if(arg)
        {
                if(sscanf(arg,"%d",ico)!=1||ico<=0||ico>=MAX_ICONS)
                        return help();
                icon=sprintf("%d",ico);
                while( sizeof(icon)<5 )        icon = "0" + icon;
                str+="它已經被修改為"+HIG+icon+NOR+"了！\n";
                set("icon", icon, me);
        }
        else help();
        tell_object(me,str);
        return 1;
}

int help()
{
        write("命令格式："+HIY+"icon [圖標編號]\n"+NOR+
                "    你可以用本命令查詢和修改自己的頭像編號。\n"+
                "    你可以去[http://www.qqchat.net]查詢和選擇自己的頭像圖標編號。\n"+
                "    目前圖標可以選擇範圍是"+HIR+" 1 - "+MAX_ICONS+NOR+" 。\n");
        return 1;
}

