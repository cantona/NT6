#include <ansi.h>

inherit NPC;
inherit F_DEALER;

mixed ask_xiongba();

void create()
{
        set_name("王方平", ({ "wang fangping", "wang", "fangping" }));
        set("nickname", WHT "鬼王" NOR);
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 475);
        set("long", "王方平本是山中道士，後在豐都山修煉成仙，御封「鬼王」。\n");

        set_skill("unarmed", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("magic", 500);
        set_temp("apply/damage", 2000);
        set_temp("apply/parry", 2000);
        set_temp("apply/dodge", 2000);
        set_temp("apply/attack", 2000);
        set_temp("apply/force", 2000);

        set("combat_exp", 20000000);
        set("attitude", "friendly");
        /*
        set("vendor_goods", ({
                "/d/death/obj/weapon1",
                "/d/death/obj/weapon2",
                "/d/death/obj/weapon3",
                "/d/death/obj/weapon4",
                "/d/death/obj/weapon5",
                "/d/death/obj/weapon6",
                "/d/death/obj/weapon7",
                "/d/death/obj/weapon8",
                "/d/death/obj/weapon9",
                "/d/death/obj/weapon10",
                "/d/death/obj/weapon11",
                "/d/death/obj/weapon12",
                "/d/death/obj/weapon13",
                "/d/death/obj/weapon14",
                "/d/death/obj/weapon15",
                "/d/death/obj/weapon16",
                "/d/death/obj/weapon17",
                "/d/death/obj/weapon18",
                "/d/death/obj/weapon19",
                "/d/death/obj/weapon20",
                "/d/death/obj/weapon21",
                "/d/death/obj/weapon22",
                "/d/death/obj/weapon23",
                "/d/death/obj/weapon24",
                "/d/death/obj/weapon25",
                "/d/death/obj/weapon26",
                "/d/death/obj/weapon27",
                "/d/death/obj/weapon28",

                "/d/death/obj/weapon29",
                "/d/death/obj/weapon30",
                "/d/death/obj/weapon31",
                "/d/death/obj/weapon32",
                "/d/death/obj/weapon33",
                "/d/death/obj/weapon34",
                "/d/death/obj/weapon35",
                "/d/death/obj/weapon36",
                "/d/death/obj/weapon37",
                "/d/death/obj/weapon38",
                "/d/death/obj/weapon39",
                "/d/death/obj/weapon40",
                "/d/death/obj/weapon41",
                "/d/death/obj/weapon42",
                "/d/death/obj/weapon43",
                "/d/death/obj/weapon44",
                "/d/death/obj/weapon45",
                "/d/death/obj/weapon46",
                "/d/death/obj/weapon47",
                "/d/death/obj/weapon48",
                "/d/death/obj/weapon49",
                "/d/death/obj/weapon50",
                "/d/death/obj/weapon51",
                "/d/death/obj/weapon52",
                "/d/death/obj/weapon53",
                "/d/death/obj/weapon54",
                "/d/death/obj/weapon55",
                "/d/death/obj/weapon56",
                "/d/death/obj/weapon57",
                "/d/death/obj/weapon58",
                "/d/death/obj/weapon59",
                "/d/death/obj/weapon60",
                "/d/death/obj/weapon61",
                "/d/death/obj/weapon62",
                "/d/death/obj/weapon63",
                "/d/death/obj/weapon64",
                "/d/death/obj/weapon65",
                "/d/death/obj/weapon66",
                "/d/death/obj/weapon67",
                "/d/death/obj/weapon68",
                "/d/death/obj/weapon69",
                "/d/death/obj/weapon70",
                "/d/death/obj/weapon71",
                "/d/death/obj/weapon72",
                "/d/death/obj/weapon73",
                "/d/death/obj/weapon74",
                "/d/death/obj/weapon75",
                "/d/death/obj/weapon76",
                "/d/death/obj/weapon77",
                "/d/death/obj/weapon78",
                "/d/death/obj/weapon79",
                "/d/death/obj/weapon80",
        }));
        */
        set("inquiry", ([
                "鎖陽丹" : "鎖陽丹乃地獄神品，只有牛頭王懂得製作，不過沒有本王的允許他也不敢擅自制作鎖陽丹。\n",
                "允許"   : "本王生前有一遺憾，愧對了自己的女兒，使之飽受輪迴之苦，天下只有聖物\n" + 
                           "錦鑭袈裟方可助她脱離苦海，重新投胎做人，如果閣下能幫助本王找到錦鑭袈裟，本王到\n" +
                           "是可以破例一次，讓牛頭王幫你製作鎖陽丹。\n",
                "錦鑭袈裟" : "此乃袈裟中的上品，穿戴者可不墜地獄，不入輪迴！\n"
                             "不過，聽説世間上也只有莫邪能製作出錦鑭袈裟。\n",  
                "雄霸天下" : (: ask_xiongba :),
                "霸刀"     : "霸刀乃當世絕學，練成之人當可雄霸天下，不過此間仍無人練成...\n",
        ]));

        setup();
        carry_object(__DIR__"obj/cloth4")->wear();
}
/*
void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
*/


