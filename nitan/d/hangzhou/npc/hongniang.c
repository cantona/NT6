// /d/hangzhou/npc/hongniang.c

// Modified by Constant Jan 11 2001

#include <ansi.h>

inherit NPC;

string marry();
string unmarry();

void create()
{
        set_name("紅娘", ({ "hong niang","hong" }) );
        set("title", "紅娘莊");
        set("gender", "女性" );
        set("age", 16);
        set("long",
                "一位明眸皓齒的小姑娘。\n");
        set("max_qi",800);
        set("max_jing",800);
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set("inquiry", ([
                "婚約" : "是啊……這裡就可以締結(marry)和解除婚約(unmarry)。",
                "結婚" : "是啊……這裡就可以締結(marry)和解除婚約(unmarry)。",
                "成親" : "是啊……這裡就可以締結(marry)和解除婚約(unmarry)。",
        ]) );
        set_skill("literate", 70);
        set_skill("dodge", 200);
        set_skill("unarmed", 100);
        setup();
        add_money("gold", 10);
        carry_object("/clone/misc/cloth")->wear();
}

/*
void init()
{
        object ob;

        ::init();
        add_action("do_marry", "marry");
        add_action("do_unmarry", "unmarry");
}
*/

int do_marry(string arg)
{
        object marry_card1,marry_card2, obj, me;
        object *list,ob;
        int i, have_marry;
        me = this_player();
        list = all_inventory(me);
        i = sizeof(list);
        have_marry = 0;

        if( query("couple/times", me)>2 )
        {
                say("紅娘笑道: 你都結了幾次婚了，還來玩弄別人家的感情？\n");
                return 1;
        }
        if( query("couple/times", me)>1 )
        {
                say("紅娘笑道: 來我這的都是少男少女，你可是這裡的老常客啦。紅娘我也不能老替你做伐。這可是最後一次了。\n");
        }
        if( query("gender", me) == "無性" )
        {
                say("紅娘笑道: 這位公公，你這不是開玩笑麼？\n");
                return 1;
        }
        if( query("class", me) == "bonze" )
                return notify_fail("紅娘笑罵道: 你是出家人，結什麼婚！你以為你是不戒和尚啊。\n");
        if( query("age", me)<17 )
                return notify_fail("紅娘笑道: 你還小，等到十七歲再來吧。\n");
        if( query("couple/couple_id", me) )
                return notify_fail("紅娘板著臉道: 你已經結婚了吧？\n");
        if(!arg || !objectp(obj = present(arg, environment(me)))
                || !find_player(arg)|| !find_living(arg))
        return notify_fail("紅娘笑道: 你想和誰締結良緣？\n");
        if( !environment() || base_name(environment()) != query("startroom") )
                return notify_fail("紅娘笑道: 真是抱歉，請您等一下到紅娘莊來找我吧。\n");
        if( !living(obj) )
                return notify_fail("紅娘嘆口氣對你說道: "+obj->name()+"已經無法和你締結良緣了。\n");
        if( query("couple/couple_id", obj) )
                return notify_fail("紅娘笑了起來: 人家已經結婚了吧？\n");
        if( query("couple/times", obj)>2 )
                return notify_fail("紅娘嘿嘿冷笑了幾聲: 人家都結了幾次婚了，是來玩弄你的感情來著。\n");
        if(obj==me)
                return notify_fail("紅娘笑道: 和自己締結婚約？你有病啊！\n");
        if( query("gender", obj) == query("gender", me) )
                return notify_fail("紅娘笑道: 同性戀？沒聽說過。\n");
        if( userp(obj) && !(query_temp("marks/"+me->name(1, obj))) )
        {
                message_vision(MAG "\n$N對著$n說道："+ RANK_D->query_self(me)
                        + me->name() + "，願意和"+ RANK_D->query_respect(obj)
                        + "結為夫婦\n\n"NOR, me,obj);
                set_temp("marks/"+obj->name(1), 1, me);
                tell_object(obj, MAG "如果你願意和對方結為夫婦，請你也對"
                        +me->name()+"("+query("id", me)+
                        ")"+ "下一次 marry 指令。\n" NOR);
                write(MAG "現在你急切盼望著你的心上人說同意……\n" NOR);
                return 1;
        }

        addn("couple/times", 1, me);
        set("couple/have_couple", 1, me);
        set("couple/couple_id",query("id",  obj), me);
        set("couple/couple_name",query("name",  obj), me);
        addn("couple/times", 1, obj);
        set("couple/have_couple", 1, obj);
        set("couple/couple_id",query("id",  me), obj);
        set("couple/couple_name",query("name",  me), obj);
        if( query("gender", me) == "男性" )
        {
                set("couple/couple_gender", "丈夫", obj);
                set("couple/couple_gender", "妻子", me);
        }
        else
        {
                set("couple/couple_gender", "丈夫", me);
                set("couple/couple_gender", "妻子", obj);
        }

        message_vision(MAG"恭喜 $N 和 $n ，一對璧人終于喜結良緣。\n"NOR,obj,me);
        CHANNEL_D->do_channel(this_object(), "chat",
                sprintf("%s 和 %s 現在開始是夫婦啦！\n",me->name(1),obj->name(1)));
        return 1;
}

