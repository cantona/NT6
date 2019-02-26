// Room: /d/fuzhou/matou.c
// Last Modified by winder on Sep. 20 2002

#include <ansi.h>
inherit RIVER;


void create()
{
  set("short", "中洲碼頭");
  set("long", @LONG
這裏是福州中洲碼頭，眼前閩江水(river) 波濤翻滾，船隻穿梭來
往不斷。這裏有通往上游延平府的客船。
LONG );
  set("exits", ([
    "east" : __DIR__"zhongzhou",
  ]));
  set("no_clean_up", 0);
  set("outdoors", "fuzhou");
  set("yell_about", "船家");             // yell 船家
  set("river_type", "江");               // 江面上傳來回響
  set("need_dodge",300);                 // 需要多少輕功
  set("busy_msg",       "只聽得江面上隱隱傳來：“別急嘛，這兒正忙着吶……”\n");
  set("come_msg_out",   "一艘客船緩緩地駛了過來，艄公將一塊踏腳板搭上堤岸，以便乘客上下。\n");
  set("come_msg_in",    "艄公説“到啦，上岸吧”，隨即把一塊踏腳板搭上堤岸。\n");
  set("wait_msg",       "岸邊一艘客船上的老艄公説道：正等着你呢，上來吧。\n");
  set("leave_msg_out",  "艄公把踏腳板收了起來，搖起櫓來，客船向上遊駛去。\n");
  set("leave_msg_in",   "艄公把踏腳板收起來，説了一聲“坐穩嘍”，搖起櫓來，客船向上遊駛去。\n");
  set("item_desc/river", HIC "\n只見近岸處有一艘客船，也許大聲喊("
                         HIY "yell" HIC ")一聲船家(" HIY "boat" HIC
                        ")就\n能聽見。倘若你自負輕功絕佳,也可直接"
                        "渡水(" HIY "cross" HIC ")踏江而過。\n" NOR);
  set("boat_short", "客船");    
  set("boat_desc",  @LONG
這是一艘在閩江上航行的大客船，大概能載上那麼百把個人。兩邊
十幾個水手握着長長的槳，船尾一名六十多歲的老艄公把着櫓。江面的
水非常清澈，兩邊的山峯險峻，蒼翠的森林中時而傳來野獸的嘶嚎。
LONG );
  set("to",         "/d/yanping/longjindu");  // 船的終點 /*   必選   */
	set("coor/x", -90);
	set("coor/y", -6220);
	set("coor/z", 0);
	setup();
}
