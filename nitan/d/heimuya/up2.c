// Room: carol/heimuya

#include <ansi.h>
inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();
void reset();
int do_insert(string arg);

void create()
{
        set("short", "懸崖");
        set("long", @LONG
又一座陡峭的懸崖立在了你的面前。懸崖上彷彿有座白色的建築，
可雲煙繚繞，看不清晰。崖上又垂下一條繩索(rope)，看上去象是懸
崖上下互通消息的工具。繩索的上面似乎隱約有一個弔籃(basket)，
懸崖的牆上似乎有一個匣子(xiazi)。
LONG );

    set("exits", ([
        "westdown" : __DIR__"up1",
    ]));
    set("item_desc", ([
        "basket": "那是一個掉籃，看樣子有些古怪。\n",
        "rope"  : "繩子就是繩子，可能是向上的工具。\n",
        "xiazi" : "這是一個匣子，看樣子是一個開關，匣子的側面有一個插孔。\n",
    ]));
    set("no_clean_up", 0);
    setup();
}

void init()
{
    add_action("do_insert", "insert");
}

void check_trigger()
{
    object room;

    if(!query("exits/enter") ) {
        if( !(room = find_object(__DIR__"basket")) )
            room = load_object(__DIR__"basket");
        if( room = find_object(__DIR__"basket") ) {
            if( query("insert_trigger", room) == 0){
                set("insert_trigger", 1, room);
                set("exits/enter", __DIR__"basket");
                set("exits/out", __FILE__, room);
                message("vision", "“叭”的一聲，你手中的令牌已被折斷，只見一個"
                        "掉籃(basket)從天而降，你不禁一怔！\n", this_object() );
                set("item_desc", ([
                    "basket" : "這是一個掉籃，是傳説中的交通工具。\n",
                ]));
                
                remove_call_out("on_board");
                call_out("on_board", 15);
            }
            else
                message("vision", "看樣子你得等下撥兒。\n",this_object() );
        }
        else
            message("vision", "ERROR: basket not found\n", this_object() );
    }
}

void on_board()
{
    object room, me = this_player();

    if( !query("exits/enter") ) return;
    tell_object(me, HIG"只見掉籃緩緩向上，四周無限美好，\n"
                "你似乎置身於一處人間仙境無異。\n"NOR);

    if( room = find_object(__DIR__"basket") )
    {
        delete("exits/out", room);
    }
    delete("exits/enter");
    remove_call_out("arrive");
    call_out("arrive",20);
}

void arrive()
{
    object room;
    if( room = find_object(__DIR__"basket") )
    {
        set("exits/out", __DIR__"up3", room);
        message("vision", "噔的一聲，你似乎一下從天上到了地上。\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object(__DIR__"basket") ) {
        delete("exits/out", room);
        delete("insert_trigger", room);
    }
}

int do_insert(string arg)
{
    string dir;
    object ob;
    object me;

    me=this_player();

    if( !arg || arg=="" ) return 0;
    if( arg=="卡" ) arg = "card2";   
    if( arg=="card2")
    {
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上沒有這樣東西。\n");

        if( !query_temp("mark/cards", me) )
                set_temp("mark/cards", 1, me);

        if( query_temp("mark/cards", me) == 4 )
        {
                delete_temp("mark/cards", me);
                destruct(ob);
                check_trigger();
        }
        else    {
                addn_temp("mark/cards", 1, me);
                message("vision", "噔的一聲，你看到掉籃向下一節。\n",me );
        }
    }
    else
    {
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上沒有這樣東西。\n");
        else    return notify_fail(ob->name() + "好像跟插孔不合，怎麼也插不進去。\n");
    }
    return 1;
}
