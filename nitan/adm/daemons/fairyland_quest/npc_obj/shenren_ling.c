//                標準描述長度示例                                   |
// 神人令  ， 持此令可令NPC不再攻擊自己。
// by naihe  2002-10-28  于茂名
// 本來寫了為了測試時用，但想想，加入遊戲內也是非常有意思呀。。。
// naihe 05-9-4 12:27 強化了，持令者可躲避來自各方面的一切攻擊行為，
//       包括NPC、玩家攻擊；驅逐、發呆旗之類的攻擊等。

#include <ansi.h>

inherit ITEM;

void create()
{
    set_name(HIY"神"HIM"人"HIR"令"NOR, ({"shenren ling","ling"}));
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);

    else
    {
        set("long", "這是一個「神人令」，它能散發神聖之氣，讓諸邪惡魔等不敢攻擊你。\n");
        set("unit", "個");
        set("value", 0);
    }

    set("hj_game/obj","shenren ling");
    setup();

    call_out("delete_me", 3 );
    // 發現未知bug。所以必須調用此函數，而任何復制此物品的主端，都需要以 waiting_delete()
    // 來設置數值。
}


// 其他地方復制此文件時，必須啟動本函數，設置刪除時間。
// 不允許有以前的“巫師用”的情況。無論如何，都要定期刪除。
void waiting_delete( int del_time )
{
    if( !del_time ) del_time = 3;
    if( del_time > 600 ) del_time = 600;
    // 最多 10 分鐘要刪除。

    set( "for_wiz_check_delete_time", del_time ); // 查詢時可以知道該令是否在延遲 delete 中
    remove_call_out( "delete_me" );
    call_out("delete_me", del_time );
}

void delete_me()
{
    if( !environment(this_object()) ) return;
    message_vision("$N忽地閃出耀眼光芒，隨即消失不見了。\n",this_object());
    destruct(this_object());
}