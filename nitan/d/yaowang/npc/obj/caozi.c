#include <ansi.h>
inherit ITEM;

#define CAO_NOR        "/d/yaowang/obj/putong-herb/"
#define CAO_SM         "/d/yaowang/obj/herb/"
#define CAO_MEM_SM     "/d/yaowang/obj/herb/rare/"
#define CAO_MEM        "/d/yaowang/obj/herb/member/"
#define MEMBER_D       "/adm/daemons/memberd" 

// 會員草藥列表
string *MEM_LIST = ({ "huanyang", "huoxuezhu", "hy-bc",
                         "hy-js", "hy-ly", "hy-mh", "hy-sb", "hy-ty",
                           "hy-yq", "hy-ys", "hy-zhu", "jiegudan", 
                         "jiujia", "lgshenjin", "shujincao", "tbrenshen",
                         "wugong", "zhjcao", });

// 會員特殊草藥列表
  string *MEM_SM_LIST = ({ "qixing-haitang", "tihuxiang", "bi", "heye",
                     "yanling", "hua", });

// 特殊草藥列表
string *SM_LIST = ({ "tihuxiang", "huoxuezhu", "hy-bc",
                         "hy-js", "hy-ly", "hy-mh", "hy-sb", "hy-ty",
                           "hy-yq", "hy-ys", "hy-zhu", "jiegudan", 
                         "jiujia", "lgshenjin", "shujincao", "tbrenshen",
                         "wugong", "zhjcao", });
                     
// 普通草藥列表 //先寫這麼多，以後在補充
string *NOR_LIST = ({ "chaihu", "chenpi", "chongcao",
                         "chuanwu", "dahuang", "danggui", "duhuo", "fangfeng",
                         "fuzi", "qianjinzi", });

//草藥先寫這麼多，以後在補充

void create()
{
        set_name("草籽", ({"cao zi"}));
        set_weight(10);
        set("no_clean_up", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("long", "一粒淡褐色的草籽，種在田地裡(zhong)會長成草藥。\n");
                set("value", 10);
        }
        setup();
}

void init()
{
        add_action("do_zhong", "zhong");
}

int do_zhong(string arg)
{
        object ob, me, where, whereob;

        me = this_player();
        ob = this_object();
        where=environment(me);
        whereob=environment(ob);

          if( query("family/family_name", me) != "藥王谷" || me->query_skill("baicao-jue",1)<10 || me->query_skill("bencao-changshi",1)<10 || me->query_skill("medical",1)<60 )
                return notify_fail("你不會種植草藥！\n");

        if(me->is_fighting() || me->is_busy())
                return notify_fail("你很忙，沒時間。\n");

        if( !arg || !present(arg, me))
                return notify_fail("指令格式：zhong cao zi\n");

        if( !query("yaotian", where) )
                return notify_fail("只能種在藥田裡。\n");

        if( query("zhongyao", where) >= 10 )
                return notify_fail("這裡已經沒地方種藥材了。\n");

        if( query("jingli", me) <= 20 )
                return notify_fail("你太累了，還是先休息一下吧！\n");
        
        if( query("jingli", me) <= 20 )
                return notify_fail("你太累了，還是先休息一下吧！\n");
                
        if( query_temp("growing", me) )
                return notify_fail("你已經在種植草藥了！\n");
                
        if( query("value", ob) != 10 )
                return notify_fail("已經種在地裡了！\n");

        message_vision("$N輕輕將$n種在地裡！\n", me, ob);

        ob->move(where);

                remove_call_out("grow_a");
                remove_call_out("grow_b");
                remove_call_out("grow_c");
                remove_call_out("grow_d");
                remove_call_out("grow_e");

        message_vision(WHT"草籽慢慢長出了芽。\n"NOR, ob);
        set_name( "小青草" , ({"xiao qingcao"}));
        set("long", "一株淡綠色的小青草，還沒有長成。\n");
        set("value", 0);
        set("no_get", 1);

        addn("zhongyao", 1, where);
        set_temp("growing", 1, me);
        if (random(2)>0)
        {
                me->improve_skill("baicao-jue",(query("int", me)/3));
        }else
        {
                me->improve_skill("bencao-changshi",(query("int", me)/3));
        }
        addn("jing", -50, me);
//      me->start_busy(50);
        call_out("grow_a", 1, ob, me);
        return 1;
}

int grow_a(object ob, object me)
{
        int i=5+random(5);
        set("no_get", 1);
        call_out("grow_b", i, ob, me);
        return 1;
}

int grow_b(object ob, object me)
{
        if (environment(ob)==environment(me))
        {
                int i=10+random(5);
                message_vision(WHT"小青草慢慢地長出了一片葉子。\n"NOR, ob);
                set_name( "青草" , ({"qingcao"}));
                set("long", "一株淡綠色的青草，還沒有長成。\n");
                call_out("grow_c", i, ob, me);
                return 1;
        }else
        {
                message_vision(WHT"由于主人沒有管理，小青草枯萎了。\n"NOR, ob);
                tell_object(me, HIC "由于你沒有加強對小青草的管理，小青草枯萎了。\n" NOR);
                delete_temp("growing", me);
                destruct(ob);
        }
}