int do_unmarry(string arg)
{
        object me = this_player();
        object ob, couple_ob;
        int i, have_marry;
        string target, tmpstr1, tmpstr2,str1,str2;
        string cardname;

        if( !arg ) return notify_fail("紅娘笑道: 你要和誰離婚？\n");
        if( !environment() || base_name(environment()) != query("startroom") )
                return notify_fail("紅娘笑道: 真是抱歉，請您等一下到紅娘莊來找我吧。\n");
        if( !query("couple/couple_id", me) )
                return notify_fail("紅娘笑道: 你沒有伴侶。\n");
        if (!objectp(couple_ob=present(arg,environment(me)))||!find_player(arg))
                return notify_fail("紅娘笑道: 你的伴侶現在不在場。\n");
        if( query("gender", couple_ob) != "女性" )
        {
                tmpstr1 = "老婆"; tmpstr2 = "老公";
                str1 = "她"; str2 = "他";
        } else
        {
                tmpstr1 = "老公"; tmpstr2 = "老婆";
                str1 = "他"; str2 = "她";
        }
        if( query("couple/couple_id", me) != query("id", couple_ob) || 
                query("couple/couple_id", couple_ob) != query("id", me) )
                return notify_fail("紅娘笑道: "+str2+"不是你的"+tmpstr2+"，你這是離的什麼婚啊。\n");

        if( userp(couple_ob) && !(couple_ob->query_temp("marks/"
                + "unmarry" +me->name(1))) )
        {
                message_vision(MAG "\n$N對著$n說道：" + RANK_D->query_self(me)
                        + me->name() + "，咱們解除婚約吧！好嗎？\n\n"
                        NOR, me, couple_ob);
                set_temp("marks/"+"unmarry"+couple_ob->name(1), 1, me);
                tell_object(couple_ob, MAG "如果你願意解除婚約，請你也"
                        + "下一次 unmarry 指令。\n" NOR);
                write(MAG "現在你只有等著" +str2 +" 同意啦...\n" NOR);
                return 1;
        }
        delete("couple/have_couple", me);
        delete("couple/couple_id", me);
        delete("couple/couple_name", me);
        delete("couple/couple_gender", me);
        delete("couple/have_couple", couple_ob);
        delete("couple/couple_id", couple_ob);
        delete("couple/couple_name", couple_ob);
        delete("couple/couple_gender", couple_ob);

        // 記錄玩家離婚次數，該屬性與學習速度等相關。
        // Added by Constant Jan 11 2001
        if( !query("divorce", me) )
                set("divorce", 1, me);
        else
                addn("divorce", 1, me);

        if( !query("divorce", couple_ob) )
                set("divorce", 1, couple_ob);
        else
                addn("divorce", 1, couple_ob);

        message_vision(MAG" $N 和 $n 從現在開始解除婚約!\n"NOR,couple_ob, me);
        CHANNEL_D->do_channel(this_object(), "chat",
        sprintf( "聚散皆是緣，%s 和 %s 從今以後，勞燕分飛，互不相幹! \n",
        me->name(1), couple_ob->name(1)));

        return 1;
}
