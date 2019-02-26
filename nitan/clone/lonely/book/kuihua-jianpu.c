#include <ansi.h>; 
inherit ITEM;

void create()
{
        set_name(HIW "「葵花劍譜」" NOR, ({ "kuihua jianpu", "kuihua", "jianpu"}));
        set_weight(500);
        if (clonep())
               set_default_object(__FILE__); 
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIW "\n這是一本用薄紙寫成的書，封皮上寫有「葵花劍"
                            "譜」四\n字。你可以試着讀讀(read)看。\n\n" NOR, );
        }
}

void init()
{
        add_action("do_du", "read");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;

        string skill, book, msg;
        int lv;

        if (! arg)
        {
                write("研讀葵花劍譜指令格式：read <技能> from <葵花劍譜>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        {
                write("研讀葵花劍譜指令格式：read <技能> from <葵花劍譜>\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("你現在正忙着呢。\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("你無法在戰鬥中專心下來研讀新知！\n");
                return 1;
        }

        if( query("no_fight", where )
            && query("doing", me) != "scheme" )
        {
                write("你無法在這裏靜下心來研讀葵花劍譜。\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        if (! id(book))
        {
                write("這裏沒有這本書。\n");
                return 1;
        }

        if (skill != "辟邪劍影" && skill != "辟邪劍影")
        {
                write("葵花劍譜上並沒有記載你打算研究的內容。\n" NOR);
                return 1;
        }

        if (me->query_skill("pixie-jian", 1) < 1000)
        {
                write("你辟邪劍法修為不足，無法領悟到其中奧妙。\n");
                return 1;
        }
        
        if (me->query_skill("dodge", 1) < 1000)
        {
                write("你基本輕功修為不足，無法領悟到其中奧妙。\n");
                return 1;
        }
                
        if( !query("reborn/times", me) )
        {
                write("你未經歷轉世考驗，無法領悟其中奧妙。\n");
                return 1;                
        }
        
        if( query("combat_exp", me)<10000000 )
        {
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }

        if( query("jing", me)<100
            || query("qi", me)<100
            || query("neili", me)<200 )
        {
                write("你現在過於疲倦，無法專心下來研讀新知。\n");
                return 1;
        }

        write(HIW "你學會了「" HIG "辟邪劍影" HIW "」。\n" NOR);
        set("can_perform/pixie-jian/jian", 1, me);
        destruct(this_object());
        return 1;

}
