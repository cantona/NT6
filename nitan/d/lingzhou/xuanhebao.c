// Room: /lingzhou/xuanhebao.c
// Java Sep.23 1998

#include <ansi.h>
inherit RIVER;

void create()
{
        set("short", "宣和堡");
        set("long", @LONG
這裡就是西北小鎮宣和堡，南面是黃河，西面是沙漠，只有這裡
有一片不大的綠洲，住戶們都是從關內遷移過來的，大多以經營手工
藝品為生, 這裡的手織羊毛掛毯頗有名氣。每逢初一、十五附近的百
姓都來到這擺渡過河到關內去趕集。河案邊熙熙攘攘，人們都在爭著
叫(yell)船過河。
LONG        );
        set("exits", ([
                "northeast" : __DIR__"mingshazhou",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
  set("yell_about", "船家");             // yell 船家
  set("river_type", "河");               // 江面上傳來回響
  set("need_dodge",300);                 // 需要多少輕功
  set("come_msg_out",   "一葉扁舟緩緩地駛了過來，艄公將一塊踏腳板搭上堤岸，以便乘客上下。\n");
  set("busy_msg",       "只聽得風浪中隱隱傳來：“別急嘛，這兒正忙著吶……”\n");
  set("wait_msg",       "岸邊一只渡船上的老艄公說道：正等著你呢，上來吧。\n");
  set("leave_msg_out",  "艄公把踏腳板收了起來，竹篙一點，扁舟向河中撐去。\n");
  set("leave_msg_in",   "艄公把踏腳板收起來，說了一聲“坐穩嘍”，竹篙一點，扁舟向河中撐去。\n");
  set("come_msg_in",    "艄公說“到啦，上岸吧”，隨即把一塊踏腳板搭上堤岸。\n");
  set("item_desc/river", HIC "\n只見近岸處有一條渡船，也許大聲喊("
                         HIY "yell" HIC ")一聲船家(" HIY "boat" HIC
                        ")就\n能聽見。倘若你自負輕功絕佳,也可直接"
                        "渡水(" HIY "cross" HIC ")踏河而過。\n" NOR);
  set("boat_short", "渡船");    
  set("boat_desc",  @LONG
黃河上的小舟都是這種很簡陋的小舟。一位中年艄公正站在船尾
吃力地掌舵，一位膀子壯碩的小伙子也在船頭用勁地劃水撐船。黃河
水流湍急，船下滑很快，橫渡卻很慢。
LONG );
  set("to",         "/d/yongdeng/guchangcheng");  // 船的終點 /*   必選   */
        set("coor/x", -6325);
        set("coor/y", 2865);
        set("coor/z", 0);
        setup();
}
