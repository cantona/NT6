//Edited by fandog, 02/15/2000

#include <ansi.h>
inherit RIVER;

void create()
{
        set("short", "漢陽碼頭");
        set("long", @LONG
面前是一條波濤翻滾的大江 (river)。濁流滾滾，千帆競發。兩岸
渡船來來往往，不少過江客都在這裏等待渡船擺渡。
LONG );
        set("exits", ([
                "west" : __DIR__"hzjie2",
        ]));
        set("item_desc", ([
                "river" : "近岸處有幾隻渡船，也許喊(yell)一聲船家就能聽見。\n",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "wuchang");
  set("yell_about", "船家");             // yell 船家
  set("river_type", "江");               // 江面上傳來回響
  set("need_dodge",300);                 // 需要多少輕功
  set("come_msg_out",   "一隻木船緩緩地駛了過來，艄公將一塊踏腳板搭上堤岸，以便乘客上下。\n");
  set("busy_msg",       "只聽得江面上隱隱傳來：“別急嘛，這兒正忙着吶……”\n");
  set("wait_msg",       "岸邊一隻渡船上的老艄公説道：正等着你呢，上來吧。\n");
  set("leave_msg_out",  "艄公把踏腳板收了起來，竹篙一點，木船向江心駛去。\n");
  set("leave_msg_in",   "艄公把踏腳板收起來，説了一聲“坐穩嘍”，竹篙一點，木船向江心駛去。\n");
  set("come_msg_in",    "艄公説“到啦，上岸吧”，隨即把一塊踏腳板搭上堤岸。\n");
  set("item_desc/river", HIC "\n只見近岸處有幾隻渡船，也許大聲喊("
                         HIY "yell" HIC ")一聲船家(" HIY "boat" HIC
                        ")就\n能聽見。倘若你自負輕功絕佳,也可直接"
                        "渡水(" HIY "cross" HIC ")踏江而過。\n" NOR);
  set("boat_short", "渡船");    
  set("boat_desc",  @LONG
    一葉小舟，最多也就能載七、八個人。一名年輕力壯的艄公手持長
竹篙，正在船尾用力地撐着船，一邊還吆喝着船歌：走四方～路迢迢～
水長長……
LONG );
  set("to",         __DIR__"matou2");  // 船的終點 /*   必選   */
	set("coor/x", -5080);
	set("coor/y", -1870);
	set("coor/z", 0);
	setup();
}
