// Room: /huanghe/guchangcheng.c
// Java Sep. 22 1998

#include <ansi.h>
inherit RIVER;

void create()
{
        set("short", "古長城");
        set("long", @LONG
這裏是一段古長城。相傳是當年秦始皇派他的心腹愛將蒙恬率三
十萬大軍所修。世事變遷、滄海桑田，如今這裏已是一片廢墟，唯一
依稀可見的是夯土製成的烽火台象個小土包一樣矗立在那裏。黃河從
西向東流去，河上有一葉小舟擺渡乘客，你可以叫(yell)一下船家。
LONG );
        set("exits", ([
                "southwest" : __DIR__"yinpanshui",
                "southeast" : __DIR__"shimen",
        ]));
        set("objects", ([
                __DIR__"npc/menmian" :1,
        ]));
        set("outdoors", "yongdeng");
  set("yell_about", "船家");             // yell 船家
  set("river_type", "河");               // 江面上傳來回響
  set("need_dodge",300);                 // 需要多少輕功
  set("come_msg_out",   "一葉扁舟緩緩地駛了過來，艄公將一塊踏腳板搭上堤岸，以便乘客上下。\n");
  set("busy_msg",       "只聽得風浪中隱隱傳來：“別急嘛，這兒正忙着吶……”\n");
  set("wait_msg",       "岸邊一隻渡船上的老艄公説道：正等着你呢，上來吧。\n");
  set("leave_msg_out",  "艄公把踏腳板收了起來，竹篙一點，扁舟向河中撐去。\n");
  set("leave_msg_in",   "艄公把踏腳板收起來，説了一聲“坐穩嘍”，竹篙一點，扁舟向河中撐去。\n");
  set("come_msg_in",    "艄公説“到啦，上岸吧”，隨即把一塊踏腳板搭上堤岸。\n");
  set("item_desc/river", HIC "\n只見近岸處有一條渡船，也許大聲喊("
                         HIY "yell" HIC ")一聲船家(" HIY "boat" HIC
                        ")就\n能聽見。倘若你自負輕功絕佳,也可直接"
                        "渡水(" HIY "cross" HIC ")踏河而過。\n" NOR);
  set("boat_short", "渡船");    
  set("boat_desc",  @LONG
黃河上的小舟都是這種很簡陋的小舟。一位中年艄公正站在船尾
吃力地掌舵，一位膀子壯碩的小夥子也在船頭用勁地划水撐船。黃河
水流湍急，船下滑很快，橫渡卻很慢。
LONG );
  set("to",         "/d/lingzhou/xuanhebao");  // 船的終點 /*   必選   */
        set("coor/x", -16070);
	set("coor/y", 4290);
	set("coor/z", 0);
	setup();
}
