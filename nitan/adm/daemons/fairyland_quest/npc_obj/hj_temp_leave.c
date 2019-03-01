// 配合 qxd 使用，玩家暫時離開時可以保護其角色的安全(攜帶此物件)
// naihe 05-9-4 13:48
// naihe 05-9-12 9:22 修正BUG，若指令 quit 時，則 quit.

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name( "幻境物件﹒臨時離開時用", ({ "hj temp leave obj" }) );
    set_weight(1);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "玩家攜帶時即禁止其一切指令。\n");
        set("unit", "個");
        set("value", 0);
    }
    set("hj_game/obj","hj leave obj");
    setup();
}
void init()
{
    object env, me = this_player();
    if( (env=environment(this_object()))
      && env == me
    )
    {
        mapping find_name = ([
            "feng" : HIW"風之國度"NOR,
            "yu"   : HIM"雨之國度"NOR,
            "lei"  : HIC"雷之國度"NOR,
            "dian" : HIG"電之國度"NOR,
        ]);
        set_temp( "apply/short", ({ sprintf( HIR"<暫時離開遊戲> "NOR"%s %s(%s)"NOR,
            find_name[ query_temp( "hj_game_find", me) ],
            query("name", me), capitalize(query("id", me)) ), }), me
        );
        set_temp("hj_apply_short", 1, me);
        message_vision( "\n$N暫時離開了幻境遊戲，系統將保護$N的角色安全。\n\n", me );
        tell_object( me, "\n\n                  返回遊戲請輸入 \"back\" \n\n\n" );
        // add_action( "filter_cmds", "", 1 );
        add_action( "filter_cmds", "");
    }
}
int filter_cmds(string arg)
{
    object me = this_player();
        if (! this_player()) return 1;
    if( query_verb() == "quit" )
    {
        return 0;
    }
    if( query_verb() == "back" )
    {
        mapping find_name = ([
            "feng" : HIW"風之國度"NOR,
            "yu"   : HIM"雨之國度"NOR,
            "lei"  : HIC"雷之國度"NOR,
            "dian" : HIG"電之國度"NOR,
        ]);
        set_temp( "apply/short", ({ sprintf( "%s %s(%s)"NOR,
            find_name[ query_temp( "hj_game_find", me) ],
            query("name", me), capitalize(query("id", me)) ), }), me
        );
        set_temp("hj_apply_short", 1, me);
        message_vision( "\n$N返回了幻境遊戲。\n\n", me );
        destruct( this_object() );
        return 1;
    }
    tell_object( me, "你現在暫時離開幻境遊戲。若需返回遊戲，請輸入 \"back\" \n" );
    return 1;
}
