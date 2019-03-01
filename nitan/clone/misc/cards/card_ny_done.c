// card_ny_done.c
#include <ansi.h>;
#include <command.h>;
inherit ITEM;

void create()
{
        set_name(HIR"新年賀卡"NOR, ({"new year card", "card"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long",
"這是一張"HIR"新年賀卡"NOR"，送給每位在新的一年進入飛雪連天的玩家。你可以打開(dakai)來看看，會有意外驚喜哦。\n");
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
"                                                                   \n"+
"            ┬┴┬┌─　●─┬─　　│─┼─┐　●├─┤○         \n"+
"            ┴┬┴├┬　┌─┼─　│◎　│　│　○└┬┘●         \n"+
"            ─┼─││　│　│　　││─┴─┴　──┼──         \n"+
"            ●│○││　┴─┼─　　│○　　●　／　│　＼         \n"+
"                                                                   \n"+
"                                             飛雪連天恭賀          \n"+
"                                                                   \n"+
"\n"NOR);
        }
        return 1;
}

int do_chaikai(string arg)
{
           object me = this_player();

           if (!present(this_object(), this_player()))
                   return 0;

           message_vision("$N試圖拆開新年賀卡，發現這張卡已經被拆開過了。\n", me); 
        return 1;
}

string query_autoload()
{ return 1 + ""; }