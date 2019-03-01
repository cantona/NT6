// Room: /d/yueyang/matou.c
// Last Modifyed by Winder on Dec. 4 2001
#include <ansi.h>
inherit RIVER;

void create()
{
        set("short", "君山碼頭");
        set("long", @LONG
君山在岳陽西南三十裡的洞庭湖中，是一座方圓不過三、四裡的小
島。原名洞府山，取意神仙“洞府之庭”。傳說這座“洞庭山浮于水上
，其下有金堂數百間，玉女居之，四時聞金石絲竹之聲，砌于山頂”。
這浪漫神話傳說，不足為信。後因舜帝的兩個妃子娥皇、女英葬于此，
屈原在《九歌》中稱之為湘君和湘夫人，故後人將此山改名為君山。
    這裡是君山碼頭，東面遠遠可以看到巍峨的岳陽樓，中間隔著洞庭
湖(hu)的萬頃波濤。
LONG );
        set("exits", ([
                "north" : __DIR__"xiaolu1",
        ]));
        set("objects", ([
                __DIR__"npc/xiaofan" : 1,
                CLASS_D("gaibang")+"/bangzhong" : 1,
        ]));
        set("item_desc", ([
                "hu" : "
    洞庭湖“銜遠山，吞長江，浩浩盪盪，橫無際涯，渚清沙白，芳草
如茵，朝暉夕陰，氣象萬千。”自古以來，洞庭湖就以湖光山色吸引遊
人，歷代著名學家為之傾倒。唐李白詩雲：“淡掃明湖開玉鏡，丹青畫
出是君山。”
    近岸處有一葉小舟，也許喊(yell)一聲船家就能聽見。\n",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "dongting");
        set("coor/x", -1710);
        set("coor/y", 2270);
        set("coor/z", -20);
  set("yell_about", "船家");             // yell 船家
  set("river_type", "湖");               // 江面上傳來回響
  set("need_dodge",300);                 // 需要多少輕功
  set("come_msg_out",   "一葉扁舟緩緩地駛了過來，艄公將一塊踏腳板搭上堤岸，以便乘客上下。\n");
  set("busy_msg",       "只聽得湖面上隱隱傳來：“別急嘛，這兒正忙著吶……”\n");
  set("wait_msg",       "岸邊一只渡船上的老艄公說道：正等著你呢，上來吧。\n");
  set("leave_msg_out",  "艄公把踏腳板收了起來，竹篙一點，扁舟向湖心駛去。\n");
  set("leave_msg_in",   "艄公把踏腳板收起來，說了一聲“坐穩嘍”，竹篙一點，扁舟向湖心駛去。\n");
  set("come_msg_in",    "艄公說“到啦，上岸吧”，隨即把一塊踏腳板搭上堤岸。\n");
  set("item_desc/river", HIC "\n只見近岸處有一葉小舟，也許大聲喊("
                         HIY "yell" HIC ")一聲船家(" HIY "boat" HIC
                        ")就\n能聽見。倘若你自負輕功絕佳,也可直接"
                        "渡水(" HIY "cross" HIC ")踏江而過。\n" NOR);
  set("boat_short", "渡船");    
  set("boat_desc",  @LONG
一葉小舟，飄搖在洞庭湖湖面。泛舟湖心，“四顧疑無地，中流忽
有山”。舉目望去，“煙波不動景沉沉，碧色全無翠色深。疑是水仙梳
洗處，一螺青黛鏡中心。”那，就是由七十二峰組成的君山，峰峰靈秀，
不知陶醉了多少文人墨客。
LONG );
  set("to",         __DIR__"matou1");  // 船的終點 /*   必選   */
        setup();
}
