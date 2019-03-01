// 9book.c

#include <ansi.h>;
inherit ITEM;
inherit F_UNIQUE;

void create()
{
        set_name(HIY"《九陰真經》"NOR,({ "jiuyin zhenjing", "9jing", "jing" }));
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是黃裳手書的《九陰真經》。紙張雖然已經發黃，但筆勢依然可以看出飛洒如雲煙：\n天之道，損有余而補不足，是故虛勝實，不足勝有余。\n");
                set("value", 3000);
                set("no_get",1);
                set("no_put",1);
                set("no_drop",1);
                set("material", "paper");
        }
}
void init()
{
  if (!query("inited"))
  {
                set("inited",1);
                remove_call_out("destbook");
                call_out("destbook", random(1200)+50);
        }
}
void destbook()
{
        message_vision(HIY "迎面走來一個模樣猥瑣的中年男人，與你擦身而過。你心中突然一個念頭冒起來：“我的$N！”\n"HIC"轉身欲追，中年男人已經消失不見了。\n"NOR, this_object());
        destruct(this_object());
}

void owner_is_killed()
{
       destruct(this_object());
}