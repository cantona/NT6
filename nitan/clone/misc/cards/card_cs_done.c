// card_cs_done.c
#include <ansi.h>;
#include <command.h>;
inherit ITEM;

void create()
{
        set_name(HIR"聖誕賀卡"NOR, ({"Christmas card", "card"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long",
"這是一張"HIR"聖誕賀卡"NOR"，送給每位在聖誕節進入俠客行一百
的玩家。你可以打開(dakai)來看看，記住自己的編號。
新年鐘聲敲響的時候，等待着我們的抽獎禮品。\n");
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
HIW"\n"+
"     ┏━━━━━━━━ "HIR"聖誕快樂"HIW" ━━━━━━━━┓\n"+
"     ┃  ┌──── Merry  Christmas ────┐  ┃\n"+
"     ┃  │                                  │  ┃\n"+
"     ┃  │                                  │  ┃\n");
                if( strlen(query("name", me)) == 2)tell_object(me,
HIW"┃│親愛的"+query("name", me)+"：│┃\n");
                if( strlen(query("name", me)) == 4)tell_object(me,
HIW"┃│親愛的"+query("name", me)+"：│┃\n");
                if( strlen(query("name", me)) == 6)tell_object(me,
HIW"┃│親愛的"+query("name", me)+"：│┃\n");
                if( strlen(query("name", me)) == 8)tell_object(me,
HIW"┃│親愛的"+query("name", me)+"：│┃\n");
                if( strlen(query("name", me)) == 10)tell_object(me,
HIW"┃│親愛的"+query("name", me)+"：│┃\n");
        tell_object(me,
HIW"     ┃  │      願您和您的家人在主的祝福    │  ┃\n"+
"     ┃  │  下，快樂、平安！                │  ┃\n"+
"     ┃  │                                  │  ┃\n"+
"     ┃  │             *  *"HIR"r"HIW"*  *            │  ┃\n"+
"     ┃  │          * *"HIR"a"HIW"* "HIG"^"HIY"Y"HIG"^"HIW" *"HIR"i"HIW"* *         │  ┃\n"+
"     ┃  │         *"HIM"m"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"*"HIG"^\\^"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"*"RED"s"HIW"*        │  ┃\n"+
"     ┃  │         "HIG"^"HIY"Y"HIG"^"HIW"*"HIG"\\"HIW"*"RED"e"HIW"*"HIG"/"HIW"*"HIG"l"HIW"*"HIG"/"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"        │  ┃\n"+
"     ┃  │         *"HIG"\\"HIW"*"CYN"t"HIW"*"HIG"|"HIY"Y"HIG"^\\^"HIY"Y"HIG"|"HIW"*"HIG"l"HIW"*"HIG"/"HIW"*        │  ┃\n"+
"     ┃  │        *"MAG"s"HIW"*"HIG"|"HIY"Y"HIG"^\\\\^/^//^"HIY"Y"HIG"|"HIW"*"HIR"a"HIW"*       │  ┃\n"+
"     ┃  │        "GRN"^"YEL"Y"GRN"^\\\\_^\\\\\\//^_//^"YEL"Y"GRN"^"HIW"       │  ┃\n"+
"     ┃  │        "GRN"^\\_^\\_\\_\\//_/_/^_/^"HIW"       │  ┃\n"+
"     ┃  │         "GRN"^^\\_^\\_\\\\/_/^_/^^"HIW"        │  ┃\n"+
"     ┃  │           "GRN"^^\\_ \\// _/^^"HIW"          │  ┃\n"+
"     ┃  │               "GRN"\\_\\_/"HIW"              │  ┃\n"+
"     ┃  │                "GRN"/|\\"HIW"               │  ┃\n"+
"     ┃  │               "GRN"/\\\\/\\"HIW"              │  ┃\n"+
"     ┃  │                                  │  ┃\n"+
"     ┃  │                  "RED"俠客行一百恭賀"HIW"  │  ┃\n"+
HIW"     ┃  └─────────────────┘  ┃\n"+
"     ┗━━━━━━━━━━━━━━━━━━━━━┛\n"+
"\n"HIY+"卡編號："+query("holiday_cards", me)+
"\n"NOR);
        }
        return 1;
}
int do_chaikai()
{
        object me = this_player();

        if (!present(this_object(), this_player()))
                return 0;

        message_vision("$N試圖拆開聖誕卡，發現這張卡已經被拆開過了。\n", me);
        return 1;
}

string query_autoload()
{ return 1 + ""; }