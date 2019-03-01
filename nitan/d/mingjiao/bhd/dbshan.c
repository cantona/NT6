// dbshan.c 冰山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"冰山"NOR);
        set("long", @LONG
大冰山在日光的照射下發出刺眼的光芒，顯得十分奇麗，這裡到
處都是冰雪，冰山頗大，如陸地上之山丘，一眼望去，橫百余丈，縱
長幾十丈，冰山上滑不留步。海中不時有幾塊小浮基(fubing)正在向
北飄流。
LONG );
	set("outdoors", "極北");
        set("exits", ([  
              "east" : __DIR__"dbshan1",
        ]));
        set("item_desc", ([
                "fubing" : "旁邊的海水裡面漂浮著幾塊浮冰，但是相隔很遠，看來還沒法過去\n",
        ]));
        setup();
}

void init()
{
      remove_call_out("change");
      remove_call_out("change1");
      call_out("change", random(150) + 50); 
      add_action("do_jump", "jump");
}

void change()
{
      tell_room(this_object(),HIW"便在此時，只聽得丁冬、丁冬數聲，極是清脆動聽，幾塊浮冰飄近了。\n"NOR);    
      this_object()->set_temp("fubing", 1);    
      remove_call_out("change1");
      call_out("change1", 10);  
}

void change1()
{
      tell_room(this_object(),"海中潮流湧過，那清脆之聲又漸漸遠去了。\n");    
      this_object()->delete_temp("fubing");    
      remove_call_out("change");
      call_out("change", 50+random(150));  
}

int do_jump(string arg)
{
     object me = this_player();
     if(!query_temp("fubing")) return 0;
     if( ! arg || arg=="fubing" ) {
         message("vision",me->name() + "一縱身，整個人已到了浮冰上。\n",environment(me), ({me}) );
         me->move(__DIR__"foubing");
         message("vision",me->name() + "從冰山上飛身而來。\n",environment(me), ({me}) );
         if(random(me->query_dex()) < 50){
             message_vision("結果$N一不小心腳下一滑，仰天一個大摔跤！\n",me);
             me->set_temp("last_damage_from", "摔倒在冰山上，腦溢血而");
             me->receive_wound("qi", 50);
             me->receive_damage("qi", 100);
         }
         return 1;
     }
     return 0;
}       

void reset()
{
       change1();
       remove_call_out("change");
       remove_call_out("change1");
       call_out("change", random(150) + 50); 
        ::reset();
}
