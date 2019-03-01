
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "日" HIY "月" NOR + WHT "鏡" NOR, ({ "riyue jing", "riyue", "jing" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "面");
                set("long", HIC "傳說女媧創造生靈的時候，為了時刻監視生靈的一舉一動，\n"
                                "于是請求上天賜予了她一面寶鏡，名曰日月鏡，擁有日月\n"
                                "鏡的人可以隨時查看到遊戲中的生物、玩家及NPC的位置。\n"
                                "每次使用消耗黃金一兩，即從炎黃銀庫扣1YSG/次。\n" HIY
                                "指令： echo 生物英文ID\n" NOR);
                set("value", 800000);
                
        }
        setup();
}

void init()
{
        add_action("do_echo", "echo");
}

int do_echo(string arg)
{

        object me, target;
        string where;
        
        me = this_player();

        if (environment(this_object()) != me)return 0;

        if (! arg)return notify_fail("指令格式： echo 生物英文ID\n");

        target = find_living(arg);

        if (! objectp(target))
                return notify_fail(HIG "日月鏡發出一道亮光：沒有找到目標生物，可能該生物不存在或未被更新！\n" NOR);
                
        // 不能查看隱身ID及巫師
        if (wizardp(target))
                return notify_fail(HIG "日月鏡發出一道亮光：沒有找到目標生物，可能該生物不存在或未被更新！\n" NOR);
                
        // 扣除YSG
        if (me->query("stocks/balance") < 1)
                return notify_fail("對不起，你的YSG不足，無法使用日月鏡！\n");        
        
        if (target->query_temp("apply/invisible") && ! me->query_condition("niuyanlei"))
                return notify_fail(HIG "日月鏡發出一道亮光：沒有找到目標生物，可能該生物不存在或未被更新！\n" NOR);

        me->add("stocks/balance", -1);

        if (! environment(target))
                return notify_fail("對不起，該對象無法查詢到具體位置。\n");

        where = stringp(environment(target)->query("short")) ? environment(target)->query("short")
                                                                 : environment(target)->short();

        tell_object(me, HIG "日月鏡發出一道亮光：" + target->name() + "(" + arg + ")現在在" + 
                         where + HIG "。\n" NOR);

        return 1;
}

int query_autoload()
{
        return 1;
}
