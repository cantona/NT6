inherit ITEM;
inherit F_UNIQUE;
#include <ansi.h>; 
void setup()
{}

void init()
{
        add_action("do_yanjiu", "yanjiu");
        add_action("do_yanjiu", "research");
        add_action("do_du", "du");
}

void create()
{
        set_name(WHT "千蛛萬毒手祕芨" NOR, ({ "qianzhu miji", "miji", "book"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", WHT
        "這是失傳已久的千蛛萬毒手祕芨下半部，你可以從中研究一些千蛛萬毒手的絕招。\n\n" NOR, );
        }
}

int do_du(string arg)
{
        string dir;

        if( ! arg || arg == "" ) return 0;

        if( arg == "miji" || arg == "qianzhu miji" || arg == "book" )
        {
                write(HIY "\n祕芨裏記載了不少千蛛萬毒手的絕招竅門，你可以試着研究研究。\n" NOR);
                return 1;
        }
}

int do_yanjiu(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        string skill, book;
        int lv;

        if(! arg)
        {
                write("研究千蛛萬毒手祕芨指令格式：\n"
                      "research|yanjiu <絕技> from <千蛛萬毒手祕芨>\n");
                return 1;
        }
        if(arg == "suck"  || arg == "wan"  
        || arg == "zhugu" || arg == "miji" 
        || arg == "book"  || arg == "qianzhu miji" )
        {
                write("研究千蛛萬毒手祕芨指令格式：\n"
                      "research|yanjiu <絕技> from <千蛛萬毒手祕芨>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        return 0;

        if( me->is_busy())
        {
                write("你現在正忙着呢。\n");
                return 1;
        }

        if( me->is_fighting())
        {
                write("你無法在戰鬥中專心下來研讀新知！\n");
                return 1;
        }

        if( ! me->query_skill("literate", 1) )
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        if (! id(book))
        {
                write("這裏沒有這本書。\n");
                return 1;
        }

        if ( skill != "suck"
          && skill != "zhugu"  
          && skill != "wan" )
        {
                write(WHT "你可以從千蛛萬毒手祕芨裏研究到吸毒練功法"
                      "門（suck）、蛛蠱決（zhugu）以及萬蠱噬天絕"
                      "技（wan）。\n\n" NOR,);
                return 1;
        }

        if( query("jing", me)<50 || query("qi", me)<50 )
        {
                write("你現在過於疲倦，無法專心研讀。\n");
                return 1;
        }

        if ( skill == "suck" )
        {
                if( query("can_perform/qianzhu-wandushou/suck", me) )
                {
                        write("你已經學會了千蛛萬毒手練毒的竅門。\n");
                        return 1;
                }

                if( query("potential", me)<1 )
                {
                        write("你研讀了一會兒，覺得有點迷糊，看來是自己的潛能不夠了。\n");
                        return 1;
                }

                message("vision", me->name() + "正專心地研讀千蛛萬毒手祕芨。\n", environment(me), me);
                tell_object(me, "\n你仔細的研讀千蛛萬毒手祕芨吸毒練功這一章節。\n");
                me->receive_damage("qi", 30);
                me->receive_damage("jing", 30);
                addn("potential", -1, me);
                remove_call_out("suck"); 
                call_out("suck", 1, me);
                me->start_busy(2);
                return 1;
        }

        if ( skill == "zhugu" )
        {
                if( query("can_perform/qianzhu-wandushou/zhugu", me) )
                {
                        write("你已經學會了「蛛蠱決」這一招。\n");
                        return 1;
                }

                if( query("potential", me)<1 )
                {
                        write("你研讀了一會兒，覺得有點迷糊，看來是自己的潛能不夠了。\n");
                        return 1;
                }

                message("vision", me->name() + "正專心地研讀千蛛萬毒手祕芨。\n", environment(me), me);
                tell_object(me, "\n你仔細的研讀千蛛萬毒手祕芨蛛蠱決這一章節。\n");
                me->receive_damage("qi", 30);
                me->receive_damage("jing", 30);
                addn("potential", -1, me);
                remove_call_out("zhugu"); 
                call_out("zhugu", 1, me);
                me->start_busy(2);
                return 1;
        }

        if ( skill == "wan" )
        {
                if( query("can_perform/qianzhu-wandushou/wan", me) )
                {
                        write("你已經學會了「萬蠱噬天」這一招。\n");
                        return 1;
                }

                if( query("potential", me)<1 )
                {
                        write("你研讀了一會兒，覺得有點迷糊，看來是自己的潛能不夠了。\n");
                        return 1;
                }

                message("vision", me->name() + "正專心地研讀千蛛萬毒手祕芨。\n", environment(me), me);
                tell_object(me, "\n你仔細的研讀千蛛萬毒手祕芨萬蠱噬天這一章節。\n");
                me->receive_damage("qi", 30);
                me->receive_damage("jing", 30);
                addn("potential", -1, me);
                remove_call_out("wan"); 
                call_out("wan", 1, me);
                me->start_busy(2);
                return 1;
        }
}

int suck(object me)
{
        if( (int)me->query_skill("qianzhu-wandushou", 1) < 100)
        {
                write(HIC "你研讀了半天，發現自己對千蛛萬毒手領悟不夠，無法學會練毒的竅門。\n" NOR);
                return 1;
        }

        if( (int)me->query_skill("hand", 1) < 100)
        {
                write(HIC "你研讀了半天，發現自己對基本手法領悟不夠，無法學會練毒的竅門。\n" NOR);
                return 1;
        }

        if( (int)me->query_skill("poison", 1) < 100)
        {
                write(HIC "你研讀了半天，發現自己對基本毒技領悟不夠，無法學會練毒的竅門。\n" NOR);
                return 1;
        }

        if( (int)me->query_skill("force") < 150)
        {
                write(HIC "你研讀了半天，發現自己的內功火候太淺，無法學會練毒的竅門。\n" NOR);
                return 1;
        }

        if( query("max_neili", me)<1000 )
        {
                write(HIC "你研讀了半天，發現自己的內力修為太淺，無法學會練毒的竅門。\n" NOR);
                return 1;
        }

        if (random(100) > 5)
        {
                write(HIY "你對吸毒練功似有所悟，但還是不夠深刻，看來還需繼續研讀才行。\n" NOR);
                return 1;
        }
   else { 
                me->improve_skill("qianzhu-wandushou", 5000000);
                me->improve_skill("poison", 5000000);
                set("can_perform/qianzhu-wandushou/suck", 1, me);
                tell_object(me, HIC "你學會了如何運用千蛛萬毒手吸毒練功。\n" NOR);
                write(HIW "\n你仔細研讀千蛛萬毒手祕芨，終於領悟了吸毒練功的竅門所在。\n" NOR);
                return 1;
        }
}

int zhugu(object me)
{
        if( (int)me->query_skill("qianzhu-wandushou", 1) < 130)
        {
                write(HIC "你研讀了半天，發現自己對千蛛萬毒手領悟不夠，無法學會蛛蠱決。\n" NOR);
                return 1;
        }

        if( (int)me->query_skill("hand", 1) < 130)
        {
                write(HIC "你研讀了半天，發現自己對基本手法領悟不夠，無法學會蛛蠱決。\n" NOR);
                return 1;
        }

        if( (int)me->query_skill("poison", 1) < 130)
        {
                write(HIC "你研讀了半天，發現自己對基本毒技領悟不夠，無法學會蛛蠱決。\n" NOR);
                return 1;
        }

        if( (int)me->query_skill("force") < 200)
        {
                write(HIC "你研讀了半天，發現自己的內功火候太淺，無法學會蛛蠱決。\n" NOR);
                return 1;
        }

        if( query("max_neili", me)<1500 )
        {
                write(HIC "你研讀了半天，發現自己的內力修為太淺，無法學會蛛蠱決。\n" NOR);
                return 1;
        }

        if (random(150) > 5)
        {
                write(HIY "你對蛛蠱決似有所悟，但還是不夠深刻，看來還需繼續研讀才行。\n" NOR);
                return 1;
        }
   else { 
                me->improve_skill("qianzhu-wandushou", 5000000);
                me->improve_skill("poison", 5000000);
                set("can_perform/qianzhu-wandushou/zhugu", 1, me);
                tell_object(me, HIC "你學會了「蛛蠱決」這一招。\n" NOR);
                write(HIW "\n你仔細研讀千蛛萬毒手祕芨，終於領悟了蛛蠱決的竅門所在。\n" NOR);
                return 1;
        }
}

int wan(object me)
{
        if( (int)me->query_skill("qianzhu-wandushou", 1) < 220)
        {
                write(HIC "你研讀了半天，發現自己對千蛛萬毒手領悟不夠，無法學會萬蠱噬天。\n" NOR);
                return 1;
        }

        if( (int)me->query_skill("hand", 1) < 220)
        {
                write(HIC "你研讀了半天，發現自己對基本手法領悟不夠，無法學會萬蠱噬天。\n" NOR);
                return 1;
        }

        if( (int)me->query_skill("poison", 1) < 200)
        {
                write(HIC "你研讀了半天，發現自己對基本毒技領悟不夠，無法學會萬蠱噬天。\n" NOR);
                return 1;
        }

        if( (int)me->query_skill("force") < 300)
        {
                write(HIC "你研讀了半天，發現自己的內功火候太淺，無法學會萬蠱噬天。\n" NOR);
                return 1;
        }

        if( query("max_neili", me)<3500 )
        {
                write(HIC "你研讀了半天，發現自己的內力修為太淺，無法學會萬蠱噬天。\n" NOR);
                return 1;
        }

        if (random(200) > 5)
        {
                write(HIY "你對萬蠱噬天似有所悟，但還是不夠深刻，看來還需繼續研讀才行。\n" NOR);
                return 1;
        }
   else { 
                me->improve_skill("qianzhu-wandushou", 5000000);
                me->improve_skill("poison", 5000000);
                set("can_perform/qianzhu-wandushou/wan", 1, me);
                tell_object(me, HIC "你學會了「萬蠱噬天」這一招。\n" NOR);
                write(HIW "\n你仔細研讀千蛛萬毒手祕芨，終於領悟了萬蠱噬天的竅門所在。\n" NOR);
                return 1;
        }
}