// Last Modified by winder on Nov. 17 2000
// wumu-yishu.c

#include <ansi.h>

inherit ITEM;
void init()
{
        add_action("do_du", "du");
}

void create()
{
        set_name( "「武穆遺書」", ({ "wumu yishu", "yishu" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        GRN
                        "\n這就是嶽武穆臨死前留下的“破金要訣”。\n"
                        "只見第一頁上寫了十八個大字：\n"
                        "“重搜選，謹訓習”\n"
                        "“公賞罰，明號令”\n"
                        "“嚴紀律，同甘苦”\n"NOR
                );
                set("value", 10000000);
                set("material", "paper");
                set("no_get", 1);
                set("no_drop", 1);
                set("treasure", 1);
        }
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;

        if (!id(arg)) return 0;
        if (!present(this_object(), this_player()))
                return 0;

//if( me->query("wumu+int")) 
        if( query("mark/+int", this_player()) )
        {
                write("這可真是一部兵法奇書呀！！！\n");
        }
        else
        {
                addn("int", 1, me);
                write(HIY"你隨手翻閲，但見一字一句之間，無不闡明臨陣對敵的妙法，不禁大聲讚歎！\n"NOR);
                write(HIR"你的悟性提高了！\n"NOR);
                set("mark/+int", 1, this_player());
        }
        return 1;
}