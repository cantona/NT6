#include <ansi.h>

inherit ROOM;
#define TSROB __DIR__"tsr_dugu-jiujian"

string look_door();

void create()
{
        string msg;

        set("short", "峭壁");
        set("exits", ([
                "hole1" : __DIR__"lockroom1",
                "hole2" : __DIR__"lockroom2",
                "hole3" : __DIR__"lockroom3",
                "hole4" : __DIR__"lockroom4",
                "hole5" : __DIR__"lockroom5",
                "hole6" : __DIR__"lockroom6",
                "out"   : "/d/jianzhong/jianzhong",
        ]));

        set("long", @LONG
四周懸崖峭壁，只見前方隱然是一個山洞，但是被一個巨大的石
門（door）封住了，石門上卻插着六把形狀奇特火炬（huoju）。 細
看石門周圍，只見有六個像是人工開鑿小山洞。
LONG );

        set("item_desc", ([
               "door"   : (: look_door :),
               "huoju"  : HIR "這些火炬看來很奇怪，似乎連接着什麼機關！\n" NOR,
        ]));

        set("no_clean_up", 0);
        setup();
}

void init()
{
        object tsrob;
        if (! tsrob = find_object(TSROB))
                 tsrob = load_object(TSROB);
        
}

string look_door()
{
        object ob;
        int n;
        string opened, msg, temp;

        mapping change_num = ([
               "1" : "一",
               "2" : "二",
               "3" : "三",
               "4" : "四",
               "5" : "五",
               "6" : "六",
        ]);

        ob = find_object(TSROB);

        if (! objectp(ob))
               return "TSR 物件出錯，請與巫師聯繫！\n";

        opened=query("lock/opened", ob);

        if (opened == "" || ! stringp(opened))
               return "只見石門緊閉，上面插着六把火炬（huoju），但都熄滅了！\n";

        if( query("lock/unlocked", ob) && sizeof(opened) == 6 )
               return NOR + WHT "\n只見石門陷入地下，六把火炬燒得正旺！一個入口露了出來。\n" NOR;

        msg = HIC "只見石門緊閉，第";
        for (n = 0; n < sizeof(opened); n ++)
        {
              temp = opened[n..n];
              msg += change_num[temp];
              if (n < sizeof(opened) - 1)msg += "、" ;              
        }
        msg += "把火炬燃燒着！\n" NOR;
 
        return msg;

}
