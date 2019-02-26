// Room: /d/yanping/yanjindu.c
// Date: Sep 28, 2002  Winder

#include <ansi.h>
inherit RIVER;

void create()
{
  set("short", "龍津渡");
  set("long", @LONG
延平又稱劍津、劍浦、南劍州，均源於晉時雌雄寶劍“雙劍化龍”
的歷史典故：〖晉書·張華傳〗載“（雷煥）遣使送一劍與華，留一自
佩，…，華誅，失劍所在。煥卒，子華為州從事，持劍行經延平，劍忽
自子腰間墜水，使人沒水取之，不見劍，但見兩龍各長數丈，蟠縈有文
章，沒者懼而返。須叟，光彩照水，波浪驚沸，於是劍失。”此處便是
化龍之處，雙溪在匯成閩江 (river)，洶湧東去。
LONG );
  set("exits", ([
    "northwest" : __DIR__"yanfumen",
  ]));
  set("no_clean_up", 0);
  set("outdoors", "yanping");
  set("coor/x", 1530);
  set("coor/y", -6200);
  set("coor/z", 10);
  set("yell_about", "船家");             // yell 船家
  set("river_type", "江");               // 江面上傳來回響
  set("need_dodge",300);                 // 需要多少輕功
  set("come_msg_out",   "一艘客船緩緩地駛了過來，艄公將一塊踏腳板搭上堤岸，以便乘客上下。\n");
  set("busy_msg",       "只聽得江面上隱隱傳來：“別急嘛，這兒正忙着吶……”\n");
  set("wait_msg",       "岸邊一艘客船上的老艄公説道：正等着你呢，上來吧。\n");
  set("leave_msg_out",  "艄公把踏腳板收了起來，竹篙一點，扁舟向江心駛去。\n");
  set("leave_msg_in",   "艄公把踏腳板收起來，説了一聲“坐穩嘍”，搖起櫓來，客船向下遊駛去。\n");
  set("come_msg_in",    "艄公説“到啦，上岸吧”，隨即把一塊踏腳板搭上堤岸。\n");
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
                                   // 渡船上的描述
  set("to",         "/d/fuzhou/matou");  // 船的終點 /*   必選   */
  setup();
}
