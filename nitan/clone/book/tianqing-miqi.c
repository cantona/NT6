
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "「天擎秘氣」" NOR, ({ "tianqing miqi", "tianqing", "miqi"}));
        set_weight(500);
        if (clonep())
               set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIY "\n這是一本用薄紙寫成的書，封皮上寫有「天擎秘氣」四\n"
                                "字。你可以試著讀讀(readtq)看。\n\n" NOR, );
        }
}

void init()
{
        add_action("do_du", "readtq");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;

        string skill, book, msg;
        int lv;

        if (me->is_busy())
        {
                write("你現在正忙著呢。\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("你無法在戰鬥中專心下來研讀新知！\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        msg = HIG "$N" HIG "翻看秘籍，仔細研究上面所記載的內容，霎那間忽有所悟……\n" NOR;
        message_vision(msg, me); 


        write(HIW "你學會了「" HIG "天擎秘氣" HIW "」特技。\n" NOR);
        me->set("special_skill/tianqing", 1);
        destruct(this_object());
        return 1;
}

