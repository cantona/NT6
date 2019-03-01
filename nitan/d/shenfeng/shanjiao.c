#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "神峰山腳");
        set("long", @LONG
此處已是神峰(peak)山腳，近看尤其美麗，通體雪白，瑩
光純凈，做玉匠的只要找到小小的一塊白玉，已然是終身吃之
不盡了，哪知這裡竟有這樣一座白玉山峰。抬頭仰望，只覺心
曠神怡，萬慮俱消。你不禁暗暗讚嘆造物之奇。
LONG);
        set("outdoors", "gaochang");
        set("item_desc", ([
                "peak" : HIW "陡峭的白玉山峰上布滿斧鑿痕跡，看來似乎"
                         "可以爬上去。\n" NOR,
        ]));

        set("exits", ([
                "south" : __DIR__"pendi",
        ]));
        setup();
}

void init()
{
        add_action("do_climb", "climb");
}

int do_climb(string arg)
{
        object me = this_player();

        if (! arg || arg != "up")
                return notify_fail("你要往哪個方向爬？\n");

        message("vision", HIW "只見" + me->name() + HIW "戰戰兢兢地往神"
                          "峰上爬去。\n" NOR, environment(me), ({me}));

        me->move(__DIR__"shenfeng");
        tell_object(me, HIW "\n你費了好大勁，終于爬上了神峰，累得你直喘"
                          "粗氣。\n\n" NOR);
        message("vision", HIW "只見" + me->name() + HIW "氣喘噓噓地爬了"
                          "上來。\n", environment(me), ({me}));
        return 1;
}