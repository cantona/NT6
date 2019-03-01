// Room: /guiyun/matou.c
// Date: Nov.18 1998 by Winder
#include <ansi.h>
inherit RIVER;

void create()
{
        set("short", "碼頭");
        set("long", @LONG
這是一個在江南水鄉極常見的碼頭，由粗糙的大青條石搭成。西面
似乎有一個極大的莊院。靠岸停有一艘大漁船(ship)，大篷斜掛，風帆
大張，看那樣子不是為了出湖(hu)，倒象是征戰用的。
LONG );
        set("outdoors", "guiyun");
        set("no_clean_up", 0);
        set("item_desc", ([
                "ship":"這是太湖水盜劫富濟貧的戰船。上去(shang ship)就出發。\n",
                "hu"  : HIC "\n近湖畔處有一葉小舟，舟上一個老梢公正在劃槳，也許大聲喊("
                         HIY "yell" HIC ")一聲船\n家(" HIY "boat" HIC
                        ")就能聽見。倘若你自負輕功絕佳,也可直接"
                        "渡水(" HIY "cross" HIC ")踏水而過。\n" NOR,
        ]));
        set("exits", ([
                "east" : __DIR__"road2",
        ]));
  set("yell_about", "船家");             // yell 船家
  set("river_type", "湖");               // 江面上傳來回響
  set("need_dodge",300);                 // 需要多少輕功
  set("come_msg_out",   "一葉扁舟緩緩地駛了過來，艄公將一塊踏腳板搭上堤岸，以便乘客上下。\n");
  set("busy_msg",       "只聽得湖面上隱隱傳來：“別急嘛，這兒正忙著吶……”\n");
  set("wait_msg",       "岸邊一只渡船上的老艄公說道：正等著你呢，上來吧。\n");
  set("leave_msg_out",  "艄公把踏腳板收了起來，竹篙一點，扁舟向湖心駛去。\n");
  set("leave_msg_in",   "艄公把踏腳板收起來，說了一聲“坐穩嘍”，竹篙一點，扁舟向湖心駛去。\n");
  set("come_msg_in",    "艄公說“到啦，上岸吧”，隨即把一塊踏腳板搭上堤岸。\n");
  set("item_desc/river", HIC "\n近湖畔處有一葉小舟，舟上一個老梢公正在劃槳，也許大聲喊("
                         HIY "yell" HIC ")一聲船\n家(" HIY "boat" HIC
                        ")就能聽見。倘若你自負輕功絕佳,也可直接"
                        "渡水(" HIY "cross" HIC ")踏水而過。\n" NOR);
  set("boat_short", "渡船");    
  set("boat_desc",  @LONG
離岸漸遠，四望空闊，真是莫知天地之在湖海，抑或是湖海之在天
地。老梢公在船尾悠閒地劃著水。
LONG );
  set("to", "/d/yixing/taihu");
        set("coor/x", 280);
        set("coor/y", -860);
        set("coor/z", 0);
        setup();
}
void init()
{
        ::init();
        add_action("do_shang", "shang");
}

int do_shang ( string arg )
{
        object ob ;
        string dir;
        if( !arg || arg !="ship" ) 
        {
                 tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
                 return 1 ;
        }
        ob = this_player () ;
        message_vision("船上群盜一見$N上船，忙叫了一聲：首領來了，開船嘍！殺金狗去！\n", ob);
        message_vision("船上升起帆，船就向湖中航行。\n", ob);
        ob ->move("/d/guiyun/ship") ;
        tell_object(ob, CYN "你率船在湖上破浪前行，戰旗獵獵.......\n" NOR ) ;
        call_out("rjinbing", 10 , ob );
        return 1 ;
}
void rjinbing( object ob )
{
        object ship, jinship;
        if(!( ship = find_object("/d/guiyun/ship")) )
                  ship = load_object("/d/guiyun/ship");
        if(!( jinship = find_object("/d/guiyun/jinship")) )
                  jinship = load_object("/d/guiyun/jinship");
        tell_object(ob , "戰船在一陣陣喊殺聲中撞上了另一艘大船。\n" ) ;
        set("exits/out", "/d/guiyun/jinship", ship);
        set("exits/out", "/d/guiyun/ship", jinship);
}
