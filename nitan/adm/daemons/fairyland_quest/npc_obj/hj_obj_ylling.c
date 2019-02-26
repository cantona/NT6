//                標準描述長度示例                                   |
// 幻境內物品  幽靈之令(本物件不加入列表)
// by naihe 8:34 03-10-30 茂名
// 此為新增物品，作用是可在 hj_room1.c 快速得到武士JOB。
// 本令只能由該玩家保留。扔在地上或移交其他玩家，將會自動清除。

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name( HIB"幽靈之令"NOR, ({ "youling ling", "ling" }) );
    set("long", "這是一個幽靈族的令牌，就似正在幽幽散發着神祕的氣息，詭異莫名。\n");
    set("waiting_set",1);
// 調用時要 delete 此設置，否則會發生錯誤！

    set("unit", "個");
    set("hj_game/obj", "yl_ling");
    set("value", 1);
    set_weight(100);
    setup();
}

void init()
{
    remove_call_out("check_environment");
    if( !query("no_check") ) call_out("check_environment", 1);
}

void check_environment()
{
    object env;

    if( query("waiting_set") ) return;
    env = environment(this_object());

    if( !query("my_master")
       || query_temp("this_time_mark", query("my_master")) != query("this_time_mark" )
      || !env || env != query("my_master") )
    {
        remove_call_out("delete_me");
        remove_call_out("check_environment");
        set("no_check",1);
        call_out("delete_me", 1);
    }
}

void delete_me()
{
    message_vision( "$N忽地發出一陣淒厲之聲，消失不見了。\n", this_object());
    destruct(this_object());
}
