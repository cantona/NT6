inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "長生村");
        set("long",@LONG
這裡便是傳說中長生村了，想來奇怪，這村與人間普通
村莊竟無任何區別，村中房舍與居民也與凡間所見相同。不
遠處幾個村民正在辛勤地勞作，雞犬相聞，好不快活。回頭
一想自己四海漂泊，浪跡天涯，不禁黯然感慨。不遠處炊煙
了了，偶有三兩個村民趕著牛車經過，看似非常忙碌，不時
地，從前方房屋中傳出機杼之聲，想必是村中婦女正忙著紡
織棉布，你心中黯然，歸家感覺油然而生。
LONG);

        set("exits", ([
                "west"          : __DIR__"changshengcunwest1",
                "east"          : __DIR__"changshengcuneast1",
                "north"         : __DIR__"changshengcunnorth1",
                "south"         : __DIR__"changshengcunsouth1",
                "out"           : __DIR__"changshengdao1",
        ]));
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島
        set("no_fight", 1);
        
        set("objects", ([
                __DIR__"npc/shuzhongxian" : 1,
                __DIR__"npc/wantong" : random(4),
        ]));
        
        setup();
}

void init ()
{
        if (! this_player()->query_temp("apply/xianshu-lingwei"))
        {
                if (! this_player()->query("penglai/go_quest/ok"))
                {
                        this_player()->start_busy(3);
                        tell_object(this_player(), NOR + WHT "你到了此處，四周仙氣繚繞令你一時間難以辨別方向。\n" NOR);
                }
                else
                {
                        if (random(2))
                        {
                                this_player()->start_busy(1);
                                tell_object(this_player(), NOR + WHT "你到了此處，四周仙氣繚繞令你一時間難以辨別方向。\n" NOR);                
                        }
                }
        }
}