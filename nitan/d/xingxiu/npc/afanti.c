// npc: /d/xingxiu/npc/afanti.c
// Jay 3/26/96

inherit NPC;

//string ask_me();

void create()
{
        set_name("阿凡提", ({ "afanti" }) );
        set("gender", "男性" );
        set("age", 48);
        set("long", 
            "他頭上包着頭巾，長着向上翹的八字鬍，最喜歡捉弄巴依、幫助窮人。他常"
            "給別人出謎語。\n");
        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 15);
        set("shen_type", 1);

        set_skill("unarmed", 30);
        set_skill("dodge", 25);
        set_temp("apply/attack", 25);
        set_temp("apply/defense", 25);
        set("combat_exp", 2500);

        set("attitude", "peaceful");
        set("inquiry", ([
            "name" : "我就是納蘇爾的阿凡提。",
            "here" : "這裏可真是個好地方。",
            "納蘇爾" : "是我出生的地方。",
            "謎語" : "你幫我找到小毛驢，我就給你出謎語。",
            "巴依" : "他把我關在這裏，有吃有喝，我就不走了。巴依是個壞蛋，願胡大懲罰他。",
            "毛驢" : "我的小毛驢在我到沙漠裏騙巴依種金子時走丟了。",
            "驢" : "我的小毛驢在我到沙漠裏騙巴依種金子時走丟了。",
            "小毛驢" : "我的小毛驢在我到沙漠裏騙巴依種金子時走丟了。",
            "捲簾格" : "捲簾格指謎底各字順序顛倒過來和謎面相扣。",
            "胡大" : "就是真主。又名安拉或阿拉。",
            "真主" : "真主至大，萬物非主，唯有真主。穆罕默德是真主的使者。",
       ]) );

        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
             "阿凡提歎了口氣：嗨，可惜我的驢。\n",
        }) );
        carry_object(__DIR__"obj/wcloth")->wear();
        carry_object(__DIR__"obj/dongbula");
}

void init()
{
        ::init();
        add_action("do_answer","answer");
}

