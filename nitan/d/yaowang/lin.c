#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "濃密樹林");
        set("long", @LONG
這裡是一片濃密的樹林，參天的大樹遮天蔽日，偶爾有幾縷
光線透進來。地上滿是枯枝敗葉，空氣中彌漫著讓人不安的氣氛。
LONG
        );

        set("outdoors", "yaowang");
        setup();
}

void init()
{
        object me = this_player();

        if( (random(10) < 7)
        || !userp(me)
         || (query("family/family_name", me) == "yaowang" )
         || query_temp("been_recommend_to_yaowang", me) )
                return;

        call_out("do_ansuan", 2, me);
}

protected void do_ansuan(object me)
{
        int flag = random(10)<5?1:0, n;
        string *limbs;

        if( !me || (environment(me) != this_object()) )
                return;

        tell_object(me, sprintf(HIB"\n突然“嗖”的一聲，樹後打來一只飛鏢。\n%s\n\n"NOR,
                flag?"你趕緊一側身躲了過去，下出了一身冷汗。":
                sprintf("一下釘在了你的%s上。",(n=sizeof(limbs=query("limbs", me)))?
                limbs[random(n)]:"身")));

        if(!flag)
        {
                me->receive_damage("qi", 10);
                if(random(10) < 2)
                        me->apply_condition("yaowang_du", 2);
        }
}
