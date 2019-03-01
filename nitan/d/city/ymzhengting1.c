#include <ansi.h>
inherit ROOM;
//void kf_same(object who,object me);

void create()
{
        set("short", "衙門正廳");
        set("long", @LONG
    堂上東西有兩根楹住，掛著一幅對聯，但是你無心細看。正
牆上懸掛一個橫匾，上書四個金光閃閃的大字。知府正坐在文案後批
閱文書，師爺隨侍在後。大堂正中高懸一匾：[1；31m               明   
 鏡    高    懸[2；37；0m
LONG );
        set("valid_startroom",1);
        set("no_steal", "1");
        set("no_magic", "1");
        set("no_fight", "1");
        set("exits", ([
           "east"  : "/d/city/dongting", 
                      "west"  : "/d/city/xiting", 
                      "north" : "/d/city/neizhai", 
                      "south" : "/d/city/yamen", 

        ]));
  

        set("objects", ([
                  "/d/city/npc/cheng" : 1, 
                  "/d/city/npc/shiye" : 1, 
        ]));
        setup();
}

void init ()
{
        add_action("do_work","work");
        add_action("do_finish","finish");
}

int do_work (string arg)
{
        object ob,ob1;
        int kf_npc,kf_whatnpc,worked_num;
        string kf_name,kf_name1,kf_where,titles;
        object me = this_player();
        if( query("kf_jiangli", me) )
                return notify_fail("程藥發說道：神捕大人還沒進京面聖啊？\n");

        if( !query("kaifengfu", me) )
                return notify_fail("兩旁衙役大聲喝道：大膽刁民，不得咆哮公堂！\n");
        if (!objectp(present("cheng yaofa", environment(me))))
                return notify_fail("風雲衙役笑道：程藥發已經退堂了，要想任務明日請早了您。\n");

        if( present("lingpai",me) || query("kf_working", me) )
                return notify_fail("程藥發臉色一沉道：本官前日交與你的差事速去辦理，不得捻輕怕重！\n");
        kf_npc = 1 + random(209);
        kf_whatnpc =1+random(8);
        set("kf_whatnpc", kf_whatnpc, me);
        ob = new("/d/city/obj/lingpai");        //50
        if(kf_whatnpc==1){ob1 = new("/d/city/npc/tufei1");}
        if(kf_whatnpc==2){ob1 = new("/d/city/npc/tufei2");}
        if(kf_whatnpc==3){ob1 = new("/d/city/npc/tufei3");}
        if(kf_whatnpc==4){ob1 = new("/d/city/npc/tufei4");}
        if(kf_whatnpc==5){ob1 = new("/d/city/npc/tufei5");}
        if(kf_whatnpc==6){ob1 = new("/d/city/npc/tufei6");}
        if(kf_whatnpc==7){ob1 = new("/d/city/npc/tufei7");}
        if(kf_whatnpc==8){ob1 = new("/d/city/npc/tufei8");}
        ob ->move(me);
        set_temp("kf_npc", kf_npc, me);
        if(kf_npc<210) kf_where = "武當附近";
        if(kf_npc<191) kf_where = "黃山附近";
        if(kf_npc<166) kf_where = "逍遙派附近";
        if(kf_npc<152) kf_where = "星宿派附近";
        if(kf_npc<141) kf_where = "泰山附近";
        if(kf_npc<125) kf_where = "雪山附近";
        if(kf_npc<107) kf_where = "揚州附近";
        if(kf_npc<84) kf_where = "北京城中";
        if(kf_whatnpc==1){ kf_name = "蒙面大盜"; kf_name1 = "攔路搶劫,殺人如麻";}
        if(kf_whatnpc==2){ kf_name = "無影神偷"; kf_name1 = "四處盜竊財物";}
        if(kf_whatnpc==3){ kf_name = "惡人裴風蕭"; kf_name1 = "經常劫掠民女，無惡不做";}
        if(kf_whatnpc==4){ kf_name = "魔教細作"; kf_name1 = "四處活動";}
        if(kf_whatnpc==5){ kf_name = "天宗姦細"; kf_name1 = "四處造謠破壞";}
        if(kf_whatnpc==6){ kf_name = "神秘人"; kf_name1 = "刺殺朝廷命官";}
        if(kf_whatnpc==7){ kf_name = "李元奎"; kf_name1 = "大家劫舍";}
        if(kf_whatnpc==8){ kf_name = "古毅"; kf_name1 = "傷人無數";}

        set_temp("kf_whatnpc", kf_whatnpc, me);
        set_temp("kf_name", kf_name, me);
        set_temp("kf_where", kf_where, me);
        message_vision("程藥發一拍驚堂木怒道：據查今有"+kf_name+"在"+kf_where+kf_name1+"，"+query("name", me)+"速去破案，不得有誤。\n",me);
        set("kf_working", 1, me);
        return 1;
}
int do_finish (string arg)
{
        object ob;
        int kf_npc,kf_whatnpc,kf_exp,kf_qn;
        string kf_name,kf_name1,kf_where,titles;
        object me = this_player();
        ob= present("ling pai",me);
        kf_name=query_temp("kf_name", me);
        kf_where=query_temp("kf_where", me);
        
        if( !query("kaifengfu", me) )
                return notify_fail("兩旁的風雲衙役大聲喝道：大膽刁民，不得咆哮公堂！\n");
        if (!objectp(present("cheng yaofa", environment(me))))
                return notify_fail("風雲衙役笑道：程大人已經退堂了，要想交令明日請早了您。\n");
        if( !query("kf_working", me) )
                return notify_fail("程藥發臉色一沉道：本官什麼時候派過你差事啊？\n");
        if( !query_temp("kf_finish", me) )
                return notify_fail("程藥發臉色一沉道：本府交你的差使至今還未辦妥，你還有面目來見我？\n");
        if (present("ling pai",me)){
                tell_object(me, "你恭恭敬敬的繳上令牌。\n" NOR );
        destruct(present("ling pai",me));
        }        
        message_vision(WHT"程藥發微微一笑道："+query("name", me)+WHT"在"+kf_where+WHT"破獲"+kf_name+WHT"一案，勞苦功高，趕快下去休息吧！\n"NOR,me);
        kf_exp = 2000+random(2000);
        kf_qn = 500+random(500);
        addn("combat_exp", kf_exp, me);
        addn("kf_worked", 1, me);
        addn("potential", kf_qn, me);
        addn("kf_worked", 1, me);
        set("kf_working", 0, me);
        delete_temp("kf_finish", me);
        tell_object(me, "你獲得了" + chinese_number(kf_exp)+ "點經驗。\n" NOR );
        tell_object(me, "你獲得了" + chinese_number(kf_qn)+ "點潛能。\n" NOR );
        if( query("kf_worked", me) == 4800){
                set("kainame", 10, me);
                addn("shen", 3000, me);
                message_vision(HIC "$N的正氣提高了！\n" NOR,me);
                tell_object(me,"你現在的正氣是"+chinese_number((query("shen", me)))+"。\n"NOR);
                message_vision(WHT"程藥發微笑著說道："+query("name", me)+"連破大案，天下聞名，本府已經奏明皇上。\n昨日朝旨已下，獎你黃金五千兩。你可以到錢莊領取。"NOR,me);
                 addn("balance", 10000000, me);
               set("kf_jiangli", 1, me);

      }
        if( query("kf_worked", me) == 3200){
                addn("shen", 3000, me);
                set("kainame", 9, me);
                message_vision(HIC "$N的正氣提高了！\n" NOR,me);
                tell_object(me,"你現在的正氣是"+chinese_number((query("shen", me)))+"。\n"NOR);
                message_vision(WHT"程藥發微笑著說道："+query("name", me)+"連破大案，天下聞名,繼續加油！！"NOR,me);
      }
        if( query("kf_worked", me) == 1600){
                set("kainame", 8, me);
                addn("shen", 1500, me);
                message_vision(HIC "$N的正氣提高了！\n" NOR,me);
                tell_object(me,"你現在的正氣是"+chinese_number((query("shen", me)))+"。\n"NOR);
      }
        if( query("kf_worked", me) == 800){
                set("kainame", 7, me);
                addn("shen", 1000, me);
                message_vision(HIC "$N的正氣提高了！\n" NOR,me);
                tell_object(me,"你現在的正氣是"+chinese_number((query("shen", me)))+"。\n"NOR);
        }
        if( query("kf_worked", me) == 400){
                set("kainame", 6, me);
                addn("shen", 800, me);
                message_vision(HIC "$N的正氣提高了！\n" NOR,me);
                tell_object(me,"你現在的正氣是"+chinese_number((query("shen", me)))+"。\n"NOR);
        }
        if( query("kf_worked", me) == 200){
                set("kainame", 5, me);
                addn("shen", 400, me);
                message_vision(HIC "$N的正氣提高了！\n" NOR,me);
                tell_object(me,"你現在的正氣是"+chinese_number((query("shen", me)))+"。\n"NOR);
        }
        if( query("kf_worked", me) == 100){
                set("kainame", 4, me);
                addn("shen", 200, me);
                message_vision(HIC "$N的正氣提高了！\n" NOR,me);
                tell_object(me,"你現在的正氣是"+chinese_number((query("shen", me)))+"。\n"NOR);
        }
        if( query("kf_worked", me) == 50){
                set("kainame", 3, me);
                addn("shen", 100, me);
                message_vision(HIC "$N的正氣提高了！\n" NOR,me);
                tell_object(me,"你現在的正氣是"+chinese_number((query("shen", me)))+"。\n"NOR);
        }
        if( query("kf_worked", me) == 20){
                set("kainame", 2, me);
        }
        me->save();
        return 1;
}
int valid_leave (object who, string dir)
{
        if(who->query_condition("kf_stop")<1){
                return ::valid_leave(who, dir);
        }
        else{
                message_vision ("$N爬起來就想往外跑。\n",who);
                return notify_fail(WHT"衙役死死把你按在地上喝道：老實點！\n"NOR);
                return 1;
}
}
