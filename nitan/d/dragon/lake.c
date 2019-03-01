inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "三清湖");
        set("long",
"[1;32m湖水清澈透明，不時可以看到幾尾魚跳上水面。湖水盡頭是\n"
"一個大瀑布。在這裡可以聽到瀑布從山上直沖而下，發出的轟轟雷聲。湖\n"
"邊一塊巨石，上寫〝三清湖〝，湖中有一葉扁舟。\n"
);
        set("exits", ([ 
  "north" : __DIR__"village",
  "east" : __DIR__"lake1",
]));
        set("resource/water",1);
         set("no_magic", 1);
        setup();
}
void init()
{
    add_action("do_yell", "yell");
}

void check_trigger()
{
    object room;

    if(!query("exits/enter") ) {
        if( !(room = find_object(__DIR__"duchuan")) )
            room = load_object(__DIR__"duchuan");
        if( room = find_object(__DIR__"duchuan") ) {
            if( query("yell_trigger", room) == 0){
                set("yell_trigger", 1, room);
                set("exits/enter", __DIR__"duchuan");
                set("exits/out", __FILE__, room);
                message("vision", "一葉扁舟緩緩地駛了過來，艄公將一塊踏腳"
                    "板搭上堤岸，以便乘客\n上下。\n", this_object() );
                message("vision", "艄公將一塊踏腳板搭上堤岸，形成一個向上"
                    "的階梯。\n", room);
                remove_call_out("on_board");
                call_out("on_board", 15);
            }
            else
                message("vision", "只聽得湖面上隱隱傳來：“別急嘛，"
                    "這兒正忙著吶……”\n",this_object() );
        }
        else
            message("vision", "ERROR: boat not found\n", this_object() );
    }
    else 
        message("vision", "岸邊一只渡船上的老艄公說道：正等著你呢，上來吧。\n",
            this_object() );
}
void on_board()
{
    object room;

    if( !query("exits/enter") ) return;

    message("vision", "艄公把踏腳板收了起來，竹篙一點，扁舟向湖心駛去。\n",
        this_object() );

    if( room = find_object(__DIR__"duchuan") )
    {
        delete("exits/out", room);
        message("vision", "艄公把踏腳板收起來，說了一聲“坐穩嘍”，"
            "竹篙一點，扁舟向\n湖心駛去。\n", room );
    }
    delete("exits/enter");

    remove_call_out("arrive");
    call_out("arrive", 20);
}
void arrive()
{
    object room;
    if( room = find_object(__DIR__"duchuan") )
    {
        set("exits/out", __DIR__"spirit9", room);
        message("vision", "艄公說“到啦，上岸吧”，隨即把一塊踏腳板"
            "搭上堤岸。\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object(__DIR__"duchuan") ) {
        delete("exits/out", room);
        message("vision","艄公把踏腳板收起來，把扁舟駛向湖心。\n", room);
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
     if( !query_temp("m_success/初級", this_player()))return notify_fail("你是怎麼來的？巫師抓的？那可不好。\n");

     if( !query_temp("m_success/幻影", this_player()))return notify_fail("你沒能親力解開封印，不能渡你過去呢。\n");

     if( !query_temp("m_success/孽龍", this_player()))return notify_fail("你參加屠龍了嗎？或者你沒親手殺了它？這樣是不行的。\n");
        check_trigger();
        return 1;
    }
    else
        message_vision("湖面上遠遠傳來一陣回聲：“" + arg +
            "～～～”\n", this_player());
    return 1;
}

void reset()
{
    object room;

    ::reset();
    if( room = find_object(__DIR__"duchuan") )
        delete("yell_trigger", room);
}

