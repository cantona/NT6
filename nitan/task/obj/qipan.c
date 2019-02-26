#include <ansi.h>
inherit TASK;
void create()
{
    set_name(YEL"棋盤"NOR, ({ "qipan" }) );
    set_weight(1);
    if( clonep() )
                destruct(this_object());
    else {
            set("unit", "個");
            set("material", "stone");
                        set("long", @LONG
弈者對壘，“三尺之局兮作戰場”，投子於枰，佈陣列勢，宛若將帥在
調動兵馬，佈置攻防。然而棋子畢竟是沒有生命力的靜物，陣列於縱橫
十九的棋盤上，竟然能生出無窮玄奧的變化來，所以竟有稱棋局為“鬼
陣”者。
LONG);
          } 
    set("owner", "蘇星河");
        setup();
}      
