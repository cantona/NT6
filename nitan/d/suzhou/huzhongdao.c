// Room: /d/suzhou/huzhongdao.c
// Last Modified by winder on Mar. 8 2001

#include <ansi.h>
inherit RIVER;

void create()
{
        set("short", "湖中島");
        set("long",@long
這裡是太湖中心的一個小島，小島的中心有一座亭子。
long);
        set("outdoors","suzhou");
        set("exits",([
                "north" : __DIR__"bishuiting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 800);
        set("coor/y", -1205);
        set("coor/z", 0);
  set("yell_about", "船家");             // yell 船家
  set("river_type", "湖");               // 江面上傳來回響
  set("need_dodge",300);                 // 需要多少輕功
  set("come_msg_out",   "一葉扁舟緩緩地駛了過來，採蓮女將一塊踏腳板搭上堤岸，以便乘客上下。\n");
  set("busy_msg",       "只聽得湖面上隱隱傳來：“別急嘛，這兒正忙著吶……”\n");
  set("wait_msg",       "岸邊一只渡船上的採蓮女說道：正等著你呢，上來吧。\n");
  set("leave_msg_out",  "採蓮女把踏腳板收了起來，竹篙一點，扁舟向湖邊駛去。\n");
  set("leave_msg_in",   "採蓮女把踏腳板收起來，說了一聲“坐穩嘍”，竹篙一點，扁舟向湖邊駛去。\n");
  set("come_msg_in",    "採蓮女說“到啦，上岸吧”，隨即把一塊踏腳板搭上堤岸。\n");
  set("item_desc/river", HIC "\n只見近岸處有一葉小舟，也許大聲喊("
                         HIY "yell" HIC ")一聲船家(" HIY "boat" HIC
                        ")就\n能聽見。倘若你自負輕功絕佳,也可直接"
                        "渡水(" HIY "cross" HIC ")踏水而過。\n" NOR);
  set("boat_short", "渡船");    
  set("boat_desc",  @LONG
一葉小舟，最多也就能載七、八個人。一名十多歲的採蓮小姑娘手
持長竹篙，正在船尾輕輕地盪舟。
LONG );
  set("to",         __DIR__"road5");  // 船的終點 /*   必選   */
        setup();
}
