#include <ansi.h>
inherit ITEM;
//inherit F_CLEAN_UP;
void kf_same(object who,object me);

void setup()
{}

void init()
{
        add_action("do_watch","guancha");
        add_action("do_watch","watch");
        add_action("do_catch","daibu");
        add_action("do_catch","catch");
}
int is_container() { return 1; }


void create()
{
        set_name("令牌", ({"ling pai","ling" }));
       set_max_encumbrance(10);
       set("unit", "塊");
       set("long", "這是一塊硃紅的令牌,精鋼打造，用來證明官府人士的身份。\n帶着它你就有權搜尋罪犯(guancha)，逮捕嫌疑犯(daibu)。\n");
       set("value", 0);
       set("no_drop", "這樣東西不能離開你。\n");
       set("no_burn",1);
       set("no_get", "這是朝廷的東西，平常人拿了會惹麻煩的。\n");
       set_weight(200);
       set("place","on");

       setup();
}
int do_watch(string arg)
{
        object obj,new_obj;
        object me = this_player();
        object ob = this_object();
        string targ;
        if( !query("kaifengfu", me) )
                return notify_fail("你並非朝廷官員，何必操這份閒心？\n");
        if (!ob=present("ling pai",me))
                return notify_fail("什麼？\n");
        if( query_temp("kf_finish", me) )
                return notify_fail("程藥發等着回話哪，你還在磨蹭什麼？\n");
        if (!arg||!obj=present(arg,environment(me)))
                return notify_fail("你要觀察誰？\n");
        if( !obj->is_character() || obj->is_corpse() )
        return notify_fail("你只能觀察一個活的物體。\n");
        if( me->is_busy() )
                return notify_fail("你正忙着。\n");
        targ=query("name", obj);
        tell_object(me,"你用鋭利的眼神盯着"+targ+"。\n\n");

        if( query_temp("kf_tufei", obj) == query_temp("kf_npc", me )
         && random(query("kar", me))>15){
                switch(random(5)) {
                case 0:
                        tell_object(me,WHT"你發現"+targ+"忽然把頭一低，似乎想避開你的目光。\n\n"NOR);
                     break;
                case 1:
                        tell_object(me,WHT"你發現"+targ+"忽然打了個哆嗦，面如土色。\n\n"NOR);
                        break;
                case 2:
                        tell_object(me,WHT"你發現"+targ+"太陽穴高高墳起，似乎是個練武的人。\n\n"NOR);
                        break;
                case 3:
                        tell_object(me,WHT"你發現"+targ+"腰間鼓鼓囊囊的，樣子象是一件兵刃。\n\n"NOR);
                        break;
                case 4:
                        tell_object(me,WHT"你發現"+targ+"的眼中精光一閃，馬上又變的一臉茫然。\n\n"NOR);
                        break;
                }
                set_temp("kf_faxian", 1, me);
                set_temp("kf_faxianed",query("id",  me), obj);

                }  
        else{
                switch(random(11)) {
                        case 0:
                        tell_object(me,"只見"+targ+"正擠眉弄眼，色迷迷的東張西望。\n\n");
                        break;
                        
                        case 1:
                        tell_object(me,"只見"+targ+"餓得面黃肌瘦，骨瘦如柴。\n\n");
                        break;
                        
                        case 2:
                        tell_object(me,"只見"+targ+"面頰微紅，一臉嬌羞的模樣。\n\n");
                     break;
                
                        case 3:
                        tell_object(me,"只見"+targ+"滿臉橫肉，嘴臉兇頑。\n\n");
                        break;
                        
                        case 4:
                        tell_object(me,"只見"+targ+"悲痛欲絕，哭的象個淚人似的。\n\n");
                        break;

                        case 5:
                        tell_object(me,"只見"+targ+"手足僵硬，渾身散發着金屬光澤。\n\n");
                        break;

                        case 6:
                        tell_object(me,"只見"+targ+"面無表情，呆若木雞。\n\n");
                        break;
                        
                        case 7:
                        tell_object(me,"只見"+targ+"長得尖嘴猴腮，目光狡詐。\n\n");
                        break;
         
                        case 8:
                        tell_object(me,"只見"+targ+"乾笑幾聲，臉上擠出一絲媚笑。\n\n");
                        break;
                
                        case 9:
         
                        tell_object(me,"只見"+targ+"挺胸疊肚，一臉傲慢的神色。\n\n");
                     break;
                
                        case 10:
                        tell_object(me,"只見"+targ+"長得明眸皓齒，一臉天真的神色。\n\n");
                        break;
                }
        }
        return 1;
}

