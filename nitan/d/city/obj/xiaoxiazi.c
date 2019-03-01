// xiaoxiazi.c
// 未調試完。 需要have_married這個標記
// 還是等結婚做好吧。

inherit ITEM;
inherit F_UNIQUE;

int opening();
int halt_opening();

void create()
{
    set_name( "小匣子", ({ "xiao xiazi", "xiazi", "box" }) );
    set_weight( 2000 );
    if ( clonep() )
        set_default_object( __FILE__ );
    else
    {
        set( "long", @LONG
這個匣子雖小，卻入手很沉，不知道是什麼材料制成的。匣子表面上刻著一些神
秘的花紋，隱隱泛著柔和的紅光，看上去有些奇異。
LONG
        );
        set( "unit", "個" );
        set( "value", 40 );
    }
    setup();
}

void init()
{
    add_action( "do_open_box", ({ "open", "kai" }) );
}

int do_open_box( string arg )
{
    object me = this_player();

    // 計劃 : 如果是結婚的一對合作打開這個匣子，能得到護花鈴。
    // 沒有結婚根本打不開。

    if ( !arg ) return 0;
    if ( !me->can_act() ) return 0;
    if ( !this_object()->id( arg ) ) return 0;

    if ( query ( "opened" ) ) return notify_fail( "這個匣子已經打開了。" );

    if( !query("have_married", me) )
        return notify_fail( "你試圖打開這個匣子，當你的手一觸到匣子，感覺到一股奇異的力量將你的手推開。\n" );
    else
    {
        set_temp("open_box_mark", 51, me);
        if ( !query_temp ( "open_box" ) )
        {
            set_temp("open_box",query("have_married", me));
        }
        {
            set_temp( "both_open", 1 ); 
        }
        me->start_busy( (:opening:), (:halt_opening:) );
        return 1;
    }
    return 0;
}

int opening()
{
    object ob, me = this_player();
    int mark=query_temp("open_box_mark", me);

    if ( mark > 50 )
    {
        message_vision( "$N伸手按在匣子上。\n", me );
        write ( "你突然感到匣子裡有一種奇異的力量吸引著你的手掌。\n" );
        addn_temp("open_box_mark", -10, me);
        return 1;
    }

    if ( mark < 10 ) 
    {
        // 很遺憾了，時間過了。
        message_vision( "時間過了", me );
        delete_temp("open_box_mark", me);
        remove_call_out( "del_temp" );
        call_out( "del_temp" , 1 );
        return 0;
    }

    addn_temp("open_box_mark", -10, me);
    if ( !query_temp( "both_open" ) )
    {
        // 接著按著這個匣子吧。
        message_vision( "還按著", me );
        return 1;
    }
    // 該合作打開這個匣子了。
    else if( query_temp("open_box") != query("have_married", me )
        && query_temp( "open_box" ) != me)
    {
        // 不是一對夫妻，卻妄圖打開這個匣子，該怎麼處理呢？
        // 一定要給懲罰！grin
        message_vision( "", me );
        delete_temp("open_box_mark", me);
        remove_call_out( "del_temp" );
        call_out( "del_temp", 1 );
        return 0;
    }
    else
    {
        // 哈哈，終于是一對夫妻在開這個匣子了。:-)
        message_vision( "", me );
        // new一雙護花鈴，夫妻倆一人一個。
        ob = new( __DIR__"huhua_ling" );
        ob->move(me);
        delete_temp("open_box_mark", me);
        remove_call_out( "del_temp" );
        call_out( "del_temp", 2 );
        return 0;
    }
    return 0;
}

int halt_opening()
{
    object me = this_player();
    write( "你放棄開啟這個匣子的企圖了。\n" );
    delete_temp("open_box_mark", me);
    remove_call_out( "del_temp" );
    call_out( "del_temp" , 1 );
    return 1;
}

void del_temp()
{
    if ( query_temp( "open_box" ) )
        delete_temp( "open_box" );
}