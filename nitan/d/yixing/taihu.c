// Room: /yixing/taihu.c
// Date: Nov.18 1998 by Winder

#include <ansi.h>
inherit RIVER;

void create()
{
        set("short", "太湖");
        set("long", @LONG
太湖古稱五湖，襟帶三州，周行五百裡，東南之水皆歸于此。其時
但見長天無波，放眼皆碧，七十二峰蒼翠挺立于三萬六千頃波濤之中，
不覺令人心懷大暢。由此登船可前往太湖之中的歸雲莊。
LONG );
        set("outdoors", "yixing");
        set("exits", ([
                "north" : __DIR__"shanlu1",
        ]));
        set("objects", ([
                "/d/guiyun/npc/xiaolu" : 1,
        ]));
        set("item_desc", ([
                "hu"  : HIC "\n近湖畔處有一葉小舟，舟上一個老梢公正在劃槳，也許大聲喊("
            HIY "yell" HIC ")一聲船\n家(" HIY "boat" HIC
            ")就能聽見。倘若你自負輕功絕佳,也可直接"
            "渡水(" HIY "cross" HIC ")踏水而過。\n" NOR,
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
                        "渡水(" HIY "cross" HIC ")踏水而過。\n" NOR );
  set("boat_short", "渡船");    
  set("boat_desc",  @LONG
離岸漸遠，四望空闊，真是莫知天地之在湖海，抑或是湖海之在天
地。老梢公在船尾悠閒地劃著水。
LONG );                                   // 渡船上的描述
  set("to",         "/d/guiyun/matou");  // 船的終點 /*   必選   */
        set("coor/x", 280);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
}
