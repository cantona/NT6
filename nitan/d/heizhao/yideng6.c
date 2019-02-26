//Cracked by Kafei
// yideng6.c
// AceP

inherit ROOM;

int do_exert(string);
int do_pian(string);

void create()
{
        set("short", "巨石下");
        set("long", @LONG
你呆呆地使出全力頂起巨石，生怕一鬆手砸死了自己，農夫冷冷
地站在一旁袖手旁觀，一點相助的意思也沒有。
LONG );
        set("invalid_startroom", 1);
        set("no_fight", "1");
    setup();
}

void init()
{
        object me;
        int i,j,k;
        i=5; k=0;
        me=this_player();
        while(i<85 && k <= query("jingli", me)){
                j=10+random(40);
                k=k+j;
                call_out("dropjingli", i, me, j);
                i=i+5;
        }
        remove_call_out("moveout");
        call_out("moveout", 90, me);
        add_action("do_exert", "exert");
        add_action("do_exert", "yun");
        add_action("do_pian", "pian");
}

void dropjingli(object me, int losejl)
{
      if (!me || environment(me) != environment()) 
              return; 
        if (environment(me)==find_object("/d/heizhao/yideng6.c")) {
                message_vision("$N託得久了，只覺得兩臂發麻，眼前一陣金星亂冒！\n",me);
                      losejl = 10+random(40);
                set_temp("die_reason", "精力透支過度而死了", me);
                addn("jing", -losejl, me);
                return;
        }
}

void moveout(object me)
{
      if (!me || environment(me) != environment())  
              return;  
        if (environment(me)==find_object("/d/heizhao/yideng6.c")) {
                message_vision("$N眼前一陣發黑，終於堅持不住了，手一鬆，“轟隆”！ ... ...\n",me);
                me->unconcious();
                me->move("/d/heizhao/shanlu9.c");
                return;
        }
}

int do_exert(string arg)
{
        tell_object(this_player(), "你正託着大石頭呢，怎麼運氣？！\n");
        return 1;
}

int do_pian(string arg)
{
        object me;
        me=this_player();
        if (arg=="nong" || arg=="wu santong" || arg=="farmer" || arg=="wu") {
                message_vision("$N情急生智，大喊道：“大叔，我懷裏有一封洪老爺子給段皇爺的信！”\n",me);
                message_vision("“你來暫託一下，待我取出給你。”\n",me);
                message_vision("等到農夫托起大石，$N身形一縱，從他身邊掠過，衝向後山！\n\n",me);
                me->move("/d/heizhao/yideng7.c");
                return 1;
        }
        return 1;
}