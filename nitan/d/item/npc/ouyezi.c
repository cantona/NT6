// npc: /d/npc/m_weapon/npc/tianjianshi.c
// Last Modified by winder on Feb. 28 2001
// Modified by sir 4/13/2001

#include <ansi.h>
inherit NPC;

int do_weapon();
int do_give_weapon(object me);
object creat_weapon();

void create()
{
        set_name("歐冶子", ({ "ouye zi", "zi" }) );
        set("nickname", RED "赤心劍膽" NOR );
        set("gender", "男性" );
        set("age", 60);
        set("no_get", 1);
        set("long", "他頭上包着頭巾，三縷長髯飄灑胸前，面目清瘦但紅暈有光，\n"
                "二目炯炯有神，爍爍閃着竟似是凜凜的劍光，渾身似乎都包圍\n"
                "在一股劍氣之中。\n");
        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 30);
        set("shen_type", 0);
        set("max_neli",5000);
        set("jiali",50);

        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("claw",200);
        set_skill("jiuyin-baiguzhao",200);
        set_skill("force",150);
        set_skill("sword",150);
        set_skill("bibo-shengong",100);
        set_skill("luoying-shenjian",100);
        set_skill("parry",90);
        set_skill("anying-fuxiang",100);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage",50);

        set("combat_exp", 250000);
        set("score",0);
        
        map_skill("force","bibo-shengong");
        map_skill("parry","luoying-shenjian");
        map_skill("sword","luoying-shenjian");
        map_skill("claw","jiuyin-baiguzhao");
        map_skill("dodge","anying-fuxiang");
        
        set("attitude", "peaceful");
        
        set("inquiry", ([
                "鑄劍" : "鑄劍可是件十分艱苦的事，要消耗人的精氣和內力，你有決心和毅力嗎？\n",
                "原料" : "鑄劍可用千年玄鐵。。。你找到了我才能幫你鑄劍。\n",
                "兵器" : (: do_weapon() :),
        ]) );

        setup();
        set("chat_chance", 3);
        set("chat_msg", ({
                "歐冶子撫劍而歌：巨闕神兵兮，人鑄就。蓋世寶劍兮，配英雄！\n",
                "歐冶子低頭沉吟，似乎在思考什麼。\n"
                "歐冶子歎了一口氣：神兵配英雄，可英雄。。。。。。\n"
        }) );
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        ::init();
        add_action("do_answer","answer");
}

int accept_object(object who, object ob)
{        
        switch(query("name", ob) )
        {
                case "倭刀" :
                case "叫化雞" :
                case "羊皮書":
                case "軟劍":
                case "辟邪劍譜":
                        if( (query_temp("condition", who)) != query("name", ob) )
                        {
                                message_vision(HIC "歐冶子一愣：我對你説過我要這樣東西麼？\n" NOR, who);
                                return 0;
                        }
                        else
                        {
                                delete_temp("condition", who);
                                message_vision(HIG "歐冶子微笑着：很好很好！那我就幫你這一次吧！\n" NOR, who);
                                set_temp("condition_ok", 1, who);
                                destruct(ob);
                                do_give_weapon(who);
                                return 1;
                        }
        }
        if( (query("weapon/make", who)) )
        {
                say("歐冶子一臉茫然：您已經有一把自造的武器了，還來幹什麼？難到不合手麼？\n");
                return 0;
        }
        switch(query("id", ob) )
        {
                case "shen mu": 
                        set_temp("or", 1, who);
                        set_temp("get_orc", 1, who);
                        break;
                case "jin mu":
                        set_temp("or", 2, who);
                        set_temp("get_orc", 1, who);
                        break;
                case "han zhu": 
                        set_temp("or", 3, who);
                        set_temp("get_orc", 1, who);
                        break;
                case "iron stone": 
                        set_temp("or", 4, who);
                        set_temp("get_orc", 1, who);
                        break;
                default :
                        message("vision","這是什麼！這不能用來打造兵器！",who);
                        return 0;
        }
        message("vision","歐冶子低頭檢視了一下手中的"+query("name", ob)+"點了點頭説：\n",who);
        write("我這兒可以打造以下兵器：\n"+
                "     劍(sword)\n"+
                "     刀(blade)\n"+
                "     槍(spear)\n"+
                "     棍(club)\n"+
                "     棒(stick)\n"+
                "     杖(staff)\n"+
                "     錘(hammer)\n"+
                "     鈎(hook)\n"+
                "     斧(axe)\n"+
                "     鞭(whip)\n");                  
        say("這位"+RANK_D->query_respect(who)+"要造什麼兵器？決定了告訴我(answer)。\n");
        return 2;

}

