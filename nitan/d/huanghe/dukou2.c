// Room: /d/huanghe/dukou2.c
// Last Modified by winder on Apr. 10 2000
#include <ansi.h>
inherit RIVER;

void create()
{
    set("short", "龍門渡口");
    set("long", @LONG
渡口前就是洶湧澎湃的黃河(he)了。濁流滾滾，泥沙俱下，聲震數
裡。兩岸渡船來來往往，在波谷中穿行，甚為兇險。過了黃河，對面就
是山西了。
LONG );
  set("yell_about", "船家");             // yell 船家
  set("river_type", "河");               // 江面上傳來回響
  set("need_dodge",300);                 // 需要多少輕功
  set("come_msg_out",   "一葉扁舟緩緩地駛了過來，艄公將一塊踏腳板搭上堤岸，以便乘客上下。\n");
  set("busy_msg",       "只聽得風浪中隱隱傳來：“別急嘛，這兒正忙著吶……”\n");
  set("wait_msg",       "岸邊一只渡船上的老艄公說道：正等著你呢，上來吧。\n");
  set("leave_msg_out",  "艄公把踏腳板收了起來，竹篙一點，扁舟向河中撐去。\n");
  set("leave_msg_in",   "艄公把踏腳板收起來，說了一聲“坐穩嘍”，竹篙一點，扁舟向河中撐去。\n");
  set("come_msg_in",    "艄公說“到啦，上岸吧”，隨即把一塊踏腳板搭上堤岸。\n");
  set("item_desc/river", HIC "\n只見一葉小舟搖擺不定地頂風前行，也許大聲喊("
                         HIY "yell" HIC ")一聲船家(" HIY "boat" HIC
                        ")就\n能聽見。倘若你自負輕功絕佳,也可直接"
                        "渡水(" HIY "cross" HIC ")踏河而過。\n" NOR);
  set("boat_short", "渡船");    
  set("boat_desc",  @LONG
黃河上的小舟都是這種很簡陋的小舟。一位中年艄公正站在船尾
吃力地掌舵，一位膀子壯碩的小伙子也在船頭用勁地劃水撐船。黃河
水流湍急，船下滑很快，橫渡卻很慢。
LONG );
  set("to",         "/d/heimuya/dukou1");  // 船的終點 /*   必選   */
    set("exits", ([
        "southwest" : "/d/huanghe/weifen",
    ]));
    set("item_desc", ([
        "he" : "一葉小舟搖擺不定地頂風前行，喊(yell)一聲試看。\n",
    ]));
    set("no_clean_up", 0);
    set("outdoors", "heimuya");
        set("coor/x", -1500);
        set("coor/y", 2000);
        set("coor/z", 0);
        setup();
}
