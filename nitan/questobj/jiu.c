// jiu.c
inherit ITEM;
#include <ansi.h>

void init()
{
}
void create()
{
        set_name(HIB "玄冰"HIG"碧火"HIR"酒" NOR,({"xuanbingbihuo jiu", "jiu"}));
        set("taskobj", 1);
        set("unit", "壺");
        set("long", "這是一壺珍貴之極的玄冰碧火酒, 據説能解百毒。\n");
        setup();
}