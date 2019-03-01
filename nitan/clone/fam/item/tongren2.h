// 銅人

#include <ansi.h>

inherit ITEM;

#define MEMBER_D        "/adm/daemons/memberd"

int is_tongren() { return 1; };
int is_dazhoutian_tongren() { return 1; }

void create()
{
        set_name(NOR + YEL "銅人中文名" NOR, ({ "銅人ID" }) );
        set_weight(50);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "這是一個沖穴銅人，上面繪制了打通大周天經脈的關鍵穴位。\n" HIG
                                      "*有關經脈沖穴的詳細介紹請參見 help jingmai \n" NOR);
                set("value", 1);
                set("unit", "個");
                set("neili", 100); // 消耗內力
                set("jingmai_name", "JINGMAI_NAME"); // 經脈名
                set("xuewei_name", "XUEWEI_NAME"); // 穴位名
                set("point", "CHONGXUE_XIAOGUO"); // 沖穴效果
        }

        setup();
}

int query_autoload()
{
         return 1;
}