mixed ask_xiongba()
{
        object me;
        
        me = this_player();
        
        if (! objectp(me))return;
        
        if( !query("can_perform/badao/can_xiong", me) )
        {
                tell_object(me, HIG "王方平告訴你：我雖已得到錦鑭袈裟讓我亡女免受輪迴之苦，但仍配合‘神聖血清’\n"
                                    "的力量方能成事，如果閣下能幫我找到神聖血清，我便傳授你雄霸天下和阿鼻道第\n"
                                    "一招的絕招。\n" NOR);
                return "如何？";                 
        }
        
        if( query("can_perform/badao/xiong", me) )
                return "這絕招看來你已經會了，我沒什麼好幫你的了。\n";
                
        if (me->query_skill("badao", 1) < 700)
                return "看來你霸刀火候還不夠，給你講了也是白講。\n";
                
        message_vision(HIY "$N" HIY "説道：既然如此，這雄霸天下的絕招就傳你了，你可看好了，我只施展一次 ....\n", 
                       this_object());
                       
        tell_object(me, HIG "恭喜你，領悟了「雄霸天下」！\n" NOR);
        tell_object(me, HIG "恭喜你，領悟了阿鼻道第一刀！\n" NOR);
        
        tell_object(me, HIM "王方平悄悄對你説道：據説，只要你霸刀達到800級，這阿鼻道第二刀可找陰長生學習。\n" NOR);
        tell_object(me, HIM "王方平又對你説道：可是陰長生不會白教你，需要找到天下第一神酒--天乙神酒與他交換。\n" NOR);

        set("can_perform/badao/xiong", 1, me);
        set("can_perform/badao/san-1", 1, me);
        me->save();
        
        return "你我從此互不相欠，各走各路吧！\n";
}

int accept_object(object me, object obj)
{                       
        // 神聖血清
        if( query("id", obj) == "god blood" && 
            base_name(obj) == "/clone/fam/etc/prize5")
        {               
                if( query("can_perform/badao/can_xiong", me) )
                {
                        command("bow"+query("id", me));
                        command("say 多謝閣下仗義相助，了卻本王的心願。");
                        return 0;
                }
                command("nod"+query("id", me));
                command("say 既然你能幫我找到神聖血清，我也會履行我的諾言。");
                command("ke");
                command("say 我得趕去超度我亡女了，多謝！");
                tell_object(me, HIY "一陣聲音從遠處飄來：這雄霸天下和阿鼻道第刀的絕招你隨時可以來找\n"
                                    "我學(ask wang about 雄霸天下)。\n" NOR);

                set("can_perform/badao/can_xiong", 1, me);
                me->save();
                destruct(obj);
                destruct(this_object());
                return 1;
        }
        if( query("badao_quest/suoyangdan_allow", me) )
        {
                command("bow"+query("id", me));
                command("say 多謝閣下仗義相助，了卻本王的心願。");
                return 0;
        }

        if( query("id", obj) == "jinlan jiasha" && 
            base_name(obj) == "/clone/armor/jinlan-jiasha")
        {
                command("yi"+query("id", me));
                command("say 這.. 這.. 不是錦鑭袈裟嗎，閣下居然能找到 ...");
                command("tan");
                command("say 既然如此，本王心願已了，你去找牛頭王幫你製作鎖陽丹吧。");
                
                set("badao_quest/suoyangdan_allow", 1, me);
                me->save();
                destruct(obj);
                return 1;
        }
        else
                return 0;
        
        
                   
}
