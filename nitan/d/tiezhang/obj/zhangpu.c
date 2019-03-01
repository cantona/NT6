#include <ansi.h> 

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");      
}

void create()
{
        set_name(WHT "鐵掌掌譜" NOR , ({ "tiezhang zhangpu", "zhangpu", "pu" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本落滿灰塵的破書，紙質發黃，邊緣處也已殘缺不全了。\n");
                set("value", 1000);
                set("material", "paper");
        }
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int level; 
        int neili_lost;

        if ( ! id(arg))
        return 0;

        if( query("pigging", where) )
        {
                write("你還是專心拱豬吧！\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("你現在正忙著呢。\n");
                return 1;
        }

        if( me->is_fighting() )
        {
                write("你無法在戰鬥中專心下來研讀新知！\n");
                return 1;
        }

        if ( ! id(arg))
        { 
                write("你要讀什麼？\n");
                return 1;
        }
       
        if( ! me->query_skill("literate", 1) )
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        if( query("jing", me)<30 )
        {
                write("你現在過于疲倦，無法專心下來研讀新知。\n");
                return 1;
        }

        if( me->query_skill("tie-zhang", 1) > 120)
        {
                write("你研讀了一會兒，但是發現上面所說的對你而言都太淺顯了，沒有學到任何東西。\n");
                return 1;
        }

        if( me->query_skill("tie-zhang", 1) < 50)
        {
                write("你研讀了一會兒，但是發現上面所說的對你而言都太深奧了，沒有學到任何東西。\n");
                return 1;
        }

        if ( me->query_skill("tie-zhang", 1) > 100)
                neili_lost = 30;

   else if ( me->query_skill("tie-zhang", 1) > 60)
                neili_lost = 20;
      else
                neili_lost = 10;


        if( query("neili", me)<neili_lost )
        {
                write("你內力不夠，無法鑽研這麼高深的武功。\n");
                return 1;
        }

        level = me->query_skill("tie-zhang", 1);
        if( query("combat_exp", me)<level*level*level/10 )
        {
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }

        switch(random(3))
        {
          case 0:
                message("vision", me->name() + "翻出一本書在讀。\n", environment(me), me);
                break;
          case 1:
                message("vision", me->name() + "一邊讀書，渾身骨骼一邊發出咯咯的脆響。\n", environment(me), me);
                break;
          case 2:
                message("vision", me->name() + "的臉色時紅時青，陰晴不定。\n", environment(me), me);
                break;
        }

        me->receive_damage("jing", 25);
        set("neili",query("neili",  me)-neili_lost, me);

        me->improve_skill("tie-zhang",query("int", me)+10);
        write("你研讀《鐵掌掌譜》，頗有心得。\n");
        return 1;
}
