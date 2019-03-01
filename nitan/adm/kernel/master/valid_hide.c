// This program is a part of NT MudLIB

/*
名稱：

       valid_hide - 允許或禁止一個物件具有匿蹤 (hide) 及看到匿蹤物件的能力。
語法：
        int valid_hide( object ob );

        整數 valid_hide( 物件 物件 );
用法：
        在主宰物件中 (master.c) 加上 valid_hide 可以讓物件具有自我匿蹤和看
        到其他匿蹤物件的能力。當一個物件使用 set_hide() 函式以進入匿蹤狀態
        時，此物件就當成 valid_hide() 的唯一參數呼叫此函式。允許此物件匿蹤
        時應傳回 1，反之則傳回 0。當一個物件想看到匿蹤狀態的物件時，也以同
        樣的方式呼叫此函式。
參考：
        set_hide
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻譯：
        spock@muds.net          2000.May.21.    v22 版
*/

// valid_hide: controls the use of the set_hide() efun, to hide objects or see hidden objects
int valid_hide(object who)
{
        return 1;
}

/*
int valid_hide(object ob)
{
        //"/system/daemons/channel_d.c"->channel_broadcast("sys",sprintf("1.%O\n this_player():%O\n this_player(1):%O\n",call_stack(1),this_player(),this_player(1)));
        //"/system/daemons/channel_d.c"->channel_broadcast("sys",sprintf("1.%O\n\n",find_player("lonely")));
        //if( call_stack(1)[<1]==this_object() ) return 1;
        if( this_player() && wizardp(this_player()) ) return 1;
        return 0;
}
*/