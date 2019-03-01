// shop.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        if( !wizardp(me) && time()-query_temp("last_combat", me)<10 )
                return notify_fail("系統氣喘噓地嘆道：慢慢來 ....\n");   

        set_temp("last_combat", time(), me);
        SKILLS_D->query_skill_power(me, arg);
        return 1;
}

int help (object me)
{
        write(@HELP
查看武功各種參數值
    combat attack             查看命中力排名
    combat dodge              查看躲閃力排名
    combat parry              查看招架力排名
    combat damage             查看傷害力排名
    combat force              查看內功的排名
    combat difficult          查看難度的排名
    combat ultimate           查看終極的武功
    combat expert             查看超級的武功
    combat advance            查看高級的武功
    combat normal             查看普通的武功
    combat public             查看公共的武功
    combat family             查看門派的武功
    combat private            查看自創的武功
    combat <門派名稱>         查看該門派武功
    combat <技能名稱>         查看該武功參數
    combat <技能種類>         查看可激發武功

HELP);
        return 1;
}