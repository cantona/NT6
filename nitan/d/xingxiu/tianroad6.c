// room: /d/xingxiu/tianroad6.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;
#include <ansi.h>;
string look_wind();
int lian(string arg);
void create()
{
        set("short", "天山頂峯");
        set("long", @LONG
這裏是天山頂峯。從這裏向周圍望去，帕米爾高原的風光盡收眼底。
東面一條小路可以下山。山風(wind)凜冽，極為強勁，幾乎無法站立。
LONG
        );
        set("exits", ([
                "eastdown" : __DIR__"tianroad5",
                "enter"    : __DIR__"candong",
        ]));
        set("item_desc", ([
                "wind" : (: look_wind :),
        ]));
        // 可打獵標誌
        set("can_hunting", 1);
        set("quarry", ([
             "can"       :  3,
             "tiancan"   :  8,
             "he"        :  4,
             "he2"       :  2,
              "niao"     :  23,
             "ying"      :  10,
             "zhang"     :  20,
             "hou"       :  20,
        ]));

        set("objects", ([
                __DIR__"npc/snake" : 2, 
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "xingxiu");
        set("coor/x", -52020);
        set("coor/y", 20100);
        set("coor/z", 50);
        setup();
}

string look_wind()
{
        return
"這是一年到頭永無止歇的來自極北溟海的玄風，刺面刮耳，\n"
"凜冽非常。\n";
}
void init()
{
        add_action("lian", "lian");
        add_action("lian", "practice");
}

int lian(string arg)
{
        string skillname;
        int skill, skill_basic, times, pertimes;
        object me=this_player();
        if (!arg)
        {
                write("你要練什麼武功？\n");
                return 1;
        }
        if ( (sscanf(arg, "%s %d", arg, times)!=2 ))
                return notify_fail("指令格式：practice|lian <技能種類> <次數>\n");
        if ( times < 1 || times > 30)
                return notify_fail("練習次數必須大於一次，但不能超過三十次。\n");
        if (arg!="blade")
        {
                write("天風浩蕩，你沒法練這種武功。\n");
                return 1;
        }
        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");
        if( me->is_fighting() )
                return notify_fail("你已經在戰鬥中了，學一點實戰經驗吧。\n");
        if( !stringp(skillname = me->query_skill_mapped(arg)) )
                return notify_fail("你只能練習用 enable 指定的特殊技能。\n");

        for (pertimes = 1; pertimes <=times ; pertimes ++)
        {
                skill_basic = me->query_skill(arg, 1);
                skill = me->query_skill(skillname, 1);
                if( skill < 1 )
                        return notify_fail("你好像還沒有學過這項技能吧？最好先去請教別人。\n");
                if( skill_basic < 1 )
                        return notify_fail("你對這方面的技能還是一竅不通，最好從先從基本學起。\n");
                if( skill_basic/2 <= skill/3 )
                return notify_fail("你的基本功火候未到，必須先打好基礎才能繼續提高。\n");

                notify_fail("你現在不能練習這項技能。\n");
                if( !SKILL_D(skillname)->valid_learn(me) ) return 0;

                notify_fail("你試着練習" + to_chinese(skillname) + "，但是並沒有任何進步。\n");
                if( skill*skill*skill/10>query("combat_exp", me) )
                {
                        return notify_fail("也許是缺乏實戰經驗，你的練習總沒法進步。\n");
                        return 1;
                }
                if( SKILL_D(skillname)->practice_skill(me) )
                {
                        me->improve_skill(skillname, skill_basic/2 +1, skill_basic > skill? 0: 1);
                        write(HIY"藉助天風浩蕩的威勢，你的"+to_chinese(skillname)+"大有進步了！\n"NOR);
                }
                else return 0;
        }
}
