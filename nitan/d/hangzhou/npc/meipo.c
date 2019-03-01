// mei_po.c
#include <ansi.h>

inherit NPC;

string marry();
string unmarry();

void create()
{
        set_name("媒婆", ({ "mei po","mei" }) );
        set("title", "紅娘莊");
        set("gender", "女性" );
        set("age", 43);
        set("long",
                "一位精明能幹的老媒婆\n");
        set("max_qi",800);
        set("max_jing",800);
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set("inquiry", ([
                "婚約" : "是啊……這裡就可以締結和解除婚約",
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

int do_marry(string arg) {
        object marry_card1,marry_card2, obj, me;
        object *list,ob;
        int i, have_marry;
        me = this_player();
        list = all_inventory(me);
        i = sizeof(list);
        have_marry = 0;
        if( query("gender", me) == "無性"){
              say("既然你已經自宮了，就不能結婚了，請回吧！\n");
              return 1;
            }
        if( query("class", me) == "bonze" )
             return notify_fail("你是出家人,怎麼能結婚！嗨！現在的和尚……\n");
        if( query("age", me)<17 )
             return notify_fail("你年齡還小,等到十七歲再來吧.\n");
        while (i--) {
              if( (query("id", list[i])) == "marrycard" )
                return notify_fail(
                "你已經和別人有婚約了吧?這裡不允許重婚的。\n");
        }

        if(!arg || !objectp(obj = present(arg, environment(me)))
                || !find_player(arg)|| !find_living(arg))
        return notify_fail("你想和誰締結良緣？\n");
        if( !environment()
        ||      base_name(environment()) != query("startroom") )
             return notify_fail(
                "真是抱歉，請您等一下到紅娘莊來找我吧。\n");

        if( !living(obj) )
                return notify_fail(obj->name() +
                "已經無法和你締結良緣了。\n");

        if( query("gender", obj) == query("gender", me) )
                return notify_fail("難道你不怕" + RED"AIDS"NOR + "嗎？\n");

        if(obj==me)     return notify_fail("你不能和自己締結婚約。\n");

        if( userp(obj) && !(query("marks/"+me->name(1, obj)))){
                message_vision(MAG "\n$N對著$n說道："
                    + RANK_D->query_self(me)
                    + me->name() + "，願意和"
               + RANK_D->query_respect(obj) +
                "結為夫婦\n\n"NOR, me,obj);
                 set("marks/"+obj->name(1), 1, me);
           tell_object(obj, MAG "如果你願意和對方結為夫婦，請你也對"
                        +me->name()+"("+query("id", me)+
                        ")"+ "下一次 marry 指令。\n" NOR);
                write(MAG
                        "現在你急切盼望著你的心上人說同意……\n" NOR);
                return 1;
        }


        marry_card1 = new("/obj/marry_card");
        set("name", "你和"+query("id", obj)+"的婚約", marry_card1);
        marry_card1->move(me);
        marry_card2 = new("/obj/marry_card");
        set("name", "你和"+query("id", me)+"的婚約", marry_card2);
        marry_card2->move(obj);

     message_vision(MAG "恭喜 $N 和 $n ，一對璧人終于喜結良緣。\n" NOR,obj,me);
        CHANNEL_D->do_channel(this_object(), "chat",
        sprintf( "%s 和 %s 現在開始是夫婦啦! \n",
        me->name(1), obj->name(1)));
        return 1;
}

int do_unmarry(string arg)
{
        object marry_card1,marry_card2,  me;
        object *list,ob, couple_ob;
        int i, have_marry;
        string target, tmpstr1, tmpstr2,str1,str2;
        string cardname;

        me = this_player();
        list = all_inventory(me);
        i = sizeof(list);
        have_marry = 0;
        while (i--) {
         if( (query("id", list[i])) == "marrycard"){
                        marry_card1 = list[i];
                        cardname=query("name", list[i]);
                        have_marry = 1;
                }
        }

        if (have_marry == 0)
                return notify_fail("你還未有婚約啊。\n");
        if( !environment()
        ||      base_name(environment()) != query("startroom") )
           return notify_fail("真是抱歉，請您等一下到紅娘莊來找我吧。\n");
        if (sscanf(cardname,"你和%s的婚約" ,target)!=1)
                return notify_fail("你沒有伴侶.\n");
         if(!objectp(couple_ob = present(target, environment(me)))
                || !find_player(target) )
                return notify_fail("你的伴侶現在不在場.\n");

        if( query("gender", couple_ob) != "女性"){
                tmpstr1 = "老婆"; tmpstr2 = "老公";
                str1 = "她"; str2 = "他";
        } else {
                tmpstr1 = "老公"; tmpstr2 = "老婆";
                str1 = "他"; str2 = "她";
        }

        list = all_inventory(couple_ob);
        i = sizeof(list);
        have_marry = 0;
        while (i--) {
              if( (query("id", list[i])) == "marrycard"){
                        marry_card2 = list[i];
                        have_marry = 1;
                }
        }
        if (have_marry = 0) {
                destruct(marry_card1);
        message_vision(MAG " $N 和 $n 從現在開始解除婚約,互不相幹!\n" NOR,
        couple_ob, me);
        CHANNEL_D->do_channel(this_object(), "chat",
        sprintf( "%s 和 %s 從現在開始解除婚約,互不相幹! \n",
        me->name(1), couple_ob->name(1)));

                return 1;
        }

        if( userp(couple_ob) && !(couple_ob->query("marks/"
                + "unmarry" +me->name(1))) ) {
                message_vision(MAG "\n$N對著$n說道："
                        + RANK_D->query_self(me)
                        + me->name() + "，咱們解除婚約吧!好嗎?\n\n"
                        NOR, me, couple_ob);
                 set("marks/"+"unmarry"+couple_ob->name(1), 1, me);
           tell_object(couple_ob, MAG "如果你願意解除婚約，請你也"
                + "下一次 unmarry 指令。\n" NOR);
                write(MAG
                "現在你只有等著" +str2 +" 同意啦...\n" NOR);
                return 1;
        }
        destruct(marry_card1);
        destruct(marry_card2);

        message_vision(MAG " $N 和 $n 從現在開始解除婚約,互不相幹!\n" NOR,
        couple_ob, me);
        CHANNEL_D->do_channel(this_object(), "chat",
        sprintf( "%s 和 %s 從現在開始解除婚約,互不相幹! \n",
        me->name(1), couple_ob->name(1)));

        return 1;
}
