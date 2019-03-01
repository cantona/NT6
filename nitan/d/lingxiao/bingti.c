#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "冰梯");
        set("long", @LONG
這裡是一座晶瑩剔透的冰梯。此處地處萬裡雪山頂峰，連接
凌霄城的天險防線分天崖。懸在這裡，只覺罡風凜冽，如利刃割
體，身側寒雲渺渺，白煙氤氳。橋下萬載寒冰，在日光下閃爍生
輝。山寒水冷，眾鳥飛盡，惟有朵朵白雪，依舊飄零。這裡往往
有傷心失意人跳崖自盡。
LONG );
        set("exits", ([
                "up" : __DIR__"shanya",
                "down" : __DIR__"fentianya",
        ]));
        set("outdoors", "lingxiao");
        setup();
}

void init()
{
        add_action("do_jump","jump");
}

int do_jump(object me)
{
        me = this_player();
        message_vision(HIW "$N" HIW "看了看腳下悠悠白雲，一咬牙，眼"
                       "一閉，縱身往冰橋下跳去。\n" NOR, me);

        if (me->query_dex() > 25)
        {
                me->move(__DIR__"juegu");
        } else
        if (me->query_dex() > 20)
        {
                me->move(__DIR__"boot");
                me->unconcious();
        } else
        {
                me->move(__DIR__"juegu");
                me->die();
        }
        return 1;
}