int accept_object(object who, object ob)
{
//     if((string)ob->query("name")=="小毛驢") {
     if( query("id", ob) == "maolv"){
           remove_call_out("destroying");
           call_out("destroying", 1, this_object(), ob);

           if( query_temp("marks/謎", who)){
                 write("阿凡提笑了笑，説：你先把上個謎猜出來再説。\n");
//               destruct(ob);
                 return 1;
           }
           else {
                 write("阿凡提笑得嘴都合不上了，説：多謝這位" + 
                       RANK_D->query_respect(who) +
                       "的幫助，咱們猜個謎語吧：\n");
                 switch(random(20)) {
                   case 0:
                       write("婦女讀物。(打一本泥潭玩家名)\n");
                       set_temp("marks/謎", 1, who);
                       break;
                   case 1:
                       write("雪在燒，雪在燒。(打一本泥潭玩家名)\n");
                       set_temp("marks/謎", 2, who);
                       break;
                   case 2:
                       write("鄧小平之後。(打一本泥潭NPC名)\n");
                       set_temp("marks/謎", 3, who);
                       break;
                   case 3:
                       write("御用經典。(打一本泥潭玩家名)\n");
                       set_temp("marks/謎", 4, who);
                       break;
                   case 4:
                       write("打穀場上的NPC。(打一本泥潭玩家名)\n");
                       set_temp("marks/謎", 5, who);
                       break;
                   case 5:
                       write("巴黎習語。(打一本泥潭技能名，捲簾格)\n");
                       set_temp("marks/謎", 6, who);
                       break;
                   case 6:
                       write("拱豬入門。(打一字)\n");
                    // this riddle made by 老哈（美國　明尼蘇達大學）
                       set_temp("marks/謎", 7, who);
                       break;
                   case 7:
                       write("拱豬王悶悶不樂。(打一字)\n");
                    // this riddle modified from one made by 綠田　（美國　密執安州）
                       set_temp("marks/謎", 8, who);
                       break;
                   case 8:
                       write("錦帆才渡兒郎去。(打一本泥潭巫師網名)\n");
                    // this riddle made by 嶽涵　（美國　密執安州）
                       set_temp("marks/謎", 9, who);
                       break;
                   case 9:
                       write("德意日戰敗。(打一本泥潭NPC名)\n");
                    // this riddle modified from one made by 牛　（美國）
                       set_temp("marks/謎", 10, who);
                       break;
                   case 10:
                       write("整年當兵。(打一本泥潭NPC名)\n");
                    // this riddle made by 四月　（美國）
                       set_temp("marks/謎", 11, who);
                       break;
                   case 11:
                       write("歐陽鋒練功。(打一成語)\n");
                    // this riddle made by 魔　（美國）
                       set_temp("marks/謎", 12, who);
                       break;
                   case 12:
                       write("胡踢亂踹。(打一本泥潭NPC名)\n");
                    // this riddle made by 居士　（美國）
                       set_temp("marks/謎", 13, who);
                       break;
                   case 13:
                       write("麥克傑克遜。(打二本泥潭NPC名)----回答時二名一起回答，中間不加任何標點。\n");
                       set_temp("marks/謎", 14, who);
                       break;
                   case 14:
                       write("召。(打二本泥潭NPC名)----回答時二名一起回答，中間不加任何標點。\n");
                    // this riddle made by 老哈　（美國）
                       set_temp("marks/謎", 15, who);
                       break;
                   case 15:
                       write("聖旨。(打一本泥潭玩家名)\n");
                       set_temp("marks/謎", 16, who);
                       break;
                   case 16:
                       write("緣何一夕夢未成。(打一本泥潭門派名)\n");
                    // this riddle made by 老哈　（美國） hanxx002@maroon.tc.umn.edu
                       set_temp("marks/謎", 17, who);
                       break;
                   case 17:
                       write("唐樂。(打一本泥潭NPC名)\n");
                    // this riddle made by ★魔　（美國） ning@phish.ecii.org
                       set_temp("marks/謎", 18, who);
                       break;
                   case 18:
                       write("一樣的不止一點兩點。(打一本泥潭地名及一技能名)\n");
                       set_temp("marks/謎", 19, who);
                       break;
                   case 19:
                       write("回扣。(打一本泥潭NPC名)\n");
                       set_temp("marks/謎", 20, who);
                       break;

                  }
                  write("想好了回答 (answer) 我。記住，不可泄露謎語或謎底。\n");
                  message("vision", "阿凡提對着"+who->name()+"嘀咕了幾句話。\n",
                          environment(who), ({who}) );
                  remove_call_out("destroying");
                  call_out("destroying", 1, this_object(), ob);
                  return 1;
            }
      }
}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}
int do_answer(string arg)
{
        object me,gold;
        int soln,riddle;
        me = this_player();
        riddle=query_temp("marks/謎", this_player());

        if (!riddle) {
           write("我又不是你師傅，你用不着回答我。\n");
           return 1;
        }

        if( !arg || arg=="" ) {
           write("想好謎底再回答。\n");
           return 1;
        }
        message("vision", me->name() + "把嘴湊到阿凡提的耳邊嘀嘀咕咕。\n",
                 environment(me), ({me}) );

        switch (arg) {
          case "姍": soln=1; break;
          case "靈靈" : soln=2; break;
          case "江百勝" : soln=3; break;
          case "玫" : soln=4; break;
          case "二娃" : soln=5; break;
          case "道學心法" : soln=6; break;
          case "閡" : soln=7; break;
          case "氦" : soln=8; break;
          case "方舟子" : soln=9; break;
          case "歐陽克" : soln=10; break;
          case "丁春秋" : soln=11; break;
          case "倒行逆施" : soln=12; break;
          case "魯有腳" : soln=13; break;
          case "黑無常白無常":
          case "白無常黑無常": soln=14; break;
          case "歐陽鋒歐陽克": soln=15; break;
          case "龍雲": soln=16; break;
          case "少林": soln=17; break;
          case "李莫愁" : soln=18; break;
          case "逍遙洞逍遙遊" : soln=19; break;
          case "買賣提" : soln=20; break;
          default :
              say("阿凡提大笑起來，説道：你説什麼呀，牛頭不對馬嘴。\n"
                  + me->name() + "的臉被臊得通紅。\n");
              return 1;
        }
        if( query("combat_exp", me)>10 )
        {
              say("阿凡提大笑起來，説道：你還來騙經驗呀。\n" + me->name() + "的臉被臊得通紅。\n");
              return 1;
        }
        if (riddle==soln) {
//          gold = new("clone/money/gold");
//          gold->move(this_player());
//          say("阿凡提給了" + me->name() + "一兩黃金。\n");
          set_temp("marks/謎", 0, this_player());
          say ("阿凡提對" + me->name() + "豎起大姆指：居然讓你猜着了。黃金是巴依的不義之財，你拿去分給窮人吧。\n");
          set("combat_exp",query("combat_exp",  this_player())+80, this_player());
          write ("你的經驗增加了！\n");

        }
        else
          write ("誰把謎底告訴你的? 不對!!\n");
        return 1;
} 
 

   