int do_catch(string arg)
{
        object obj,new_obj;
        object me = this_player();
        object ob = this_object();                        //100
        if (!ob=present("ling pai",me))
                return notify_fail("什麼？\n");
        if( !query("kaifengfu", me) )
                return notify_fail("你並非朝廷官員，何必操這份閒心？\n");
        if( query_temp("kf_finish", me) )
                return notify_fail("林大人等着回話哪，你還在磨蹭什麼？\n");
        if (!arg||!obj=present(arg,environment(me)))
                return notify_fail("你要逮捕誰？\n");
        if( !obj->is_character() || obj->is_corpse() )
                return notify_fail("你只能逮捕一個活人。\n");
        if( !query_temp("kf_faxian", me )
         || query_temp("kf_faxianed", obj) != query("id", me) )
                return notify_fail("朝廷紀律嚴明，沒有證據怎好拿人？\n");
        message_vision ("$N對着$n冷笑一聲道：閣下的案子發了，老老實實跟本官走一趟。\n\n",me,obj);
        if( query_temp("kf_whatnpc", me) == 1)new_obj=new("/d/kaifeng/npc/tufei1.c");
    if( query_temp("kf_whatnpc", me) == 2)new_obj=new("/d/kaifeng/npc/tufei2.c");
    if( query_temp("kf_whatnpc", me) == 3)new_obj=new("/d/kaifeng/npc/tufei3.c");
    if( query_temp("kf_whatnpc", me) == 4)new_obj=new("/d/kaifeng/npc/tufei4.c");
    if( query_temp("kf_whatnpc", me) == 5)new_obj=new("/d/kaifeng/npc/tufei5.c");
    if( query_temp("kf_whatnpc", me) == 6)new_obj=new("/d/kaifeng/npc/tufei6.c");
    if( query_temp("kf_whatnpc", me) == 7)new_obj=new("/d/kaifeng/npc/tufei7.c");
    if( query_temp("kf_whatnpc", me) == 8)new_obj=new("/d/kaifeng/npc/tufei8.c");
        message_vision (RED"$n大叫一聲揭開偽裝，露出本來面目。\n"NOR,me,obj);
//      destruct(obj);
        delete_temp("kf_faxianed", obj);
//       new_obj = present("picture",ob);
        kf_same(new_obj,me);    
       new_obj->move(environment(me));    
        message_vision (RED"$n大喝道：老子和你拼了！\n"NOR,me,new_obj);
       new_obj->kill_ob(me);
       me->kill_ob(new_obj);
       new_obj->set_leader(me);
       set_temp("kf_npc",query_temp("kf_npc",  me), new_obj);
       set_temp("kf_ownname",query("id",  me), new_obj);
       delete("no_see", new_obj);
       new_obj->start_busy(1);
       delete_temp("kf_faxian", me);
//      me->set_temp("kf_finish");
       return 1;
}

void kf_same(object who,object me)
{
        mapping myscore;
        int maxskill;
        myscore = me->query_entire_dbase();
        set("combat_exp",query("combat_exp",  me)*10/7, who);

        set("max_qi", myscore["max_qi"], who);
        set("eff_qi", myscore["eff_qi"], who);
        set("qi", myscore["max_qi"], who);

        set("max_jing", myscore["max_jing"], who);
        set("eff_jing", myscore["eff_jing"], who);
        set("jing", myscore["max_jing"], who);

          set("max_neili", myscore["max_neili"], who);
        set("neili", myscore["max_neili"], who);
        set("jiali", 0, who);
        maxskill = me->query_skill("force",1);
        if(maxskill < me->query_skill("parry",1)) maxskill=me->query_skill("parry",1); 
        if(maxskill < me->query_skill("dodge",1)) maxskill=me->query_skill("dodge",1); 
        if(maxskill < me->query_skill("sword",1)) maxskill=me->query_skill("sword",1); 
        if(maxskill < me->query_skill("blade",1)) maxskill=me->query_skill("blade",1); 
        if(maxskill < me->query_skill("unarmed",1)) maxskill=me->query_skill("unarmed",1); 
        set("maxskill", maxskill, who);

}