// 上古十大神器之 東皇鐘
// Create by Rcwiz for Hero.cn 2003/09
// 在 /d/songshan/fengchangtai.c可以打開天界之門

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIC "東皇鐘" NOR, ({ "donghuang zhong", "donghuang", "zhong" }) );
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "口");
                set("long", HIC "這是一口看似普通的古鐘，卻有一種令人神往的氣魄。\n"                                
                                "可用之來打開(qiao)天界之門，進入通天門。\n" NOR);

        }
        setup();
}

void init()
{
        add_action("do_qiao", "qiao");
}

int do_qiao(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("donghuang zhong", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");

        if (environment(me)->query("short") != "封禪台")
                 return notify_fail("你得到封禪台才能打開天界之門。\n");

        message_sort(HIC "\n$N" HIC "將東皇鐘放在地上，然後用力一敲，只"
                         "聽得一聲巨響，剎那間，天際出現一道彩色之門，伴"
                         "隨著千萬道玄目的光華，東皇鐘將$N" HIC "卷了進"
                         "去 ……\n" NOR, me);

        me->move("/kungfu/class/sky/tianmen0");
        destruct(this_object());

        return 1;
}
