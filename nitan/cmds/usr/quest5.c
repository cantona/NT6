#include <ansi.h>
inherit F_CLEAN_UP;
int time_period(int timep, object me);
int main(object me, string arg)
{
        int mark;
        int quest;
        string *site;

        site=({"玄武門內","青龍門內","朱雀門內","白虎門內"});
        if( !(quest=query("jungong", me)) )
        return notify_fail(
               HIW"你並沒有做過任何郭靖任務，想試一下嗎？\n"NOR);

        mark=query_temp("guo_shoucheng/mark_shadi", me);

        if( mark && mark < 5 )
             write(HIW"\n你現在的任務是去協助"HIR+site[mark-1]
                     +HIW"的宋軍，抗擊蒙古韃子的入侵！\n"NOR);
         
        else
          if( query_temp("guo_shoucheng/mark_jianlou", me) )
             write(HIW"\n你現在的任務是去協助青龍門內"HIR"東城箭樓"
                    +HIW"的宋軍，擔任狙擊蒙古弓箭手的任務！\n"NOR);
        else
             write(
HIW"\n===============================================================\n"NOR
+HIR"            你已經榮立軍功"HIY
+chinese_number(quest)+HIR"策！\n"NOR+
HIW"===============================================================\n"NOR);

       return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : quest5  這個指令可以顯示出你已經參與郭靖任務情況。
HELP
        );
        return 1;
}
