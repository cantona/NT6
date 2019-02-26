// /guanwai/taxue.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "踏雪院");
        set("long", @LONG
這是一條碎石子鋪的小路，西面煙霧繚繞的，牆壁都有些發黑了，
看上去有些刺眼，不過裏面卻飄來陣陣香氣，看來是廚房。東面則是
一個顯得有些荒涼的小院子，似乎沒什麼東西。時不時有一些胡家的
弟子匆匆而過。
LONG );
        set("exits", ([
                "west"  : __DIR__"shizilu",
        ]));

        set("outdoors", "changbai");
        setup();
}

void init()
{
        add_action("do_amble", "amble");
}

int is_valid()
{
        int m = NATURE_D->query_month();

        return (m >= 10 || m <= 2);
}

string long()
{
        string msg;

        if (is_valid())
                msg = "看到這一地的積雪，你不由得感覺到陣陣寒意。入冬"
                      "以來老天爺落下層層的積雪，從來沒有人打掃，以至"
                      "於地上積雪足足有上尺之深。時不時有一些胡家的弟"
                      "子慢悠悠的飄然踏雪(amble) 從院子這頭邁到那一頭"
                      "，有的留下一些腳印，也有人走過沒留半點足跡，令"
                      "人歎羨。\n";
        else
                msg = "院子鋪了一地的碎石子，顯得有些荒涼。角落裏靠着"
                      "一塊木牌子，上面寫着：" HIW "踏雪無痕，也亦不難  胡一"
                      "刀" NOR "。字寫的雖然潦草拙劣，卻也顯得頗有力道，與眾"
                      "不同。\n";

        return sort_string(msg, 60, 4);
}

int do_amble()
{
        object me;
        int lvl;

        me = this_player();

        if (me->is_busy())
                return notify_fail("你現在忙着呢。\n");

        if (me->is_fighting())
                return notify_fail("你正忙着打架呢。\n");

        me->start_busy(2 + random(3));
        if (! is_valid())
        {
                write("你在院子裏面慢慢的溜達了一圈，滿愜意，就是太無聊了。\n");
                return 1;
        }

        if( query("neili", me)<100 )
        {
                write("你看了看滿院的積雪，提了一口真氣，忽然覺得內力有些不濟。\n");
                return 1;
        }

        addn("neili", -50-random(50), me);
        write("你深吸一口氣，腳點積雪，輕飄飄的邁開步去。\n");
        lvl = me->query_skill("sixiang-bufa", 1);
        if (lvl < 50)
        {
                message_vision("$N晃晃悠悠的走了兩步，“噗”的一下腳深深的"
                               "陷入了雪中，一臉懊喪之色。\n", me);
                return 1;
        } else
        if (lvl < 100)
        {
                message_vision("$N勉勉強強的繞着院子走了一圈，留了一地深淺"
                               "不一的腳印，惹得眾人大笑。\n", me);
                return 1;
        }

        switch (random(3))
        {
        case 0:
                message_vision("$N哈哈一笑，雙足連環踏雪而走，身"
                               "形飄灑之極！\n", me);
                break;

        case 1:
                message_vision("$N臉色木然，只是不住的凝神前行，"
                               "背後幾乎沒有留下半點腳印。\n", me);
                break;

        default:
                message_vision("$N邁開大步，一步步的走了出去，不"
                               "一會兒便走了一圈，自顧坐下冥神思索。\n", me);
                break;
        }

        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", lvl / 2 + random(lvl / 2));

        if (me->can_improve_skill("sixiang-bufa"))
                me->improve_skill("sixiang-bufa", lvl / 2 + random(lvl / 2));
        return 1;
}