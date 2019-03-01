#include <ansi.h>

inherit ROOM;

string look_zi();
int tell_player();

void create()
{
        set("short", "斷腸崖");
        set("long", @LONG
到得此處只見崖壁上刻了“斷腸崖”三字，自此而上，數
十丈光溜溜的寸草不生，終年雲霧環繞，天風猛烈，便飛鳥也
甚難在峰頂停足。山崖下臨深淵，自淵口下望，黑黝黝的深不
見底。“斷腸崖”前後風景清幽，只因地勢實在太險，山石滑
溜溜，極易掉入深淵崖，俯視深谷，但見灰霧茫茫四下裡山石
嶙峋，樹木茂密。隱約可見崖壁上用利器刻著兩行字(zi)。抬
頭見一座山峰沖天而起，正是絕險之地的絕情峰。
LONG);
        set("outdoors", "jueqing");
        set("item_desc",([
                "zi" : (: look_zi :),
        ]));
        set("exits", ([
               "southdown" : __DIR__"shanlu5",
               "east"      : __DIR__"shulin2",
               "north"     : __DIR__"shanlu7",
        ]));

        set("no_clean_up", 0);

        setup();
}

void init()
{       
        add_action("do_jump", ({ "tiao", "jump" }));
}

int do_jump(string arg)
{
        object me = this_player();

        if (! arg || (arg != "ya" && arg != "down" ))
                return notify_fail("你要做什麼？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢！\n");

        if (me->is_fighting())
                return notify_fail("你還是先把你面前這個家伙解決了再說。\n"); 
        
        if( !query_temp("marks/跳", me) )
        {
                write(HIR "你真的要跳下" HIW "斷腸崖" HIR "嗎，如果確定"
                      "再執行一次該指令。\n" NOR);

                set_temp("marks/跳", 1, me);

                return 1;
        }

        write(HIG "\n你鼓起勇氣，縱身一躍跳下" HIW "斷腸崖" HIG "…\n" NOR);   
        write(HIR "\n你只覺得耳邊風聲蕭蕭，渾身使不處半點力氣，一顆心都提到\n"
              "了喉嚨上。但見萬千景致飛快地向上飛去，而感覺自己卻越落\n越快"
              "，想不到這斷腸崖竟如此之高。\n" NOR);

        remove_call_out("tell_player");
        call_out("tell_player", random(6) + 6);

        return 1;
}

string look_zi()
{
        return
        HIC "\n"
        "\t※※※※※※※        ※※※※※※※\n"
        "\t※※※※※※※        ※※※※※※※\n"
        "\t※※      ※※        ※※      ※※\n"
        "\t※※" NOR + HIR "　十　" HIC "※※        ※※" NOR + HIR "  夫  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" NOR + HIR "　六　" HIC "※※        ※※" NOR + HIR "  妻  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" NOR + HIR "　年　" HIC "※※        ※※" NOR + HIR "  情  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" NOR + HIR "　後　" HIC "※※        ※※" NOR + HIR "  深  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIR "　在　" HIC "※※        ※※" HIR "  莫  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIR "　此　" HIC "※※        ※※" HIR "  失  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIR "　相　" HIC "※※        ※※" HIR "  信  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIR "　聚　" HIC "※※        ※※" HIR "  約  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n" 
        "\t※※※※※※※        ※※※※※※※\n"
        "\t※※※※※※※        ※※※※※※※\n\n" NOR;
}

int tell_player()
{  
       object me = this_player();
       object ob;
     
       if (! ob = find_object(__DIR__"underya"))
               ob = load_object(__DIR__"underya");

       tell_object(me, HIY "\n猛然間你看見下面竟有一個深潭，眼看快要落入潭中，你屏住\n"
                           "呼吸閉住雙目，只聽“撲咚”一聲，你頓感潭水冰冷刺骨，你\n"
                           "猛地向岸邊掙紮而去，終于達到了岸邊，但此時你只覺得全身\n"
                           "麻木，體力不知，眼前一片模糊…\n" NOR);
       me->move(ob);
       delete_temp("marks/跳", me);
       me->unconcious();

       return 1;
}