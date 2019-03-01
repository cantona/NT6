// Room: carol/heimuya

#include <ansi.h>
inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();
int do_insert(string arg);
int do_push(string arg);
void goto_heimuya(object ob);

void create()
{
    set("short", "日月坪");
        set("long", @LONG
這裡是半山的一片小土坪，離崖頂還有一段路途，可到這已經沒
有路上去，面前是如境般的峭壁，仰頭而望，但見崖頂依稀聳立著樓
閣，宛如仙境。可雲煙繚繞，看不清晰。從懸崖上垂下一條繩索(rop
e)，看上去象是懸崖上下互通消息的工具，繩索的上面似乎隱約有一
個吊籃(basket)。懸崖的牆上似乎有一個匣子(xiazi) ，你似乎走入
一個霧宅，真不知如何是好。
LONG );

    set("exits", ([
        "eastdown" : __DIR__"shimen",
    ]));
    set("objects", ([
        CLASS_D("riyue") + "/zhang1" : 1,
    ]));

    set("outdoors", "heimuya");
    set("item_desc", ([
        "basket": "那是一個掉籃，看樣子有些古怪。\n",
        "rope"  : "繩子就是繩子，可能是向上的工具。\n",
        "xiazi" : "這是一個匣子，好像可以按(push)下去。匣子的側面有一個插孔。\n",
    ]));

    setup();
}

void init()
{
    add_action("do_insert", "insert");
    add_action("do_push", "push");
        add_action("do_float", "float");
        add_action("do_float", "piao");
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
                        "掉籃(basket)從天而降，你不禁一怔！\n", this_object());
                set("item_desc", ([
                    "basket" : "這是一個掉籃，是傳說中的交通工具。\n",
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
    tell_object(me, HIG"只見掉籃緩緩向上，四周無限美好，"
                "你似乎置身于一處人間仙境無異。\n"NOR);

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
        set("exits/out", __DIR__"up2", room);
        message("vision", "□的一聲，你似乎一下從天上到了地上。\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object(__DIR__"basket") )
    {
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

    if( !arg || arg=="" )   return 0;

    if( arg=="卡" )   arg = "card1";

    if( arg=="card1")
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
                message("vision", "□的一聲，你看到掉籃向下一節。\n",me );
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

int do_push(string arg)
{
    object ob, myenv;
    ob = this_player();

    if( !arg || arg != "xiazi" )
         return notify_fail("你要 push 什麼？\n");

    if( query("family/family_name", ob) == "日月神教" )
    {
         message_vision("$N把匣子按了幾下，只聽“吱扭吱扭”幾聲，從崖上落下一個大吊籃。\n", ob);
         message_vision("$N一彎腰進了吊籃，吊籃緩緩地絞上崖去......\n", ob);
         myenv = environment(ob);
         ob->move (__DIR__"basket");
         call_out("goto_heimuya", 10, ob);
         return 1;
    }
    else
         message_vision("$N把匣子按了幾下，但好像沒什麼作用。\n",ob);
    return 1;
}

void goto_heimuya(object ob)
{
    tell_object(ob , "你眼前一亮，一幢幢白色建築屹立眼前，霎是輝煌。\n");
    ob->move(__DIR__"chengdedian");
}

int do_float()
{
        object me;

        me = this_player();

        if (me->query_skill("juechen-shenfa", 1) < 180)
        {
                message_vision("$N遙望山崖，沉思良久，嘆了口氣。\n", me);
                return 1;
        }

        if( query("neili", me)<100 )
        {
                tell_object(me, "你的內力不夠，還是休息一下再說吧。\n");
                return 1;
        }

        addn("neili", -80, me);

        message_sort(HIC "\n$N" HIC "深深納入一口氣，驀地一飛而起，朝"
                     "山崖上飄去。\n\n" NOR, me);

        me->move(__DIR__"shanya3");
        tell_object(me, "你順著崖壁飄上了黑木崖。\n");
        message("vision", HIC "\n忽聽一聲清嘯由遠及近，" + me->name() +
                          HIC "順著崖壁飄然而上，落定身形。\n" NOR,
                          environment(me), ({ me }));
        return 1;
}
