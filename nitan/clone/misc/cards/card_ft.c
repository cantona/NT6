// card_ft.c
#include <ansi.h>;
#include <command.h>;
inherit ITEM;

void create()
{
        set_name(HIR"新春賀卡"NOR, ({"spring festival card", "card"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long",
"這是一張"HIR"新春賀卡"NOR"，送給每位在新春佳節連入飛雪連天
的玩家。你可以打開(dakai)來看看，會有意外驚喜哦。\n");
                set("value", 0);
                set_weight(10);
        }
        setup();
}
void init()
{
        add_action("do_dakai", "dakai");
        add_action("do_chaikai", "chaikai");
}
int do_dakai(string arg)
{
        object me = this_player();
        string message;
        int col;

        if (!present(this_object(), this_player()))
                return 0;

        if (arg == "card")
        {
                tell_object(me,
HIR"\n"+
"                                              \n"+
"        │       │       │       │         \n"+   
"     □┴┴□ □┴┴□ □┴┴□ □┴┴□      \n"+
"     │    │ │    │ │    │ │    │      \n"+
"     │    │ │    │ │    │ │    │      \n"+
"     │ 迎 │ │ 春 │ │ 接 │ │ 福 │      \n"+
"     │    │ │    │ │    │ │    │      \n"+
"     │    │ │    │ │    │ │    │      \n"+
"     □┬┬□ □┬┬□ □┬┬□ □┬┬□      \n"+
"        !!       !!       !!       !!         \n"+
"        ;;       ;;       ;;       ;;         \n"+
"\n"+
HIY"                      「俠客行一百」恭賀    \n"+
"\n"NOR);
        }
        return 1;
}

int do_chaikai(string arg)
{
        object newcard, box, obj0, obj1, obj2, obj3;
        object me = this_player();
        int col;

        if (!present(this_object(), this_player()))
                return 0;

//        return notify_fail("還沒到時候呢，別急拆開啊！\n");

        if (arg == "card")
        {
                message_vision(HIG"$N興高採烈地拆開了賀卡，突然掉下一個"HIR"紅包"HIG"！\n"NOR, me);
                box = new(__DIR__"redbag");
                newcard = new(__DIR__"card_ft_done");
                newcard->move(me);
                if (random(100) == 1)
                {
//                        obj0 = new("/clone/money/28gold");
                        obj0 = new("/clone/money/gold");
                        obj0->set_amount(28);
                        obj0->move(box);
                }
                if (random(50) == 1)
                {
//                        obj1 = new("/clone/money/18gold");
                        obj1 = new("/clone/money/gold");
                        obj1->set_amount(18);
                        obj1->move(box);
                }
                if (random(20) == 1)
                {
//                        obj2 = new("/clone/money/9gold");
                        obj2 = new("/clone/money/gold");
                        obj2->set_amount(9);
                        obj2->move(box);
                }
                if (random(3) == 1)
                {
//                        obj3 = new("/clone/money/6gold");
                        obj3 = new("/clone/money/gold");
                        obj3->set_amount(6);
                        obj3->move(box);
                }
                obj3 = new("/clone/medicine/nostrum/xiongdan");
                obj2 = new("/clone/money/gold");
                obj3->move(box);
                obj2->move(box);
                box->move(environment(me));
                destruct(this_object());
        }
        return 1;
}

string query_autoload()
{ return 1 + ""; }
