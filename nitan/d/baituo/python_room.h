// snake_room.h 蛇谷中有蛇的房間

void python_attack(object);

#include <ansi.h>

void init()
{
        object me, here;

        string *msg =
        ({
                HIR"你走到這裏，突然覺得有股腥臭的氣味……\n"NOR,
                HIR"你耳邊聽到一陣u沙沙v的細碎聲響，心裏提高了警覺。\n"NOR,
                HIR"你一走到這地方，突然有點心神不寧……\n"NOR,
        });

        me = this_player();
        here = this_object();

        set("enter_shegu", 1, me);
        addn("jingli", -5, me);

        if( time()-query("last_comeout", here)>180 || !query("last_search", here) )
                set("hide_python", 1, here);


        if( random(query("hide_python")+1) != 0 && query("race", me) != "蛇類"){
                remove_call_out("python_attack");
                call_out("python_attack", 6+random(3), me);
                if( query("family/family_name", me) == "白駝山" )
                tell_object(me, msg[random(sizeof(msg))]);
        }
}

void python_attack(object me)
{
        object python, here;
        here = this_object();

    if (! objectp(me))
        return;

        if ( environment(me) != here) return;

        if ( query("hide_python") < 1) return;

        addn("hide_python", -1);
        python = new(__DIR__"npc/bt_python");
        python->move(here);
        set("last_comeout", time() );

        message("vision", HIR"你忽然聞得一陣腥風，猛見一條"+python->name()+HIR"竄了出來，露出獠牙，疾向"+me->name()+"咬去！\n"NOR, environment(me), me);
        tell_object(me, HIR"你耳中忽聞嘶嘶聲響，一遲疑間，驀地腥臭迎面，一條"+python->name()+HIR"從旁竄出，猛然向你張口撲來！\n"NOR);

        python->kill_ob(me);

}
