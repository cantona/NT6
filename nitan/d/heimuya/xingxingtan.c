// xingxingtan.c

inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();
int do_yell(string arg);
void reset();

void create()
{
        set("short", "猩猩灘");
        set("long", @LONG
只見一片長灘，山石殷紅如血，水流湍急，這便是有名的猩猩灘，
對面岸邊停泊着幾艘小船(boat)，要過對面就要靠這幾艘小船了。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "eastup" : __DIR__"shidao2",
        ]));
        set("item_desc", ([
            "boat" : "一葉小舟隱藏在蘆葦中，喊(yell)一聲試看。\n",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "heimuya");
        set("boat",1);
        set("opposite", __DIR__"changtan");
        setup();
}

void init()
{
    add_action("do_yell", "yell");
    add_action("do_cross", "cross");
}

void check_trigger()
{
    object room;

    if(!query("exits/enter") ) {
        if( !(room = find_object(__DIR__"duchuan1")) )
            room = load_object(__DIR__"duchuan1");
        if( room = find_object(__DIR__"duchuan1") ) {
            if( query("yell_trigger", room) == 0){
                set("yell_trigger", 1, room);
                set("exits/enter", __DIR__"duchuan1");
                set("exits/out", __FILE__, room);
                message("vision", "一葉扁舟緩緩地駛了過來，艄公將一塊踏腳"
                    "板搭上堤岸，以便乘客\n上下。\n", this_object() );
                message("vision", "艄公將一塊踏腳板搭上堤岸，形成一個向上"
                    "的階梯。\n", room);
                remove_call_out("on_board");
                call_out("on_board", 15);
            }
            else
                message("vision", "只聽得風浪中隱隱傳來：“別急嘛，"
                    "這兒正忙着吶……”\n",this_object() );
        }
        else
            message("vision", "ERROR: boat not found\n", this_object() );
    }
    else 
        message("vision", "岸邊一隻渡船上的艄公説道：正等着你呢，上來吧。\n",
            this_object() );
}


void on_board()
{
    object room;

    if( !query("exits/enter") ) return;

    message("vision", "艄公把踏腳板收了起來，竹篙一點，扁舟向河中撐去。\n",
        this_object() );

    if( room = find_object(__DIR__"duchuan1") )
    {
        delete("exits/out", room);
        message("vision", "艄公把踏腳板收起來，説了一聲“坐穩嘍”，"
            "竹篙一點，扁舟向\n河中撐去。\n", room );
    }
    delete("exits/enter");

    remove_call_out("arrive");
    call_out("arrive", 20);
}

void arrive()
{
    object room;
    if( room = find_object(__DIR__"duchuan1") )
    {
        set("exits/out", __DIR__"changtan", room);
        message("vision", "艄公説“到啦，上岸吧”，隨即把一塊踏腳板"
            "搭上堤岸。\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object(__DIR__"duchuan1") ) {
        delete("exits/out", room);
        message("vision","艄公把踏腳板收起來，把扁舟撐向河近岸。\n", room);
        delete("yell_trigger", room);
    }
}

int do_yell(string arg)
{
    string dir;

    if( !arg || arg=="" ) return 0;

    if( arg=="boat" ) arg = "船家";
    if( query("age", this_player())<16 )
        message_vision("$N使出吃奶的力氣喊了一聲：“" + arg + "”\n",
            this_player());
    else if( query("neili", this_player())>500 )
        message_vision("$N吸了口氣，一聲“" + arg + "”，聲音中正平和地遠遠傳"
            "了出去。\n", this_player());
    else
        message_vision("$N鼓足中氣，長嘯一聲：“" + arg + "！”\n",
            this_player());
    if( arg=="船家")
    {
        check_trigger();
        return 1;
    }
    else
        message_vision("風浪中遠遠傳來一陣回聲：“" + arg +
            "～～～”\n", this_player());
    return 1;
}

void reset()
{
    object room;

    ::reset();
    if( room = find_object(__DIR__"duchuan1") )
        delete("yell_trigger", room);
}

int do_cross()
{
    object me = this_player();

    if( query("family/family_name", me) != "日月神教" )
         return notify_fail("什麼？\n");

    if (me->query_skill("piaomiao-shenfa",1) < 100) 
    {
         tell_object(me, random(2) ? "你覺得江面太寬，沒有十足的把握躍過去。\n"
                     : "你看着波濤洶湧的江面，心裏不禁打了個突，沒敢亂來。\n");
         return 1;
    }

    if( query("neili", me)<100 )
    {
         tell_object(me, "你的內力不夠，還是休息一下再説吧。\n");
         return 1;
    }

    addn("neili", -50, me);
    message_vision("$N身形一晃，施展出飄渺身法，只見$P足尖點水，漸漸遠去。\n", me);
    tell_object(me, "你順利的到達了彼岸！\n");
    me->move(__DIR__"changtan");
    return 1;
}