int do_answer(string arg)
{
        object me,w_or;
        me = this_player();
        if( !(query_temp("get_orc", me)) )
        {
//                write("你找到原料了嗎？\n");
                return 0;
        }
        
        if(!arg)
        {
                write("你要造什麼兵器？\n");
                return 0;
        }

        message("vision",me->name()+"對歐冶子輕聲説了幾句。\n",environment(me), ({me}) );
        switch (arg)
        {
                case "sword" :
                        addn_temp("sword", 1, me);
                        write("帶着原料去找侍劍吧！\n");
                        message("vision","去吧！"+me->name()+"！\n",me);
                        break;
                case "blade" :
                        addn_temp("blade", 1, me);
                        write("帶着原料去找侍刀吧！\n");
                        message("vision","去吧！"+me->name()+"！\n",me);
                        break;
                case "spear" :
                        addn_temp("spear", 1, me);
                        write("帶着原料去找侍槍吧！\n");
                        message("vision","去吧！"+me->name()+"！\n",me);
                        break;
                case "club" :
                        addn_temp("club", 1, me);
                        write("帶着原料去找侍棍吧！\n");
                        message("vision","去吧！"+me->name()+"！\n",me);
                        break;
                case "stick" :
                        addn_temp("stick", 1, me);
                        write("帶着原料去找侍棒吧！\n");
                        message("vision","去吧！"+me->name()+"！\n",me);
                        break;
                case "staff" :
                        addn_temp("staff", 1, me);
                        write("帶着原料去找侍杖吧！\n");
                        message("vision","去吧！"+me->name()+"！\n",me);
                        break;
                case "axe" :
                        addn_temp("axe", 1, me);
                        write("帶着原料去找侍斧吧！\n");
                        message("vision","去吧！"+me->name()+"！\n",me);
                        break;
                case "hammer" :
                        addn_temp("hammer", 1, me);
                        write("帶着原料去找侍錘吧！\n");
                        message("vision","去吧！"+me->name()+"！\n",me);
                        break;
                case "hook" :
                        addn_temp("hook", 1, me);
                        write("帶着原料去找侍鈎吧！\n");
                        message("vision","去吧！"+me->name()+"！\n",me);
                        break;
                case "whip" :
                        addn_temp("whip", 1, me);
                        write("帶着原料去找侍鞭吧！\n");
                        message("vision","去吧！"+me->name()+"！\n",me);
                        break;
                default :
                        message_vision(HIC"歐冶子一臉狐疑：什麼兵器？\n"NOR,me);
                        return notify_fail("歐冶子仔細的説：此事不可兒戲，請慎重！！\n");
        }
        switch(query_temp("or", me) )
        {
                case 1:
//                        w_or = new("/d/npc/m_weapon/tan/item/shenmu",1);
//                        w_or->move(me);                        
//                        message_vision(HIC"歐冶子給了$N一塊千年神木。\n"NOR,me);
                command("giveshenmuto"+query("id", me));
                        break;
                case 2:
//                        w_or = new("/d/npc/m_weapon/tan/item/jinmu",1);
//                        w_or->move(me);
//                        message_vision(HIC"歐冶子給了$N一塊海底金母。\n"NOR,me);
                command("givejinmuto"+query("id", me));
                        break;
                case 3:
//                        w_or = new("/d/npc/m_weapon/tan/item/hanzhu",1);
//                        w_or->move(me);
//                        message_vision(HIC"歐冶子給了$N一塊寒絲羽竹。\n"NOR,me);
                command("givehanzhuto"+query("id", me));
                        break;
                case 4:
//                        w_or = new("/d/qilian/obj/ironstone",1);
//                        w_or->move(me);
//                        message_vision(HIC"歐冶子給了$N一塊隕星鐵石。\n"NOR,me);
                command("giveironstoneto"+query("id", me));
                        break;
        }

        delete_temp("get_orc", me);
        return 1;
}

