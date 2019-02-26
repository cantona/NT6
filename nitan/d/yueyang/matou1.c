// Room: /d/yueyang/matou1.c
// Last Modifyed by Winder on Dec. 4 2001

#include <ansi.h>
inherit RIVER;

void create()
{
        set("short", "岳陽碼頭");
        set("long", @LONG
岳陽碼頭十分熱鬧，各色人等來來往往，有很多是往湖裏遊玩或上
君山的，也有些流氓混混在人羣中磨肩擦踵想撈點外快。岳陽是丐幫總
舵常駐之處，江湖人物也非常多。腳邊西面就是洞庭湖(hu)水面了。遠
遠可以看到青碧的君山浸泡在亮綠的湖水中。
LONG );
        set("exits", ([
                "eastup" : __DIR__"shijie7",
        ]));
        set("objects", ([
                __DIR__"npc/xingren" : 1,
                CLASS_D("gaibang")+"/bangzhong" : 1,
        ]));
        set("item_desc", ([
                "hu" : "
　　洞庭湖“銜遠山，吞長江，浩浩蕩蕩，橫無際涯，渚清沙白，芳草
如茵，朝暉夕陰，氣象萬千。”自古以來，洞庭湖就以湖光山色吸引遊
人，歷代著名學家為之傾倒。詩人劉禹錫吟道：“湖光秋月兩相和，潭
面無風鏡未磨，遙望洞庭山水色，白銀盤裏一青螺。”
    近岸處有一葉小舟，也許喊(yell)一聲船家就能聽見。\n",
        ]));
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
  set("yell_about", "船家");             // yell 船家
  set("river_type", "湖");               // 江面上傳來回響
  set("need_dodge",300);                 // 需要多少輕功
  set("come_msg_out",   "一葉扁舟緩緩地駛了過來，艄公將一塊踏腳板搭上堤岸，以便乘客上下。\n");
  set("busy_msg",       "只聽得湖面上隱隱傳來：“別急嘛，這兒正忙着吶……”\n");
  set("wait_msg",       "岸邊一隻渡船上的老艄公説道：正等着你呢，上來吧。\n");
  set("leave_msg_out",  "艄公把踏腳板收了起來，竹篙一點，扁舟向湖心駛去。\n");
  set("leave_msg_in",   "艄公把踏腳板收起來，説了一聲“坐穩嘍”，竹篙一點，扁舟向湖心駛去。\n");
  set("come_msg_in",    "艄公説“到啦，上岸吧”，隨即把一塊踏腳板搭上堤岸。\n");
  set("item_desc/river", HIC "\n只見近岸處有一葉小舟，也許大聲喊("
                         HIY "yell" HIC ")一聲船家(" HIY "boat" HIC
                        ")就\n能聽見。倘若你自負輕功絕佳,也可直接"
                        "渡水(" HIY "cross" HIC ")踏江而過。\n" NOR);
  set("boat_short", "渡船");    
  set("boat_desc",  @LONG
一葉小舟，飄搖在洞庭湖湖面。泛舟湖心，“四顧疑無地，中流忽
有山”。舉目望去，“煙波不動景沉沉，碧色全無翠色深。疑是水仙梳
洗處，一螺青黛鏡中心。”那，就是由七十二峯組成的君山，峯峯靈秀，
不知陶醉了多少文人墨客。
LONG );
  set("to",         __DIR__"matou");  // 船的終點 /*   必選   */
	set("coor/x", -6240);
	set("coor/y", -3010);
	set("coor/z", -20);
	setup();
}
