// This program is a part of NT MudLIB

#include <ansi.h>

#define ZHOUTIAN_D      "/adm/daemons/zhoutiand"

inherit F_CLEAN_UP;

int help(object me);
int main(object me, string arg)
{
        string *xs;
        string msg;
        int i;

        if( me->is_busy() || me->is_fighting() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || arg == "" ) {
                msg  = HIC "經脈名衝穴狀態\n" NOR;
                msg += HIC "≡" HIY "───────────────────────" HIC "≡\n" NOR;
                msg += HIC "\t\t小週天經脈\n" NOR;
                msg += HIC "≡" HIY "───────────────────────" HIC "≡\n" NOR;
                msg+=HIG"陰蹺脈\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/陰蹺脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"陽蹺脈\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/陽蹺脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"陰維脈\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/陰維脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"陽維脈\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/陽維脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"帶脈\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/帶脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"衝脈\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/衝脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"任外脈\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/任外脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"督外脈\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/督外脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"經外奇脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/經外奇脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg += HIC "≡" HIY "───────────────────────" HIC "≡\n" NOR;
                msg += HIY "\t\t大周天經脈\n" NOR;
                msg += HIC "≡" HIY "───────────────────────" HIC "≡\n" NOR;
                msg+=HIG"手太陰脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/手太陰脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"手太陽脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/手太陽脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"足太陰脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/足太陰脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"足太陽脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/足太陽脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"手少陰脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/手少陰脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"手少陽脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/手少陽脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"足少陰脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/足少陰脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"足少陽脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/足少陽脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"手陽明脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/手陽明脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"足陽明脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/足陽明脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"手厥陰脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/手厥陰脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"足厥陰脈\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/足厥陰脈/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg += HIC "≡" HIY "───────────────────────" HIC "≡\n" NOR;
                write(msg);
                help(me);

                if( query("jingmai/finish", me) || query("jingmai/陰蹺脈/chongxue_ok", me) )
                        MYGIFT_D->check_mygift(me, "newbie_mygift/yinqiaomai");

                return 1;
        }

        if( arg == "all" || arg == "bh" || arg == "bh2" )
        {
                me->start_more(ZHOUTIAN_D->show_bianhao(arg));
                return 1;
        }

        ZHOUTIAN_D->show_jingmai(me, arg);

        return 1;
}

int help(object me)
{
        write(@HELP
查看指定經脈衝學情況使用指令 jingmai <經脈名> 查詢。
查看小週天銅人編號輸入 jingmai bh 查詢。
查看大周天銅人編號輸入 jingmai bh2 查詢。
查看大小週天銅人編號輸入 jingmai all 查詢。
更詳細的參考文件請通過幫助文件 help zhoutian 查看。

HELP
);
        return 1;
}