int do_weapon()
{
        object me,obj;
//object weapon;        
        string w_id;
        me = this_player();
        w_id=query("weapon/id", me);
        if( !(query("weapon/make", me)) )
                return notify_fail("你造過兵器嗎？\n");

        if( objectp(obj = present(w_id, me)) )
        {
                say("歐冶子臉色一沉：您的武器不就在你手邊麼？還來幹什麼！\n");
                return 1;
        }
        if( query_temp("condition", me) )
        {
                say("歐冶子臉色一沉：不是讓你去拿"+(query_temp("condition", me))+
"了麼？還沒拿到回來幹嘛！\n");
                return 1;
        }

        if( !(query_temp("condition_ok", me)) )
        {
                message_vision(HIY"這位"+RANK_D->query_respect(me)+"想要重新得到兵器？這不難。不過......\n" NOR, me);
                message_vision(HIY"歐冶子沉吟了一下説：你得找到我要的東西。\n" NOR, me);
                switch( random(5) )
                {
                        case 0:
                                message_vision("拿到倭刀，再來吧！\n",me);
                                set_temp("condition", "倭刀", me);
                                break;
                        case 1:
                                message_vision("給我叫化雞，我就幫你！！\n",me);
                                set_temp("condition", "叫化雞", me);
                                break;
                        case 2:
                                message_vision("嗯..你就拿羊皮書來換吧！\n",me);
                                set_temp("condition", "羊皮書", me);
                                break;
                        case 3:
                                message_vision("..我想看看軟劍！\n",me);
                                set_temp("condition", "軟劍", me);
                                break;
                        case 4:
                                message_vision("如果你能替我找到辟邪劍譜的話......\n",me);
                                set_temp("condition", "辟邪劍譜", me);
                                break;
                }
        }
        return 1;
}
int do_give_weapon(object me)
{
                object weapon;
                object *obs;
                int i;
                object env;
                string env_name;
    string area;
    

                
                delete_temp("condition_ok", me);
                obs = children("/d/npc/m_weapon/weapon/m_weapon");
                for (i=0;i<sizeof(obs);i++)
                {
                        if( query("owner", obs[i]) == query("id", me) )
                        {
                                if (!environment(obs[i])) continue;
                                env = environment(obs[i]);
        sscanf(base_name(env),"/%*s/%s/%*s",area);
        area=to_chinese(area);
                                if (env->is_character())
                                  env_name=query("name", env)+"手中";
                                else
                                  env_name=query("short", env);
                          if (!userp(env))
                            env_name = area +"的" + env_name;
                          message_vision("$N説道：你的"+query("name", obs[i])+
                          "在"+ env_name+"，快去找吧。\n",this_object());
                          return 1;
                        }
                }
                
                weapon = creat_weapon();
                weapon->move(me);
                return 1;
}

object creat_weapon()
{
        object me,weapon;
        string mask;        //the verible that record the type of weapon
        me = this_player();
        mask=query("weapon/type", me);
        weapon = new("/d/npc/m_weapon/weapon/m_weapon",1);
        return weapon;
/*
        switch(mask)
        {
                case "劍":
                        weapon = new("/d/npc/m_weapon/weapon/m_sword",1);
                        return weapon;
                case "刀":
                        weapon = new("/d/npc/m_weapon/weapon/m_blade",1);
                        return weapon;
                case "槍":
                        weapon = new("/d/npc/m_weapon/weapon/m_spear",1);
                        return weapon;
                case "棍":
                        weapon = new("/d/npc/m_weapon/weapon/m_club",1);
                        return weapon;
                case "棒":
                        weapon = new("/d/npc/m_weapon/weapon/m_stick",1);
                        return weapon;
                case "杖":
                        weapon = new("/d/npc/m_weapon/weapon/m_staff",1);
                        return weapon;
                case "錘":
                        weapon = new("/d/npc/m_weapon/weapon/m_hammer",1);
                        return weapon;
                case "鈎":
                        weapon = new("/d/npc/m_weapon/weapon/m_hook",1);
                        return weapon;
                case "鞭":
                        weapon = new("/d/npc/m_weapon/weapon/m_whip",1);
                        return weapon;
                case "斧":
                        weapon = new("/d/npc/m_weapon/weapon/m_axe",1);
                        return weapon;
        }
*/
}