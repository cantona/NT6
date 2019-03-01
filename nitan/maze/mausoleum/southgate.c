#include <ansi.h>
inherit ROOM;

string look_door();
void create()
{
        set("short", HIR "秦陵內宮南門" NOR);
        set("long", @LONG
通道兩側，自東向西依次排列著獅、獬、駱駝、象、麒麟和馬六
種石雕巨獸，各有兩對四座，共十二對二十四座，造型生動，栩栩如
生，使你像來到了傳說的仙界。在淡淡的月照下，眾石獸或蹲或立，
不畏風霜雨雪，前面通向秦陵內宮，但是被一個巨大的石門（door）
封住了，，石門上卻插著四把形狀奇特火炬（huoju）。 細看石門周
圍，只見有四個像是人工開鑿小山洞。
LONG );
        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room", 1);
        set("no_clean_up", 1);
        set("item_desc", ([
               "door"   : (: look_door :),
               "huoju"  : HIR "這些火炬看來很奇怪，似乎連接著什麼機關！\n" NOR,
        ]));

        set("exits", ([
                //"north" : __DIR__"maze4/entry",
                "northup" : __DIR__"maze/5/5",
        ]));

        /*
        set("objects", ([
                "/maze/mausoleum/npc/jiangling": 1,
                "/maze/mausoleum/npc/qianrenzhang": 1,
                "/maze/mausoleum/npc/bairenzhang": 2,
                "/maze/mausoleum/npc/bingshi": 3,
                "/maze/mausoleum/npc/baozi": 2,
                "/maze/mausoleum/npc/tiger": 2,
                "/maze/mausoleum/npc/lions": 1,
                "/maze/mausoleum/npc/ni": 1,
                "/maze/mausoleum/npc/mammoth": 1,
        ]));
        */
        setup();
}

string look_door()
{
        object ob, me;
        int n;
        string opened, msg, temp;

        mapping change_num = ([
               "1" : "一",
               "2" : "二",
               "3" : "三",
               "4" : "四",
        ]);

        me = this_player();
        ob = FUBEN_D->query_maze_mainobj(me);

        if (! objectp(ob))
               return "TSR 物件出錯，請與巫師聯系！\n";

        opened=query("lock/opened", ob);

        if (opened == "" || ! stringp(opened))
               return "只見石門緊閉，上面插著四把火炬（huoju），但都熄滅了！\n";

        if( TIME_D->realtime_digital_clock()[0..3] != "上午" &&
            TIME_D->realtime_digital_clock()[0..3] != "中午" )
               return "只見石門緊閉，上面插著四把火炬（huoju），但都熄滅了！\n";

        if( query("lock/unlocked", ob) && sizeof(opened) == 4 )
               return NOR + WHT "\n只見石門陷入地下，四把火炬燒得正旺！一個入口露了出來。\n" NOR;

        msg = HIC "只見石門緊閉，第";
        for (n = 0; n < sizeof(opened); n ++)
        {
              temp = opened[n..n];
              msg += change_num[temp];
              if (n < sizeof(opened) - 1)msg += "、" ;
        }
        msg += "把火炬燃燒著！\n" NOR;

        return msg;

}
