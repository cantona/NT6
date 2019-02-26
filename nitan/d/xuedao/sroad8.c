#include <ansi.h>
inherit ROOM;

#define QIANGPU   "/clone/lonely/book/zhongping"

void create()
{
        set("short", "雪山山谷");
        set("long", @LONG
一個寬大山谷，羣山環繞，山頂上全是白閃閃的積雪，山谷南方
有兩個山洞。附近有幾棵説不出什麼名字的古樹，下面有一些亂七八
糟的零碎(mash)堆擺在那裏。
LONG );
        set("exits", ([
                "enter"    : __DIR__"shandong1",
                "eastdown" : __DIR__"wangyougu",
                "northup"  : __DIR__"sroad7",
        ]));
        set("outdoors", "xuedao");
        setup();
}

void init()
{
        object ob;

        ob = find_object(QIANGPU);
        if (! ob) ob = load_object(QIANGPU);

        if (! environment(ob))
        {
                set("item_desc", ([
                        "mash": HIR "\n這是一些亂七八糟的零碎，散發出陣陣噁心的"
                                "臭味。你定睛看\n去，零碎中居然有本" NOR + CYN
                                "「中平槍譜」" HIR "(zhongping qiangpu)" HIR "。"
                                "\n\n" NOR,

                        "zhongping qiangpu" : CYN "這是本薄薄的書冊，封皮上用正"
                                              "楷寫有「中平槍法」四個大字。\n" NOR,

                        "zhongping" : CYN "這是本薄薄的書冊，封皮上用正楷寫有「"
                                      "中平槍法」四個大字。\n" NOR,

                        "qiangpu"   : CYN "這是本薄薄的書冊，封皮上用正楷寫有「"
                                      "中平槍法」四個大字。\n" NOR,

                ]));
                add_action("do_get", "get");
        } else
        {
                set("item_desc", ([
                        "mash": HIR "\n這是一些亂七八糟的零碎，散發出陣陣噁心的"
                                "臭味。\n" NOR,
                ]));
        }
        add_action("do_enter", "enter");
}

int do_get(string arg)
{
        object me, ob;

        me = this_player();
        ob = find_object(QIANGPU);
        if (! ob) ob = load_object(QIANGPU);

        if (environment(ob)) return 0;

        if (! arg || arg == "" ) return 0;

        if (arg == "zhongping qiangpu from mash"
           || arg == "zhongping from mash"
           || arg == "qiangpu from mash"
           || arg == "book from mash"
           || arg == "all from mash"
           || arg == "pu from mash")
        {
                ob->move(me, 1);
                message_vision(HIY "\n$N" HIY "從零碎中翻出一本「中平槍法」。\n"
                               "\n" NOR, me);

                set("item_desc", ([
                        "mash": HIR "\n這是一些亂七八糟的零碎，散發出陣陣噁心的"
                                "臭味。\n" NOR,
                ]));
                return 1;
        }
        return 0;
}

int do_enter(string arg)
{
        object me;

        me = this_player();

        if (arg != "mash")
                return notify_fail("你要進入什麼？\n");

        if( query("family/family_name", me) != "血刀門" )
                return notify_fail(HIR "\n你翻了一下這些零碎，只覺一股"
                                   "血腥氣翻湧上來，直欲嘔吐。\n" NOR);

        message("vision", HIY "\n" + me->name() + HIY "走到一邊不知道在"
                          "鬼鬼祟祟地幹些什麼，突然人就不見了。\n\n" NOR,
                          this_object(), ({ me }));

        tell_object(me, HIY "\n你躡手躡腳掀開這些零碎，越了下去，直穿過"
                        "密道奔揚州而去。\n\n" NOR);
        me->move("/d/city/datiepu");
        return 1;
}