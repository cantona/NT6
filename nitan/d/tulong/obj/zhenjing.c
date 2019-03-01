inherit ITEM;
inherit F_UNIQUE;
#include <ansi.h>; 
void setup()
{}
void init()
{
        add_action("do_du", "yanjiu");
        add_action("do_du", "research");
}
void create()
{
        set_name(HIY "《" NOR+HIW "九陰真經" NOR+HIY "》" NOR, ({ "jiuyin zhenjing", "zhenjing"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIW
        "這是一本用薄紙寫成的書。書面上寫著《九陰真經》。書皮泛黃，看來已經保存很久了。\n"
        "真經裡記載了催心掌、九陰白骨爪、易筋鍛骨和蛇行貍翻，你可以試著研究研究。\n\n" NOR, );
        }
}
int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        string skill, book;
        int lv;

        if(! arg)
        {
                write("研究九陰真經的指令格式：\n"
                      "research|yanjiu <技能> from <九陰真經>\n");
                return 1;
        }
        if(arg == "yijin-duangu" || arg == "shexing-lifan"  
        || arg == "cuixin-zhang" || arg == "jiuyin-baiguzhao" 
        || arg == "jiuyin zhenjing" || arg == "zhenjing"
        || arg == "yinlong-bian" )
        {
                write("研究九陰真經的指令格式：\n"
                      "research|yanjiu <技能> from <九陰真經>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        return 0;
        if( me->is_busy())
        {
                write("你現在正忙著呢。\n");
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
                write("這裡沒有這本書。\n");
                return 1;
        }
        if ( skill != "yijin-duangu" && skill != "shexing-lifan"  
          && skill != "cuixin-zhang" && skill != "jiuyin-baiguzhao"
          && skill != "yinlong-bian" )
        {
                write(HIW "你可以從九陰真經裡研究到易筋鍛骨（yijin-duangu），蛇行貍翻（shexing-lifan），\n"
                          "催心掌（cuixin-zhang），銀龍鞭法 (yinlong-bian) 以及九陰白骨爪（jiuyin-baiguzhao）。\n\n" NOR,);
                return 1;
        }
        if( me->query_skill("sanscrit", 1) < 199)
        {
                write("你的梵文水平太低，無法看懂真經裡所記載的內容。\n");        
                return 1;
        }
        if( query("combat_exp", me)<500000 )
        {
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }
        if( query("jing", me)<101 || query("qi", me)<101 )
        {
                write("你現在過于疲倦，無法專心下來研讀新知。\n");
                return 1;
        }
        if ( skill == "yijin-duangu" )
        {
                lv = me->query_skill("yijin-duangu", 1);
                if( query("con", me)<30 )
                {
                        write("你研讀了一會兒，但是發現自己先天根骨不足，一時難以修煉。\n");
                        return 1;
                }

                if( query("combat_exp", me)<lv*lv*lv/10){
                        write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                        return 1;
                }
                if( lv > 199) {
                        write("你研讀了一會兒，但是發現上面所說的對你而言都太淺了，沒有學到任何東西。\n");
                        return 1;
                }
                message("vision", me->name() + "正專心地研讀九陰真經。\n", environment(me), me);
                me->receive_damage("qi", 100);
                me->receive_damage("jing", 100);
                me->improve_skill("yijin-duangu",query("int", me)/4+1);
                write("你仔細研讀九陰真經，對真經裡所記載的易筋鍛骨頗有心得。\n");
                return 1;
        }
        if ( skill == "shexing-lifan" )
        {
                lv = me->query_skill("shexing-lifan", 1);
                if( query("combat_exp", me)<lv*lv*lv/10){
                        write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                        return 1;
                }
                if( lv > 199) {
                        write("你研讀了一會兒，但是發現上面所說的對你而言都太淺了，沒有學到任何東西。\n");
                        return 1;
                }
                message("vision", me->name() + "正專心地研讀九陰真經。\n", environment(me), me);
                me->receive_damage("qi", 100);
                me->receive_damage("jing", 100);
                me->improve_skill("shexing-lifan",query("int", me)/4+1);
                write("你仔細研讀九陰真經，對真經裡所記載的蛇行貍翻輕功頗有心得。\n");
                return 1;
        }
        if ( skill == "cuixin-zhang" )
        {
                lv = me->query_skill("cuixin-zhang", 1);
                if( query("combat_exp", me)<lv*lv*lv/10){
                        write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                        return 1;
                }
                if( lv > 199) {
                        write("你研讀了一會兒，但是發現上面所說的對你而言都太淺了，沒有學到任何東西。\n");
                        return 1;
                }
                message("vision", me->name() + "正專心地研讀九陰真經。\n", environment(me), me);
                me->receive_damage("qi", 100);
                me->receive_damage("jing", 100);
                me->improve_skill("cuixin-zhang",query("int", me)/4+1);
                write("你仔細研讀九陰真經，對真經裡所記載的催心掌頗有心得。\n");
                return 1;
        }
        if ( skill == "jiuyin-baiguzhao" )
        {
                lv = me->query_skill("jiuyin-baiguzhao", 1);
                if( query("combat_exp", me)<lv*lv*lv/10){
                        write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                        return 1;
                }
                if( lv > 199) {
                        write("你研讀了一會兒，但是發現上面所說的對你而言都太淺了，沒有學到任何東西。\n");
                        return 1;
                }
                message("vision", me->name() + "正專心地研讀九陰真經。\n", environment(me), me);
                me->receive_damage("qi", 100);
                me->receive_damage("jing", 100);
                me->improve_skill("jiuyin-baiguzhao",query("int", me)/4+1);
                write("你仔細研讀九陰真經，對真經裡所記載的九陰白骨爪頗有心得。\n");
                return 1;
        }
        if ( skill == "yinlong-bian" )
        {
                lv = me->query_skill("yinlong-bian", 1);
                if( query("combat_exp", me)<lv*lv*lv/10){
                        write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                        return 1;
                }
                if( lv > 199) {
                        write("你研讀了一會兒，但是發現上面所說的對你而言都太淺了，沒有學到任何東西。\n");
                        return 1;
                }
                message("vision", me->name() + "正專心地研讀九陰真經。\n", environment(me), me);
                me->receive_damage("qi", 100);
                me->receive_damage("jing", 100);
                me->improve_skill("yinlong-bian",query("int", me)/4+1);
                write("你仔細研讀九陰真經，對真經裡所記載的銀龍鞭法頗有心得。\n");
                return 1;
        }
}