int grow_c(object ob, object me)
{
        if (environment(ob)==environment(me))
        {
                int i=10+random(5);
                message_vision(WHT"青草慢慢地長大了一點。\n"NOR, ob);
                call_out("grow_d", i, ob, me);  
                return 1;
        }else
        {
                message_vision(WHT"由于主人沒有管理，青草枯萎了。\n"NOR, ob);
                tell_object(me, HIC "由于你沒有加強對青草的管理，青草枯萎了。\n" NOR);
                delete_temp("growing", me);
                destruct(ob);
        }
}

int grow_d(object ob, object me)
{
        if (environment(ob)==environment(me))
        {                       
                int i=10+random(10);
                message_vision(WHT"青草慢慢地又長大了一些。\n"NOR, ob);
                set_name( CYN"大青草"NOR , ({"da qingcao"}));
                set("long", "一株綠色的大青草，還沒有長成。\n");
                call_out("grow_e", i, ob, me);  
                return 1;
        }else
        {
                message_vision(WHT"由于主人沒有管理，大青草枯萎了。\n"NOR, ob);
                tell_object(me, HIC "由于你沒有加強對大青草的管理，大青草枯萎了。\n" NOR);
                delete_temp("growing", me);
                destruct(ob);
        }
}

int grow_e(object ob, object me)
{
        object obj;
        int skill, skilla, skillb, exp, pot;
        skill = (int)me->query_skill("baicao-jue", 1) + (int)me->query_skill("bencao-changshi", 1);
        skilla = (int)me->query_skill("baicao-jue", 1);
        skillb = (int)me->query_skill("bencao-changshi", 1);
        
        exp = 8 + random(5);
        pot = 3 + random(3);

        if( query("potential", me)>me->query_potential_limit() )
                pot = 1;
                
        if (environment(ob)!=environment(me))
        {                       
                message_vision(WHT"由于主人沒有管理，大青草枯萎了。\n"NOR, ob);
                tell_object(me, HIC "由于你沒有加強對大青草的管理，大青草枯萎了。\n" NOR);
                delete_temp("growing", me);
                destruct(ob);
                return 1;
        }
        
        message_vision(WHT"大青草長成了，可以挖起來了(dig)。\n"NOR, me);
        me->receive_damage("jing", 50 + random(30));
        me->receive_damage("qi", 50 + random(30));
        if (random(skill) < 100 && random(3) == 1) 
        {
                delete_temp("growing", me);
                obj=new(__DIR__"cao"); 
                set("owner",query("id",  me), obj);
                obj->move(environment(ob)); 
                addn("combat_exp", exp, me);
                me->improve_potential(pot);
                        tell_object(me, HIC "你獲得了" + chinese_number(exp) +
                                "點經驗和" + chinese_number(pot) + "點潛能。\n"NOR );      
                addn("zhongyao", -1, (environment(ob)));
                destruct(ob); 
        } else

        if( MEMBER_D->is_valib_member(query("id", me)) )
        {
                if (random(skill) > 300 && random(5) == 1)
                {
                        message_vision(HIY "$N種植的草藥長成了，可以挖起來了(dig)。$N忽然發現上面好象懸浮著一道金光。\n"NOR, me);
                delete_temp("growing", me);
                        obj = new(CAO_MEM_SM + MEM_SM_LIST[random(sizeof(MEM_SM_LIST))]);
                        tell_object(me, HIC "你種成了稀有草藥「" + NOR + obj->name() + NOR + HIC "」。\n" NOR);                
                        set("owner",query("id",  me), obj);
                        set("no_get", 1, obj);
                        obj->move(environment(ob)); 
                        exp += exp;
                        pot += pot;
                        addn("combat_exp", exp, me);
                        me->improve_potential(pot);
                        tell_object(me, HIC "你獲得了" + chinese_number(exp) +
                                "點經驗和" + chinese_number(pot) + "點潛能。\n"NOR );
                        addn("zhongyao", -1, (environment(ob)));
                        destruct(ob); 
        
                        if (me->can_improve_skill("baicao-jue") && skilla < 500)
                        {
                                me->improve_skill("baicao-jue",query("int", me)+10);
                                tell_object(me, HIC "在種草過程中你的「百草訣」提高了！\n" NOR);
                        }
                        if (me->can_improve_skill("bencao-changshi") && skillb < 500)
                        {
                                me->improve_skill("bencao-changshi",query("int", me)+10);
                                tell_object(me, HIC "在種草過程中你的「本草常識」提高了！\n" NOR);
                        }
                        
                } else 
                if (random(skill) > 100 && random(2) == 1)
                {
                        message_vision(HIC "$N種植的草藥長成了，可以挖起來了(dig)。\n" NOR, me);
                        delete_temp("growing", me);
                        obj = new(CAO_MEM + MEM_LIST[random(sizeof(MEM_LIST))]);
                        tell_object(me, HIC "你種成了「" + NOR + obj->name() + NOR + HIC "」。\n" NOR);
                        set("owner",query("id",  me), obj);
                        set("no_get", 1, obj);
                        obj->move(environment(ob)); 
                        addn("combat_exp", exp, me);
                        me->improve_potential(pot);
                        tell_object(me, HIC "你獲得了" + chinese_number(exp) +
                                "點經驗和" + chinese_number(pot) + "點潛能。\n"NOR );
                        addn("zhongyao", -1, (environment(ob)));
                        destruct(ob); 
        
                        if (me->can_improve_skill("baicao-jue") && skilla < 500)
                        {
                                me->improve_skill("baicao-jue",query("int", me)/4);
                                tell_object(me, HIC "在種草過程中你的「百草訣」提高了！\n" NOR);
                        }
                        if (me->can_improve_skill("bencao-changshi") && skillb < 500)
                        {
                                me->improve_skill("bencao-changshi",query("int", me)/4);
                                tell_object(me, HIC "在種草過程中你的「本草常識」提高了！\n" NOR);
                        }
                }
                else
                {
                        message_vision(HIC "$N種植的草藥長成了，可以挖起來了(dig)。\n" NOR, me);
                        delete_temp("growing", me);
                        obj = new(CAO_NOR + NOR_LIST[random(sizeof(NOR_LIST))]);
                        tell_object(me, HIC "你種成了「" + NOR + obj->name() + NOR + HIC "」。\n" NOR);
                        set("owner",query("id",  me), obj);
                        set("no_get", 1, obj);
                        obj->move(environment(ob)); 
                        addn("combat_exp", exp, me);
                        me->improve_potential(pot);
                        tell_object(me, HIC "你獲得了" + chinese_number(exp) +
                                "點經驗和" + chinese_number(pot) + "點潛能。\n"NOR );
                        addn("zhongyao", -1, (environment(ob)));
                        destruct(ob); 
        
                        if (me->can_improve_skill("baicao-jue") && skilla < 500)
                        {
                                me->improve_skill("baicao-jue",query("int", me)/4);
                                tell_object(me, HIC "在種草過程中你的「百草訣」提高了！\n" NOR);
                        }
                        if (me->can_improve_skill("bencao-changshi") && skillb < 500)
                        {
                                me->improve_skill("bencao-changshi",query("int", me)/4);
                                tell_object(me, HIC "在種草過程中你的「本草常識」提高了！\n" NOR);
                        }
                }
                                
        }else

        if (random(skill) > 300 && random(10) == 1)
        {
                message_vision(HIY "$N種植的草藥長成了，可以挖起來了(dig)。$N忽然發現上面好象懸浮著一道金光。\n"NOR, me);
                        delete_temp("growing", me);
                obj = new(CAO_SM + SM_LIST[random(sizeof(SM_LIST))]);
                tell_object(me, HIC "你種成了稀有草藥「" + NOR + obj->name() + NOR + HIC "」。\n" NOR);                
                set("owner",query("id",  me), obj);
                set("no_get", 1, obj);
                obj->move(environment(ob)); 
                exp += exp;
                pot += pot;
                addn("combat_exp", exp, me);
                me->improve_potential(pot);
                tell_object(me, HIC "你獲得了" + chinese_number(exp) +
                        "點經驗和" + chinese_number(pot) + "點潛能。\n"NOR );
                addn("zhongyao", -1, (environment(ob)));
                destruct(ob); 

                if (me->can_improve_skill("baicao-jue") && skilla < 400)
                {
                        me->improve_skill("baicao-jue",query("int", me)+10);
                        tell_object(me, HIC "在種草過程中你的「百草訣」提高了！\n" NOR);
                }
                if (me->can_improve_skill("bencao-changshi") && skillb < 400)
                {
                        me->improve_skill("bencao-changshi",query("int", me)+10);
                        tell_object(me, HIC "在種草過程中你的「本草常識」提高了！\n" NOR);
                }
                
        } else
        {
                message_vision(HIC "$N種植的草藥長成了，可以挖起來了(dig)。\n" NOR, me);
                        delete_temp("growing", me);
                obj = new(CAO_NOR + NOR_LIST[random(sizeof(NOR_LIST))]);
                tell_object(me, HIC "你種成了「" + NOR + obj->name() + NOR + HIC "」。\n" NOR);
                set("owner",query("id",  me), obj);
                set("no_get", 1, obj);
                obj->move(environment(ob)); 
                addn("combat_exp", exp, me);
                me->improve_potential(pot);
                tell_object(me, HIC "你獲得了" + chinese_number(exp) +
                        "點經驗和" + chinese_number(pot) + "點潛能。\n"NOR );
                addn("zhongyao", -1, (environment(ob)));
                destruct(ob); 

                if (me->can_improve_skill("baicao-jue") && skilla < 400)
                {
                        me->improve_skill("baicao-jue",query("int", me)/4);
                        tell_object(me, HIC "在種草過程中你的「百草訣」提高了！\n" NOR);
                }
                if (me->can_improve_skill("bencao-changshi") && skillb < 400)
                {
                        me->improve_skill("bencao-changshi",query("int", me)/4);
                        tell_object(me, HIC "在種草過程中你的「本草常識」提高了！\n" NOR);
                }
        }

}
