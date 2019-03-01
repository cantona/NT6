// conjure.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string spells, spl, trg;
        object target;
        
        seteuid(getuid());
        if( me->is_busy() )
                return notify_fail("( 你上一個動作還沒有完成，不能施展神通。)\n");
                
/*
        if (me->query_condition("killer"))
               return notify_fail("通緝犯無法使用神通！\n");
*/

        if( query("no_magic", environment(me)) )
                return notify_fail("這裡無法使用神通。\n");
                
        if( !arg ) return notify_fail("指令格式：conjure <神通> [on <目標>]\n");
        
        if( sscanf(arg, "%s on %s", spl, trg)==2 ) {
                target = present(trg, environment(me));
                if( !target ) target = present(trg, me);
                if( !target ) return notify_fail("這裡沒有 " + trg + "。\n");
        } else {
                spl = arg;
                target = 0;
        }
        
        spl = replace_string( spl, " ", "_");
        if( stringp(spells = me->query_skill_mapped("taoism")) )
                return (int)SKILL_D(spells)->conjure_magic(me, spl, target);
                
        return notify_fail("你請先用 enable 指令選擇你要使用的神通系。\n");
}
int help (object me)
{
        write(@HELP
指令格式：conjure <法術名稱> [on <對象>]
 
施法，你必需要指定<法術名稱>，<對象>則可有可無。
在你使用某一個法術之前，你必須先用 enable 指令來指定你要使用的法術系。
 
HELP
        );
        return 1;
}
